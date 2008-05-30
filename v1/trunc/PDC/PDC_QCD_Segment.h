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

#ifndef __PDC_QCD_SEGMENT_H__
#define __PDC_QCD_SEGMENT_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C
	
	struct str_PDC_QCD_Segment;
	typedef struct str_PDC_QCD_Segment PDC_QCD_Segment;
	typedef enum{PDC_READ_SEGMENT_BYTE_POS, PDC_READ_BUFFER_BYTE_POS} PDC_Segment_read_pos;

	#include "PDC_COD_Segment.h"
	
#define NO_QUANTIZATION		0x00
#define SCALAR_DERIVED		0x01
#define SCALAR_EXPOUNDED	0x02
#define	MASK_QUANTIZATION	0x1F
#define MASK_GUARD_BITS		0xE0
#define MASK_MANTISSA		0x007F
#define MASK_EXPONENT		0xF800
#define SHIFT_EXPONENT		11
	
	struct str_PDC_QCD_Segment{
		PDC_bool				succesfull_read;
		PDC_uint32				read_buffer_pos;
		PDC_uint16				Lqcd;
		PDC_uint8				Sqcd;
		PDC_uint16*				SPqcd;
		PDC_Segment_read_pos	read_pos_from;
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
	PDC_QCD_Segment* delete_PDC_QCD_Segment(PDC_Exception* exception,
											PDC_QCD_Segment* qcd_segment);


	/*
	 *
	 */
	PDC_QCD_Segment* PDC_QCD_Segment_read_buffer(	PDC_Exception* exception,
													PDC_QCD_Segment* qcd_segment,
													PDC_Buffer* buffer,
													PDC_COD_Segment* cod_segment);

STOP_C
#endif