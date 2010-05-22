/*
 * Copyright (C) 2008  Uwe Brünen
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
	if( a < 0 && b < 0){		
		if(a%b != 0){
			i += 1;
		}
		
	}else if( a > 0 && b > 0){
		if(a%b != 0){
			i += 1;
		}
	}
	return i;	
}

PDC_int PDC_i_floor( PDC_int a, PDC_int b)
{
	PDC_int i = a/b;

	if( a < 0 && b > 0){
		if(a%b != 0){
			i -= 1;
		}	
	}else if( a > 0 && b < 0){
		if(a%b != 0){
			i -= 1;
		}
	}

	return i;
}

PDC_uint PDC_ui_ceiling( PDC_uint a, PDC_uint b)
{
	PDC_uint i = a/b;
	if(a%b != 0){
		i += 1;
	}
	return i;	
}

PDC_uint PDC_ui_floor( PDC_uint a, PDC_uint b)
{
	PDC_int i = a/b;

	return i;
}


PDC_int PDC_f_ceiling(PDC_float32 in)
{
	PDC_int back = 0;
	back = (PDC_int)(in + 1.0f);
	return back;
}

PDC_int	PDF_f_floor(PDC_float32 in)
{
	PDC_int back = 0;
	back = (PDC_int)(in);
	return back;
}

PDC_uint32 max_uint32(PDC_uint32 in1, PDC_uint32 in2)
{
	if(in1 > in2){
		return in1;
	}
	return in2;
}

PDC_uint32 min_uint32(PDC_uint32 in1, PDC_uint32 in2)
{
	if(in1 < in2){
		return in1;
	}
	return in2;
}

PDC_int min_int(PDC_int in1, PDC_int in2)
{
	if(in1 < in2){
		return in1;
	}
	return in2;
}

PDC_uint max_uint(PDC_uint in1, PDC_uint in2)
{
	if(in1 > in2){
		return in1;
	}
	return in2;
}

PDC_uint min_uint(PDC_uint in1, PDC_uint in2)
{
	if(in1 < in2){
		return in1;
	}
	return in2;
}

PDC_uint PDC_floor_log2( PDC_uint in)
{
	PDC_uint back = 0;

	while(in > 1){
		back += 1;
		in >>= 1;
	}
	return back;
}


PDC_int PDC_max_thread()
{
	return 1;
}

STOP_C
