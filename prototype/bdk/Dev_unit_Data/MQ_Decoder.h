#pragma once

#include "MQ_coder.h"
#include <vector>
using namespace std;

class MQ_Decoder
{
private:

    static const int qe[]; 
    static const int nMPS[];
    static const int nLPS[];
	static const int switchT[];

	int I[NUMBER_OF_CONTEXT];
	int MPS[NUMBER_OF_CONTEXT];

	vector<unsigned char> *byte_buffer;
	vector<unsigned char>::const_iterator pos;
	unsigned int B;
	unsigned int C;
	int	CT;
	unsigned int A;

public:
	MQ_Decoder(vector<unsigned char> *byte_buffer);
	~MQ_Decoder(void);

	void initdec();
	int decode(unsigned int CX);
};
