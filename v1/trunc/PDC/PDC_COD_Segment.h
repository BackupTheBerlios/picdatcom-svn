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

#ifndef __PDC_COD_SEGMENT_H__
#define __PDC_COD_SEGMENT_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C
	
	struct str_PDC_COD_Segment;
	typedef struct str_PDC_COD_Segment PDC_COD_Segment;
	typedef enum{PDC_COD_SEGMENT_READING_STATE1, PDC_COD_SEGMENT_READING_STATE2} PDC_COD_SEGMENT_READING_STATE;

	#include "PDC_Buffer.h"
	#include "PDC_Decoder.h"

	#define LAYER_RESOLUTION_LEVEL_COMPONENT_POSITION 0x00
	#define	RESOLUTION_LEVEL_LAYER_COMPONENT_POSITION 0x01
	#define RESOLUTION_LEVEL_POSITION_COMPONENT_LAYER 0x02
	#define POSITION_COMPONENT_RESOLUTION_LEVEL_LAYER 0x03
	#define COMPONENT_POSITION_RESOLUTION_LEVEL_LAYER 0x04

	#define DEFAULT_PRECINCT_SIZE		0x01
	#define USE_SOP						0x02	
	#define USE_EPH						0x04
	#define SELECTIVE_ARITHMETIC_CODING	0x01
	#define	RESET_CONTEXT				0x02
	#define TERMINATION_EACH_CODING		0x04
	#define VERITCAL_CAUSAL_CONTEXT		0x08
	#define PREDICTABLE_TERMINATION		0x16
	#define	SEGMANTION_SYMBOLS_USED		0x32
	#define MULTIPLE_TRANSFORMATION		0x01
	#define TRANSFORMATION_REVERSIBLE	0x01

	struct str_PDC_COD_Segment{
		PDC_uint16	lcot;
		PDC_uint8	scot;
		PDC_uint8	progression_order;
		PDC_uint16	number_of_layer;
		PDC_uint8	multiple_component_transformation;
		PDC_uint8	number_of_decompostion_levels;
		PDC_uint8	code_block_width;
		PDC_uint8	code_block_height;
		PDC_uint8	code_block_style;
		PDC_uint8	transformation;
		PDC_Buffer*	precinct_size;

		PDC_COD_SEGMENT_READING_STATE	reading_state;
	};

	/*
	 *
	 */
	PDC_COD_Segment* new_PDC_COD_Segment_01(PDC_Exception *exception);

	/*
	 *
	 */
	PDC_COD_Segment* new_PDC_COD_Segment_02(	PDC_Exception *exception,
												PDC_Buffer* buffer);

	/*
	 *
	 */
	PDC_COD_Segment* delete_PDC_COD_Segment(	PDC_Exception* exception,
												PDC_COD_Segment* cod_segment);

	/*
	 *
	 */
	PDC_COD_Segment* PDC_COD_Segment_read_buffer(	PDC_Exception* exception,
													PDC_COD_Segment* cod_segment,
													PDC_Buffer* buffer);

	/*
	 *
	 */
	PDC_COD_Segment* PDC_COD_Segment_read_buffer_01(PDC_Exception* exception,
													PDC_COD_Segment* cod_segment,
													PDC_Buffer* buffer,
													PDC_Decoder* decoder);
STOP_C
#endif
