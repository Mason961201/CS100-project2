#include <stack>
#include <queue>

#include "HCTree.hpp"

/**
 * Destructor for HCTree
 */
HCTree::~HCTree() {
    // TODO (checkpoint)
    deleteAll(root);
}
void HCTree::deleteAll(HCNode * n) {
        if( n == nullptr ){
                return;
        }else{
                deleteAll( n->c0 );
                deleteAll( n->c1 );
                delete n;
        }
}

/** Use the Huffman algorithm to build a Huffman coding tree.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the tree,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs) {
    // TODO (checkpoint)
    if ( this->root != nullptr ){
	deleteAll(this->root);
	
    }
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> node_queue;
    for( int i = 0; i < 256; i++ ){
	if ( freqs[i] != 0 ){
		HCNode * node = new HCNode( freqs[i], i);
		leaves[node->symbol] = node;
		node_queue.push(node);
	}
    }
    while ( node_queue.size() > 1 ){
	HCNode * n1 = node_queue.top();
	node_queue.pop();
	HCNode * n2 = node_queue.top();
	node_queue.pop();
	HCNode * parent;
	if ( n1->symbol < n2->symbol ){
		parent = new HCNode( n1->count + n2->count,n2->symbol);
	} 
	else {
		parent = new HCNode( n1->count + n2->count,n1->symbol);
	}
	parent->c0 = n1;
	parent->c1 = n2;
	n1->p = parent;
	n2->p = parent;
        node_queue.push(parent);

    }
    if ( node_queue.size() < 1 ){
	root = nullptr;
    }
    else{
    	root = node_queue.top();
    }
}

/** Write to the given ostream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, ostream& out) const {
    // TODO (checkpoint)
    //cout << "this is the symbol "<<symbol<<" "<<(unsigned int) symbol <<'\n';
    HCNode * node = leaves[(unsigned int) symbol];
    string code = "";
    while( node->p != nullptr ){
	if( node->p->c0 == node ){
		code.insert(0,1,'0');
	}
	else if( node->p->c1 == node ){
		code.insert(0,1,'1');
	}
	node = node->p;
    }
    //cout<<"this is the answer"<<code<<endl;
    out<<code;
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the istream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(istream& in) const {
    char a;
    HCNode * node = root;
    int count = 0;
    while( in.get(a) ){
	//cout<<a<<"    this is the count:"<< count <<endl;
	if( a == '1' ){
		node = node->c1;
	}
	else if ( a == '0' ){
		node = node->c0;
	}
	if( node ->c1 == nullptr || node->c0 == nullptr){
                break;
        }

	count++;
    }
    return node->symbol;  // TODO (checkpoint)
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    // TODO (final)
    HCNode * node = leaves[ symbol];
    string code = "";
    while( node->p != nullptr ){
        if( node->p->c0 == node ){
        	code.insert(0,1,'0');
	}
        else if( node->p->c1 == node ){
		code.insert(0,1,'1');
	}
        node = node->p;
    }
    for ( unsigned int i = 0; i < code.length(); i++ ){
	if( code[i] == '0' ){
		out.writeBit(0);
		//cout <<"The bit I write: 0"<<'\n';
	}
	if( code[i] == '1' ){
		out.writeBit(1);
		//cout <<"The bit I write: 1" <<'\n';
	}
    }
    //out.flush();
    
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(BitInputStream& in) const {
    //return 0;  // TODO (final)
    HCNode * node = root;
    int count = 0;
    while( 1 ){
	bool answer = in.readBit();
	//cout << "The bit I read: "<< answer <<'\n';
	if( answer == true ){
                node = node->c1;
        }
        else if ( answer ==false ){
                node = node->c0;
        }
        if( node ->c1 == nullptr && node->c0 == nullptr){
                break;
        }

        count++;
    }
    return node->symbol;
}

/**
 * Print the contents of a tree
 */
void HCTree::printTree() const {
    cout << "=== PRINT TREE BEGIN ===" << endl;
    printTreeHelper(root);
    cout << "=== PRINT TREE END =====" << endl;
}

/**
 * Recursive helper function for printTree
 */
void HCTree::printTreeHelper(HCNode * node, string indent) const {
    if (node == nullptr) {
        cout << indent << "nullptr" << endl;
        return;
    }

    cout << indent << *node << endl;
    if (node->c0 != nullptr || node->c1 != nullptr) {
        printTreeHelper(node->c0, indent + "  ");
        printTreeHelper(node->c1, indent + "  ");
    }
}
