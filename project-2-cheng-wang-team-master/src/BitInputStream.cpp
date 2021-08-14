#include "BitInputStream.hpp"

// TODO (final)
BitInputStream::BitInputStream(istream & i) : in(i) {
     buf = 0;
     nbits = 8;	
}

bool BitInputStream::readBit() {
    //return false;  // TODO (final)
     if ( nbits == 8 ){
	buf = in.get();
	//cout << buf << '\n';
	nbits = 7;
     }
     if ( nbits < 0 ){
	buf = in.get();
	//cout<<buf<<'\n';
        nbits = 7;
     }
     bool answer = ( buf & (1<<nbits)) >>nbits;
     nbits--;
     //cout<< answer <<'\n';
     return answer;
}
