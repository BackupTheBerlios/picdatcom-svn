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

	struct str_PDC_Transformation_97_decoder{
		PDC_Exception*	exception;
		float			*workbuffer;
		float			*green;
		float			*pink;
		float			*orange;
		float			*brown;
		PDC_uint32		greenSize;
		PDC_uint32		pinkSize;
		PDC_uint32		orangeSize;
		PDC_uint32		brownSize;
		PDC_uint32		maxSize;
		PDC_Datatype	datatype;	
	};
	
	/*
	 *
	 */
	PDC_Transformation_97_decoder* new_PDC_Transformation_97_decoder(PDC_uint32 maxSize);

	/*
	 *
	 */
	PDC_Transformation_97_decoder* delete_PDC_Transformation_97_decoder(PDC_Transformation_97_decoder* decoder);
	
	/*
	 *
	 */
	PDC_Transformation_97_decoder* PDC_td_start(	PDC_Transformation_97_decoder* decoder,
													float *out, float *in_high, float* in_low, 
													PDC_uint out_start, PDC_uint out_size, PDC_uint out_plus, PDC_bool even, 
													PDC_uint in_high_start, PDC_uint in_hight_plus,
													PDC_uint in_low_start, PDC_uint in_low_plus);
												

STOP_C
#endif