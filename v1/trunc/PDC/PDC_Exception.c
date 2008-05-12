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

#include "PDC_Exception.h"
#include <string.h>
#include <stdio.h>
#include <pthread.h>

char PDC_error_code[][20]	= {"No Error", "Out of memory", "NULL Pointer", "out_size > maxSize " };
PDC_Exception exception[]	= {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
unsigned int exception_pos	= 0;


pthread_mutex_t exception_mutex =	PTHREAD_MUTEX_INITIALIZER;


int error(const PDC_EXCEPTION_TYPES code, const unsigned int line, const char* file)
{
	int back = 0;
	pthread_mutex_lock(&exception_mutex);
	if(exception_pos < MAX_NUMBER_OF_EXCEPTION){
		exception[exception_pos].code = code;
		exception[exception_pos].line = line;
		strcpy(exception[exception_pos].file, file);
		exception_pos++;
	}else{
		back = 1;
	}
	pthread_mutex_unlock(&exception_mutex);
	return back;
}

int print_errors()
{
	int back = 0;
	unsigned int pos;

	for(pos = 0; pos < exception_pos; pos++){
		printf(	"Exception in file %s on line %d description %s \n",	
				exception[pos].file, 
				exception[pos].line, 
				PDC_error_code[exception[pos].code]);

	}
	return back;
}