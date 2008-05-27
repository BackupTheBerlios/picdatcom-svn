// PDC_test_run.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <PicDatCom.h>

#define data_read_plus 1024
#define test_file "C:\\Dokumente und Einstellungen\\uwe_work\\Eigene Dateien\\Visual Studio 2008\\Projects\\PicDatCom\\prototype\\bdk\\image.jpc"

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned char*	data;
	unsigned int	read_byte;
	int inf;

	PDC_Decoder*	decoder;
	PDC_Exception*	exception;

	data = (unsigned char*)malloc(data_read_plus);
	inf = _open(test_file,O_RDONLY);
	if(inf == -1){
		printf("Can´t open the file\n");
		return 0;
	}

	
	exception	= new_PDC_Exception(); 
	decoder		= new_PDC_Decoder(exception);
	//print_errors();
	
	do{
		read_byte = _read(inf, data, data_read_plus);
		PDC_Decoder_add_Data_01(exception, decoder, data, read_byte, PDC_DATA_MORE_DATA);
	}while(read_byte == data_read_plus);
	_close(inf);

	PDC_Decoder_add_Data_01(exception, decoder, NULL, 0, PDC_DATA_END);

	//print_errors();
	
	return 0;
}

