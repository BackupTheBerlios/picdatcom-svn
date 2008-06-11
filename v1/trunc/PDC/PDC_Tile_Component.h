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

#ifndef __PDC_TILE_COMPONENT_H__
#define __PDC_TILE_COMPONENT_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C

	struct str_PDC_Tile_Component;
	typedef struct str_PDC_Tile_Component PDC_Tile_Component;

	#include "PDC_Tile.h"
	#include "PDC_SIZ_Segment.h"
	#include "PDC_Picture.h"

	struct str_PDC_Tile_Component{
		PDC_uint32		tcx0;
		PDC_uint32		tcx1;
		PDC_uint32		tcy0;
		PDC_uint32		tcy1;
		PDC_Tile*		tile;
		PDC_float32*	memory;
	};

	/*
	 *
	 */
	PDC_Tile_Component* new_PDC_Tile_Component_01(PDC_Exception* exception, PDC_Tile* tile, PDC_uint32 pos);

	/*
	 *
	 */
	PDC_Tile_Component* delete_PDC_Tile_Component(PDC_Exception* exception, PDC_Tile_Component* tile_component);

STOP_C

#endif