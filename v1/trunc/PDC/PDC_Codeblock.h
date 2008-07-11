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

#ifndef __PDC_CODEBLOCK_H__
#define __PDC_CODEBLOCK_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C
	
	struct str_PDC_Codeblock;
	typedef struct str_PDC_Codeblock PDC_Codeblock;

	#include "PDC_Subband.h"
	#include "PDC_Resolution.h"

	struct str_PDC_Codeblock{
		PDC_Subband*	subband;

		PDC_uint32		cx0;	
		PDC_uint32		cx1;
		PDC_uint32		cy0;
		PDC_uint32		cy1;
	};
	
	/*
	 *
	 */
	PDC_Codeblock* new_PDC_Codeblock_01(PDC_Exception* exception);

	/*
	 *
	 */
	PDC_Codeblock* new_PDC_Codeblock_02(PDC_Exception* exception, PDC_Subband* subband, PDC_uint pos_x, PDC_uint pos_y);

	
	/*
	 *
	 */
	PDC_Codeblock* delete_PDC_Codeblock(PDC_Exception* exception, PDC_Codeblock* codeblock);

STOP_C
#endif