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

#include "PDC_Precinct.h"

START_C

/*
 *
 */
PDC_Precinct* new_PDC_Precinct_01(PDC_Exception* exception)
{
	PDC_Precinct* precinct;
	precinct = malloc(sizeof(PDC_Precinct));
	if(precinct == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	precinct->codeblock_x0	= 0;
	precinct->codeblock_x1	= 0;
	precinct->codeblock_y0	= 0;
	precinct->codeblock_y1	= 0;
	precinct->resolution	= NULL;

	return precinct;
}

/*
 *
 */
PDC_Precinct* new_PDC_Precinct_02(PDC_Exception* exception, 
								  PDC_Resolution* resolution, 
								  PDC_uint pos_x, 
								  PDC_uint pos_y)
{
	PDC_uint		codeblocks_x;
	PDC_uint		codeblocks_y;
	PDC_Precinct*	precinct = NULL;
	PDC_uint		x0, x1, y0, y1;

	precinct = new_PDC_Precinct_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Precinct(exception, precinct);
		return NULL;
	}
	
	precinct->resolution = resolution;

	codeblocks_x = 1 << (resolution->PPx - resolution->xcb);
	codeblocks_y = 1 << (resolution->PPy - resolution->ycb);
	
	x0 = codeblocks_x * pos_x;
	x1 = x0 + codeblocks_x;
	y0 = codeblocks_y * pos_y;
	y1 = y0 + codeblocks_y;

	precinct->codeblock_x0 = max_uint(x0, resolution->codeblock_x0);
	precinct->codeblock_x1 = min_uint(x1, resolution->codeblock_x1);
	precinct->codeblock_y0 = max_uint(y0, resolution->codeblock_y0);
	precinct->codeblock_y1 = min_uint(y1, resolution->codeblock_y1);
	
	return precinct;
}


/*
 * 
 */
PDC_Precinct* delete_PDC_Precinct(	PDC_Exception* exception,
									PDC_Precinct* precinct)
{
	if(precinct != NULL){
		free(precinct);
	}
	return NULL;
}

STOP_C

