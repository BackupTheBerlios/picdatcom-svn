/*
 * Copyright (C) 2008  Uwe Brünen
 * Contact Email: bruenen.u@web.de
 * 
 * This file is part of PicDatCom.
 * 
 * PicDatCom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * PicDatCom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with PicDatCom.  If not, see <http://www.gnu.org/licenses/>.
 * */


#include "PDC_Decoder.h"


START_C

/*
 * 
 */
DLL PDC_Decoder* new_PDC_Decoder()
{
	PDC_Decoder* decoder = NULL;

	decoder = malloc(sizeof(PDC_Decoder));
	if(decoder == NULL){
		return NULL;
	}

	decoder->exception		= NULL;
	decoder->in_data		= NULL;
	decoder->in_data_save	= NULL;

	decoder->exception =  new_PDC_Exception();
	if(decoder->in_data == NULL){
		delete_PDC_Decoder(decoder);
		return NULL;
	}


	decoder->in_data = new_PDC_Buffer_1( PDC_FIRST_LENGTH);
	if(decoder->in_data == NULL){
		delete_PDC_Decoder(decoder);
		return NULL;
	}

	decoder->in_data_save = new_PDC_Buffer_3();
	if(decoder->in_data == NULL){
		delete_PDC_Decoder(decoder);
		return NULL;
	}

	decoder->reading_state	= PDC_UNKNOW;
	decoder->data_situation	= PDC_WAIT_FOR_DATA;

	return decoder;
}

/*
 *
 */
DLL PDC_Decoder* PDC_Decoder_add_Data_01(	PDC_Decoder* decoder, 
											PDC_uchar* data, 
											PDC_uint32 length, 
											PDC_DECODER_DATA_END end)
{
	PDC_Buffer* temp_buffer;

	if(decoder->in_data->end_state != END_OF_BUFFER && data != NULL && length != 0 && decoder != NULL){
		temp_buffer = PDC_Buffer_add_bytes_1(decoder->in_data, data, length);
		if(temp_buffer == NULL){
			return NULL;
		}
		decoder->in_data = temp_buffer;

		if(end == PDC_DATA_END){
			decoder->in_data->end_state = END_OF_BUFFER;
		}
		decoder->data_situation	= PDC_HAS_DATA;
		PDC_Decoder_decode(decoder);

	}else{
		PDC_Exception_error(decoder->exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return NULL;
	}

	return decoder;
}


/*
 * 
 */
DLL PDC_Decoder* delete_PDC_Decoder(PDC_Decoder* decoder)
{
	if(decoder != NULL){
		delete_PDC_Buffer(decoder->in_data);
		delete_PDC_Buffer(decoder->in_data_save);
		delete_PDC_Exception(decoder->exception);
	}
	return NULL;
}


/*
 * 
 */
PDC_Decoder* PDC_Decoder_decode(PDC_Decoder* decoder)
{

	PDC_READING_STATE	reading_state;

	reading_state	= decoder->reading_state;
	
	do{
		switch(reading_state){
			case PDC_UNKNOW:
				decoder			= PDC_Decoder_decode_unknow(decoder);
				reading_state	= decoder->reading_state;
				break;

			case PDC_MAIN_HEADER_SIZ:
				decoder			= PDC_Decoder_decode_main_header_siz(decoder);
				reading_state	= decoder->reading_state;
				break;

			case PDC_MAIN_HEADER:
				break;

			case PDC_TILE_PART_HEADER:
				break;
		}
	
		if(reading_state == PDC_ERROR){
			break;
		}

	}while(decoder->data_situation == PDC_HAS_DATA);

	return decoder;
}


/*
 * 
 */
PDC_Decoder* PDC_Decoder_decode_unknow(PDC_Decoder* decoder)
{
	PDC_uint16			symbol;
	PDC_Buffer*			buffer;

	buffer = decoder->in_data;

	do{
		buffer = PDC_Buffer_read_uint16(buffer, &symbol);
		if(buffer->exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			if(buffer->end_state == END_OF_BUFFER){
				PDC_Exception_error(decoder->exception, buffer->exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
				decoder->data_situation = PDC_WAIT_FOR_DATA;
				return decoder;
			}else{
				PDC_Exception_unset_exception(buffer->exception);
				decoder->data_situation = PDC_WAIT_FOR_DATA;
				return decoder;
			}
		}

		if(symbol == PDC_SOC){
			decoder->reading_state = PDC_MAIN_HEADER_SIZ;
		}else{
			buffer->read_byte_pos -= 1;
		}

	}while(symbol != PDC_SOC);

	return decoder;
}

/*
 * 
 */
PDC_Decoder* PDC_Decoder_decode_main_header_siz(PDC_Decoder* decoder)
{
	PDC_uint16			symbol;
	PDC_Buffer*			buffer;

	buffer = decoder->in_data;

	
	buffer = PDC_Buffer_read_uint16(buffer, &symbol);
	if(buffer->exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		if(buffer->end_state == END_OF_BUFFER){
			PDC_Exception_error(decoder->exception, buffer->exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
			decoder->data_situation = PDC_WAIT_FOR_DATA;
			return decoder;
		}else{
			PDC_Exception_unset_exception(buffer->exception);
			decoder->data_situation = PDC_WAIT_FOR_DATA;
			return decoder;
		}
	}

	if(symbol == PDC_SIZ){
		
	}else{
		PDC_Exception_error(decoder->exception, NULL, PDC_EXCEPTION_FALSE_SYMBOL, __LINE__, __FILE__);
	}

	

	return decoder;
}


STOP_C