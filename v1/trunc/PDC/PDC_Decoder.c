/*
 * Copyright (C) 2008  Uwe Br�nen
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
	decoder->current_tile	= NULL;

	decoder->exception		= exception;

	decoder->cod_segments	= NULL;
	decoder->qcd_segments	= NULL;
	decoder->com_segments	= NULL;
	decoder->sot_segments	= NULL;

	decoder->cod_segments	= new_PDC_Pointer_Buffer_02(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Decoder(exception, decoder);
		return NULL;
	}

	decoder->qcd_segments	= new_PDC_Pointer_Buffer_02(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Decoder(exception, decoder);
		return NULL;
	}

	decoder->com_segments	= new_PDC_Pointer_Buffer_02(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Decoder(exception, decoder);
		return NULL;
	}

	decoder->sot_segments	= new_PDC_Pointer_Buffer_02(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Decoder(exception, decoder);
		return NULL;
	}

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
DLL PDC_Decoder* new_PDC_Decoder_02(const char *filepath)
{
	PDC_Decoder	*decoder			= NULL;
	PDC_Exception *exception		= NULL;
	FILE *fp						= NULL;
	unsigned int read_byte			= 0;
	unsigned int data_read_plus	= 1048576;
	unsigned char*	data			= NULL;


	data = malloc(data_read_plus);
	if(data == NULL){
		return NULL;
	}

	fp = fopen(filepath, "rb");
	if(fp == NULL){
		return NULL;
	}

	exception	= new_PDC_Exception();
	if(exception == NULL){
		return NULL;
	}

	decoder		= new_PDC_Decoder(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Decoder(exception, decoder);
		delete_PDC_Exception(exception);
		free(data);
		fclose(fp);
		return NULL;
	}

	do{
		read_byte = fread(data, 1, data_read_plus, fp);
		PDC_Decoder_add_Data_01(exception, decoder, data, read_byte, PDC_DATA_MORE_DATA);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Decoder(exception, decoder);
			delete_PDC_Exception(exception);
			free(data);
			fclose(fp);
			return NULL;
		}

	}while(read_byte > 0) ;
	fclose(fp);
	free(data);
	PDC_Decoder_add_Data_01(exception, decoder, NULL, 0, PDC_DATA_END);
	PDC_Decoder_decode(exception, decoder);

	return decoder;
}


/*
 *
 */
DLL PDC_Decoder* new_PDC_Decoder_03(const unsigned char *byte_stream, unsigned int length)
{
	PDC_Decoder	*decoder			= NULL;
	PDC_Exception *exception		= NULL;

	exception	= new_PDC_Exception();
	if(exception == NULL){
		return NULL;
	}

	decoder		= new_PDC_Decoder(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Decoder(exception, decoder);
		delete_PDC_Exception(exception);
		return NULL;
	}

	PDC_Decoder_add_Data_01(exception, decoder, byte_stream, length, PDC_DATA_END);
	PDC_Decoder_decode(exception, decoder);

	return decoder;
}

/*
 *
 */
DLL PDC_Decoder* PDC_Decoder_add_Data_01(	PDC_Exception* exception,
											PDC_Decoder* decoder,
											const PDC_uchar* data,
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
		//PDC_Decoder_decode(exception, decoder);

	}else if(length == 0){
		if(end == PDC_DATA_END){
			decoder->in_data->end_state = END_OF_BUFFER;
		}
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
		delete_PDC_Exception(decoder->exception);


		free(decoder);

	}
	return NULL;
}

FILE* DEBUG_FILE;
FILE* DEBUG_FILE2;
/*
 *
 */
DLL PDC_Decoder* PDC_Decoder_decode(PDC_Exception* exception, PDC_Decoder* decoder)
{

	PDC_READING_STATE	reading_state;

	DEBUG_FILE 	= fopen("debug_file1.txt", "w");
	DEBUG_FILE2 = fopen("debug_file2.txt", "w");
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
				PDC_Decoder_decode_tile_part_header(exception, decoder);
				reading_state	= decoder->reading_state;
				break;
			case PDC_ERROR:
				PDC_Exception_error(exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
				break;
		}

		if(reading_state == PDC_ERROR){
			break;
		}

	}while(decoder->data_situation == PDC_HAS_DATA);

	fclose(DEBUG_FILE);
	fclose(DEBUG_FILE2);
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
		decoder->picture = PDC_Picture_set_SIZ_Segment(	exception,
														decoder->picture,
														siz_segment);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return decoder;
		}
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
	PDC_uint32			t_tile;
	PDC_uint16			symbol;
	PDC_Buffer*			buffer;
	PDC_bool			decode_more;
	PDC_COD_Segment*	cod_segment;
	PDC_QCD_Segment*	qcd_segment;
	PDC_COM_Segment*	com_segment;
	PDC_SOT_Segment*	sot_segment;

	buffer		= decoder->in_data;
	cod_segment	= decoder->picture->cod_segment;
	qcd_segment = decoder->picture->qcd_segment;
	com_segment = decoder->picture->com_segment;

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
 				if(cod_segment == NULL){
					cod_segment = new_PDC_COD_Segment_02(exception, buffer);
					if(qcd_segment != NULL){
						PDC_QCD_Segment_read_buffer(exception, qcd_segment, buffer, cod_segment);
					}
					PDC_Picture_set_COD_Segment(exception, decoder->picture, cod_segment);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						return decoder;
					}
				}else{
					PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
					return decoder;
				}
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				break;
			case PDC_QCD:
				if(qcd_segment == NULL){
					qcd_segment = new_PDC_QCD_Segment_02(exception, buffer, cod_segment);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						return decoder;
					}
					PDC_Picture_set_QCD_Segment(exception, decoder->picture, qcd_segment);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						return decoder;
					}
				}else{
					PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
					return decoder;
				}
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				break;
			case PDC_COM:
				if(com_segment == NULL){
					com_segment = new_PDC_COM_Segment_02(exception, buffer);
				}else{
					PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
					return decoder;
				}
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}

				break;
			case PDC_SOT:
				sot_segment = new_PDC_SOT_Segment_02(exception, buffer);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				t_tile = sot_segment->Isot;
				decoder->current_tile = PDC_Pointer_Buffer_get_pointer(exception, decoder->picture->tiles, t_tile);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				decoder->reading_state = PDC_TILE_PART_HEADER;
				decode_more = PDC_false;
				break;
			default:
				PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
				return decoder;
				break;

		}

	}while(decode_more);

	return decoder;
}


/*
 *
 */
PDC_Decoder* PDC_Decoder_decode_tile_part_header(PDC_Exception* exception,
													 PDC_Decoder* decoder)
{
	PDC_uint16			symbol;
	PDC_Buffer*			buffer;
	PDC_bool			decode_more;
	PDC_Tile*			tile;
	PDC_COD_Segment*	cod_segment;
	PDC_QCD_Segment*	qcd_segment;

	buffer		= decoder->in_data;
	tile		= decoder->current_tile;
	decode_more	= PDC_true;
	cod_segment	= tile->cod_segment;
	qcd_segment	= NULL;


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

		switch(symbol){
			case PDC_COD:
				cod_segment = new_PDC_COD_Segment_02(exception, buffer);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				PDC_Tile_set_COD_Segment(exception, tile, cod_segment);
				break;
			case PDC_SOD:
				PDC_Tile_read_SOD_01(exception, tile, buffer);
				break;
			case PDC_EOC:
				decoder->data_situation = PDC_NO_DATA;
				break;
			case PDC_SOC:
				break;
			default:
				PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
				return decoder;
				break;
		}
	}while(symbol != PDC_SOC && symbol != PDC_EOC);

	return decoder;
}

STOP_C
