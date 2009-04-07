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

#include "PDC_Exception.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

char PDC_error_code[][25]	= {	"No Error", "Out of memory", "NULL Pointer", "out_size > maxSize ", "Out of Range.",
								"NULL-Pointer not allowed", "No code found", "False symbol no valid jpc",
								"Unkow code", "Decoderexception"};
PDC_Exception exception[]	= {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
unsigned int exception_pos	= 0;


pthread_mutex_t exception_mutex =	PTHREAD_MUTEX_INITIALIZER;


/*
 *
 */
DLL PDC_Exception* new_PDC_Exception()
{
	PDC_Exception* exception = NULL;

	exception = malloc(sizeof(PDC_Exception));

	if(exception == NULL){
		return NULL;
	}

	exception->code = PDC_EXCEPTION_NO_EXCEPTION;
	return exception;
}

/*
 *
 */
void delete_PDC_Exception(PDC_Exception* exception)
{
	if(exception != NULL){
		free(exception);
	}
}


PDC_Exception*  PDC_Exception_error(	PDC_Exception* exception,
										PDC_Exception* last_exception,
										const PDC_EXCEPTION_TYPES code,
										const unsigned int line,
										const char* file)
{

	pthread_mutex_lock(&exception_mutex);

	if(exception->code == PDC_EXCEPTION_NO_EXCEPTION){
		exception->code = code;
		exception->line = line;
		strcpy(exception->file, file);
		exception->last_exception = last_exception;
	}

	pthread_mutex_unlock(&exception_mutex);
	return exception;
}

/*
 *
 */
void PDC_Exception_unset_exception(PDC_Exception* exception)
{
	if(exception->last_exception != NULL){
		PDC_Exception_unset_exception(exception->last_exception);
	}
	exception->code				= PDC_EXCEPTION_NO_EXCEPTION;
	exception->last_exception	= NULL;
}
