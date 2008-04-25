/*
 * Copyright (C) 2008  Uwe Brünen
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

#ifdef __cplusplus     
extern "C" {         
#endif

PDC_Buffer* new_PDC_Buffer_1(PDC_uint length)
{
	PDC_Buffer* buffer = NULL;
	PDC_uchar*	charbuffer = NULL;
	buffer = malloc(sizeof(PDC_Buffer));
	if(buffer == NULL){
		error(PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
	}

	charbuffer = malloc(sizeof(PDC_uchar) * length);
	if(charbuffer == NULL){
		free(buffer);
		error(PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
	}
	buffer->buffer = charbuffer;

	return buffer;
}

#ifdef __cplusplus     
}       
#endif