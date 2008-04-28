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

#include <stdio.h>
#include "PDC_Exception.h"
#include <pthread.h>

void *print_minus(void *data);
void *print_plus(void *data);
void thread_test();

int main()
{
	printf("This is the PDC_Buffer test\n");
	
	error(PDC_EXCEPTION_OUT_OF_MEMORY	,__LINE__,__FILE__);
	error(PDC_EXCEPTION_NO_EXCEPTION	,__LINE__,__FILE__);

	print_errors();

	thread_test();
	return 0;
}


void thread_test()
{
	pthread_t thread_id1;
	pthread_t thread_id2;

	pthread_create(&thread_id1,NULL, &print_minus, NULL);
	pthread_create(&thread_id2,NULL, &print_plus, NULL);
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
}

void *print_minus(void *data)
{
	int run;
	printf("Gestarteter Threid id = %d \n",(int)(pthread_self().p));
	for(run = 0; run < 8; run++){
		printf("Minus \n");
	}
	return NULL;
}

void *print_plus(void *data)
{
	int run;
	printf("Gestarteter Threid id = %d \n",(int)(pthread_self().p));
	for(run = 0; run < 8; run++){
		printf("Plus \n");
	}
	return NULL;
}