// Wavelet_transformation.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Filter97_encoder.h"
#include "Filter97_decoder.h"
#include "Data.h"
using namespace BDK;

#define LENGTH 3
#define SIZE 20
#define TYPE true

void show(float*, int);

int _tmain(int argc, _TCHAR* argv[])
{
	printf("97 Filter test \n");

	Filter97_encoder *encoder = new Filter97_encoder(LENGTH);
	Filter97_decoder *decoder = new Filter97_decoder(LENGTH);
	float in[] = { 2.0 , 4.0, 44.0, 40.0, 5.0, 4.0};
	float out_high[LENGTH/2 + 1];
	float out_low[LENGTH/2 + 1];
	float out[LENGTH] = {0.0f ,0.0f ,0.0f };//,0.0f ,0.0f };

	encoder->start(in, out_high, out_low, 0, LENGTH, 1, TYPE, 0, 1, 0, 1);
	decoder->start(out, out_high, out_low, 0, LENGTH, 1, TYPE, 0, 1, 0, 1);

	show(in, LENGTH);
	show(out, LENGTH);



	Data *data							= new Data(SIZE, SIZE);
	Filter97_encoder *filter_encoder	= new Filter97_encoder(SIZE);
	Filter97_decoder *filter_decoder	= new Filter97_decoder(SIZE);
	data->random_fill_float();
	data->showData_float();
	data->filter_encode(filter_encoder);
	data->showData_float();
	data->filter_decode(filter_decoder);
	data->showData_float();
	
	return 0;
}

void show(float *out, int length){
	int i;
	for(i = 0; i < length; i++){
		printf(" %f", out[i]);
	}
	printf("\n");
}
