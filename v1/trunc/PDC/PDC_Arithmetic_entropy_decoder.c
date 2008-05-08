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

extern PDC_uint_32 PDC_A_Encoder_qe[];
extern PDC_uint_32 PDC_A_Encoder_switcher[];
extern PDC_uint_32 PDC_A_Encoder_nlps[];
extern PDC_uint_32 PDC_A_Encoder_nmps[];


/*
 *	This is the software version see page 151 and 152.
 */
PDC_Arithmetic_entropy_decoder* PDC_Aed_decode_01(	PDC_Arithmetic_entropy_decoder* decoder,
													PDC_context context,
		 											PDC_Buffer* in_buffer)
{
	PDC_Arithmetic_entropy_decoder* return_decoder = decoder;
	PDC_context		CX;
	PDC_uint_32		I_CX;
	PDC_uint_32		Qe_I_CX;
	PDC_decision	D;

	PDC_uint_32		C;
	PDC_uint_32		Chigh;
	PDC_uint_32		A;
	PDC_uint_32		CT;
	PDC_decision*	MPS;
	PDC_decision	MPS_old;
	PDC_uint_32*	I;
	PDC_uint_32		I_old;

	PDC_uchar*		buffer;
	PDC_uint_32		length;
	PDC_uint_32		read_byte_pos, read_byte_pos_new;
	PDC_uint_32		write_byte_pos;
	PDC_uint_32		B, B1;

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
						C = C + 0XFF00 - (B << 9);
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
	}
	return return_decoder;
}


/*
 *
 */
PDC_Arithmetic_entropy_decoder* new_PDC_Arithmetic_entropy_decoder()
{
	PDC_Arithmetic_entropy_decoder* return_decoder = NULL;

	return_decoder = malloc(sizeof(PDC_Arithmetic_entropy_decoder));
	if(return_decoder != NULL){
		return_decoder->decode_state = INIT_DECODER;
	}
	return return_decoder;
}

/*
 *
 */
PDC_Arithmetic_entropy_decoder* delete_PDC_Arithmetic_entropy_decoder(PDC_Arithmetic_entropy_decoder* decoder)
{
	free(decoder);
	return NULL;
}

/*
 *
 */
PDC_Arithmetic_entropy_decoder* PDC_Aed_initdec_01(	PDC_Arithmetic_entropy_decoder* decoder,
													PDC_Buffer* in_buffer)
{

	PDC_uint_32		C;
	PDC_uint_32		A;
	PDC_uint_32		CT;

	PDC_uchar*		buffer;
	PDC_uint_32		length;
	PDC_uint_32		read_byte_pos, read_byte_pos_new;
	PDC_uint_32		write_byte_pos;
	PDC_uint_32		B, B1;	

	buffer			= in_buffer->buffer;
	length			= in_buffer->length;
	read_byte_pos	= in_buffer->read_byte_pos;
	write_byte_pos	= in_buffer->write_byte_pos;

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
					C = C + 0xFF00 - (B << 9);
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
PDC_Arithmetic_entropy_decoder* PDC_Aed_set_I_MPS_01(	PDC_Arithmetic_entropy_decoder* decoder,
														PDC_decision* default_MPS,
														PDC_uint_32* default_I)
{
	PDC_decision*	MPS;
	PDC_uint_32*	I;
	PDC_uint_32		index;

	MPS = decoder->MPS;
	I	= decoder->I;

	for(index = 0; index < MPS_I_LENGTH; index += 1){
		MPS[index]	= default_MPS[index];
		I[index]	= default_I[index];
	}
	return decoder;
}
STOP_C