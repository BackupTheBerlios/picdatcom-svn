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

#include "PDC_Pointer_Buffer.h"

START_C

/*
 *
 */
PDC_Pointer_Buffer* new_PDC_Pointer_Buffer_01(PDC_Exception* exception, PDC_uint size)
{
	PDC_Pointer_Buffer* buffer;

	buffer = malloc(sizeof(PDC_Pointer_Buffer));
	if(buffer == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	buffer->pointer		= NULL;

	buffer->pointer = malloc(sizeof(void*) * size);
	if(buffer->pointer == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		delete_PDC_Pointer_Buffer_01(exception, buffer);
		return NULL;
	}

	buffer->last_pointer	= 0;
	buffer->size			= size;
	buffer->full			= PDC_false;
	return buffer;
}

/*
 *
 */
PDC_Pointer_Buffer* new_PDC_Pointer_Buffer_02(PDC_Exception* exception )
{
	return new_PDC_Pointer_Buffer_01(exception, PDC_POINTER_BUFFER_RESIZE);
}


/*
 *
 */
PDC_Pointer_Buffer* delete_PDC_Pointer_Buffer_01(PDC_Exception* exception,  PDC_Pointer_Buffer* buffer)
{
	if(buffer != NULL){
		if(buffer->pointer != NULL){
			free(buffer->pointer);
		}
		free(buffer);
	}
	return NULL;
}

/*
 *
 */
void* PDC_Pointer_Buffer_get_pointer(PDC_Exception* exception, PDC_Pointer_Buffer* buffer, PDC_uint pos)
{
	
	if(buffer->full && buffer->last_pointer >= pos){
		return buffer->pointer[pos];
	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return NULL;
	}
}

/*
 *
 */
PDC_Pointer_Buffer* PDC_Pointer_Buffer_add_pointer(PDC_Exception* exception, PDC_Pointer_Buffer* buffer, void* pointer)
{
	PDC_uint	new_size;
	void**		pointer1;

	
	if(buffer->last_pointer + 1 >= buffer->size){
		new_size = buffer->size + PDC_POINTER_BUFFER_RESIZE;	
		pointer1 = realloc(buffer->pointer, sizeof(void*) * new_size);
		if(pointer1 == NULL){
			PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
			return buffer;
		}
		buffer->pointer	= pointer1;
		buffer->size	= new_size;
	}

	if(buffer->full){
		buffer->last_pointer += 1;
		buffer->pointer[buffer->last_pointer] = pointer;
	}else{
		buffer->pointer[0]		= pointer;
		buffer->last_pointer	= 0;	
		buffer->full			= PDC_true;
	}

	return buffer;
}


/*
 *
 */
void*  PDC_Pointer_Buffer_get_next(PDC_Exception* exception, PDC_Pointer_Buffer* buffer)
{
	void* pointer = NULL;
	if(buffer->pos <= buffer->last_pointer){
		pointer = buffer->pointer[buffer->pos];
		buffer->pos += 1;
	}

	return pointer;
}

/*
 *
 */
void  PDC_Pointer_Buffer_set_start(PDC_Exception* exception, PDC_Pointer_Buffer* buffer)
{
	buffer->pos = 0;
}

STOP_C


