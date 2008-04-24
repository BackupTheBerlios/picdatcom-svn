#include "MQ_Decoder.h"


const int MQ_Decoder::qe[] = {0x5601, 0x3401, 0x1801, 0x0ac1, 0x0521, 0x0221, 0x5601,
                  0x5401, 0x4801, 0x3801, 0x3001, 0x2401, 0x1c01, 0x1601, 
                  0x5601, 0x5401, 0x5101, 0x4801, 0x3801, 0x3401, 0x3001,
                  0x2801, 0x2401, 0x2201, 0x1c01, 0x1801, 0x1601, 0x1401,
                  0x1201, 0x1101, 0x0ac1, 0x09c1, 0x08a1, 0x0521, 0x0441,
                  0x02a1, 0x0221, 0x0141, 0x0111, 0x0085, 0x0049, 0x0025,
                  0x0015, 0x0009, 0x0005, 0x0001, 0x5601};

const int MQ_Decoder::nMPS[] = { 1 , 2, 3, 4, 5,38, 7, 8, 9,10,11,12,13,29,15,16,17,
                     18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
                     35,36,37,38,39,40,41,42,43,44,45,45,46 };

const int MQ_Decoder::nLPS[] = { 1 , 6, 9,12,29,33, 6,14,14,14,17,18,20,21,14,14,15,
                     16,17,18,19,19,20,21,22,23,24,25,26,27,28,29,30,31,
                     32,33,34,35,36,37,38,39,40,41,42,43,46 };

const int MQ_Decoder::switchT[]={ 1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
                         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };


MQ_Decoder::MQ_Decoder(vector<unsigned char> *byte_buffer)
{
	this->byte_buffer = byte_buffer;

	int iWork1;

	for(iWork1 = 0; iWork1 < NUMBER_OF_CONTEXT; iWork1++){
		I[iWork1]	= 0;
		MPS[iWork1]	= 0;
	}

	I[UNIFORM]		= 46;
	I[RUNLENGTH]	= 3;
	I[0]			= 4;
	B = 0;
}

MQ_Decoder::~MQ_Decoder(void)
{
}

void MQ_Decoder::initdec()
{
	unsigned char B1;
	pos = (*byte_buffer).begin();
	B	= *pos;
	C	= B << 16;

	//BYTEIN
	if(B == 0xFF){
		pos++;
		B1 = *pos;
		if(B1 > 0x8F){
			pos--;
			C = C + 0xFF00;
			CT = 8;
		}else{
			B = B1;
			C = C + (B << 9);
			CT = 7;
		}
	}else{
		pos++;
		B = *pos;
		C = C + (B << 8);
	}
	//BYTEIN END

	C	= C << 7;
	CT	= CT - 7;
	A	= 0x8000;
}

int MQ_Decoder::decode(unsigned int CX)
{
	int i_temp	= I[CX];
	int qe_temp	= qe[itemp];

	A = A - qe_temp;

}