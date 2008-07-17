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

#ifndef __PDC_RESOLUTION_H__
#define __PDC_RESOLUTION_H__

#include "PDC_Parameter.h"

START_C
	
	struct str_PDC_Resolution;
	typedef struct str_PDC_Resolution PDC_Resolution;

	#include "PDC_Tile_Component.h"
	#include "PDC_Subband.h"
	#include "PDC_COD_Segment.h"
	#include "PDC_Precinct.h"

	struct str_PDC_Resolution
	{
		PDC_Tile_Component* tile_component;
		PDC_Resolution*		resolution_big;
		PDC_Resolution*		resolution_small;
		PDC_Precinct**		precinct;
		
		PDC_Subband*		subband_ll;
		PDC_Subband*		subband_hl;
		PDC_Subband*		subband_lh;
		PDC_Subband*		subband_hh;

		PDC_uint			n;
		PDC_uint			r;
		PDC_uint			trx0;
		PDC_uint			trx1;
		PDC_uint			try0;
		PDC_uint			try1;

		PDC_uint			PPx;
		PDC_uint			PPy;
		PDC_uint			xcb;
		PDC_uint			ycb;

		PDC_uint			codeblock_x0;
		PDC_uint			codeblock_x1;
		PDC_uint			codeblock_y0;
		PDC_uint			codeblock_y1;

		PDC_uint			precinct_x0;
		PDC_uint			precinct_x1;
		PDC_uint			precinct_y0;
		PDC_uint			precinct_y1;

	};

	/*
	 *
	 */
	PDC_Resolution* new_PDC_Resolution_01(PDC_Exception* exception);

	/*
	 *
	 */
	PDC_Resolution* new_PDC_Resolution_02(	PDC_Exception* exception,
											PDC_Tile_Component* tile_cmponent);

	/*
	 *
	 */
	PDC_Resolution* new_PDC_Resolution_03(	PDC_Exception* exception,
											PDC_Resolution* in_resolution);

	/*
	 *
	 */
	PDC_Resolution* delete_PDC_Resolution(	PDC_Exception* exception,
											PDC_Resolution* resolution);


	/*
	 *
	 */
	PDC_Resolution* PDC_Resolution_init_01(	PDC_Exception* exception,
											PDC_Resolution* in_resolution);


	/*
	 *
	 */
	PDC_Resolution* PDC_Resolution_get_resolution(	PDC_Exception* exception,
													PDC_Resolution* resolution,
													PDC_uint resolution_pos);

	/*
	 *
	 */
	PDC_uint PDC_Resolution_get_number_precinct(	PDC_Exception* exception,
													PDC_Resolution* resolution);
	
STOP_C
#endif