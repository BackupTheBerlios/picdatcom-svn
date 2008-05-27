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
DLL PDC_Decoder* new_PDC_Decoder(PDC_Exception* exception)
{
	PDC_Decoder* decoder = NULL;

	decoder = malloc(sizeof(PDC_Decoder));
	if(decoder == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	decoder->in_data		= NULL;
	decoder->in_data_save	= NULL;
	decoder->picture		= NULL;


	decoder->in_data = new_PDC_Buffer_1( exception, PDC_FIRST_LENGTH);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Decoder(exception, decoder);
		return NULL;
	}

	decoder->in_data_save = new_PDC_Buffer_3(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Decoder(exception, decoder);
		return NULL;
	}

	decoder->reading_state	= PDC_UNKNOW;
	decoder->data_situation	= PDC_WAIT_FOR_DATA;

	return decoder;
}

/*
 *
 */
DLL PDC_Decoder* PDC_Decoder_add_Data_01(	PDC_Exception* exception,
											PDC_Decoder* decoder, 
											PDC_uchar* data, 
											PDC_uint32 length, 
											PDC_DECODER_DATA_END end)
{
	if(decoder->in_data->end_state != END_OF_BUFFER && data != NULL && length != 0 && decoder != NULL){
		decoder->in_data = PDC_Buffer_add_bytes_1(exception, decoder->in_data, data, length);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return decoder;
		}
	

		if(end == PDC_DATA_END){
			decoder->in_data->end_state = END_OF_BUFFER;
		}
		decoder->data_situation	= PDC_HAS_DATA;
		PDC_Decoder_decode(exception, decoder);

	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return NULL;
	}

	return decoder;
}


/*
 * 
 */
DLL PDC_Decoder* delete_PDC_Decoder(PDC_Exception* exception, PDC_Decoder* decoder)
{
	if(decoder != NULL){
		delete_PDC_Buffer(exception, decoder->in_data);
		delete_PDC_Buffer(exception, decoder->in_data_save);
		delete_PDC_Picture(exception, decoder->picture);
	}
	return NULL;
}


/*
 * 
 */
PDC_Decoder* PDC_Decoder_decode(PDC_Exception* exception, PDC_Decoder* decoder)
{

	PDC_READING_STATE	reading_state;

	reading_state	= decoder->reading_state;
	
	do{
		switch(reading_state){
			case PDC_UNKNOW:
				decoder			= PDC_Decoder_decode_unknow(exception, decoder);
				reading_state	= decoder->reading_state;
				break;

			case PDC_MAIN_HEADER_SIZ:
				decoder			= PDC_Decoder_decode_main_header_siz(exception, decoder);
				reading_state	= decoder->reading_state;
				break;

			case PDC_MAIN_HEADER:
				PDC_Decoder_decode_main_header(exception, decoder);
				reading_state	= decoder->reading_state;
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
PDC_Decoder* PDC_Decoder_decode_unknow(PDC_Exception* exception, PDC_Decoder* decoder)
{
	PDC_uint16			symbol;
	PDC_Buffer*			buffer;

	buffer = decoder->in_data;

	do{
		buffer = PDC_Buffer_read_uint16(exception, buffer, &symbol);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			if(buffer->end_state == END_OF_BUFFER){
				PDC_Exception_error(exception, NULL, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
				decoder->data_situation = PDC_WAIT_FOR_DATA;
				return decoder;
			}else{
				PDC_Exception_unset_exception(exception);
				decoder->data_situation = PDC_WAIT_FOR_DATA;
				return decoder;
			}
		}

		if(symbol == PDC_SOC){
			decoder->reading_state	= PDC_MAIN_HEADER_SIZ;
			decoder->picture		= new_PDC_Picture(exception);
			if(decoder->picture == NULL){
				PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
				return decoder;
			}
		}else{
			buffer->read_byte_pos -= 1;
		}

	}while(symbol != PDC_SOC);

	return decoder;
}

/*
 * 
 */
PDC_Decoder* PDC_Decoder_decode_main_header_siz(PDC_Exception* exception, PDC_Decoder* decoder)
{
	PDC_uint16			symbol;
	PDC_Buffer*			buffer;
	PDC_SIZ_Segment*	siz_segment;

	buffer = decoder->in_data;

	buffer = PDC_Buffer_read_uint16(exception, buffer, &symbol);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		if(buffer->end_state == END_OF_BUFFER){
			PDC_Exception_error(exception, NULL, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
			decoder->data_situation = PDC_WAIT_FOR_DATA;
			return decoder;
		}else{
			PDC_Exception_unset_exception(exception);
			decoder->data_situation = PDC_WAIT_FOR_DATA;
			return decoder;
		}
	}

	if(symbol == PDC_SIZ){
		siz_segment = new_PDC_SIZ_Segment_02(exception, buffer);
		if(siz_segment == NULL){
			PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
			return decoder;
		}
		decoder->picture->siz_segment = siz_segment;
		decoder->reading_state = PDC_MAIN_HEADER;
	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_FALSE_SYMBOL, __LINE__, __FILE__);
	}

	return decoder;
}

/*
 * 
 */
PDC_Decoder* PDC_Decoder_decode_main_header(PDC_Exception* exception, PDC_Decoder* decoder)
{
	PDC_uint16			symbol;
	PDC_Buffer*			buffer;
	PDC_bool			decode_more;
	PDC_COD_Segment*	cod_segment;
	
	buffer		= decoder->in_data;
	cod_segment	= NULL;

	decode_more = PDC_true;

	do{
		buffer = PDC_Buffer_read_uint16(exception, buffer, &symbol);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			if(buffer->end_state == END_OF_BUFFER){
				PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
				decoder->data_situation = PDC_WAIT_FOR_DATA;
				return decoder;
			}else{
				PDC_Exception_unset_exception(exception);
				decoder->data_situation = PDC_WAIT_FOR_DATA;
				return decoder;
			}
		}

		switch(symbol){
			case PDC_COD:
				cod_segment = new_PDC_COD_Segment_02(exception, buffer);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				break;
			default:
				PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
				return decoder;
				break;

		}

	}while(decode_more);

	return decoder;
}
STOP_C