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

#include "PDC_COD_Segment.h"

START_C

/*
 *
 */
 PDC_COD_Segment* new_PDC_COD_Segment(PDC_Exception *exception)
{
	PDC_COD_Segment* cod_segment = NULL;
	cod_segment = malloc(sizeof(PDC_COD_Segment));
	if(cod_segment == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__),
		return NULL;
	}

}

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

STOP_C
