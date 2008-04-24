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

#ifndef __PDC_EXCEPTION_H__
#define __PDC_EXCEPTION_H__

#ifdef __cplusplus     
extern "C" {         
#endif

#define MAX_NUMBER_OF_EXCEPTION 10

typedef enum{	PDC_EXCEPTION_NO_EXCEPTION	= 0,
				PDC_EXCEPTION_OUT_OF_MEMORY	= 1}PDC_EXCEPTION_TYPES;	

typedef struct 
{
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

}PDC_Exception;



int error(const PDC_EXCEPTION_TYPES code, const unsigned int line, const char* file);
int print_errors();

#ifdef __cplusplus     
}         
#endif

#endif

