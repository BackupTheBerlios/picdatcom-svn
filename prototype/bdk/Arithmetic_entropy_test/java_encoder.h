#ifndef __JAVA_ENCODER_H__
#define __JAVA_ENCODER_H__

#include "ByteBuffer.h"
using namespace BDK;

class java_encoder
{
public:
	ByteBuffer* bytebuffer;
	static unsigned int qe[];
	static unsigned int nMPS[];
	static unsigned int nLPS[];
	static unsigned int switchLM[];

    /** The current most probable signal for each context */
    unsigned int* mPS;

    /** The current index of each context */
    unsigned int* I;

    /** The current bit code */
    unsigned int c;

    /** The bit code counter */
    int cT;

    /** The current interval */
    unsigned int a;

    /** The last byte read */
    unsigned int b;

	unsigned int* initStates;
	int I_length;

	unsigned char decodeSymbol(unsigned int context);
	void resetCtxts();
	void init();
	void byteIn();
	int decodeSymbol(unsigned char context);
	java_encoder(ByteBuffer *bytebuffer,  const int length, unsigned int* default_mps, unsigned int* default_index );

public:
	~java_encoder(void);
};

#endif