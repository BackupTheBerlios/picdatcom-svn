#pragma once

#include <vector>
using namespace std;

#define NUMBER_OF_CONTEXT 19

class MQ_Encoder
{
private:
        static const int qe[]; 
        static const int nMPS[];
        static const int nLPS[];
		static const int switchT[];

		int I[NUMBER_OF_CONTEXT];
		int MPS[NUMBER_OF_CONTEXT];

		int C;
		int A;
		int CT;
		unsigned char B;

		vector<unsigned char> byte_buffer;

public:
	MQ_Encoder(void);
	~MQ_Encoder(void);

	void initenc();
	void start(vector<struct context_label> &buffer);
	void flush();
};
