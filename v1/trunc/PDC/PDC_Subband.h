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

#ifndef __PDC_SUBBAND_H__
#define __PDC_SUBBAND_H__

#include "PDC_Parameter.h"

START_C

	struct str_PDC_Subband;
	typedef struct str_PDC_Subband PDC_Subband;
	typedef enum{SUBBAND_LL, SUBBAND_HL, SUBBAND_LH, SUBBAND_HH, SUBBAND_UNKNOW} SUBBAND_TYPE;

	#include "PDC_Resolution.h"
	#include "PDC_Codeblock.h"


	struct str_PDC_Subband{
		PDC_Resolution* resolution;
		PDC_Codeblock**	codeblocks;
		PDC_uint		number_codeblocks;
		SUBBAND_TYPE	type;


		PDC_uint		tbx0;
		PDC_uint		tbx1;
		PDC_uint		tby0;
		PDC_uint		tby1;

		PDC_int			mx0;
		PDC_int			mx1;
		PDC_int			my0;
		PDC_int			my1;
		PDC_float32*	memory;
	};

	/*
	 *
	 */
	PDC_Subband* new_PDC_Subband_01(PDC_Exception* exception);

	/*
	 *
	 */
	PDC_Subband* new_PDC_Subband_02(PDC_Exception* exception, SUBBAND_TYPE type, PDC_Resolution* resolution);

	/*
	 *
	 */
	PDC_Subband* delete_PDC_Subband(PDC_Exception* exception, PDC_Subband* subband);

	/*
	 *
	 */
	PDC_Subband* PDC_Subband_inverse_quantization(	PDC_Exception* exception,
													PDC_Subband* subband);

	
	/*
	 *	Only to compare it with other decoder. 
	 */
	void PDC_Subband_print(PDC_Exception *exception, PDC_Subband *subband, FILE *file, int component);

STOP_C
#endif
