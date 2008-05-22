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

PDC_Buffer* new_PDC_Buffer_1(PDC_uint32 length)
{
	PDC_Buffer* buffer = NULL;
	PDC_uchar*	charbuffer = NULL;
	buffer = malloc(sizeof(PDC_Buffer));
	if(buffer == NULL){
		return NULL;
	}
	buffer->exception	= NULL;
	buffer->buffer		= NULL;	
	
	buffer->exception = new_PDC_Exception();
	if(buffer->exception == NULL){
		delete_PDC_Buffer(buffer);
		return NULL;		
	}	
	

	if(length == 0){
		length = 1;
	}

	charbuffer = malloc(sizeof(PDC_uchar) * length);
	if(charbuffer == NULL){
		delete_PDC_Buffer(buffer);
		return NULL;
	}

	buffer->buffer			= charbuffer;
	buffer->end_state		= MORE_DATA_EXPECTED;
	buffer->read_byte_pos	= 0;
	buffer->write_byte_pos	= 0;
	buffer->length			= length;

	return buffer;
}

/*
 * Empty Buffer
 */
PDC_Buffer* new_PDC_Buffer_3()
{
	PDC_Buffer* buffer = NULL;

	buffer = malloc(sizeof(PDC_Buffer));
	if(buffer == NULL){
		return NULL;
	}	
	buffer->exception	= NULL;
	buffer->buffer		= NULL;	
	buffer->exception = new_PDC_Exception();
	if(buffer->exception == NULL){
		delete_PDC_Buffer(buffer);
		return NULL;		
	}

	buffer->length			= 0;
	buffer->read_byte_pos	= 0;
	buffer->write_byte_pos	= 0;
	buffer->end_state		= MORE_DATA_EXPECTED;

	return buffer;
}

void delete_PDC_Buffer(PDC_Buffer* buffer)
{
	if(buffer != NULL){
		if(buffer->buffer != NULL){
			free(buffer->buffer);
			delete_PDC_Exception(buffer->exception);
		}
		free(buffer);
	}
}

/*
 *
 */
PDC_Buffer* PDC_Buffer_realloc(PDC_Buffer* buffer, PDC_uint32 plus_buffer_length)
{
	PDC_Buffer* return_buffer = buffer;
	PDC_uchar*  new_buffer;
	PDC_uint32	new_size = buffer->length + plus_buffer_length;
	                                   
	new_buffer = realloc(buffer->buffer, sizeof(PDC_uchar) * new_size);
	if(new_buffer == NULL){
		PDC_Exception_error(buffer->exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
	}else{
		return_buffer->length = new_size;
		return_buffer->buffer = new_buffer;
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

/*
 *
 */
PDC_Buffer* PDC_Buffer_add_bytes_1(PDC_Buffer* buffer, PDC_uchar* byte, PDC_uint numbytes)
{
	PDC_uint32	plus_length, i, i2;
	PDC_uchar*	data;
	if(buffer->write_byte_pos + numbytes > buffer->length){
		plus_length = buffer->write_byte_pos + numbytes - buffer->length;
		plus_length += 1024;

		buffer =  PDC_Buffer_realloc(buffer, plus_length);
		if(buffer->exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return buffer;
		}
	}
	
	data = buffer->buffer;
	for(i = 0, i2 = buffer->write_byte_pos; i < numbytes; i++, i2++){
		data[i2] = byte[i];
	}
	buffer->write_byte_pos = i2;
	return buffer;
}

/*
 *
 */
PDC_Buffer* PDC_Buffer_save_state(PDC_Buffer* buffer, PDC_Buffer* save_buffer)
{
	
	save_buffer->read_byte_pos	= buffer->read_byte_pos;
	save_buffer->write_byte_pos	= buffer->write_byte_pos;

	return buffer;
}



PDC_Buffer* PDC_Buffer_read_uint16(PDC_Buffer* buffer, PDC_uint16 *value)
{
	PDC_uint16 temp_value = 0;
	*value = 0;

	if(buffer->read_byte_pos + 2 < buffer->write_byte_pos){
		temp_value = buffer->buffer[buffer->read_byte_pos];
		buffer->read_byte_pos += 1;
		*value = temp_value << 8;

		temp_value = buffer->buffer[buffer->read_byte_pos];
		buffer->read_byte_pos += 1;
		*value  |= temp_value;
		


	}else{
		PDC_Exception_error(buffer->exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return buffer;
	}

	return buffer;
}


/*
 *
 */
PDC_Buffer* PDC_Buffer_read_uint32(PDC_Buffer* buffer, PDC_uint32 *value)
{
	PDC_uint32 temp_value = 0;
	*value = 0;

	if(buffer->read_byte_pos + 4 < buffer->write_byte_pos){
		temp_value = buffer->buffer[buffer->read_byte_pos];
		buffer->read_byte_pos += 1;
		*value = temp_value << 24;

		temp_value = buffer->buffer[buffer->read_byte_pos];
		buffer->read_byte_pos += 1;
		*value  |= temp_value << 16;
		
		temp_value = buffer->buffer[buffer->read_byte_pos];
		buffer->read_byte_pos += 1;
		*value  |= temp_value << 8;

		temp_value = buffer->buffer[buffer->read_byte_pos];
		buffer->read_byte_pos += 1;
		*value  |= temp_value;

	}else{
		PDC_Exception_error(buffer->exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return buffer;
	}

	return buffer;
}

/*
 *
 */
PDC_Buffer* PDC_Buffer_read_uint8(PDC_Buffer* buffer, PDC_uint8 *value)
{

	PDC_uint8 temp_value = 0;
	*value = 0;

	if(buffer->read_byte_pos + 1 < buffer->write_byte_pos){
		temp_value = buffer->buffer[buffer->read_byte_pos];
		buffer->read_byte_pos += 1;
		*value = temp_value;		

	}else{
		PDC_Exception_error(buffer->exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return buffer;
	}

	return buffer;
}

#ifdef __cplusplus     
}       
#endif