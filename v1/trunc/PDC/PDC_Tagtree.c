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

#include "PDC_Tagtree.h"

START_C

/* 
 *
 */
PDC_Tagtree* new_PDC_Tagtree_01(PDC_Exception* exception,
								PDC_uint size_x,
								PDC_uint size_y)
{
	PDC_Tagtree* tagtree;

	tagtree = malloc(sizeof(PDC_Tagtree));
	if(tagtree == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	tagtree->size_x	= size_x;
	tagtree->size_y = size_y;
	tagtree->level	= 


	return tagtree;
}

STOP_C
