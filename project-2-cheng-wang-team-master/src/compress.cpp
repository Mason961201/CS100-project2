#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitOutputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void compressAscii(const string & infile, const string & outfile) {
    // TODO (checkpoint)
    ifstream in;
    ofstream out;
    in.open(infile, ios::binary);
    out.open(outfile);
    vector<int> freqs(256,0);
    int i = in.get();
    while ( i != EOF ){
	freqs[i] = freqs[i]+1;
	i = in.get();
    } 
    HCTree tree;
    tree.build(freqs);
    for( int d = 0; d < 256; d++ ){
	out<<freqs[d]<<'\n';
    }
    int count = 0;
    for( int d = 0; d < 256; d++ ){
	if( freqs[d] != 0 ){
		count++;
	}
    }
    if( count == 1 || count == 0 ){
	return;
    }
    in.clear();
    in.seekg(0,ios::beg);
    char next;
    if ( in.eof()==false ){
	next = in.get();
    }
    while( next != EOF ){
	tree.encode( next, out);
	next = in.get();
    }
    in.close();
    out.close();
    //cerr << "TODO: compress '" << infile << "' -> '"
    //    << outfile << "' here (ASCII)" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * Uses bitwise I/O.
 */
void compressBitwise(const string & infile, const string & outfile) {
    // TODO (final)
    //cerr << "TODO: compress '" << infile << "' -> '"
      //  << outfile << "' here (bitwise)" << endl;
    ifstream in;
    ofstream out;
    in.open(infile, ios::binary);
    out.open(outfile);
    //istream i1( in );
    //ostream o( out );
    BitOutputStream bitOut( out );
    BitInputStream bitIn( in );
    vector<int> freqs(256,0);
    int i = in.get();
    int z = 0;
    while ( i != EOF ){
	z++;
        freqs[i] = freqs[i]+1;
        i = in.get();
    }
    //cout << z <<'\n';
    //cout << freqs[65] << '\n';
    HCTree tree;
    tree.build(freqs);
    for( int d = 0; d < 256; d++ ){
        bool answer;
	for( int i = 31; i >= 0; i-- ){
		answer = (freqs[d] & 1<<i) >> i;
		bitOut.writeBit(answer);
	}
    }
    int count = 0;
    for( int d = 0; d < 256; d++ ){
        if( freqs[d] != 0 ){
                count++;
        }
    }
    if( count == 1 || count == 0 ){
        bitOut.flush();
	return;
    }
    in.clear();
    in.seekg(0,ios::beg);
    char next;
    if ( in.eof()==false ){
        next = in.get();
    }
    while( next != EOF ){
        tree.encode( next, bitOut);
        next = in.get();
    }
    bitOut.flush();
    in.close();
    out.close();

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
        compressBitwise(infile, outfile);
    } else {
        compressAscii(infile, outfile);
    }

    return 0;
}
