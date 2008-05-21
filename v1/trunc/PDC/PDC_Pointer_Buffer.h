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

#ifndef __PDC_POINTER_BUFFER_H__
#define __PDC_POINTER_BUFFER_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C

	struct str_PDC_Pointer_Buffer;
	typedef struct str_PDC_Pointer_Buffer PDC_Pointer_Buffer;

	#include "PDC_Exception.h"

	#define PDC_POINTER_BUFFER_RESIZE 3

	struct str_PDC_Pointer_Buffer{
		PDC_Exception*	exception;
		void**			pointer;
		PDC_uint		last_pointer;
		PDC_uint		size;
		PDC_bool		full;
	};

	/*
	 *
	 */
	PDC_Pointer_Buffer* new_PDC_Pointer_Buffer_01(PDC_uint size);

	/*
	 *
	 */
	PDC_Pointer_Buffer* new_PDC_Pointer_Buffer_02();

	/*
	 *
	 */
	PDC_Pointer_Buffer* delete_PDC_Pointer_Buffer_01(PDC_Pointer_Buffer* buffer);

	/*
	 *
	 */
	void* PDC_Pointer_Buffer_get_pointer(PDC_Pointer_Buffer* buffer, PDC_uint pos);

	/*
	 *
	 */
	PDC_Pointer_Buffer*  PDC_Pointer_Buffer_add_pointer(PDC_Pointer_Buffer* buffer, void* pointer);

STOP_C
#endif