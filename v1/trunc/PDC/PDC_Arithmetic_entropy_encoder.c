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

#include "PDC_Arithmetic_entropy_encoder.h"

START_C

PDC_uint_32 PDC_A_Encoder_length = 19;

PDC_uint_32 PDC_A_Encoder__index[] = {	
						46, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0};

PDC_decision PDC_A_Encoder__mps[] = {	
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0};

PDC_uint_32 PDC_A_Encoder_qe[] = {
						0x5601, 0x3401, 0x1801, 0x0ac1, 0x0521, 0x0221, 0x5601,
						0x5401, 0x4801, 0x3801, 0x3001, 0x2401, 0x1c01, 0x1601, 
						0x5601, 0x5401, 0x5101, 0x4801, 0x3801, 0x3401, 0x3001,
						0x2801, 0x2401, 0x2201, 0x1c01, 0x1801, 0x1601, 0x1401,
						0x1201, 0x1101, 0x0ac1, 0x09c1, 0x08a1, 0x0521, 0x0441,
						0x02a1, 0x0221, 0x0141, 0x0111, 0x0085, 0x0049, 0x0025,
						0x0015, 0x0009, 0x0005, 0x0001, 0x5601 };


PDC_uint_32 PDC_A_Encoder_nmps[] = {	
						1 , 2, 3, 4, 5,38, 7, 8, 9,10,11,12,13,29,15,16,17,
						18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
						35,36,37,38,39,40,41,42,43,44,45,45,46 };

PDC_uint_32 PDC_A_Encoder_nlps[] = {	
						1 , 6, 9,12,29,33, 6,14,14,14,17,18,20,21,14,14,15,
						16,17,18,19,19,20,21,22,23,24,25,26,27,28,29,30,31,
						32,33,34,35,36,37,38,39,40,41,42,43,46 };

PDC_uint_32 PDC_A_Encoder_switcher[] = {	
						1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };


/*
 *
 */
PDC_Arithmetic_entropy_encoder* new_PDC_Arithmetic_entropy_encoder()
{
	PDC_Arithmetic_entropy_encoder* return_encoder = NULL;

	return_encoder = malloc(sizeof(PDC_Arithmetic_entropy_encoder));
	if(return_encoder == NULL){
		error(PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
	}
	return return_encoder;
}

/*
 *
 */
PDC_Arithmetic_entropy_encoder* delete_PDC_Arithmetic_entropy_encoder(PDC_Arithmetic_entropy_encoder* encoder)
{
	if(encoder != NULL){
		free(encoder);
	}
	return NULL;
}

/*
 *
 */
PDC_Arithmetic_entropy_encoder* PDC_Aee_encode_01(	PDC_Arithmetic_entropy_encoder* in_encoder, 
													PDC_decision* d,
													PDC_context* cx,
													PDC_uint size,
													PDC_Buffer* in_buffer)
{
	PDC_Arithmetic_entropy_encoder* return_encoder = in_encoder;
	PDC_uint		sym_index, sym_index_max;
	PDC_decision*	MPS;
	PDC_uint_32*	I;
	PDC_uint_32		C;
	PDC_uint_32		A;
	PDC_uint_32		CT;
	PDC_uint_32		I_CX;
	PDC_uint_32		Qe_I_CX;
	PDC_context		CX;
	PDC_uchar		B;

	PDC_uchar*		buffer;
	PDC_uint_32		length;
	PDC_uint_32		write_byte_pos;

	sym_index_max	= size;
	MPS				= return_encoder->MPS;
	I				= return_encoder->I;	
	A				= return_encoder->a_register;
	C				= return_encoder->c_register;
	CT				= return_encoder->CT;

	buffer			= in_buffer->buffer;
	length			= in_buffer->length;
	write_byte_pos	= in_buffer->write_byte_pos;
	
	if(write_byte_pos == 0){
		B = 0;
	}else{
		B = buffer[write_byte_pos - 1];
	}

	for(sym_index = 0; sym_index < sym_index_max; sym_index += 1){
		CX		= cx[sym_index];
		I_CX	= I[CX];
		Qe_I_CX	= PDC_A_Encoder_qe[I_CX];

		if(MPS[CX] == d[sym_index]){
			/* CODEMPS */
			A -= Qe_I_CX;
			if(A < 0x8000){   //if((A & 0x8000) == 0){
				if(A < Qe_I_CX){
					A = Qe_I_CX;
				}else{
					C += Qe_I_CX;
				}
				I[CX] = PDC_A_Encoder_nmps[I_CX];
				/* RENORM */
				do{
					A <<= 1;
					C <<= 1;
					CT -= 1;
					if(CT == 0){
						/* BYTEOUT */
						if(B == 0xFF){
							if(write_byte_pos >= length){
								in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
								buffer		= in_buffer->buffer;
								length		= in_buffer->length;
							}
							B = C >> 20;
							buffer[write_byte_pos] = B;
							write_byte_pos += 1;
							C &= 0xFFFFF;
							CT = 7;
						}else{
							if(C < 0x8000000){
								if(write_byte_pos >= length){
									in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
									buffer		= in_buffer->buffer;
									length		= in_buffer->length;
								}
								B = C >> 19;
								buffer[write_byte_pos] = B;
								write_byte_pos += 1;
								C &= 0x7FFFF;
								CT = 8;
							}else{
								B += 1;
								if(write_byte_pos != 0){
									buffer[write_byte_pos - 1] = B;
								}
								if(B == 0xFF){
									C &= 0x7FFFFFF;
									if(write_byte_pos >= length){
										in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
										buffer		= in_buffer->buffer;
										length		= in_buffer->length;
									}
									B = C >> 20;
									buffer[write_byte_pos] = B;
									write_byte_pos += 1;
									C &= 0xFFFFF;
									CT = 7;
								}else{
									if(write_byte_pos >= length){
										in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
										buffer		= in_buffer->buffer;
										length		= in_buffer->length;
									}
									B = C >> 19;
									buffer[write_byte_pos] = B;
									write_byte_pos += 1;
									C &= 0x7FFFF;
									CT = 8;
								}
							}
						}
						/* BYTEOUT END */
					}
				}while((A & 0x8000) == 0);
				/* RENORM END */
			}else{
				C += Qe_I_CX;
			}
		}else{
			/* CODELPS */
			A -= Qe_I_CX;
			if(A < Qe_I_CX){
				C += Qe_I_CX;
			}else{
				A = Qe_I_CX;
			}
			if(PDC_A_Encoder_switcher[I_CX] == 1){
				MPS[CX] = 1 - MPS[CX];
			}
			I[CX] = PDC_A_Encoder_nlps[I_CX];
			/* RENORM */
			do{
				A <<= 1;
				C <<= 1;
				CT -= 1;
				if(CT == 0){
					/* BYTEOUT */
					if(B == 0xFF){
						if(write_byte_pos >= length){
							in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
							buffer		= in_buffer->buffer;
							length		= in_buffer->length;
						}
						B = C >> 20;
						buffer[write_byte_pos] = B;
						write_byte_pos += 1;
						C &= 0xFFFFF;
						CT = 7;
					}else{
						if(C < 0x8000000){
							if(write_byte_pos >= length){
								in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
								buffer		= in_buffer->buffer;
								length		= in_buffer->length;
							}
							B = C >> 19;
							buffer[write_byte_pos] = B;
							write_byte_pos += 1;
							C &= 0x7FFFF;
							CT = 8;
						}else{
							B += 1;
							if(write_byte_pos != 0){
								buffer[write_byte_pos - 1] = B;
							}
							if(B == 0xFF){
								C &= 0x7FFFFFF;
								if(write_byte_pos >= length){
									in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
									buffer		= in_buffer->buffer;
									length		= in_buffer->length;
								}
								B = C >> 20;
								buffer[write_byte_pos] = B;
								write_byte_pos += 1;
								C &= 0xFFFFF;
								CT = 7;
							}else{
								if(write_byte_pos >= length){
									in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
									buffer		= in_buffer->buffer;
									length		= in_buffer->length;
								}
								B = C >> 19;
								buffer[write_byte_pos] = B;
								write_byte_pos += 1;
								C &= 0x7FFFF;
								CT = 8;
							}
						}
					}
					/* BYTEOUT END */
				}
			}while((A & 0x8000) == 0);
			/* RENORM END */
		}
	}
	
	return_encoder->a_register	= A;
	return_encoder->c_register	= C;
	return_encoder->CT			= CT;

	in_buffer->write_byte_pos	= write_byte_pos;
	return return_encoder;
}

/*
 *
 */
PDC_Arithmetic_entropy_encoder* PDC_Aee_init_01(	PDC_Arithmetic_entropy_encoder* in_encoder,
													PDC_decision* default_MPS,
													PDC_uint_32* default_I)
{
	PDC_Arithmetic_entropy_encoder* return_encoder = in_encoder;
	PDC_decision*	MPS;
	PDC_uint_32*	I;
	PDC_uint_32		index;

	if(return_encoder != NULL){
		return_encoder->a_register	= 0x8000;
		return_encoder->c_register	= 0;
		return_encoder->CT			= 12;

		MPS	= &return_encoder->MPS[0];
		I	= &return_encoder->I[0];
		
		for(index = 0; index < MPS_I_LENGTH; index += 1){
			MPS[index]	= default_MPS[index];
			I[index]	= default_I[index];
		}
	}else{
		error(PDC_EXCEPTION_NULL_POINTER, __LINE__, __FILE__);
	}

	return return_encoder;
}

/*
 *
 */
PDC_Arithmetic_entropy_encoder* PDC_Aee_flush_01(	PDC_Arithmetic_entropy_encoder* in_encoder, 
													PDC_Buffer* in_buffer)
{
	PDC_Arithmetic_entropy_encoder* return_encoder = in_encoder;
	PDC_uint_32	TEMP;
	PDC_uint_32 A;
	PDC_uint_32 C;
	PDC_uint_32 CT;
	PDC_uchar	B;

	PDC_uchar*		buffer;
	PDC_uint_32		length;
	PDC_uint_32		write_byte_pos;

	A	= return_encoder->a_register;
	C	= return_encoder->c_register;
	CT	= return_encoder->CT;

	buffer			= in_buffer->buffer;
	length			= in_buffer->length;
	write_byte_pos	= in_buffer->write_byte_pos;
	
	if(write_byte_pos == 0){
		B = 0;
	}else{
		B = buffer[write_byte_pos];
	}

	/* SETBITS */
	TEMP = A + C;
	C |= 0xFFFF;
	if(C >= TEMP){
		C -= 0x8000;
	}
	/* SETBITS END */
	C <<= CT;
	/* BYTEOUT */
	if(B == 0xFF){
		if(write_byte_pos >= length){
			in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
			buffer		= in_buffer->buffer;
			length		= in_buffer->length;
		}
		B = C >> 20;
		buffer[write_byte_pos] = B;
		write_byte_pos += 1;
		C &= 0xFFFF;
		CT = 7;
	}else{
		if(C < 0x8000000){
			if(write_byte_pos >= length){
				in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
				buffer		= in_buffer->buffer;
				length		= in_buffer->length;
			}
			B = C >> 19;
			buffer[write_byte_pos] = B;
			write_byte_pos += 1;
			C &= 0x7FFFF;
			CT = 8;
		}else{
			B += 1;
			if(write_byte_pos != 0){
				buffer[write_byte_pos - 1] = B;
			}
			if(B == 0xFF){
				C &= 0x7FFFFFF;
				if(write_byte_pos >= length){
					in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
					buffer		= in_buffer->buffer;
					length		= in_buffer->length;
				}
				B = C >> 20;
				buffer[write_byte_pos] = B;
				write_byte_pos += 1;
				C &= 0xFFFF;
				CT = 7;
			}else{
				if(write_byte_pos >= length){
					in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
					buffer		= in_buffer->buffer;
					length		= in_buffer->length;
				}
				B = C >> 19;
				buffer[write_byte_pos] = B;
				write_byte_pos += 1;
				C &= 0x7FFFF;
				CT = 8;
			}
		}
	}
	/* BYTEOUT END */
	C <<= CT;
	/* BYTEOUT */
	if(B == 0xFF){
		if(write_byte_pos >= length){
			in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
			buffer		= in_buffer->buffer;
			length		= in_buffer->length;
		}
		B = C >> 20;
		buffer[write_byte_pos] = B;
		write_byte_pos += 1;
		C &= 0xFFFFF;
		CT = 7;
	}else{
		if(C < 0x8000000){
			if(write_byte_pos >= length){
				in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
				buffer		= in_buffer->buffer;
				length		= in_buffer->length;
			}
			B = C >> 19;
			buffer[write_byte_pos] = B;
			write_byte_pos += 1;
			C &= 0x7FFFF;
			CT = 8;
		}else{
			B += 1;
			if(write_byte_pos != 0){
				buffer[write_byte_pos - 1] = B;
			}
			if(B == 0xFF){
				C &= 0x7FFFFFF;
				if(write_byte_pos >= length){
					in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
					buffer		= in_buffer->buffer;
					length		= in_buffer->length;
				}
				B = C >> 20;
				buffer[write_byte_pos] = B;
				write_byte_pos += 1;
				C &= 0xFFFFF;
				CT = 7;
			}else{
				if(write_byte_pos >= length){
					in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
					buffer		= in_buffer->buffer;
					length		= in_buffer->length;
				}
				B = C >> 19;
				buffer[write_byte_pos] = B;
				write_byte_pos += 1;
				C &= 0x7FFFF;
				CT = 8;
			}
		}
	}
	/* BYTEOUT END */
	if(B != 0xFF){
		if(write_byte_pos >= length){
			in_buffer	= PDC_Buffer_realloc(in_buffer, RESIZE_BUFFER);
			buffer		= in_buffer->buffer;
			length		= in_buffer->length;
		}
		buffer[write_byte_pos] = B;
		write_byte_pos += 1;
	}

	return_encoder->a_register	= A;
	return_encoder->c_register	= C;
	return_encoder->CT			= CT;

	in_buffer->write_byte_pos	= write_byte_pos;

	return return_encoder;
}

/*
 *
 */



STOP_C
