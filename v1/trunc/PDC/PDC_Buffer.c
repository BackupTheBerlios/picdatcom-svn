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

#ifdef __cplusplus     
extern "C" {         
#endif

#include "PDC_Buffer.h"

PDC_Buffer* new_PDC_Buffer_1(PDC_uint_32 length)
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
		buffer = NULL;
		error(PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
	}
	buffer->buffer = charbuffer;

	return buffer;
}

void delete_PDC_Buffer(PDC_Buffer* buffer)
{
	if(buffer != NULL){
		if(buffer->buffer != NULL){
			free(buffer->buffer);
		}
		free(buffer);
	}
}

/*
 *
 */
PDC_Buffer* PDC_Buffer_realloc(PDC_Buffer* buffer, PDC_uint_32 plus_buffer_length)
{
	PDC_Buffer* return_buffer = buffer;
	PDC_uchar*  new_buffer;
	PDC_uint_32	new_size = buffer->length + plus_buffer_length;
	
	new_buffer = realloc(buffer->buffer, new_size);
	if(new_buffer == NULL){
		return_buffer = NULL;
		error(PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
	}
	return return_buffer;
}

/*
 *
 */
PDC_Buffer* PDC_Buffer_add_byte_1(PDC_Buffer* buffer, PDC_uchar byte)
{
	PDC_Buffer* return_buffer = buffer;
	

	return return_buffer;
}

#ifdef __cplusplus     
}       
#endif