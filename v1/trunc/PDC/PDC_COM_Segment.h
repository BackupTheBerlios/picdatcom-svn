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

#ifndef __PDC_COM_SEGMENT_H__
#define __PDC_COM_SEGMENT_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C

	struct str_PDC_COM_Segment;
	typedef struct str_PDC_COM_Segment PDC_COM_Segment;

	#include "PDC_Buffer.h"

	struct str_PDC_COM_Segment{
		PDC_uint16	Lcom;
		PDC_uint16	Rcom;
		PDC_uint8*	Ccom;
	};

	/*
	 *
	 */
	PDC_COM_Segment* new_PDC_COM_Segment_01(	PDC_Exception* exception);

	/*
	 *
	 */	
	PDC_COM_Segment* new_PDC_COM_Segment_02(	PDC_Exception*	exception,
												PDC_Buffer*		buffer);

	/*
	 *
	 */
	PDC_COM_Segment* delete_PDC_COM_Segment(	PDC_Exception*		exception,
												PDC_COM_Segment*	com_segment);

	/*
	 *
	 */
	PDC_COM_Segment* PDC_COM_Segment_read_buffer(	PDC_Exception*		exception,
													PDC_COM_Segment*	com_segment,
													PDC_Buffer*			buffer);


STOP_C
#endif