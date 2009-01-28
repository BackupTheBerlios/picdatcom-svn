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

#ifndef __PDC_DECODER_H__
#define __PDC_DECODER_H__

#include <stdio.h>
#include <stdlib.h>
#include "PDC_Parameter.h"

START_C

	struct str_PDC_Decoder;
	typedef struct str_PDC_Decoder PDC_Decoder;
	typedef enum{PDC_DATA_END, PDC_DATA_MORE_DATA}PDC_DECODER_DATA_END;
	typedef enum{PDC_UNKNOW, PDC_MAIN_HEADER, PDC_TILE_PART_HEADER, PDC_MAIN_HEADER_SIZ, PDC_ERROR} PDC_READING_STATE;
	typedef enum{PDC_WAIT_FOR_DATA, PDC_HAS_DATA, PDC_NO_DATA} PDC_DATA_SITUATION;

	#include "PDC_Buffer.h"
	#include "PDC_Picture.h"
	
	#define PDC_FIRST_LENGTH 204800

	#define PDC_SOC 0xFF4F
	#define PDC_SOT 0xFF90
	#define PDC_SOD 0xFF93
	#define PDC_EOC 0xFFD9
	#define PDC_SIZ 0xFF51
	#define PDC_COD 0xFF52
	#define PDC_COC 0xFF53
	#define PDC_RGN 0xFF5E
	#define PDC_QCD	0xFF5C
	#define PDC_QCC 0xFF5D
	#define PDC_POC 0xFF5F
	#define PDC_TLM	0xFF55
	#define PDC_PLM	0xFF57
	#define PDC_PLT	0xFF58
	#define PDC_PPM 0xFF60
	#define PDC_PPT 0xFF61
	#define PDC_SOP 0xFF91
	#define PDC_EPH 0xFF92
	#define PDC_CRG	0xFF63
	#define PDC_COM 0xFF64


	struct str_PDC_Decoder{
		PDC_Buffer*			in_data;
		PDC_Buffer*			in_data_save;
		PDC_Picture*		picture;
		PDC_READING_STATE	reading_state;
		PDC_DATA_SITUATION	data_situation;
		PDC_Tile*			current_tile;
		PDC_Exception*		exception;
	};
	
	/*
	 * 
	 */
	DLL PDC_Decoder* new_PDC_Decoder(PDC_Exception* exception);
	
	/*
	 * 
	 */
	DLL PDC_Decoder* new_PDC_Decoder_02(const char *filepath);

	/*
	 * 
	 */
	DLL PDC_Decoder* delete_PDC_Decoder(PDC_Exception* exception,
										PDC_Decoder* decoder);

	/*
	 *
	 */
	DLL PDC_Decoder* PDC_Decoder_add_Data_01(	PDC_Exception* exception,
												PDC_Decoder* decoder, 
												PDC_uchar* data, 
												PDC_uint32 length, 
												PDC_DECODER_DATA_END end);

	/*
	 * 
	 */
	DLL PDC_Decoder* PDC_Decoder_decode(PDC_Exception* exception,
										PDC_Decoder* decoder);

	/*
	 * 
	 */
	PDC_Decoder* PDC_Decoder_decode_unknow(	PDC_Exception* exception,
											PDC_Decoder* decoder);

	/*
	 * 
	 */
	PDC_Decoder* PDC_Decoder_decode_main_header_siz(PDC_Exception* exception,
													PDC_Decoder* decoder);

	/*
	 * 
	 */
	PDC_Decoder* PDC_Decoder_decode_main_header(PDC_Exception* exception,
												PDC_Decoder* decoder);

	/*
	 * 
	 */
	PDC_Decoder* PDC_Decoder_decode_tile_part_header(PDC_Exception* exception,
													 PDC_Decoder* decoder);

STOP_C
#endif