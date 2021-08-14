#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitOutputStream {
private:
    char buf;
    int nbits;
    ostream & out;

public:
    BitOutputStream(ostream & o);
    void writeBit(bool bit);
    void flush();
};

#endif // BITOUTPUTSTREAM_HPP
