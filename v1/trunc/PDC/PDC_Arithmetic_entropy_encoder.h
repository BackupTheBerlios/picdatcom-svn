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

#ifndef __PDC_ARITHMETIC_ENTROPY_ENCODER_H__
#define __PDC_ARITHMETIC_ENTROPY_ENCODER_H__

#include <stdlib.h>
#include "PDC_Parameter.h"
#include "PDC_Exception.h"


START_C

	struct str_PDC_Arithmetic_entropy_encoder;
	typedef struct str_PDC_Arithmetic_entropy_encoder PDC_Arithmetic_entropy_encoder;

	#define MPS_I_LENGTH 19
	#define RESIZE_BUFFER 10


	PDC_uint32 PDC_A_Encoder__index[MPS_I_LENGTH];
	PDC_decision PDC_A_Encoder__mps[MPS_I_LENGTH];


	#include "PDC_Buffer.h"

	struct str_PDC_Arithmetic_entropy_encoder{
		PDC_uint32		c_register;
		PDC_uint32		a_register;
		PDC_uint32		CT;
		PDC_decision	MPS[MPS_I_LENGTH];
		PDC_uint32		I[MPS_I_LENGTH];
	};

	/*
	 *
	 */
	PDC_Arithmetic_entropy_encoder* new_PDC_Arithmetic_entropy_encoder(PDC_Exception*	exception);

	/*
	 *
	 */
	PDC_Arithmetic_entropy_encoder* delete_PDC_Arithmetic_entropy_encoder(PDC_Exception*	exception, PDC_Arithmetic_entropy_encoder* encoder);

	/*
	 *
	 */
	PDC_Arithmetic_entropy_encoder* PDC_Aee_encode_01(	PDC_Exception*	exception,
														PDC_Arithmetic_entropy_encoder* in_encoder,
														PDC_decision* d,
														PDC_context* cx,
														PDC_uint size,
														PDC_Buffer* in_buffer);

	/*
	 *
	 */
	PDC_Arithmetic_entropy_encoder* PDC_Aee_flush_01(	PDC_Exception*	exception,
														PDC_Arithmetic_entropy_encoder* in_encoder,
														PDC_Buffer* in_buffer);
	/*
	 *
	 */
	PDC_Arithmetic_entropy_encoder* PDC_Aee_init_01(	PDC_Exception*	exception,
														PDC_Arithmetic_entropy_encoder* in_encoder,
														PDC_decision* default_MPS,
														PDC_uint32* default_I);

STOP_C

#endif
