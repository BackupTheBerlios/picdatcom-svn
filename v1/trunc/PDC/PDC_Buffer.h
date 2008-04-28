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

#ifndef __PDC_BUFFER_H__
#define __PDC_BUFFER_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C

	struct str_PDC_Buffer;
	typedef struct str_PDC_Buffer PDC_Buffer;

	#include "PDC_Exception.h"

	struct str_PDC_Buffer{
		PDC_uchar*  buffer;
		PDC_uint_32	length;
		PDC_uint_32	read_byte_pos;
		PDC_uint_32	write_byte_pos;
	};

	/*
	 *	Length of the buffer
	 */
	PDC_Buffer* new_PDC_Buffer_1(	PDC_uint_32 length);

	/*
	 *	Length of the buffer
	 *
	 *  buffer_size is the number of bytes in buffer that have to be copyed
	 *
	 *  buffer the pointer to the bytes.
	 *
	 */
	PDC_Buffer* new_PDC_Buffer_2(	PDC_uint_32 length,
									PDC_uint_32 buffer_size,
									PDC_uchar* buffer);

	/*
	 * Destructor of the PDC_Buffer*
	 */
	void delete_PDC_Buffer(PDC_Buffer* buffer);

	/*
	 *
	 */
	PDC_Buffer* PDC_Buffer_realloc(PDC_Buffer* buffer, PDC_uint_32 plus_buffer_length);
	
	/*
	 *
	 */
	PDC_Buffer* PDC_Buffer_add_byte_1(PDC_Buffer* buffer, PDC_uchar byte);


STOP_C

#endif
