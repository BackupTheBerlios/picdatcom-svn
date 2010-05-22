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

#ifndef __PDC_QCD_SEGMENT_H__
#define __PDC_QCD_SEGMENT_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C
	
	struct str_PDC_QCD_Segment;
	typedef struct str_PDC_QCD_Segment PDC_QCD_Segment;
	typedef enum{PDC_READ_SEGMENT_BYTE_POS, PDC_READ_BUFFER_BYTE_POS} PDC_Segment_read_pos;
	typedef enum{PDC_QCD_SEGMENT_READING_STATE1, PDC_QCD_SEGMENT_READING_STATE2} PDC_QCD_SEGMENT_READING_STATE;

	#include "PDC_COD_Segment.h"
	#include "PDC_Decoder.h"
	
#define NO_QUANTIZATION		0x00
#define SCALAR_DERIVED		0x01
#define SCALAR_EXPOUNDED	0x02
#define	MASK_QUANTIZATION	0x1F
#define MASK_GUARD_BITS		0xE0
#define MASK_MANTISSA		0x07FF
#define MASK_EXPONENT		0xF800
#define SHIFT_EXPONENT		11
#define SHIFT_GUARD_BITS	5
	
	struct str_PDC_QCD_Segment{
		PDC_bool						succesfull_read;
		PDC_size_t						read_buffer_pos;
		PDC_uint16						Lqcd;
		PDC_uint8						Sqcd;
		PDC_uint16*						SPqcd;
		PDC_Segment_read_pos			read_pos_from;
		PDC_QCD_SEGMENT_READING_STATE	reading_state;
	};

	/*
	 *
	 */
	PDC_QCD_Segment* new_PDC_QCD_Segment_01(PDC_Exception* exception);

	/*
	 *
	 */
	PDC_QCD_Segment* new_PDC_QCD_Segment_02(PDC_Exception* exception,
											PDC_Buffer* buffer,
											PDC_COD_Segment* cod_segment);

	/*
	 *
	 */
	PDC_QCD_Segment* new_PDC_QCD_Segment_03(	PDC_Exception* exception,
												PDC_Buffer* buffer);

	/*
	 *
	 */
	PDC_QCD_Segment* delete_PDC_QCD_Segment(PDC_Exception* exception,
											PDC_QCD_Segment* qcd_segment);


	/*
	 *
	 */
	PDC_QCD_Segment* PDC_QCD_Segment_read_buffer(	PDC_Exception* exception,
													PDC_QCD_Segment* qcd_segment,
													PDC_Buffer* buffer,
													PDC_COD_Segment* cod_segment);

	/*
	 *
	 */
	PDC_QCD_Segment* PDC_QCD_Segment_read_buffer_01(PDC_Exception* exception,
													PDC_QCD_Segment* qcd_segment,
													PDC_Buffer* buffer,
													PDC_COD_Segment* cod_segment,
													PDC_Decoder* decoder);

STOP_C
#endif
