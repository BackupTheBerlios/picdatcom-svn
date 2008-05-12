/*
 * Copyright (C) 2008  Uwe Br�nen
 *      Contact Email: 
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

#include "PDC_Parameter.h"

START_C

PDC_int PDC_i_ceiling(PDC_int a, PDC_int b)
{
	PDC_int i = a/b;
	if(a%b != 0){
		i += 1;
	}
	return i;	
}

PDC_int PDC_i_floor( PDC_int a, PDC_int b)
{
	PDC_int i = a/b;

	return i;
}

STOP_C