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

PDC_Buffer* new_PDC_Buffer_1(PDC_Exception* exception, PDC_uint32 length)
{
	PDC_Buffer* buffer = NULL;
	PDC_uchar*	charbuffer = NULL;
	buffer = malloc(sizeof(PDC_Buffer));
	if(buffer == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	buffer->buffer		= NULL;

	if(length == 0){
		length = 1;
	}

	charbuffer = malloc(sizeof(PDC_uchar) * length);
	if(charbuffer == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		delete_PDC_Buffer(exception, buffer);
		return NULL;
	}

	buffer->buffer			= charbuffer;
	buffer->end_state		= MORE_DATA_EXPECTED;
	buffer->read_byte_pos	= 0;
	buffer->write_byte_pos	= 0;
	buffer->length			= length;
	buffer->read_bit_pos	= 0;
	buffer->write_bit_pos	= INIT_WRITE_BIT_POS;

	return buffer;
}

/*
 * Empty Buffer
 */
PDC_Buffer* new_PDC_Buffer_3(PDC_Exception* exception)
{
	PDC_Buffer* buffer = NULL;

	buffer = malloc(sizeof(PDC_Buffer));
	if(buffer == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	buffer->buffer			= NULL;
	buffer->length			= 0;
	buffer->read_byte_pos	= 0;
	buffer->write_byte_pos	= 0;
	buffer->read_bit_pos	= 0;
	buffer->end_state		= MORE_DATA_EXPECTED;
	buffer->write_bit_pos	= INIT_WRITE_BIT_POS;

	return buffer;
}

PDC_Buffer* delete_PDC_Buffer(PDC_Exception* exception, PDC_Buffer* buffer)
{
	if(buffer != NULL){
		if(buffer->buffer != NULL){
			free(buffer->buffer);
		}
		free(buffer);
	}
	return NULL;
}

/*
 *
 */
PDC_Buffer* PDC_Buffer_realloc(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uint32 plus_buffer_length)
{
	PDC_Buffer* return_buffer = buffer;
	PDC_uchar*  new_buffer;
	PDC_uint32	new_size = buffer->length + plus_buffer_length;

	new_buffer = realloc(buffer->buffer, sizeof(PDC_uchar) * new_size);
	if(new_buffer == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
	}else{
		return_buffer->length = new_size;
		return_buffer->buffer = new_buffer;
	}
	return return_buffer;
}

/*
 *
 */
PDC_Buffer* PDC_Buffer_add_byte_1(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uchar byte)
{
	PDC_uint32	plus_length;
	PDC_Buffer* return_buffer = buffer;

	if(return_buffer->write_byte_pos + 1 > return_buffer->length){
		plus_length = return_buffer->write_byte_pos + 1 - return_buffer->length;
		plus_length += 1024;

		return_buffer =  PDC_Buffer_realloc(exception, return_buffer, plus_length);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return return_buffer;
		}
	}

	return_buffer->buffer[return_buffer->write_byte_pos]	= byte;
	return_buffer->write_byte_pos							+= 1;

	return return_buffer;
}

/*
 *
 */
PDC_Buffer* PDC_Buffer_add_bytes_1(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uchar* byte, PDC_uint numbytes)
{
	PDC_uint32	plus_length, i, i2;
	PDC_uchar*	data;
	if(buffer->write_byte_pos + numbytes > buffer->length){
		plus_length = buffer->write_byte_pos + numbytes - buffer->length;
		plus_length += 1024;

		buffer =  PDC_Buffer_realloc(exception, buffer, plus_length);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
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
PDC_Buffer* PDC_Buffer_save_state(PDC_Exception* exception, PDC_Buffer* buffer, PDC_Buffer* save_buffer)
{

	save_buffer->read_byte_pos	= buffer->read_byte_pos;
	save_buffer->write_byte_pos	= buffer->write_byte_pos;

	return buffer;
}



PDC_Buffer* PDC_Buffer_read_uint16(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uint16 *value)
{
	PDC_uint16 temp_value = 0;
	*value = 0;

	if(buffer->read_byte_pos + 1 < buffer->write_byte_pos){
		temp_value = buffer->buffer[buffer->read_byte_pos];
		buffer->read_byte_pos += 1;
		*value = temp_value << 8;

		temp_value = buffer->buffer[buffer->read_byte_pos];
		buffer->read_byte_pos += 1;
		*value  |= temp_value;



	}else{		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return buffer;
	}

	return buffer;
}


/*
 *
 */
PDC_Buffer* PDC_Buffer_read_uint32(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uint32 *value)
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
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return buffer;
	}

	return buffer;
}

/*
 *
 */
PDC_Buffer* PDC_Buffer_read_uint8(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uint8 *value)
{

	PDC_uint8 temp_value = 0;
	*value = 0;

	if(buffer->read_byte_pos + 1 < buffer->write_byte_pos){
		temp_value = buffer->buffer[buffer->read_byte_pos];
		buffer->read_byte_pos += 1;
		*value = temp_value;

	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return buffer;
	}

	return buffer;
}

/*
 *
 */
PDC_Buffer* PDC_Buffer_read_uint8_02(PDC_Exception* exception,
									 PDC_Buffer* buffer,
									 PDC_uint8 *value,
									 PDC_uint32 number)
{
	PDC_uint32	pos, pos_end, pos1;
	PDC_uint8*	temp_buffer;

	if(buffer->read_byte_pos + number > buffer->write_byte_pos){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return buffer;
	}

	pos = buffer->read_byte_pos;
	pos_end = pos + number;
	temp_buffer = buffer->buffer;
	for( pos1 = 0; pos < pos_end; pos += 1, pos1 += 1){
		value[pos1] = temp_buffer[pos];
	}
	buffer->read_byte_pos = pos_end;
	return buffer;
}


/*
 *
 */
PDC_Buffer* PDC_Buffer_read_uint8_03(	PDC_Exception* exception,
										PDC_Buffer* buffer,
										PDC_uint8 *value,
										PDC_uint32 position)
{
	if(position > buffer->write_byte_pos){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return buffer;
	}
	*value = buffer->buffer[position];

	return buffer;
}

/*
 *
 */
PDC_bit PDC_Buffer_get_next_bit(	PDC_Exception* exception,
									PDC_Buffer* buffer)
{
	PDC_bit back = 0;

	if(buffer->read_byte_pos < buffer->write_byte_pos){
		if(buffer->read_bit_pos < 8){
			back = (buffer->buffer[buffer->read_byte_pos] >> (7 - buffer->read_bit_pos)) & 1;
			buffer->read_bit_pos += 1;
		}else{
			if(buffer->buffer[buffer->read_byte_pos] == 0xFF){
				buffer->read_bit_pos = 1;
			}else{
				buffer->read_bit_pos = 0;
			}
			buffer->read_byte_pos += 1;
			if(buffer->read_byte_pos < buffer->write_byte_pos){
				back = (buffer->buffer[buffer->read_byte_pos] >> (7 - buffer->read_bit_pos)) & 1;
				buffer->read_bit_pos += 1;
			}else{
				if(buffer->write_bit_pos > buffer->read_bit_pos){
					back = buffer->buffer[buffer->read_byte_pos];
					back = (back >> (7 - buffer->read_bit_pos)) & 1;
					buffer->read_bit_pos += 1;
				}else if(buffer->end_state == MORE_DATA_EXPECTED){
					back = 0;
					PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
				}else{
					back = 0;
					PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
				}
			}
		}
	}else{

		if(buffer->write_bit_pos > buffer->read_bit_pos){
			back = buffer->buffer[buffer->read_byte_pos];
			back = (back >> (7 - buffer->read_bit_pos)) & 1;
			buffer->read_bit_pos += 1;
		}else if(buffer->end_state == MORE_DATA_EXPECTED){
			back = 0;
			PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		}else{
			back = 0;
			PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		}
	}
	return back;
}

/*
 *
 */
void PDC_Buffer_push_state(	PDC_Exception* exception,
							PDC_Buffer* buffer)
{
	buffer->save_read_bit_pos	= buffer->read_bit_pos;
	buffer->save_read_byte_pos	= buffer->read_byte_pos;
	buffer->save_write_byte_pos	= buffer->write_byte_pos;
}

/*
 *
 */
void PDC_Buffer_pop_state(	PDC_Exception* exception,
							PDC_Buffer* buffer)
{
	buffer->read_bit_pos	= buffer->save_read_bit_pos;
	buffer->read_byte_pos	= buffer->save_read_byte_pos;
	buffer->write_byte_pos	= buffer->save_write_byte_pos;
}

/*
 *
 */
PDC_Buffer* PDC_Buffer_add_bit_1(	PDC_Exception* exception,
									PDC_Buffer* buffer,
									PDC_bit bit)
{
	PDC_uint plus_length = 10;
	PDC_uint8 mask = 0xFF;
	PDC_uint8 byte;


	if(buffer->write_bit_pos > 7){
		buffer->write_bit_pos	= INIT_WRITE_BIT_POS;
		buffer->write_byte_pos	+= 1;
	}

	if(buffer->write_byte_pos >= buffer->length){
		buffer =  PDC_Buffer_realloc(exception, buffer, plus_length);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return buffer;
		}
	}
	byte = buffer->buffer[buffer->write_byte_pos];
	mask <<= (8 - buffer->write_bit_pos);
	byte &= mask;
	if(bit != 0){
		mask = 1 << (7 - buffer->write_bit_pos) ;
		byte |= mask;
	}
	buffer->buffer[buffer->write_byte_pos] = byte;
	buffer->write_bit_pos += 1;
	return buffer;
}

/*
 *
 */
PDC_uint PDC_Buffer_get_number_of_codingpasses(	PDC_Exception* exception,
												PDC_Buffer* buffer)
{
	PDC_uint	value = 0;
	PDC_bit		bit;
	PDC_uint	pos;

	bit = PDC_Buffer_get_next_bit(exception, buffer);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return 0;
	}
	if(bit == 0){
		return 1;
	}else{
		value = 1;
		bit = PDC_Buffer_get_next_bit(exception, buffer);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return 0;
		}
		if(bit == 0){
			return 2;
		}else{
			value = 0;
			for(pos = 0; pos < 2; pos += 1){
				bit = PDC_Buffer_get_next_bit(exception, buffer);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return 0;
				}
				value |= bit <<( 1 - pos);
			}
			if(value != 3){
				return value + 3;
			}else{
				value = 0;
				for(pos = 0; pos < 5; pos += 1){
					bit = PDC_Buffer_get_next_bit(exception, buffer);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						return 0;
					}
					value |= bit <<( 4 - pos);
				}
				if(value != 31){
					return value + 6;
				}else{
					value = 0;
					for(pos = 0; pos < 8; pos += 1){
						bit = PDC_Buffer_get_next_bit(exception, buffer);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							return 0;
						}
						value |= bit <<( 7 - pos);
					}
					return value + 37;
				}
			}
		}
	}
}

/*
 *
 */
PDC_uint PDC_Buffer_get_Lblock_increase(PDC_Exception* exception,
										PDC_Buffer* buffer)
{
	PDC_uint	back = 0;
	PDC_bit		bit;

	do{
		bit = PDC_Buffer_get_next_bit(exception, buffer);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return 0;
		}
		if(bit != 0){
			back += 1;
		}
	}while(bit != 0);

	return back;
}

/*
 *
 */
PDC_uint PDC_Buffer_read_bits(	PDC_Exception* exception,
								PDC_Buffer* buffer,
								PDC_uint number_bits)
{
	//PDC_uint number_of_bits = number_bits;
	PDC_uint bit_pos;
	PDC_bit bit;

	PDC_uint result = 0;
	if(number_bits > 32){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_FALSE_SYMBOL, __LINE__, __FILE__);
		return 0;
	}

	for(bit_pos = 0; bit_pos < number_bits; bit_pos += 1){
		bit = PDC_Buffer_get_next_bit(exception, buffer);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return 0;
		}
		result <<= 1;
		if(bit != 0){
			result |= 1;
		}
	}

	return result;
}

/*
 *
 */
void PDC_Buffer_padding_read(	PDC_Exception* exception,
								PDC_Buffer* buffer)
{
	if(buffer->read_bit_pos != 0){
		buffer->read_byte_pos	+= 1;
		buffer->read_bit_pos	= 0;
	}
}

/*
 *
 */
void PDC_Buffer_copy_bytes_01(	PDC_Exception* exception,
								PDC_Buffer* buffer_source,
								PDC_Buffer* buffer_destination,
								PDC_uint num_bytes)
{
	PDC_uint	length_add, read_pos, write_pos, read_end;
	PDC_uchar*	source, *destination;
	if(buffer_source->read_byte_pos + num_bytes < buffer_source->write_byte_pos){
		if(buffer_destination->write_byte_pos + num_bytes >= buffer_destination->length){
			length_add = buffer_destination->write_byte_pos + num_bytes + 5 - buffer_destination->length;
			PDC_Buffer_realloc(exception, buffer_destination, length_add);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return;
			}
		}
		source		= buffer_source->buffer;
		destination	= buffer_destination->buffer;
		read_end = buffer_source->read_byte_pos + num_bytes;
		for(read_pos = buffer_source->read_byte_pos, write_pos = buffer_destination->write_byte_pos; read_pos < read_end; read_pos += 1, write_pos += 1){
			destination[write_pos] = source[read_pos];
		}
		buffer_source->read_byte_pos		= read_pos;
		buffer_destination->write_byte_pos	= write_pos;
	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return;
	}

}

#ifdef __cplusplus
}
#endif
