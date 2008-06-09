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

#ifndef __PDC_TILE_H__
#define __PDC_TILE_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C
	struct str_PDC_Tile;
	typedef struct str_PDC_Tile PDC_Tile;


	struct str_PDC_Tile{
		PDC_uint32	q;
		PDC_uint32	p;
		PDC_uint32	tx0;
		PDC_uint32	tx1;
		PDC_uint32	ty0;
		PDC_uint32	ty1;
	};

STOP_C
#endif
	
