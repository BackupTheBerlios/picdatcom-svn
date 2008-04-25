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

#ifndef __PDC_BUFFER_H__
#define __PDC_BUFFER_H__

#ifdef __cplusplus     
extern "C" {         
#endif

	struct str_PDC_Buffer;
	typedef struct str_PDC_Buffer PDC_Buffer;

	#include "PDC_Parameter.h"
	#include "PDC_Exception.h"

	struct str_PDC_Buffer{
		PDC_uchar*  buffer;
		PDC_uint	length;
		PDC_uint	read_byte_pos;
		PDC_uint	write_byte_pos;
	};

	/*
	 *	Length of the buffer
	 */
	PDC_Buffer* new_PDC_Buffer_1(PDC_uint length);

	/*
	 *	Length of the buffer
	 *
	 *  buffer_size is the number of bytes in buffer that have to be copyed
	 *
	 *  buffer the pointer to the bytes.
	 *
	 */
	PDC_Buffer* new_PDC_Buffer_2(	PDC_uint length,
									PDC_uint buffer_size;
									PDC_uchar* buffer);

	/*
	 * Destructor of the PDC_Buffer*
	 */
	void delete_PDC_Buffer(PDC_Buffer* buffer);
	

#ifdef __cplusplus     
}         
#endif

#endif
