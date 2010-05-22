/*
 * run.c
 *
 *  Created on: 20.04.2009
 *      Author: uwe
 */

#include <stdio.h>
#include <PicDatCom.h>
#include <PDC_Exception.h>

#define data_read_plus 800
#define test_file "/home/uwe/temp_programmieren/picdatcom/prototype/bdk/image.jpc"

void print(PDC_Exception* exception){
	int code = (int)exception->code;
	switch(code){
		case PDC_EXCEPTION_NO_EXCEPTION:
			printf("PDC_EXCEPTION_NO_EXCEPTION \n");
			break;
		case PDC_EXCEPTION_OUT_OF_MEMORY:
			printf("PDC_EXCEPTION_OUT_OF_MEMORY \n");
			break;
		case PDC_EXCEPTION_NULL_POINTER:
			printf("PDC_EXCEPTION_NULL_POINTER \n");
			break;
		case PDC_EXCEPTION_OUT_OF_SIZE:
			printf("PDC_EXCEPTION_OUT_OF_SIZE \n");
			break;
		case PDC_EXCEPTION_OUT_OF_RANGE:
			printf("PDC_EXCEPTION_OUT_OF_RANGE \n");
			break;
		case PDC_EXCEPTION_NO_NULLPOINTER_ALLOWED:
			printf("PDC_EXCEPTION_NO_NULLPOINTER_ALLOWED \n");
			break;
		case PDC_EXCEPTION_NO_CODE_FOUND:
			printf("PDC_EXCEPTION_NO_CODE_FOUND \n");
			break;
		case PDC_EXCEPTION_FALSE_SYMBOL:
			printf("PDC_EXCEPTION_FALSE_SYMBOL \n");
			break;
		case PDC_EXCEPTION_UNKNOW_CODE:
			printf("PDC_EXCEPTION_UNKNOW_CODE \n");
			break;
		case PDC_EXCEPTION_DECODER:
			printf("PDC_EXCEPTION_DECODER \n");
			break;
		case PDC_EXCEPTION_DAMAGED_CODE:
			printf("PDC_EXCEPTION_DAMAGED_CODE \n");
			break;
		default:
			printf("There is a undocument exception \n");
	}

	printf("In file %s on line %d \n", exception->file, exception->line );
};

int main(int argc, char* argv[]){
	unsigned char*	data;
	PDC_size_t		read_byte;
	FILE* fp;

	PDC_Decoder*	decoder;
	PDC_Exception*	exception;



	printf("Hallo Picdatcom  new %ld \n", sizeof(unsigned long));
	printf("sizeof(int) = %d \n", sizeof(int));
	printf("sizeof(size_t) = %d \n", sizeof(size_t));

	//printf("Hallo Picdatcom  new %d \n", sizeof(unsigned long));


	data = (unsigned char*)malloc(data_read_plus);
	if(argc > 1){
		fp = fopen(argv[1], "rb");
		if(fp == NULL){
			printf("Can't open file \n");
			return EXIT_FAILURE;
		}
		exception	= new_PDC_Exception();
		decoder		= new_PDC_Decoder(exception);

		do{
			read_byte = fread(data, 1, data_read_plus, fp);
			if(read_byte != 0){
				PDC_Decoder_add_Data_01(exception, decoder, data, read_byte, PDC_DATA_MORE_DATA);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					break;
				}

				PDC_Decoder_decode(exception, decoder);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					break;
				}
			}
		}while(read_byte > 0) ;//data_read_plus);
		fclose(fp);

		if(exception->code == PDC_EXCEPTION_NO_EXCEPTION){
			PDC_Decoder_add_Data_01(exception, decoder, NULL, 0, PDC_DATA_END);
			PDC_Decoder_decode(exception, decoder);
		}
		print(exception);

		delete_PDC_Decoder(exception, decoder);
		delete_PDC_Exception(exception);

		free(data);
		printf("Goodbye PicDatCom \n");
	}else{
		printf("You must add the Path to a JPEG2000 file.\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
