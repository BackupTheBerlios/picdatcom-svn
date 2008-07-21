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
#include "PDC_Parameter.h"
#include "PDC_Tagtree.h"
#include <pthread.h>

void *print_minus(void *data);
void *print_plus(void *data);
void thread_test();
void Arithmetic_entropy_test();
void Tagtree_test();
void showtagtree(PDC_Tagtree* tagtree);

#define TESTSIZE 4400

int main()
{
	Tagtree_test();
	//Arithmetic_entropy_test();
	//thread_test();
	return 0;
}

/*
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

*/

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


void Tagtree_test()
{
	PDC_Exception* exception;
	PDC_Tagtree* tagtree1	= NULL;
	PDC_Tagtree* tagtree2	= NULL;
	PDC_Buffer* buffer		= NULL;
	PDC_uint size_x = 5;
	PDC_uint size_y = 9;
	PDC_uint pos_x, pos_y;

	PDC_int max, test;
	
	max = 0;
	exception = new_PDC_Exception();
	tagtree1 = new_PDC_Tagtree_01(exception, size_x, size_y);
	tagtree2 = new_PDC_Tagtree_01(exception, size_x, size_y);
	buffer = new_PDC_Buffer_1(exception, 50);
	showtagtree(tagtree1);

	for(pos_y = 0; pos_y < size_y; pos_y += 1){
		for(pos_x = 0; pos_x < size_x; pos_x += 1){
			test = rand() % 8;
			if(test > max){
				max = test;
			}
			PDC_Tagtree_set_value(exception, tagtree1, pos_x, pos_y, test);
		}
	}
	
	PDC_Tagtree_create_tree(exception, tagtree1);
	showtagtree(tagtree1);

	for(test = 0; test <= max ; test += 1){
		for(pos_y = 0; pos_y < size_y; pos_y += 1){
			for(pos_x = 0; pos_x < size_x; pos_x += 1){
				PDC_Tagtree_encode_pos(exception, tagtree1, buffer,pos_x, pos_y, test + 1 ); 
			}
		}
	}

	for(test = 0; test <= max; test += 1){
		for(pos_y = 0; pos_y < size_y; pos_y += 1){
			for(pos_x = 0; pos_x < size_x; pos_x += 1){
				PDC_Tagtree_decode_pos(exception, tagtree2, buffer,pos_x, pos_y, test + 1); 
			}
		}
	}
	showtagtree(tagtree2);

}

void showtagtree(PDC_Tagtree* tagtree)
{
	PDC_uint pos, pos_x, pos_y;

	for(pos = 0; pos < tagtree->level; pos += 1){
		printf("\n\n");
		for(pos_y = 0; pos_y < tagtree->size_y[pos]; pos_y += 1){
			for(pos_x = 0; pos_x < tagtree->size_x[pos]; pos_x += 1){
				printf("  %d", tagtree->item[pos][pos_x][pos_y].value );
			}
			printf("\n");
		}
	}


}