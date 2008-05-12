// PDC_Transformation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PDC_Transformation_97_decoder.h"
#include "PDC_Transformation_97_encoder.h"

void test_transformation_97();
#define TESTLENGTH 100

int _tmain(int argc, _TCHAR* argv[])
{
	test_transformation_97();
	return 0;
}

void test_transformation_97()
{
	float in[TESTLENGTH];
	float out_high[TESTLENGTH];
	float out_low[TESTLENGTH];
	float result[TESTLENGTH];
	float dif = 0.0f;

	PDC_Transformation_97_decoder* decoder;
	PDC_Transformation_97_encoder* encoder;

	PDC_uint i;

	decoder = new_PDC_Transformation_97_decoder(TESTLENGTH);
	encoder = new_PDC_Transformation_97_encoder(TESTLENGTH);

	srand(0);
	for(i = 0; i < TESTLENGTH; i++){
		in[i] = (float)(rand() % 500);
	}


	encoder = PDC_te_start(	encoder,
							in, out_high, out_low, 
							0, TESTLENGTH, 1, PDC_true, 
							0, 1,
							0, 1);

	decoder = PDC_td_start(	decoder,
							result, out_high, out_low, 
							0, TESTLENGTH, 1, PDC_true, 
							0, 1,
							0, 1);

	for(i = 0; i < TESTLENGTH; i++){
		dif += in[i] - result[i];
		printf("in = %f <<--->>  resout = %f dif = %f \n",in[i], result[i], in[i] - result[i]);
	}
	printf("dif =%f \n", dif);

}