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

#ifndef __PDC_SOT_SEGMENT_H__
#define __PDC_SOT_SEGMENT_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C
	
	struct str_PDC_SOT_Segment;
	typedef struct str_PDC_SOT_Segment PDC_SOT_Segment;

	#include "PDC_Tile.h"
	#include "PDC_Buffer.h"

	struct str_PDC_SOT_Segment{
		PDC_uint32	Psot;
		PDC_uint16	Lsot;
		PDC_uint16	Isot;
		PDC_uint8	TPsot;
		PDC_uint8	TNsot;
	};

	/*
	 *
	 */
	PDC_SOT_Segment* new_PDC_SOT_Segment_01(PDC_Exception* exception);
	
	/*
	 *
	 */
	PDC_SOT_Segment* new_PDC_SOT_Segment_02(PDC_Exception* exception, PDC_Buffer* buffer);

	/*
	 *
     */
	void delete_PDC_SOT_Segment(PDC_Exception* exception, PDC_SOT_Segment* sot_segment);

	/*
	 *
	 */
	PDC_SOT_Segment* PDC_SOT_Segment_read_buffer(	PDC_Exception* exception,
													PDC_SOT_Segment* sot_segment,
													PDC_Buffer* buffer,
													PDC_Decoder* decoder);

STOP_C
#endif
