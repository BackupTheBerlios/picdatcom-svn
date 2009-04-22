/*
 * Copyright (C) 2008  Uwe Br�nen
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

extern FILE* DEBUG_FILE;

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
	/*
	resolution->subband_hh			= NULL;
	resolution->subband_lh			= NULL;
	resolution->subband_hl			= NULL;
	resolution->subband_ll			= NULL;
	*/
	resolution->subband[0]			= NULL;
	resolution->subband[1]			= NULL;
	resolution->subband[2]			= NULL;
	resolution->codeblock_x0		= 0;
	resolution->codeblock_x1		= 0;
	resolution->codeblock_y0		= 0;
	resolution->codeblock_y1		= 0;
	resolution->precinct			= NULL;

	resolution->mx0					= 0;
	resolution->mx1					= 0;
	resolution->my0					= 0;
	resolution->my1					= 0;

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
	PDC_uint32		precinct_number_x;
	PDC_uint32		precinct_number_y;
	PDC_uint32		precinct_number_xy;
	//PDC_uint32		precinct_size_xy;
	PDC_uint32		precinct_pos_x;
	PDC_uint32		precinct_pos_y;
	PDC_uint32		pos;

	PDC_Tile_Component* tile_component	= in_resolution->tile_component;
	PDC_COD_Segment*	cod_segment		= in_resolution->tile_component->cod_segment;
	PDC_int factor	= 1 << (cod_segment->number_of_decompostion_levels - in_resolution->r);

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

	precinct_number_x		= in_resolution->precinct_x1 - in_resolution->precinct_x0;
	precinct_number_y		= in_resolution->precinct_y1 - in_resolution->precinct_y0;
	precinct_number_xy		= precinct_number_x * precinct_number_y;

	in_resolution->mx0	= tile_component->mx0;
	in_resolution->mx1	= tile_component->mx0 + in_resolution->trx1 - in_resolution->trx0;
	in_resolution->my0	= tile_component->my0;
	in_resolution->my1	= tile_component->my0 + in_resolution->try1 - in_resolution->try0;

	in_resolution->precinct = malloc(sizeof(PDC_Precinct*) * precinct_number_xy);
	if(in_resolution->precinct == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return in_resolution;
	}

	if(in_resolution->r == 0){
		in_resolution->subband[0] = new_PDC_Subband_02(exception, SUBBAND_LL, in_resolution);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return in_resolution;
		}
	}else{
		in_resolution->subband[0] = new_PDC_Subband_02(exception, SUBBAND_HL, in_resolution);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return in_resolution;
		}

		in_resolution->subband[1] = new_PDC_Subband_02(exception, SUBBAND_LH, in_resolution);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return in_resolution;
		}

		in_resolution->subband[2] = new_PDC_Subband_02(exception, SUBBAND_HH, in_resolution);
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

/*
 *
 */
PDC_Resolution* PDC_Resolution_get_resolution(	PDC_Exception* exception,
												PDC_Resolution* resolution,
												PDC_uint resolution_pos)
{
	if(resolution->r == resolution_pos){
		return resolution;
	}else if(resolution->r < resolution_pos){
		return NULL;
	}else if(resolution->r != 0){
		return PDC_Resolution_get_resolution(	exception, resolution->resolution_small, resolution_pos);
	}

	return NULL;
}


/*
 *
 */
PDC_uint PDC_Resolution_get_number_precinct(	PDC_Exception* exception,
												PDC_Resolution* resolution)
{
	PDC_uint back = 0;

	back = (resolution->precinct_x1 - resolution->precinct_x0) * (resolution->precinct_y1 - resolution->precinct_y0);
	return back;
}


/*
 *
 */
PDC_uint PDC_Resolution_get_codeblock_position(	PDC_Exception* exception,
												PDC_Resolution* resolution,
												PDC_uint pos_x,
												PDC_uint pos_y)
{
	PDC_uint pos_x1, pos_y1, size, pointer;

	pos_x1 = pos_x - resolution->codeblock_x0;
	pos_y1 = pos_y - resolution->codeblock_y0;
	size = resolution->codeblock_x1 - resolution->codeblock_x0;

	if(pos_x1 >= resolution->codeblock_x1 || pos_y1  >= resolution->codeblock_y1){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
	}

	pointer = pos_y1 * size + pos_x1;
	return pointer;
}

/*
 *
 */
PDC_Precinct* PDC_Resolution_get_precinct(	PDC_Exception*	exception,
											PDC_Resolution*	resolution,
											PDC_uint		precinct_pos)
{
	PDC_uint	size_x, size_y, size;

	size_x = resolution->precinct_x1 - resolution->precinct_x0;
	size_y = resolution->precinct_y1 - resolution->precinct_y0;

	size = size_x * size_y;
	if(precinct_pos >= size){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
		return NULL;
	}
	return resolution->precinct[precinct_pos];
}

/*
 *
 */
PDC_Resolution* PDC_Resolution_inverse_quantization(PDC_Exception* exception,
													PDC_Resolution* resolution)
{
	PDC_uint num_subband, pos_subband;

	if(resolution->r != 0){
		PDC_Resolution_inverse_quantization(exception, resolution->resolution_small);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return resolution;
		}
		num_subband = 3;
	}else{
		num_subband = 1;
	}

	for(pos_subband = 0; pos_subband < num_subband; pos_subband += 1){
		PDC_Subband_inverse_quantization(exception, resolution->subband[pos_subband]);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return resolution;
		}
	}

	return resolution;
}


int uwe_count = 0;
/*
 *
 */
PDC_Resolution* PDC_Resolution_inverse_transformation_97(	PDC_Exception* exception,
																PDC_Resolution* resolution)
{
	PDC_Transformation_97_decoder* transformer = resolution->tile_component->transformer_97_decoder;

	float		*out, *in_high,*in_low;
	PDC_uint	out_start, out_size, out_plus, in_high_start, in_hight_plus,
				in_low_start, in_low_plus, pos0, pos1, m_size; // pos_y, pos_y_end, pos_x, pos_x_end;
	PDC_bool	even;

	if(resolution->r != 1){
		PDC_Resolution_inverse_transformation_97(exception, resolution->resolution_small);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return resolution;
		}
	}

	m_size		= resolution->tile_component->msizex;
	out = in_high = in_low = resolution->tile_component->memory;

	out_plus = in_hight_plus = in_low_plus = 1;
	out_start		= resolution->mx0 + resolution->my0 * m_size;
	in_low_start	= out_start;
	in_high_start	= resolution->subband[0]->mx0 + resolution->subband[0]->my0 * m_size;
	out_size		= resolution->mx1 - resolution->mx0;
	if(resolution->trx0 % 2 == 1){
		even = PDC_false;
	}else{
		even = PDC_true;
	}

	for(pos0 = 0, pos1 = resolution->my1 - resolution->my0; pos0 < pos1; pos0 += 1){
		PDC_td_start_v1(	exception, transformer, out, in_high, in_low,
							out_start + pos0 * m_size, out_size,out_plus, even,
							in_high_start + pos0 * m_size, in_hight_plus,
							in_low_start + pos0 * m_size, in_low_plus);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return resolution;
		}
	}

	out_plus = in_hight_plus = in_low_plus = resolution->tile_component->msizex;
	out_start		= resolution->mx0 + resolution->my0 * m_size;
	in_low_start	= out_start;
	in_high_start	= resolution->subband[1]->mx0 + resolution->subband[1]->my0 * m_size;
	out_size		= resolution->my1 - resolution->my0;
	if(resolution->try0 % 2 == 1){
		even = PDC_false;
	}else{
		even = PDC_true;
	}

	for(pos0 = 0, pos1 = resolution->mx1 - resolution->mx0; pos0 < pos1; pos0 += 1){
		PDC_td_start_v1(	exception, transformer, out, in_high, in_low,
							out_start + pos0, out_size,out_plus, even,
							in_high_start + pos0, in_hight_plus,
							in_low_start + pos0, in_low_plus);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return resolution;
		}
	}
	/*
	if(uwe_count == 9){
		out_start = resolution->mx0 + resolution->my0 * m_size;
		for(pos_y = 0, pos_y_end = resolution->my1 - resolution->my0; pos_y < pos_y_end; pos_y += 1, out_start += m_size){
			for(pos_x = 0, pos_x_end = resolution->mx1 - resolution->mx0; pos_x < pos_x_end; pos_x += 1){
				fprintf(DEBUG_FILE,"%13.2f \n", out[out_start + pos_x]);
			}
		}
	}
	uwe_count += 1;
	*/
	return resolution;
}


/*
 *
 */
PDC_Resolution* PDC_Resolution_inverse_transformation_97_v2(	PDC_Exception* exception,
																	PDC_Resolution* resolution)
{
	PDC_Transformation_97_decoder* transformer = resolution->tile_component->transformer_97_decoder;

	float		*out, *in_high,*in_low;
	PDC_uint	out_start, out_size, out_plus, in_high_start, in_hight_plus,
				in_low_start, in_low_plus, pos0, pos1, pos1_rest, m_size; // pos_y, pos_y_end, pos_x, pos_x_end;
	PDC_bool	even;

	if(resolution->r != 1){
		PDC_Resolution_inverse_transformation_97_v2(exception, resolution->resolution_small);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return resolution;
		}
	}

	m_size		= resolution->tile_component->msizex;
	out = in_high = in_low = resolution->tile_component->memory;

	out_plus 		= in_hight_plus = in_low_plus = 1;
	out_start		= resolution->mx0 + resolution->my0 * m_size;
	in_low_start	= out_start;
	in_high_start	= resolution->subband[0]->mx0 + resolution->subband[0]->my0 * m_size;
	out_size		= resolution->mx1 - resolution->mx0;
	if(resolution->trx0 % 2 == 1){
		even = PDC_false;
	}else{
		even = PDC_true;
	}

	pos1 = resolution->my1 - resolution->my0;
	pos1_rest = pos1 % 4;
	pos1 = pos1 - pos1_rest;

	for(pos0 = 0; pos0 < pos1; pos0 += 4){
		PDC_td_start_v2(	exception, transformer, out, in_high, in_low,
							out_start + pos0 * m_size, out_size,out_plus, even,
							in_high_start + pos0 * m_size, in_hight_plus,
							in_low_start + pos0 * m_size, in_low_plus,
							4, m_size, m_size, m_size);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return resolution;
		}
	}

	if(pos1_rest != 0){
		PDC_td_start_v2(	exception, transformer, out, in_high, in_low,
							out_start + pos0 * m_size, out_size,out_plus, even,
							in_high_start + pos0 * m_size, in_hight_plus,
							in_low_start + pos0 * m_size, in_low_plus,
							pos1_rest, m_size, m_size, m_size);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return resolution;
		}
	}

	out_plus = in_hight_plus = in_low_plus = resolution->tile_component->msizex;
	out_start		= resolution->mx0 + resolution->my0 * m_size;
	in_low_start	= out_start;
	in_high_start	= resolution->subband[1]->mx0 + resolution->subband[1]->my0 * m_size;
	out_size		= resolution->my1 - resolution->my0;
	if(resolution->try0 % 2 == 1){
		even = PDC_false;
	}else{
		even = PDC_true;
	}

	pos1 = resolution->mx1 - resolution->mx0;
	pos1_rest = pos1 % 4;
	pos1 = pos1 - pos1_rest;

	for(pos0 = 0; pos0 < pos1; pos0 += 4){
		PDC_td_start_v2(	exception, transformer, out, in_high, in_low,
							out_start + pos0, out_size,out_plus, even,
							in_high_start + pos0, in_hight_plus,
							in_low_start + pos0, in_low_plus,
							4, 1, 1, 1);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return resolution;
		}
	}
	if(pos1_rest != 0){
		PDC_td_start_v2(	exception, transformer, out, in_high, in_low,
							out_start + pos0, out_size,out_plus, even,
							in_high_start + pos0, in_hight_plus,
							in_low_start + pos0, in_low_plus,
							pos1_rest, 1, 1, 1);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return resolution;
		}
	}

	/*
	if(uwe_count == 9){
		out_start = resolution->mx0 + resolution->my0 * m_size;
		for(pos_y = 0, pos_y_end = resolution->my1 - resolution->my0; pos_y < pos_y_end; pos_y += 1, out_start += m_size){
			for(pos_x = 0, pos_x_end = resolution->mx1 - resolution->mx0; pos_x < pos_x_end; pos_x += 1){
				fprintf(DEBUG_FILE,"%13.2f \n", out[out_start + pos_x]);
			}
		}
	}
	uwe_count += 1;
	*/
	return resolution;
}


STOP_C

