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

	struct str_PDC_Resolution
	{
		PDC_Tile_Component* tile_component;
		PDC_Resolution*		resolution_big;
		PDC_Resolution*		resolution_small;

		PDC_uint	n;
		PDC_uint	r;
		PDC_uint	trx0;
		PDC_uint	trx1;
		PDC_uint	try0;
		PDC_uint	try1;

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
											PDC_Resolution* resolution);

	/*
	 *
	 */
	PDC_Resolution* delete_PDC_Resolution(	PDC_Exception* exception,
											PDC_Resolution* resolution);

STOP_C
#endif