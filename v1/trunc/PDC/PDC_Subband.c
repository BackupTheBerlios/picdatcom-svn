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

#include "PDC_Subband.h"

START_C


/*
 *
 */
PDC_Subband* new_PDC_Subband_01(PDC_Exception* exception)
{
	PDC_Subband* subband = NULL;
	subband = malloc(sizeof(PDC_Subband));
	if(subband == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	subband->resolution		= NULL;
	subband->tbx0			= 0;
	subband->tbx1			= 0;
	subband->tby0			= 0;
	subband->tby1			= 0;
	subband->type			= SUBBAND_UNKNOW;
	subband->mx0			= 0;
	subband->mx1			= 0;
	subband->my0			= 0;
	subband->my1			= 0;

	return subband;
}

/*
 *
 */
PDC_Subband* new_PDC_Subband_02(PDC_Exception* exception, SUBBAND_TYPE type, PDC_Resolution* resolution)
{
	PDC_Tile_Component* tile_component;
	PDC_uint			twohighnb;
	PDC_uint			twohighnbminone;
	PDC_uint			tcx0, tcx1, tcy0, tcy1;
	PDC_uint			pos_x, pos_y, pos, sizex, sizey;
	PDC_uint			number_codeblocks_x, number_codeblocks_y;
	PDC_Codeblock**		codeblocks;

	PDC_Subband* subband = NULL;
	subband = new_PDC_Subband_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Subband(exception, subband);
		return NULL;
	}
	subband->type		= type;
	subband->resolution	= resolution;

	tile_component	= resolution->tile_component;
	twohighnb		= 1 << subband->resolution->n;
	twohighnbminone	= 1 << (subband->resolution->n - 1);

	tcx0 = tile_component->tcx0;
	tcx1 = tile_component->tcx1;
	tcy0 = tile_component->tcy0;
	tcy1 = tile_component->tcy1;

	switch(subband->type){
		case SUBBAND_HL:
			tcx0 -= twohighnbminone;
			tcx1 -= twohighnbminone;
			break;
		case SUBBAND_LH:
			tcy0 -= twohighnbminone;
			tcy1 -= twohighnbminone;
			break;
		case SUBBAND_HH:
			tcx0 -= twohighnbminone;
			tcx1 -= twohighnbminone;
			tcy0 -= twohighnbminone;
			tcy1 -= twohighnbminone;
			break;
		default:
			break;
	}

	subband->tbx0	= PDC_i_ceiling(tcx0, twohighnb);
	subband->tbx1	= PDC_i_ceiling(tcx1, twohighnb);
	subband->tby0	= PDC_i_ceiling(tcy0, twohighnb);
	subband->tby1	= PDC_i_ceiling(tcy1, twohighnb);
	sizex			= subband->tbx1 - subband->tbx0;
	sizey			= subband->tby1 - subband->tby0;

	switch(subband->type){
		case SUBBAND_LL:
			subband->mx0	= resolution->mx0;
			subband->my0	= resolution->my0;
			subband->mx1	= subband->mx0 + sizex;
			subband->my1	= subband->my0 + sizey;
			break;
		case SUBBAND_HL:
			subband->mx1	= resolution->mx1;
			subband->my0	= resolution->my0;
			subband->mx0	= subband->mx1 - sizex;
			subband->my1	= subband->my0 + sizey;
			break;
		case SUBBAND_LH:
			subband->mx0	= resolution->mx0;
			subband->my1	= resolution->my1;
			subband->mx1	= subband->mx0 + sizex;
			subband->my0	= subband->my1 - sizey;
			break;
		case SUBBAND_HH:
			subband->mx1	= resolution->mx1;
			subband->my1	= resolution->my1;
			subband->mx0	= subband->mx1 - sizex;
			subband->my0	= subband->my1 - sizey;
			break;
		default:
			break;
	}
	number_codeblocks_x	= resolution->codeblock_x1 - resolution->codeblock_x0;
	number_codeblocks_y = resolution->codeblock_y1 - resolution->codeblock_y0;
	subband->number_codeblocks	=  number_codeblocks_x * number_codeblocks_y;
	subband->codeblocks	= malloc(sizeof(PDC_Codeblock*) * subband->number_codeblocks);
	if(subband->codeblocks == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		delete_PDC_Subband(exception, subband);
		return NULL;
	}
	codeblocks = subband->codeblocks;

	for(pos = 0; pos < subband->number_codeblocks; pos += 1){
		codeblocks[pos] = NULL;
	}

	for(pos_y = resolution->codeblock_y0, pos = 0; pos_y < resolution->codeblock_y1; pos_y += 1){
		for(pos_x = resolution->codeblock_x0; pos_x < resolution->codeblock_x1; pos_x += 1){
			subband->codeblocks[pos] = new_PDC_Codeblock_02(exception, subband, pos_x, pos_y);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				delete_PDC_Subband(exception, subband);
				return NULL;
			}
			pos += 1;
		}
	}

	return subband;
}

/*
 *
 */
PDC_Subband* delete_PDC_Subband(PDC_Exception* exception, PDC_Subband* subband)
{
	return NULL;
}

/*
 *
 */
PDC_Subband* PDC_Subband_inverse_quantization(	PDC_Exception* exception,
												PDC_Subband* subband)
{
	PDC_uint pos_codeblock, num_codeblock;
	PDC_Codeblock* codeblock;
	
	num_codeblock = subband->number_codeblocks;
	
	for(pos_codeblock = 0; pos_codeblock < num_codeblock; pos_codeblock += 1){
		codeblock = subband->codeblocks[pos_codeblock];
		PDC_Codeblock_inverse_quantization(exception, codeblock);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return subband;
		}	
	}
	return subband;
}												

STOP_C

