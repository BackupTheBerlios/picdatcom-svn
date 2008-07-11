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

#include "PDC_Codeblock.h"

START_C

	
/*
 *
 */
PDC_Codeblock* new_PDC_Codeblock_01(PDC_Exception* exception)
{
	PDC_Codeblock* codeblock = NULL;
	codeblock = malloc(sizeof(PDC_Codeblock));
	if(codeblock == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	codeblock->cx0		= 0;
	codeblock->cx1		= 0;
	codeblock->cy0		= 0;
	codeblock->cy1		= 0;
	codeblock->subband	= NULL;

	return codeblock;
}

/*
 *
 */
PDC_Codeblock* new_PDC_Codeblock_02(PDC_Exception* exception, PDC_Subband* subband, PDC_uint pos_x, PDC_uint pos_y)
{
	PDC_Codeblock* codeblock;

	PDC_Resolution* resolution	= subband->resolution;
	PDC_uint		size_x		= 1 << resolution->xcb;
	PDC_uint		size_y		= 1 << resolution->ycb;

	codeblock = new_PDC_Codeblock_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Codeblock(exception, codeblock);
		return NULL;
	}

	codeblock->cx0	= max_uint32(size_x * pos_x, subband->tbx0);
	codeblock->cx1	= min_uint32(size_x *(pos_x + 1), subband->tbx1);
	codeblock->cy0	= max_uint32(size_y * pos_y, subband->tby0);
	codeblock->cy1	= min_uint32(size_y *(pos_y + 1), subband->tby1);

	return codeblock;
}


/*
 *
 */
PDC_Codeblock* delete_PDC_Codeblock(PDC_Exception* exception, PDC_Codeblock* codeblock)
{
	if(codeblock != NULL){
		free(codeblock);
	}
	return NULL;
}


STOP_C

