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

#ifndef __PDC_EXCEPTION_H__
#define __PDC_EXCEPTION_H__

#include "PDC_Parameter.h"

START_C

struct str_PDC_Exception;
typedef struct str_PDC_Exception PDC_Exception;

	typedef enum{	PDC_EXCEPTION_NO_EXCEPTION				= 0,
					PDC_EXCEPTION_OUT_OF_MEMORY				= 1,
					PDC_EXCEPTION_NULL_POINTER				= 2,
					PDC_EXCEPTION_OUT_OF_SIZE				= 3,
					PDC_EXCEPTION_OUT_OF_RANGE				= 4,
					PDC_EXCEPTION_NO_NULLPOINTER_ALLOWED	= 5,
					PDC_EXCEPTION_NO_CODE_FOUND				= 6,
					PDC_EXCEPTION_FALSE_SYMBOL				= 7}PDC_EXCEPTION_TYPES;	


	#define MAX_NUMBER_OF_EXCEPTION 10

	struct str_PDC_Exception 
	{

		PDC_Exception* last_exception;

		/*
		 *	With PDC_error_code[] it describe the exception in words.
		 */
		PDC_EXCEPTION_TYPES	code;

		/*
		 * The line where the exception occur.
		 */
		unsigned int	line;

		/*
		 * The file where the exception occur.
		 */
		char			file[200];

	};


	/*
	 *
	 */
	PDC_Exception* new_PDC_Exception();

	/*
	 *
	 */
	void delete_PDC_Exception(PDC_Exception* exception);


	/*
	 *
	 */
	void PDC_Exception_unset_exception(PDC_Exception* exception);

	/*
	 * 
	 */
	PDC_Exception* PDC_Exception_error(	PDC_Exception* exception,
										PDC_Exception* last_exception, 
										const PDC_EXCEPTION_TYPES code, 
										const unsigned int line, 
										const char* file);
	

STOP_C
#endif

