
#ifndef __JAVA_DECODER_H__
#define __JAVA_DECODER_H__

#include "ByteBuffer.h"
using namespace BDK;

class Java_decoder
{
private:
	
	static unsigned int qe[];
	static unsigned int nMPS[];
	static unsigned int nLPS[];
	static unsigned int switchLM[];

	/** The current most probable signal for each context */
    int* mPS;

    /** The current index of each context */
    int* I;

    /** The current bit code */
    unsigned int c;

    /** The bit code counter */
    int cT;

    /** The current interval */
    unsigned int a;

    /** The last encoded byte of data */
    unsigned int b;
   /** If a 0xFF byte has been delayed and not yet been written to the output 
     * (in the MQ we can never have more than 1 0xFF byte in a row). */
    bool delFF;

    /** The number of written bytes so far, excluding any delayed 0xFF
     * bytes. Upon initialization it is -1 to indicated that the byte buffer
     * 'b' is empty as well. */
    int nrOfWrittenBytes;

    /** The initial state of each context */
    int* initStates;

	ByteBuffer *bytebuffer;
	int I_length;
public:
	Java_decoder(int nrOfContexts, int *init);
	void byteOut();
	void resetCtxts(); 
	void codeSymbols(int* bits, int* cX, int n);
public:
	~Java_decoder(void);
};

#endif