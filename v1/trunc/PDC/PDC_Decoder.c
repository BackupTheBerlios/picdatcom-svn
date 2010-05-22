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

FILE* DEBUG_FILE;
FILE* DEBUG_FILE2;
FILE* DEBUG_FILE3;


/*
 *
 */
DLL PDC_Decoder* new_PDC_Decoder(PDC_Exception* exception)
{
	PDC_Decoder* decoder = NULL;

	//DEBUG_FILE 	= fopen("debugnew_file1.txt", "w");

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

	decoder->siz_segment	= NULL;
	decoder->siz_segments	= NULL;
	decoder->cod_segments	= NULL;
	decoder->qcd_segments	= NULL;
	decoder->com_segments	= NULL;
	decoder->sot_segments	= NULL;

	decoder->siz_segments	= new_PDC_Pointer_Buffer_02(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Decoder(exception, decoder);
		return NULL;
	}

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

	decoder->reading_state			= PDC_UNKNOW;
	decoder->data_situation			= PDC_WAIT_FOR_DATA;
	decoder->main_header_siz_read	= PDC_MAIN_HEADER_SIZ_SYMBOL;
	decoder->symbol_16				= 0;
	decoder->symbol_main_header		= PDC_SYMBOL;

	decoder->cod_segment_number		= 0;
	decoder->qcd_segment_number		= 0;
	decoder->com_segment_number		= 0;
	decoder->sot_segment_number		= 0;

	decoder->sot_segment			= NULL;

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
	PDC_size_t read_byte			= 0;
	PDC_size_t data_read_plus	= 1048576;
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
											PDC_size_t length,
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

	PDC_COD_Segment*	cod_segment;
	PDC_SIZ_Segment*	siz_segment;
	PDC_QCD_Segment*	qcd_segment;
	PDC_COM_Segment*	com_segment;
	PDC_SOT_Segment*	sot_segment;

	if(decoder != NULL){
		delete_PDC_Buffer(exception, decoder->in_data);
		delete_PDC_Buffer(exception, decoder->in_data_save);
		delete_PDC_Picture(exception, decoder->picture);

		if(decoder->cod_segments != NULL){
			if(decoder->cod_segments->full == PDC_true){
				PDC_Pointer_Buffer_set_start(exception, decoder->cod_segments);
				for(cod_segment = PDC_Pointer_Buffer_get_next(exception, decoder->cod_segments);
					cod_segment != NULL;
					cod_segment = PDC_Pointer_Buffer_get_next(exception, decoder->cod_segments)){

						delete_PDC_COD_Segment(exception, cod_segment);
				}
			}
			delete_PDC_Pointer_Buffer_01(exception, decoder->cod_segments);
			decoder->cod_segments = NULL;
		}

		if(decoder->siz_segments != NULL){
			if(decoder->siz_segments->full == PDC_true){
				PDC_Pointer_Buffer_set_start(exception, decoder->siz_segments);
				for(siz_segment = PDC_Pointer_Buffer_get_next(exception, decoder->siz_segments);
					siz_segment != NULL;
					siz_segment = PDC_Pointer_Buffer_get_next(exception, decoder->siz_segments)){

						delete_PDC_SIZ_Segment_01(exception, siz_segment);
				}
			}
			delete_PDC_Pointer_Buffer_01(exception, decoder->siz_segments);
			decoder->siz_segments = NULL;
		}

		if(decoder->qcd_segments != NULL){
			if(decoder->qcd_segments->full == PDC_true){
				PDC_Pointer_Buffer_set_start(exception, decoder->qcd_segments);
				for(qcd_segment = PDC_Pointer_Buffer_get_next(exception, decoder->qcd_segments);
					qcd_segment != NULL;
					qcd_segment = PDC_Pointer_Buffer_get_next(exception, decoder->qcd_segments)){

						delete_PDC_QCD_Segment(exception, qcd_segment);
				}
			}
			delete_PDC_Pointer_Buffer_01(exception, decoder->qcd_segments);
			decoder->qcd_segments = NULL;
		}

		if(decoder->com_segments != NULL){
			if(decoder->com_segments->full == PDC_true){
				PDC_Pointer_Buffer_set_start(exception, decoder->com_segments);
				for(com_segment = PDC_Pointer_Buffer_get_next(exception, decoder->com_segments);
					com_segment != NULL;
					com_segment = PDC_Pointer_Buffer_get_next(exception, decoder->com_segments)){

						delete_PDC_COM_Segment(exception, com_segment);
				}
			}
			delete_PDC_Pointer_Buffer_01(exception, decoder->com_segments);
			decoder->com_segments = NULL;
		}

		if(decoder->sot_segments != NULL){
			if(decoder->sot_segments->full == PDC_true){
				PDC_Pointer_Buffer_set_start(exception, decoder->sot_segments);
				for(sot_segment = PDC_Pointer_Buffer_get_next(exception, decoder->sot_segments);
					sot_segment != NULL;
					sot_segment = PDC_Pointer_Buffer_get_next(exception, decoder->sot_segments)){

						delete_PDC_SOT_Segment(exception, sot_segment);
				}
			}
			delete_PDC_Pointer_Buffer_01(exception, decoder->sot_segments);
			decoder->sot_segments = NULL;
		}

		free(decoder);

	}

	//fclose(DEBUG_FILE);
	return NULL;
}


/*
 *
 */
DLL PDC_Decoder* PDC_Decoder_decode(PDC_Exception* exception, PDC_Decoder* decoder)
{

	PDC_READING_STATE	reading_state;

	//DEBUG_FILE 	= fopen("debugnew_file1.txt", "w");
	//DEBUG_FILE2 = fopen("debugnew_file2.txt", "w");
	//DEBUG_FILE3 = fopen("debugnew_file3.txt", "w");
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
			case PDC_EOC:
				decoder->data_situation = PDC_NO_DATA;
				break;
		}

		if(reading_state == PDC_ERROR){
			break;
		}

	}while(decoder->data_situation == PDC_HAS_DATA);

	//fclose(DEBUG_FILE);
	//fclose(DEBUG_FILE2);
	//fclose(DEBUG_FILE3);
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
	PDC_uint16			symbol		= decoder->symbol_16;
	PDC_Buffer*			buffer;
	//PDC_SIZ_Segment*	siz_segment;

	buffer = decoder->in_data;

	switch(decoder->main_header_siz_read){
	case PDC_MAIN_HEADER_SIZ_SYMBOL:

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
			decoder->siz_segment = new_PDC_SIZ_Segment_01(exception);
			if(decoder->siz_segment == NULL){
				PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
				return decoder;
			}
		}else{
			PDC_Exception_error(exception, NULL, PDC_EXCEPTION_FALSE_SYMBOL, __LINE__, __FILE__);
			return decoder;
		}
		decoder->main_header_siz_read 	= PDC_MAIN_HEADER_SIZ_DATA1;
		decoder->symbol_16				= symbol;

	case PDC_MAIN_HEADER_SIZ_DATA1:

		decoder->siz_segment = PDC_SIZ_Segment_read_buffer_01(	exception,
																buffer,
																decoder);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_SIZ_Segment_01(exception, decoder->siz_segment);
			decoder->siz_segment = NULL;
			return decoder;
		}
		if(decoder->data_situation == PDC_WAIT_FOR_DATA){
			return decoder;
		}

		decoder->main_header_siz_read 	= PDC_MAIN_HEADER_SIZ_DATA2;

	case PDC_MAIN_HEADER_SIZ_DATA2:
		decoder->siz_segment = PDC_SIZ_Segment_read_buffer_02(	exception,
																buffer,
																decoder);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_SIZ_Segment_01(exception, decoder->siz_segment);
			decoder->siz_segment = NULL;
			return decoder;
		}
		if(decoder->data_situation == PDC_WAIT_FOR_DATA){
			return decoder;
		}

		decoder->picture = PDC_Picture_set_SIZ_Segment(	exception,
														decoder->picture,
														decoder->siz_segment);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return decoder;
		}
		decoder->reading_state = PDC_MAIN_HEADER;

		/*
		 * Only to deconstruct and free the memory the pointer is saved.
		 */
		PDC_Pointer_Buffer_add_pointer(exception, decoder->siz_segments, decoder->siz_segment);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_SIZ_Segment_01(exception, decoder->siz_segment);
			decoder->siz_segment = NULL;
			return decoder;
		}
		decoder->main_header_siz_read 	= PDC_MAIN_HEADER_SIZ_SYMBOL;
		decoder->symbol_16				= 0;
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
	sot_segment	= decoder->sot_segment;
	symbol		= decoder->symbol_main_header;

	decode_more = PDC_true;

	do{
		switch(symbol){
		case PDC_SYMBOL:
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
			PDC_Decoder_set_decode_main_header_symbol(exception,decoder, symbol);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return decoder;
			}
			break;

			case PDC_COD:
				if(cod_segment == NULL){
					cod_segment 					= new_PDC_COD_Segment_01(exception);
					decoder->picture->cod_segment	= cod_segment;
					PDC_Pointer_Buffer_add_pointer(exception, decoder->cod_segments, cod_segment);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						delete_PDC_COD_Segment(exception, cod_segment);
						return decoder;
					}
				}
				cod_segment = PDC_COD_Segment_read_buffer_01(	exception,
																cod_segment,
																buffer,
																decoder);

				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				if(decoder->data_situation == PDC_WAIT_FOR_DATA){
					return decoder;
				}

				PDC_Picture_set_COD_Segment(exception, decoder->picture, cod_segment);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				if(qcd_segment != NULL){
					PDC_QCD_Segment_read_buffer(exception, qcd_segment, buffer, cod_segment);
				}

				symbol						= PDC_SYMBOL;
				PDC_Decoder_set_decode_main_header_symbol(exception,decoder, symbol);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				break;
			case PDC_QCD:
				if(qcd_segment == NULL){
					qcd_segment = new_PDC_QCD_Segment_03(exception, buffer);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						return decoder;
					}
					PDC_Pointer_Buffer_add_pointer(exception, decoder->qcd_segments, qcd_segment);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						delete_PDC_QCD_Segment(exception, qcd_segment);
						return decoder;
					}
					decoder->picture->qcd_segment = qcd_segment;
				}
				qcd_segment = PDC_QCD_Segment_read_buffer_01(	exception,
																qcd_segment,
																buffer,
																cod_segment,
																decoder);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				if(decoder->data_situation == PDC_WAIT_FOR_DATA){
					return decoder;
				}

				PDC_Picture_set_QCD_Segment(exception, decoder->picture, qcd_segment);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}

				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				symbol						= PDC_SYMBOL;
				PDC_Decoder_set_decode_main_header_symbol(exception,decoder, symbol);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				break;
			case PDC_COM:
				if(com_segment == NULL){
					com_segment = new_PDC_COM_Segment_01(exception);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						return decoder;
					}
					PDC_Pointer_Buffer_add_pointer(exception, decoder->com_segments, com_segment);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						delete_PDC_COM_Segment(exception, com_segment);
						return decoder;
					}
					decoder->picture->com_segment = com_segment;
				}

				com_segment = PDC_COM_Segment_read_buffer_01(	exception,
																com_segment,
																buffer,
																decoder);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				if(decoder->data_situation == PDC_WAIT_FOR_DATA){
					return decoder;
				}

				symbol						= PDC_SYMBOL;
				PDC_Decoder_set_decode_main_header_symbol(exception,decoder, symbol);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				break;
			case PDC_SOT:
				if(sot_segment == NULL){
					sot_segment = new_PDC_SOT_Segment_01(exception);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						return decoder;
					}
					PDC_Pointer_Buffer_add_pointer(exception, decoder->sot_segments, sot_segment);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						delete_PDC_SOT_Segment(exception, sot_segment);
						return decoder;
					}
					decoder->sot_segment = sot_segment;
				}

				sot_segment = PDC_SOT_Segment_read_buffer(	exception,
															sot_segment,
															buffer,
															decoder);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}
				if(decoder->data_situation == PDC_WAIT_FOR_DATA){
					return decoder;
				}

				t_tile = sot_segment->Isot;
				decoder->current_tile = PDC_Pointer_Buffer_get_pointer(exception, decoder->picture->tiles, t_tile);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return decoder;
				}

				decoder->sot_segment		= NULL;
				decoder->reading_state 		= PDC_TILE_PART_HEADER;
				decode_more 				= PDC_false;

				symbol						= PDC_SYMBOL;
				PDC_Decoder_set_decode_main_header_symbol(exception,decoder, symbol);
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


/*
 *
 */
PDC_Decoder* PDC_Decoder_decode_tile_part_header(	PDC_Exception* exception,
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
	symbol		= tile->symbol;

	do{
		switch(symbol){
		case PDC_SYMBOL:
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
			PDC_Decoder_set_decode_tile_part_header_symbol(	exception,
															decoder,
															symbol,
															tile);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return decoder;
			}
			cod_segment	= tile->cod_segment;
			break;

		case PDC_COD:
			if(cod_segment == NULL){
				cod_segment 					= new_PDC_COD_Segment_01(exception);
				tile->cod_segment	= cod_segment;
				PDC_Pointer_Buffer_add_pointer(exception, decoder->cod_segments, cod_segment);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					delete_PDC_COD_Segment(exception, cod_segment);
					return decoder;
				}
			}
			cod_segment = PDC_COD_Segment_read_buffer_01(	exception,
															cod_segment,
															buffer,
															decoder);

			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return decoder;
			}
			if(decoder->data_situation == PDC_WAIT_FOR_DATA){
				return decoder;
			}

			PDC_Tile_set_COD_Segment(exception, tile, cod_segment);
			PDC_Decoder_set_decode_tile_part_header_symbol(	exception,
															decoder,
															PDC_SYMBOL,
															tile);
			symbol = PDC_SYMBOL;

			break;
		case PDC_SOD:
			PDC_Tile_read_SOD_02(exception, tile, buffer, decoder);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return decoder;
			}
			if(decoder->data_situation == PDC_WAIT_FOR_DATA){
				return decoder;
			}
			symbol = PDC_SYMBOL;
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

/*
 *
 */
PDC_Decoder* PDC_Decoder_set_decode_main_header_symbol(	PDC_Exception* exception,
														PDC_Decoder* decoder,
														PDC_uint16 symbol)
{

	switch(symbol){
	case PDC_COD:
		if(decoder->cod_segment_number == 0){
			decoder->symbol_main_header = symbol;
			decoder->cod_segment_number	+= 1;
		}else{
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
		}
		break;
	case PDC_QCD:
		if(decoder->qcd_segment_number == 0){
			decoder->symbol_main_header = symbol;
			decoder->qcd_segment_number	+= 1;
		}else{
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
		}
		break;
	case PDC_COM:
		if(decoder->com_segment_number == 0){
			decoder->symbol_main_header = symbol;
			decoder->com_segment_number	+= 1;
		}else{
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
		}
		break;
	case PDC_SOT:
		decoder->symbol_main_header = symbol;
		decoder->sot_segment_number	+= 1;
		break;
	case PDC_SYMBOL:
		decoder->symbol_main_header = symbol;
		break;
	}
	return decoder;
}


/*
 *
 */
PDC_Decoder* PDC_Decoder_set_decode_tile_part_header_symbol(PDC_Exception* exception,
															PDC_Decoder* decoder,
															PDC_uint16 symbol,
															PDC_Tile* tile)
{
	switch(symbol){
	case PDC_COD:
		if(tile->cod_segment_number == 0){
			tile->symbol 				= symbol;
			tile->cod_segment_number	+= 1;
			PDC_Tile_set_COD_Segment(exception, tile, NULL);
		}else{
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
		}
		break;
	case PDC_SYMBOL:
		tile->symbol = symbol;
		break;
	case PDC_SOD:
		tile->symbol = symbol;
		break;
	case PDC_EOC:
		tile->symbol = symbol;
		decoder->reading_state = symbol;
		break;
	}

	return decoder;
}

STOP_C
