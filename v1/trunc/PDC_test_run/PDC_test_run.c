/*
 * run.c
 *
 *  Created on: 20.04.2009
 *      Author: uwe
 */

#include <stdio.h>
#include <PicDatCom.h>
#include <PDC_Exception.h>

#define data_read_plus 2000
#define test_file "/home/uwe/programmieren/picdatcom/prototype/bdk/image.jpc"


int main(int argc, char* argv[]){
	unsigned char*	data;
	unsigned int	read_byte;
	FILE* fp;

	PDC_Decoder*	decoder;
	PDC_Exception*	exception;


	printf("Hallo Picdatcom %lld \n", sizeof(unsigned long));

	data = (unsigned char*)malloc(data_read_plus);

	fp = fopen(test_file, "rb");
	if(fp == NULL){
		printf("Can't open file \n");
		return 0;
	}
	exception	= new_PDC_Exception();
	decoder		= new_PDC_Decoder(exception);

	do{
		read_byte = fread(data, 1, data_read_plus, fp);
		PDC_Decoder_add_Data_01(exception, decoder, data, read_byte, PDC_DATA_MORE_DATA);
	}while(read_byte > 0) ;//data_read_plus);
	fclose(fp);
	PDC_Decoder_add_Data_01(exception, decoder, NULL, 0, PDC_DATA_END);
	PDC_Decoder_decode(exception, decoder);

	delete_PDC_Decoder(exception, decoder);
	delete_PDC_Exception(exception);

	free(data);
	printf("Goodbye PicDatCom \n");
	return 0;
}
