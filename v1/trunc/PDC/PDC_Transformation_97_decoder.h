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

#ifndef __PDC_TRANSFORMATION_97_DECODER_H__
#define __PDC_TRANSFORMATION_97_DECODER_H__

#include <stdlib.h>
#include "PDC_Parameter.h"
#include "PDC_Exception.h"




START_C

	struct str_PDC_Transformation_97_decoder;
	typedef struct str_PDC_Transformation_97_decoder PDC_Transformation_97_decoder;
	typedef enum{USE_32, USE_64}PDC_Datatype;

	#include "PDC_Resolution.h"

	struct str_PDC_Transformation_97_decoder{
		PDC_Exception*	exception;
		float			*workbuffer;
		float			*green;
		float			*pink;
		float			*orange;
		float			*brown;

		float			*delete_green;
		float			*delete_orange;

		float			*alpha;
		float			*beta;
		float			*gamma;
		float			*delta;
		float			*K;
		float 			*K1;

		float			*delete_alpha;
		float			*delete_beta;
		float			*delete_gamma;
		float			*delete_delta;
		float			*delete_K;
		float 			*delete_K1;

		PDC_uint		greenSize;
		PDC_uint		pinkSize;
		PDC_uint		orangeSize;
		PDC_uint		brownSize;
		PDC_uint		maxSize;
		PDC_Datatype	datatype;
	};

	/*
	 *
	 */
	PDC_Transformation_97_decoder* new_PDC_Transformation_97_decoder(	PDC_Exception* exception,
																		PDC_uint32 maxSize);

	/*
	 *
	 */
	PDC_Transformation_97_decoder* delete_PDC_Transformation_97_decoder(PDC_Exception* exception,
																		PDC_Transformation_97_decoder* decoder);

	/*
	 *
	 */
	PDC_Transformation_97_decoder* PDC_td_start_v1(	PDC_Exception* exception,
														PDC_Transformation_97_decoder* decoder,
														float *out, float *in_high, float* in_low,
														PDC_uint out_start, PDC_uint out_size, PDC_uint out_plus, PDC_bool even,
														PDC_uint in_high_start, PDC_uint in_hight_plus,
														PDC_uint in_low_start, PDC_uint in_low_plus);


	/*
	 *
	 */
	PDC_Transformation_97_decoder* PDC_td_start_v2(	PDC_Exception* exception,
													PDC_Transformation_97_decoder* decoder,
													float *out, float *in_high, float* in_low,
													PDC_uint out_start, PDC_uint out_size,
													PDC_uint out_plus, PDC_bool even,
													PDC_uint in_high_start, PDC_uint in_high_plus,
													PDC_uint in_low_start, PDC_uint in_low_plus,
													PDC_uint num_rows, PDC_uint high_stride, PDC_uint low_stride,
													PDC_uint out_stride	);

	/*
	 *
	 */
	PDC_Transformation_97_decoder* PDC_td_start_v2_sse2(	PDC_Exception* exception,
															PDC_Transformation_97_decoder* decoder,
															float *out, float *in_high, float* in_low,
															PDC_uint out_start, PDC_uint out_size,
															PDC_uint out_plus,  PDC_bool even,
															PDC_uint in_high_start, PDC_uint in_high_plus,
															PDC_uint in_low_start, PDC_uint in_low_plus,
															PDC_uint num_rows, PDC_uint high_stride, PDC_uint low_stride,
															PDC_uint out_stride);


	/*
	 *
	 */
	PDC_Transformation_97_decoder* PDC_td_start_v3_vertical(	PDC_Threadcall *variable );

	/*
	 *
	 */
	PDC_Transformation_97_decoder* PDC_td_start_v3_horizontal(	PDC_Threadcall *variable );

STOP_C
#endif
