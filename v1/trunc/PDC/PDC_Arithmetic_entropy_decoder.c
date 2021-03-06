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

#include "PDC_Arithmetic_entropy_decoder.h"

START_C

#define MPS_I_LENGTH 19
#define RESIZE_BUFFER 10

/*
extern FILE* DEBUG_FILE;
extern FILE* DEBUG_FILE3;
extern int uwe_count;


unsigned int count = 0;
*/

extern PDC_uint32 PDC_A_Encoder_qe[];
extern PDC_uint32 PDC_A_Encoder_switcher[];
extern PDC_uint32 PDC_A_Encoder_nlps[];
extern PDC_uint32 PDC_A_Encoder_nmps[];


/*
 *	This is the software version see page 151 and 152.
 */
PDC_Arithmetic_entropy_decoder* PDC_Aed_decode_01(	PDC_Exception* exception,
													PDC_Arithmetic_entropy_decoder* decoder,
													PDC_context context,
		 											PDC_Buffer* in_buffer)
{
	PDC_Arithmetic_entropy_decoder* return_decoder = decoder;
	PDC_context		CX;
	PDC_uint32		I_CX;
	PDC_uint32		Qe_I_CX;
	PDC_decision	D;

	PDC_uint32		C;
	PDC_uint32		Chigh;
	PDC_uint32		A;
	PDC_uint32		CT;
	PDC_decision*	MPS;
	PDC_decision	MPS_old;
	PDC_uint32*		I;
	PDC_uint32		I_old;

	PDC_uchar*		buffer;
	PDC_size_t		length, read_byte_pos, read_byte_pos_new, write_byte_pos;
	PDC_uint32		B, B1;

	return_decoder = decoder;

	C		= return_decoder->c_register;
	A		= return_decoder->a_register;
	CT		= return_decoder->CT;
	MPS		= return_decoder->MPS;
	I		= return_decoder->I;
	B		= return_decoder->B;
	Chigh	= C >> 16;

	buffer			= in_buffer->buffer;
	length			= in_buffer->length;
	read_byte_pos	= in_buffer->read_byte_pos;
	write_byte_pos	= in_buffer->write_byte_pos;

	CX		= context;
	I_CX	= I[CX];
	I_old	= I_CX;
	MPS_old	= MPS[CX];
	Qe_I_CX	= PDC_A_Encoder_qe[I_CX];

	return_decoder->decode_state = DECODE_SUCCESFULL;

	/* DECODE */
	A = A - Qe_I_CX;
	if(Chigh < A){
		if((A & 0x8000) == 0){
			/* MPS_EXCHANGE */
			if( A < Qe_I_CX){
				D = 1 - MPS[CX];
				if(PDC_A_Encoder_switcher[I_CX] == 1){
					MPS_old	= MPS[CX];
					MPS[CX] = 1 - MPS[CX];
				}
				I_old = I_CX;
				I_CX = I[CX] = PDC_A_Encoder_nlps[I_CX];
			}else{
				D = MPS[CX];
				I_old = I_CX;
				I_CX = I[CX] = PDC_A_Encoder_nmps[I_CX];
			}
			/* MPS_EXCHANGE END */

			/* RENORMD */
			do{
				if(CT == 0){
					/* BYTEIN */
					if(read_byte_pos < write_byte_pos){
						B1 = buffer[read_byte_pos];
						read_byte_pos_new = read_byte_pos + 1;
					}else if(in_buffer->end_state == END_OF_BUFFER){
						B1 = 0xFF;
						read_byte_pos_new = read_byte_pos;
					}else{
						return_decoder->decode_state = DECODE_BUFFER_EMPTY;
						I[CX]	= I_old;
						MPS[CX]	= MPS_old;
						break;
					}

					if(B == 0xFF){
						if(B1 > 0x8F){
							CT = 8;
						}else{
							read_byte_pos = read_byte_pos_new;
							B = B1;
							C = C + 0xFE00 - (B << 9);
							CT = 7;
						}
					}else{
						read_byte_pos = read_byte_pos_new;
						B = B1;
						C = C + 0xFF00 - (B << 8);
						CT = 8;
					}
					/* BYTEIN END */
				}
				A	= A << 1;
				C	= C << 1;
				CT	= CT - 1;
			}while((A & 0x8000 ) == 0);
			/* RENORMD END */
		}else{
			D = MPS[CX];
		}
	}else{
		Chigh -= A;
		C = (C & 0xFFFF) | (Chigh << 16);
		/* LPS_EXCHANGE */
		if(A < Qe_I_CX){
			A = Qe_I_CX;
			D = MPS[CX];
			I_old = I_CX;
			I_CX = I[CX] = PDC_A_Encoder_nmps[I_CX];
		}else{
			A	= Qe_I_CX;
			D	= 1 - MPS[CX];
			if(PDC_A_Encoder_switcher[I_CX] == 1){
				MPS_old = MPS[CX];
				MPS[CX] = 1 - MPS[CX];
			}
			I_old = I_CX;
			I_CX = I[CX] = PDC_A_Encoder_nlps[I_CX];
		}
		/* LPS_EXCHANGE END */
		/* RENORMD */
		do{
			if(CT == 0){
				/* BYTEIN */
				if(read_byte_pos < write_byte_pos){
					B1 = buffer[read_byte_pos];
					read_byte_pos_new = read_byte_pos + 1;
				}else if(in_buffer->end_state == END_OF_BUFFER){
					B1 = 0xFF;
					read_byte_pos_new = read_byte_pos;
				}else{
					return_decoder->decode_state = DECODE_BUFFER_EMPTY;
					I[CX]	= I_old;
					MPS[CX]	= MPS_old;
					break;
				}

				if(B == 0xFF){
					if(B1 > 0x8F){
						CT = 8;
					}else{
						read_byte_pos = read_byte_pos_new;
						B = B1;
						C = C + 0XFE00 - (B << 9);
						CT = 7;
					}
				}else{
					read_byte_pos = read_byte_pos_new;
					B = B1;
					C = C + 0XFF00 - (B << 8);
					CT = 8;
				}
				/* BYTEIN END */
			}
			A	= A << 1;
			C	= C << 1;
			CT	= CT - 1;
		}while((A & 0x8000 ) == 0);
		/* RENORMD END */
	}
	/* DECODE END */

	if(return_decoder->decode_state == DECODE_SUCCESFULL){
		in_buffer->read_byte_pos	= read_byte_pos;
		return_decoder->c_register	= C;
		return_decoder->a_register	= A;
		return_decoder->CT			= CT;
		return_decoder->B			= B;
		return_decoder->D			= D;

		//PDC_Aed_save_01(exception, decoder, context, in_buffer);
	}
	return return_decoder;
}


/*
 *
 */
PDC_Arithmetic_entropy_decoder* new_PDC_Arithmetic_entropy_decoder(PDC_Exception* exception)
{
	PDC_Arithmetic_entropy_decoder* return_decoder = NULL;

	return_decoder = malloc(sizeof(PDC_Arithmetic_entropy_decoder));
	if(return_decoder == NULL){
		PDC_Exception_error(exception,NULL, PDC_EXCEPTION_OUT_OF_MEMORY	,__LINE__, __FILE__);
		return_decoder->decode_state = INIT_DECODER;
	}

	return return_decoder;
}

/*
 *
 */
PDC_Arithmetic_entropy_decoder* delete_PDC_Arithmetic_entropy_decoder(	PDC_Exception* exception,
																		PDC_Arithmetic_entropy_decoder* decoder)
{
	if(decoder != NULL){
		free(decoder);
	}
	return NULL;
}

/*
 *
 */
PDC_Arithmetic_entropy_decoder* PDC_Aed_initdec_01(	PDC_Exception* exception,
														PDC_Arithmetic_entropy_decoder* decoder,
														PDC_Buffer* in_buffer)
{

	PDC_uint32		C;
	PDC_uint32		A;
	PDC_uint32		CT;

	PDC_uchar*		buffer;
	PDC_size_t		length, read_byte_pos, read_byte_pos_new, write_byte_pos;
	PDC_uint32		B, B1;

	buffer			= in_buffer->buffer;
	length			= in_buffer->length;
	read_byte_pos	= in_buffer->read_byte_pos;
	write_byte_pos	= in_buffer->write_byte_pos;

	decoder->decode_state = DECODER_START;

	if(read_byte_pos < write_byte_pos){
		B				= buffer[read_byte_pos];
		read_byte_pos	+= 1;
		C				= (B ^ 0xFF) << 16;

		/* BYTEIN */
		if(read_byte_pos < write_byte_pos){
			B1 = buffer[read_byte_pos];
			read_byte_pos_new = read_byte_pos + 1;
		}else if(in_buffer->end_state == END_OF_BUFFER){
			B1 = 0xFF;
			read_byte_pos_new = read_byte_pos ;
		}else{
			decoder->decode_state = INIT_DECODER_BUFFER_EMPTY;
		}

		if(decoder->decode_state != INIT_DECODER_BUFFER_EMPTY){
			if(B == 0xFF){
				if(B1 > 0x8F){
					CT = 8;
				}else{
					B = B1;
					read_byte_pos = read_byte_pos_new;
					C = C + 0xFE00 - (B << 9);
					CT = 7;
				}
			}else{
				B = B1;
				read_byte_pos = read_byte_pos_new;
				C = C + 0XFF00 - (B << 8);
				CT = 8;
			}

			/* BYTEIN END */

			C	= C << 7;
			CT	= CT - 7;
			A	= 0x8000;

			in_buffer->read_byte_pos = read_byte_pos;
			decoder->a_register		= A;
			decoder->B				= B;
			decoder->c_register		= C;
			decoder->CT				= CT;
			decoder->decode_state	= DECODE_SUCCESFULL;
		}

	}else{
		decoder->decode_state = INIT_DECODER_BUFFER_EMPTY;
	}

	return decoder;
}

/*
 *
 */
PDC_Arithmetic_entropy_decoder* PDC_Aed_set_I_MPS_01(	PDC_Exception* exception,
														PDC_Arithmetic_entropy_decoder* decoder,
														PDC_decision* default_MPS,
														PDC_uint32* default_I)
{
	PDC_decision*	MPS;
	PDC_uint32*	I;
	PDC_uint32		index;

	MPS = decoder->MPS;
	I	= decoder->I;

	for(index = 0; index < MPS_I_LENGTH; index += 1){
		MPS[index]	= default_MPS[index];
		I[index]	= default_I[index];
	}
	return decoder;
}

struct SAVESTATE
{
	unsigned int a;
	unsigned int c;
	unsigned int count;
	unsigned int context;
	unsigned int MPS[MPS_I_LENGTH];
	unsigned int I[MPS_I_LENGTH];
		
		
};


unsigned int STATECOUNT = 0;
unsigned int DOIT = 1;

void PDC_Aed_save_01(	PDC_Exception* exception,
						PDC_Arithmetic_entropy_decoder* decoder,
						PDC_context context,
						PDC_Buffer* in_buffer)
{
	struct SAVESTATE state;
	FILE * file;
	int i;

	if(DOIT == 0 ){
		state.a			= decoder->a_register;
		state.c			= decoder->c_register;
		state.count		= STATECOUNT;
		state.context	= context;
		for(i = 0; i < MPS_I_LENGTH; i += 1){
			state.MPS[i]	= decoder->MPS[i];
			state.I[i]		= decoder->I[i];
		}
		file = fopen("PDC_decoder", "ab");
		fwrite(&state, sizeof(struct SAVESTATE), 1, file);
		fclose(file);
		STATECOUNT += 1;
	}
	
}

STOP_C
