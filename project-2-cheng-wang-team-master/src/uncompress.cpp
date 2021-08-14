#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitInputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void uncompressAscii(const string & infile, const string & outfile) {
    // TODO (checkpoint)
    //cerr << "TODO: uncompress '" << infile << "' -> '"
      //  << outfile << "' here (ASCII)" << endl;
    ifstream in;
    ofstream out;
    in.open(infile);
    out.open(outfile);
    vector<int> freqs(256,0);
    int next;
    for ( int i = 0; i < 256; i++ ){
	in>>next;
	freqs[i] = next;
    }
    HCTree tree;
    tree.build(freqs);
    int count = 0;
    int index = 0;
    for ( int i = 0; i < 256; i++ ){
	if( freqs[i] != 0 ){
		count++;
                index = i;
	}
    }
    if ( count == 1 ){
	char a = (char) index;
	for ( int d = 0; d < freqs[index]; d++ ){
		out<< a;
	}
	return;
    }
    if ( count == 0 ){
	return;
    }
    for( int i = 0; i < 256; i++ ){
	if( freqs[i] != 0){
		for( int d = 0; d < freqs[i]; d++){
			out<< tree.decode( in );
		}
	}
    }
    out.close();
    in.close();
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * Uses bitwise I/O.
 */
void uncompressBitwise(const string & infile, const string & outfile) {
    // TODO (final)
    //cerr << "TODO: uncompress '" << infile << "' -> '"
      //  << outfile << "' here (bitwise)" << endl;
    ifstream in;
    ofstream out;
    in.open(infile);
    out.open(outfile);
    //istream i( in );
    //ostream o( out );

    vector<int> freqs(256,0);
    int int1;
    int int2;
    int int3;
    int int4;
    for ( int i = 0; i < 256; i++ ){
        int1 = in.get();
	int2 = in.get();
    	int3 = in.get();
	int4 = in.get();
	freqs[i] = (int1 << 24) + (int2 << 16) + (int3 << 8) + (int4 << 0);
    }
    HCTree tree;
    tree.build(freqs);
    int count = 0;
    int index = 0;
    for ( int i = 0; i < 256; i++ ){
        if( freqs[i] != 0 ){
                count++;
                index = i;
        }
    }
    if ( count == 1 ){
        char a = (char) index;
	//cout<< "this is the answer " << a << '\n';
	//cout<< "this is the answer " << index << '\n';

        for ( int d = 0; d < freqs[index]; d++ ){
		out.put( a );
        }
        return;
    }
    if ( count == 0 ){
        return;
    }
    //cout << "this is the first char after header: "<< in.get() <<'\n';
    BitOutputStream bitOut( out );
    BitInputStream bitIn( in );
    for( int i = 0; i < 256; i++ ){
        if( freqs[i] != 0){
                for( int d = 0; d < freqs[i]; d++){
                        out.put( tree.decode( bitIn ));
                }
        }
    }
    
    out.close();
    in.close();
}

int main(int argc, char ** argv) {
    string infile = "";
    string outfile = "";
    bool bitwise = false;
    for (int i = 1; i < argc; i++) {
        string currentArg = argv[i];
        if (currentArg == "-b") {
            bitwise = true;
        } else if (infile == "") {
            infile = currentArg;
        } else {
            outfile = currentArg;
        }
    }

    if (infile == "" || outfile == "") {
        cout << "ERROR: Must provide input and output files" << endl;
        print_usage(argv);
        return 1;
    }

    if (bitwise) {
        uncompressBitwise(infile, outfile);
    } else {
        uncompressAscii(infile, outfile);
    }

    return 0;
}
