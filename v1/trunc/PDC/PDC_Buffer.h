/*
 * Copyright (C) 2008  Uwe Br�nen
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

#ifndef __PDC_BUFFER_H__
#define __PDC_BUFFER_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C

	#define INIT_WRITE_BIT_POS 0

	struct str_PDC_Buffer;
	typedef struct str_PDC_Buffer PDC_Buffer;
	typedef enum {END_OF_BUFFER, MORE_DATA_EXPECTED} PDC_buffer_end_state;

	#include "PDC_Exception.h"

	struct str_PDC_Buffer{
		PDC_uchar*				buffer;
		PDC_uint32				length;
		PDC_uint32				read_byte_pos;
		PDC_uint32				write_byte_pos;
		PDC_uint32				read_bit_pos;
		PDC_uint32				write_bit_pos;
		PDC_uint32				save_read_byte_pos;
		PDC_uint32				save_write_byte_pos;
		PDC_uint32				save_read_bit_pos;
		PDC_buffer_end_state	end_state;
	};

	/*
	 *	Length of the buffer
	 */
	PDC_Buffer* new_PDC_Buffer_1(PDC_Exception* exception, PDC_uint32 length);

	/*
	 *	Length of the buffer
	 *
	 *  buffer_size is the number of bytes in buffer that have to be copyed
	 *
	 *  buffer the pointer to the bytes.
	 *
	 */
	PDC_Buffer* new_PDC_Buffer_2(	PDC_Exception* exception,
									PDC_uint32 length,
									PDC_uint32 buffer_size,
									PDC_uchar* buffer);

	/*
	 * Empty Buffer
	 */
	PDC_Buffer* new_PDC_Buffer_3(PDC_Exception* exception);

	/*
	 * Destructor of the PDC_Buffer*
	 */
	PDC_Buffer* delete_PDC_Buffer(	PDC_Exception* exception,
									PDC_Buffer* buffer);

	/*
	 *
	 */
	PDC_Buffer* PDC_Buffer_realloc(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uint32 plus_buffer_length);

	/*
	 *
	 */
	PDC_Buffer* PDC_Buffer_add_byte_1(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uchar byte);

	/*
	 *
	 */
	PDC_Buffer* PDC_Buffer_add_bytes_1(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uchar* byte, PDC_uint numbytes);

	/*
	 *
	 */
	PDC_Buffer* PDC_Buffer_save_state(PDC_Exception* exception, PDC_Buffer* buffer, PDC_Buffer* save_buffer);

	/*
	 *
	 */
	PDC_Buffer* PDC_Buffer_read_uint16(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uint16 *value);

	/*
	 *
	 */
	PDC_Buffer* PDC_Buffer_read_uint32(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uint32 *value);

	/*
	 *
	 */
	PDC_Buffer* PDC_Buffer_read_uint8(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uint8 *value);

	/*
	 *
	 */
	PDC_Buffer* PDC_Buffer_read_uint8_02(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uint8 *value, PDC_uint32 number);

	/*
	 *
	 */
	PDC_Buffer* PDC_Buffer_read_uint8_03(PDC_Exception* exception, PDC_Buffer* buffer, PDC_uint8 *value, PDC_uint32 position);

	/*
	 *
	 */
	PDC_bit PDC_Buffer_get_next_bit(	PDC_Exception* exception,
										PDC_Buffer* buffer);

	/*
	 *
	 */
	void PDC_Buffer_return_bit(	PDC_Exception* exception,
								PDC_Buffer* buffer);

	/*
	 *
	 */
	void PDC_Buffer_push_state(	PDC_Exception* exception,
								PDC_Buffer* buffer);

	/*
	 *
	 */
	void PDC_Buffer_pop_state(	PDC_Exception* exception,
								PDC_Buffer* buffer);

	/*
	 *
	 */
	PDC_Buffer* PDC_Buffer_add_bit_1(	PDC_Exception* exception,
										PDC_Buffer* buffer,
										PDC_bit bit);

	/*
	 *
	 */
	PDC_uint PDC_Buffer_get_number_of_codingpasses(	PDC_Exception* exception,
													PDC_Buffer* buffer);

	/*
	 *
	 */
	PDC_uint PDC_Buffer_get_Lblock_increase(PDC_Exception* exception,
											PDC_Buffer* buffer);

	/*
	 *
	 */
	PDC_uint PDC_Buffer_read_bits(	PDC_Exception* exception,
									PDC_Buffer* buffer,
									PDC_uint number_bits);

	/*
	 *
	 */
	void PDC_Buffer_padding_read(	PDC_Exception* exception,
									PDC_Buffer* buffer);

	/*
	 *
	 */
	void PDC_Buffer_copy_bytes_01(	PDC_Exception* exception,
									PDC_Buffer* buffer_source,
									PDC_Buffer* buffer_destination,
									PDC_uint num_bytes);

STOP_C

#endif
