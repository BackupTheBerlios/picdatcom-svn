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
#include "PDC_Arithmetic_entropy_encoder.h"
#include "PDC_Arithmetic_entropy_decoder.h"
#include <pthread.h>

void *print_minus(void *data);
void *print_plus(void *data);
void thread_test();
void Arithmetic_entropy_test();

#define TESTSIZE 4400

int main()
{
	Arithmetic_entropy_test();
	//thread_test();
	return 0;
}


void Arithmetic_entropy_test()
{
	
	PDC_Arithmetic_entropy_encoder*	encoder;
	PDC_Arithmetic_entropy_decoder*	decoder;
	PDC_Buffer*						buffer1;
	int								i, diff , difff;
	PDC_decision					d1[TESTSIZE];
	PDC_decision					d2[TESTSIZE];
	PDC_context						cx[TESTSIZE];
	PDC_uint32						old_write_byte_pos;
	
	printf("This is the PDC_Arithmetic_entropy_**coder test\n");

	srand(0);
	for(i = 0; i < TESTSIZE; i++){
		cx[i]	= rand() % 19;
		d1[i]	= rand() % 2;
	}
	
	encoder = new_PDC_Arithmetic_entropy_encoder();
	decoder	= new_PDC_Arithmetic_entropy_decoder();
	buffer1	= new_PDC_Buffer_1(0);

	encoder = PDC_Aee_init_01( encoder, PDC_A_Encoder__mps, PDC_A_Encoder__index);
	encoder = PDC_Aee_encode_01( encoder, d1, cx, TESTSIZE,	buffer1);
	encoder = PDC_Aee_flush_01(	encoder, buffer1);

	buffer1->end_state = END_OF_BUFFER;
	decoder = PDC_Aed_set_I_MPS_01(decoder, PDC_A_Encoder__mps, PDC_A_Encoder__index);
	decoder = PDC_Aed_initdec_01(decoder, buffer1);

	old_write_byte_pos = buffer1->write_byte_pos;
	buffer1->write_byte_pos = buffer1->write_byte_pos / 2;
	buffer1->end_state = MORE_DATA_EXPECTED;
	for(i = 0; i < TESTSIZE; i++){
		decoder	= PDC_Aed_decode_01( decoder, cx[i], buffer1);
		if(decoder->decode_state == DECODE_SUCCESFULL){
			d2[i]	= decoder->D;
		}else{
			break;
		}
	}

	buffer1->write_byte_pos	= old_write_byte_pos;
	buffer1->end_state		= END_OF_BUFFER;
	for(; i < TESTSIZE; i++){
		decoder	= PDC_Aed_decode_01( decoder, cx[i], buffer1);
		if(decoder->decode_state == DECODE_SUCCESFULL){
			d2[i]	= decoder->D;
		}else{
			break;
		}
	}

	diff = 0;
	for(i = 0; i < TESTSIZE; i++){
		difff = (int) d1[i] - (int)d2[i];
		if(difff == -1){
			difff = 1;
		}
		if(difff == 1){
			printf("i = %d \n",i);
		}
		diff += difff;
		//printf(" %d  Input %d --> Output %d diff %d\n",i, (int)d1[i], (int)d2[i], (int)d1[i] - (int)d2[i]);
	}
	printf("diff = %d \n", diff);

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