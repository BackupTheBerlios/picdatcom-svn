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

#ifndef __PDC_ARITHMETIC_ENTROPY_DECODER_H__
#define __PDC_ARITHMETIC_ENTROPY_DECODER_H__

#include <stdlib.h>
#include "PDC_Parameter.h"
#include "PDC_Exception.h"


START_C
	struct str_PDC_Arithmetic_entropy_decoder;
	typedef struct str_PDC_Arithmetic_entropy_decoder PDC_Arithmetic_entropy_decoder;
	typedef enum { DECODE_SUCCESFULL, DECODE_BUFFER_EMPTY, INIT_DECODER, INIT_DECODER_BUFFER_EMPTY} PDC_decode_state;

	#include "PDC_Buffer.h"
	#include "PDC_Arithmetic_entropy_encoder.h"

	struct str_PDC_Arithmetic_entropy_decoder{
		PDC_uint_32			c_register;
		PDC_uint_32			a_register;
		PDC_uint_32			CT;
		PDC_uint_32			B;
		PDC_uint_32			I[MPS_I_LENGTH];
		PDC_decode_state	decode_state;
		PDC_decision		MPS[MPS_I_LENGTH];
		PDC_decision		D;
		
	};

	/*
	 *
	 */
	PDC_Arithmetic_entropy_decoder* new_PDC_Arithmetic_entropy_decoder();

	/*
	 *
	 */
	PDC_Arithmetic_entropy_decoder* delete_PDC_Arithmetic_entropy_decoder(PDC_Arithmetic_entropy_decoder* decoder);

	/*
	 *
	 */
	PDC_Arithmetic_entropy_decoder* PDC_Aed_decode_01(	PDC_Arithmetic_entropy_decoder* decoder,
														PDC_context context,
														PDC_Buffer* in_buffer);

	/*
	 *
	 */
	PDC_Arithmetic_entropy_decoder* PDC_Aed_initdec_01(	PDC_Arithmetic_entropy_decoder* decoder,
														PDC_Buffer* in_buffer);

	/*
	 *
	 */
	PDC_Arithmetic_entropy_decoder* PDC_Aed_set_I_MPS_01(	PDC_Arithmetic_entropy_decoder* decoder,
															PDC_decision* default_MPS,
															PDC_uint_32* default_I);


STOP_C
#endif