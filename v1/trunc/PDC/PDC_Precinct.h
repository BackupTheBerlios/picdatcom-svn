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

#ifndef __PDC_PRECINCT_H__
#define __PDC_PRECINCT_H__

#include "PDC_Parameter.h"


START_C
	struct str_PDC_Precinct;
	typedef struct str_PDC_Precinct PDC_Precinct;

	#include "PDC_Parameter.h"
	#include "PDC_Subband.h"
	#include "PDC_Resolution.h"
	#include "PDC_Codeblock.h"
	#include "PDC_Tagtree.h"

	struct str_PDC_Precinct{
		PDC_Resolution*	resolution;
		PDC_Tagtree*	codeblock_inclusion[3];
		PDC_Tagtree*	zero_bitplane[3];

		PDC_uint codeblock_x0;
		PDC_uint codeblock_x1;
		PDC_uint codeblock_y0;
		PDC_uint codeblock_y1;

		PDC_bit	bit1;
	};

	/*
	 *
	 */
	PDC_Precinct* new_PDC_Precinct_01(PDC_Exception* exception);

	/*
	 *
	 */
	PDC_Precinct* new_PDC_Precinct_02(	PDC_Exception* exception, 
										PDC_Resolution* resolution, 
										PDC_uint pos_x, 
										PDC_uint pos_y);

	/*
	 * 
	 */
	PDC_Precinct* delete_PDC_Precinct(	PDC_Exception* exception,
										PDC_Precinct* precinct);

	/*
	 *
	 */
	PDC_Precinct* PDC_Precinct_read_package_header(	PDC_Exception* exception,
													PDC_Precinct* precinct,
													PDC_Buffer*	buffer,
													PDC_uint layer_pos);

	/*
	 *
	 */
	PDC_Precinct* PDC_Precinct_decode_package_01(	PDC_Exception *exception,
													PDC_Precinct *precinct,
													PDC_uint layer_pos);

	/*
	 *
	 */
	PDC_Precinct* PDC_Precinct_decode_package_02(	PDC_Exception *exception,
													PDC_Precinct *precinct);

	/*
	 *
	 */
	PDC_Precinct* PDC_Precinct_set_End_of_Buffer(	PDC_Exception *exception,
													PDC_Precinct *precinct);

	/*
	 *
	 */
	PDC_Precinct* PDC_Precinct_read_package_header_02(	PDC_Exception* exception,
														PDC_Precinct* precinct,
														PDC_Buffer*	buffer,
														PDC_uint layer_pos,
														PDC_uint layer_max,
														PDC_Decoder* decoder);

	/*
	 *
	 */
	PDC_Precinct* PDC_Precinct_push(PDC_Exception* exception,
									PDC_Precinct* precinct);

	/*
	 *
	 */
	PDC_Precinct* PDC_Precinct_pop(PDC_Exception* exception,
									PDC_Precinct* precinct);

	/*
	 *
	 */
	PDC_Precinct* PDC_Precinct_pop_unlock(	PDC_Exception* exception,
											PDC_Precinct* precinct);

	void PDC_Precinct_print_codeblock_01(PDC_Exception* exception, PDC_Precinct* precinct, FILE *file, int component, int resolution, int n, int m);
STOP_C
#endif
