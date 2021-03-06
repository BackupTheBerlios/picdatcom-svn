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

#ifndef __PDC_SIZ_SEGMENT_H__
#define __PDC_SIZ_SEGMENT_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C

	struct str_PDC_SIZ_Segment;
	typedef struct str_PDC_SIZ_Segment PDC_SIZ_Segment;

	#include "PDC_Pointer_Buffer.h"
	#include "PDC_Buffer.h"
	#include "PDC_SIZ_Segment_Componente.h"
	#include "PDC_Decoder.h"

	#define DEFAULT_NUMBER_COMPONENTEN 3

	struct str_PDC_SIZ_Segment{
		//PDC_Exception*	exception;
		PDC_uint16		Lsiz;
		PDC_uint16		Rsiz;
		PDC_uint32		Xsiz;
		PDC_uint32		Ysiz;
		PDC_uint32		XOsiz;
		PDC_uint32		YOsiz;
		PDC_uint32		XTsiz;
		PDC_uint32		YTsiz;
		PDC_uint32		XTOsiz;
		PDC_uint32		YTOsiz;
		PDC_uint16		Csiz;

		PDC_Pointer_Buffer* componente_part;
	};

	/*
	 *
	 */
	PDC_SIZ_Segment* new_PDC_SIZ_Segment_01(PDC_Exception* exception);

	/*
	 *
	 */
	PDC_SIZ_Segment* new_PDC_SIZ_Segment_02(PDC_Exception* exception, PDC_Buffer* buffer);

	/*
	 *
	 */
	void delete_PDC_SIZ_Segment_01(PDC_Exception* exception, PDC_SIZ_Segment* siz_segment);

	/*
	 *
	 */
	PDC_SIZ_Segment* PDC_SIZ_Segment_read_buffer(	PDC_Exception* exception,
													PDC_SIZ_Segment* siz_segment,
													PDC_Buffer* buffer);

	/*
	 *
	 */
	PDC_SIZ_Segment* PDC_SIZ_Segment_read_buffer_01(	PDC_Exception* exception,
														PDC_Buffer* buffer,
														PDC_Decoder* decoder);

	/*
	 *
	 */
	PDC_SIZ_Segment* PDC_SIZ_Segment_read_buffer_02(	PDC_Exception* exception,
														PDC_Buffer* buffer,
														PDC_Decoder* decoder);
STOP_C
#endif
