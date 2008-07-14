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

#include "PDC_Resolution.h"

START_C

/*
 *
 */
PDC_Resolution* new_PDC_Resolution_01(PDC_Exception* exception)
{
	PDC_Resolution* resolution = NULL;
	resolution = malloc(sizeof(PDC_Resolution));
	if(resolution == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	resolution->n					= 0;
	resolution->r					= 0;
	resolution->resolution_big		= NULL;
	resolution->resolution_small	= NULL;
	resolution->tile_component		= NULL;
	resolution->trx0				= 0;
	resolution->trx1				= 0;
	resolution->try0				= 0;
	resolution->try1				= 0;
	resolution->subband_hh			= NULL;
	resolution->subband_lh			= NULL;
	resolution->subband_hl			= NULL;
	resolution->subband_ll			= NULL;
	resolution->codeblock_x0		= 0;
	resolution->codeblock_x1		= 0;
	resolution->codeblock_y0		= 0;
	resolution->codeblock_y1		= 0;
	resolution->precinct			= NULL;

	return resolution;
}

/*
 *
 */
PDC_Resolution* new_PDC_Resolution_02(	PDC_Exception* exception,
										PDC_Tile_Component* tile_component)
{
	PDC_Resolution* resolution = NULL;
	resolution = new_PDC_Resolution_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Resolution(exception, resolution);
		return NULL;
	}
	
	resolution->tile_component	= tile_component;
	resolution->r				= tile_component->cod_segment->number_of_decompostion_levels;
	resolution->n				= 1;

	if(resolution->r != 0){
		resolution->resolution_small = new_PDC_Resolution_03(exception, resolution);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Resolution(exception, resolution);
			return NULL;
		}
	}
	PDC_Resolution_init_01( exception, resolution);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Resolution(exception, resolution);
		return NULL;
	}
	return resolution;
}

/*
 *
 */
PDC_Resolution* new_PDC_Resolution_03(	PDC_Exception* exception,
										PDC_Resolution* in_resolution)
{

	PDC_Resolution* resolution = NULL;
	resolution = new_PDC_Resolution_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Resolution(exception, resolution);
		return NULL;
	}
	resolution->resolution_big	= in_resolution;
	resolution->r				= in_resolution->r - 1;
	resolution->tile_component	= in_resolution->tile_component;

	if(resolution->r != 0){
		resolution->n	= in_resolution->n + 1;
		resolution->resolution_small = new_PDC_Resolution_03(exception, resolution);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Resolution(exception, resolution);
			return NULL;
		}
	}else{
		resolution->n	= in_resolution->n;
	}
	PDC_Resolution_init_01( exception, resolution);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Resolution(exception, resolution);
		return NULL;
	}		
	return resolution;
}

/*
 *
 */
PDC_Resolution* delete_PDC_Resolution(	PDC_Exception* exception,
										PDC_Resolution* resolution)
{
	return NULL;
}


/*
 *
 */
PDC_Resolution* PDC_Resolution_init_01(	PDC_Exception* exception,
										PDC_Resolution* in_resolution)
{
	PDC_uint		PPx;
	PDC_uint		PPy;
	PDC_uint		xcb;
	PDC_uint		ycb;
	PDC_uint8		precinct_size;
	PDC_uint32		codeblock_size_x;
	PDC_uint32		codeblock_size_y;

	PDC_uint32		precinct_size_x;
	PDC_uint32		precinct_size_y;
	PDC_uint32		precinct_size_xy;
	PDC_uint32		precinct_pos_x;
	PDC_uint32		precinct_pos_y;
	PDC_uint32		pos;

	PDC_Tile_Component* tile_component	= in_resolution->tile_component;
	PDC_COD_Segment*	cod_segment		= in_resolution->tile_component->cod_segment;
	PDC_int factor	= 2 << (cod_segment->number_of_decompostion_levels - in_resolution->r);

	xcb = in_resolution->xcb	= cod_segment->code_block_width		+ 2;
	ycb = in_resolution->ycb	= cod_segment->code_block_height	+ 2;

	cod_segment->precinct_size =  PDC_Buffer_read_uint8_03(	exception, 
															cod_segment->precinct_size, 
															&precinct_size, 
															in_resolution->r);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return in_resolution;
	}
	PPx = in_resolution->PPx	= precinct_size & 0xF;
	PPy = in_resolution->PPy	= (precinct_size >> 4) & 0xF;
	precinct_size_x = 1 << PPx;
	precinct_size_y	= 1 << PPy;

	if(in_resolution->r == 0){
		xcb = in_resolution->xcb = min_int(PPx, xcb);
		ycb	= in_resolution->ycb = min_int(PPy, ycb);
		codeblock_size_x	= 1 << xcb;
		codeblock_size_y	= 1 << ycb;
	}else{
		xcb = in_resolution->xcb = min_int(PPx - 1, xcb);
		ycb	= in_resolution->ycb = min_int(PPy - 1, ycb);
		codeblock_size_x	= 1 << (xcb + 1);
		codeblock_size_y	= 1 << (ycb + 1);
	}
	
	
	in_resolution->trx0 = PDC_i_ceiling(tile_component->tcx0, factor);
	in_resolution->trx1 = PDC_i_ceiling(tile_component->tcx1, factor);
	in_resolution->try0 = PDC_i_ceiling(tile_component->tcy0, factor);
	in_resolution->try1 = PDC_i_ceiling(tile_component->tcy1, factor);

	in_resolution->codeblock_x0	= PDC_i_floor(in_resolution->trx0, codeblock_size_x);
	in_resolution->codeblock_x1	= PDC_i_ceiling(in_resolution->trx1, codeblock_size_x);
	in_resolution->codeblock_y0	= PDC_i_floor(in_resolution->try0, codeblock_size_y);
	in_resolution->codeblock_y1	= PDC_i_ceiling(in_resolution->try1, codeblock_size_y);	

	in_resolution->precinct_x0	= PDC_i_floor(in_resolution->trx0, precinct_size_x);
	in_resolution->precinct_x1	= PDC_i_ceiling(in_resolution->trx1, precinct_size_x);
	in_resolution->precinct_y0	= PDC_i_floor(in_resolution->try0, precinct_size_y);
	in_resolution->precinct_y1	= PDC_i_ceiling(in_resolution->try1, precinct_size_y);	

	precinct_size_x		= in_resolution->precinct_x1 - in_resolution->precinct_x0;
	precinct_size_y		= in_resolution->precinct_y1 - in_resolution->precinct_y0;
	precinct_size_xy	= precinct_size_x * precinct_size_y;
	
	in_resolution->precinct = malloc(sizeof(PDC_Precinct*) * precinct_size_xy);
	if(in_resolution->precinct == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return in_resolution;
	}

	if(in_resolution->r == 0){
		in_resolution->subband_ll = new_PDC_Subband_02(exception, SUBBAND_LL, in_resolution);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return in_resolution;
		}
	}else{
		in_resolution->subband_hl = new_PDC_Subband_02(exception, SUBBAND_HL, in_resolution);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return in_resolution;
		}

		in_resolution->subband_lh = new_PDC_Subband_02(exception, SUBBAND_LH, in_resolution);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return in_resolution;
		}

		in_resolution->subband_hh = new_PDC_Subband_02(exception, SUBBAND_HH, in_resolution);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return in_resolution;
		}
	}

	for(precinct_pos_y = in_resolution->precinct_y0, pos = 0; precinct_pos_y < in_resolution->precinct_y1; precinct_pos_y += 1){
		for(precinct_pos_x = in_resolution->precinct_x0; precinct_pos_x < in_resolution->precinct_y1; precinct_pos_x += 1){
			in_resolution->precinct[pos] = new_PDC_Precinct_02(exception, in_resolution, precinct_pos_x, precinct_pos_y);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return in_resolution;
			}
			pos += 1;
		}
	}
	

	return in_resolution;
}

STOP_C

