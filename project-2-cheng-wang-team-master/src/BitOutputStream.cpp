#include "BitOutputStream.hpp"

// TODO (final)
BitOutputStream::BitOutputStream(ostream & o) : out(o) {
    nbits = 7;
    buf = 0;
}
void BitOutputStream::writeBit(bool bit) {
    // TODO (final)
    //cout << bit << '\n';
    buf = (buf & ~(1<<nbits)) | ((bit << nbits ) & (1<<nbits));
    nbits--;
    //cout << buf <<'\n';
    if( nbits < 0){
	out.put( buf );
        buf = 0;
	nbits = 7;
    }
}

void BitOutputStream::flush() {
    // TODO (final)
    if ( nbits == 7 ){
	out.flush();
	return;
    }
    if( nbits <= 0 ){
	out.put( buf );
	buf = 0;
	nbits = 7;
    }
    else{
	for ( int i = nbits; i > 0; i-- ){
		writeBit(0);
	}
	out.put(buf);
	buf = 0;
	nbits = 7;
    }
    out.flush();
}
