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

#ifndef __PDC_SIZ_SEGMENT_COMPONENTE_H__
#define __PDC_SIZ_SEGMENT_COMPONENTE_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C

	struct str_PDC_SIZ_Segment_Componente;
	typedef struct str_PDC_SIZ_Segment_Componente PDC_SIZ_Segment_Componente;
	
	#include "PDC_Buffer.h"

	struct str_PDC_SIZ_Segment_Componente{
		PDC_Exception*	exception;
		PDC_uint8		Ssiz;
		PDC_uint8		XRsiz;
		PDC_uint8		YRsiz;
	};

	/*
	 * 
	 */
	PDC_SIZ_Segment_Componente* new_PDC_SIZ_Segment_Componente_01(PDC_Exception* exception);

	/*
	 * 
	 */
	PDC_SIZ_Segment_Componente* new_PDC_SIZ_Segment_Componente_02(	PDC_Exception* exception, 
																	PDC_Buffer* buffer);

	/*
	 *
	 */
	void delete_PDC_SIZ_Segment_Componente(	PDC_Exception* exception,
											PDC_SIZ_Segment_Componente* siz_segment_com);

	/*
	 *
	 */
	PDC_SIZ_Segment_Componente* PDC_SIZ_Segment_Componente_read_buffer(	PDC_Exception* exception,
																		PDC_SIZ_Segment_Componente* siz_segment,
																		PDC_Buffer* buffer);

STOP_C
#endif
