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

extern FILE* DEBUG_FILE;
extern FILE* DEBUG_FILE2;
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
	PDC_uint32		precinct_pos_x;
	PDC_uint32		precinct_pos_y;
	PDC_uint32		pos;

	if(resolution != NULL){
		delete_PDC_Resolution(exception, resolution->resolution_small);

		delete_PDC_Subband(exception, resolution->subband[0]);
		delete_PDC_Subband(exception, resolution->subband[1]);
		delete_PDC_Subband(exception, resolution->subband[2]);

		for(precinct_pos_y = resolution->precinct_y0, pos = 0; precinct_pos_y < resolution->precinct_y1; precinct_pos_y += 1){
			for(precinct_pos_x = resolution->precinct_x0; precinct_pos_x < resolution->precinct_y1; precinct_pos_x += 1){
				delete_PDC_Precinct(exception, resolution->precinct[pos]);
				resolution->precinct[pos] = NULL;
				pos += 1;
			}
		}

		free(resolution->precinct);
		resolution->precinct = NULL;

		free(resolution);
	}
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

	in_resolution->mx0	= 0;
	in_resolution->mx1	= in_resolution->trx1 - in_resolution->trx0;
	in_resolution->my0	= 0;
	in_resolution->my1	= in_resolution->try1 - in_resolution->try0;

	in_resolution->precinct = malloc(sizeof(PDC_Precinct*) * precinct_number_xy);
	if(in_resolution->precinct == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return in_resolution;
	}

	for(pos = 0; pos < precinct_number_xy; pos += 1){
		in_resolution->precinct[pos] = NULL;
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

	if(resolution->r != 0){
		PDC_Resolution_inverse_transformation_97_v3(exception, resolution);
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
				in_low_start, in_low_plus, pos0, pos1, m_size;// pos_y, pos_y_end, pos_x, pos_x_end;
	PDC_bool	even;

	if(resolution->r != 1){
		PDC_Resolution_inverse_transformation_97(exception, resolution->resolution_small);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return resolution;
		}
	}

	m_size		= resolution->tile_component->msizex;
	out = in_high = in_low = resolution->tile_component->image_memory;

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
	uwe_count += 2;
	if(uwe_count == 0){
		out_start = resolution->mx0 + resolution->my0 * m_size;
		for(pos_y = 0, pos_y_end = resolution->my1 - resolution->my0; pos_y < pos_y_end; pos_y += 1, out_start += m_size){
			for(pos_x = 0, pos_x_end = resolution->mx1 - resolution->mx0; pos_x < pos_x_end; pos_x += 1){
				fprintf(DEBUG_FILE,"%5d   %13.2f \n",pos_y, out[out_start + pos_x]);
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
				in_low_start, in_low_plus, pos0, pos1, pos1_rest, m_size, SSE2; // pos_y, pos_y_end, pos_x, pos_x_end;
	PDC_bool	even;

	SSE2 = 1;

	if(resolution->r != 1){
		PDC_Resolution_inverse_transformation_97_v2(exception, resolution->resolution_small);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return resolution;
		}
	}

	m_size	= resolution->tile_component->msizex;
	out = in_high = in_low = resolution->tile_component->image_memory;

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

	if(SSE2 == 1){
		for(pos0 = 0; pos0 < pos1; pos0 += 4){

			PDC_td_start_v2_sse2(	exception, transformer, out, in_high, in_low,
									out_start + pos0 * m_size, out_size,out_plus, even,
									in_high_start + pos0 * m_size, in_hight_plus,
									in_low_start + pos0 * m_size, in_low_plus,
									4, m_size, m_size, m_size);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return resolution;
			}
		}

		if(pos1_rest != 0){
			PDC_td_start_v2_sse2(	exception, transformer, out, in_high, in_low,
									out_start + pos0 * m_size, out_size,out_plus, even,
									in_high_start + pos0 * m_size, in_hight_plus,
									in_low_start + pos0 * m_size, in_low_plus,
									pos1_rest, m_size, m_size, m_size);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return resolution;
			}
		}
	}else{
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
	}


	out_plus 		= in_hight_plus = in_low_plus = resolution->tile_component->msizex;
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


	if(SSE2 == 1){
		for(pos0 = 0; pos0 < pos1; pos0 += 4){
			PDC_td_start_v2_sse2(	exception, transformer, out, in_high, in_low,
									out_start + pos0, out_size,out_plus, even,
									in_high_start + pos0, in_hight_plus,
									in_low_start + pos0, in_low_plus,
									4, 1, 1, 1);


			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return resolution;
			}
		}
		if(pos1_rest != 0){
			PDC_td_start_v2_sse2(	exception, transformer, out, in_high, in_low,
									out_start + pos0, out_size,out_plus, even,
									in_high_start + pos0, in_hight_plus,
									in_low_start + pos0, in_low_plus,
									pos1_rest, 1, 1, 1);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return resolution;
			}
		}
	}else{
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
	}

	return resolution;
}


/*
 *
 */
PDC_Resolution* PDC_Resolution_inverse_transformation_97_v3(	PDC_Exception* exception,
																PDC_Resolution* resolution)
{
	PDC_int		line_stride_float, out_size1, out_size2 ,lowh_size, lowv_size, highh_size, highv_size;
	float 		*sub1_data, *sub2_data, *sub3_data, *sub4_data, *out_data1, *out_data2;
	PDC_bool	evenhl, evenvl, evenhr, evenvr;
	PDC_int		max_threads, pos_thread;
	PDC_Threadcall *variable;

	line_stride_float = resolution->tile_component->line_stride_float;



	if(resolution->trx0 % 2 == 1){
		evenhl = PDC_false;
	}else{
		evenhl = PDC_true;
	}

	if((resolution->trx1 - 1) % 2 == 1){
		evenhr = PDC_false;
	}else{
		evenhr = PDC_true;
	}


	if(resolution->try0 % 2 == 1){
		evenvl = PDC_false;
	}else{
		evenvl = PDC_true;
	}

	if((resolution->try1 - 1) % 2 == 1){
		evenvr = PDC_false;
	}else{
		evenvr = PDC_true;
	}

	lowv_size	= resolution->subband[0]->my1 - resolution->subband[0]->my0;
	lowh_size	= resolution->subband[1]->mx1 - resolution->subband[1]->mx0;
	highv_size	= resolution->subband[1]->my1 - resolution->subband[1]->my0;
	highh_size	= resolution->subband[0]->mx1 - resolution->subband[0]->mx0;

	out_size1	= resolution->trx1 - resolution->trx0;
	out_size2	= resolution->try1 - resolution->try0;
	out_data1	= resolution->tile_component->tile_memory2;
	out_data2	= out_data1 + resolution->subband[1]->my0 * line_stride_float;

	sub1_data	= resolution->tile_component->tile_memory2 - 2;

	sub2_data	= resolution->tile_component->tile_memory2 + resolution->subband[0]->mx0 +
				  resolution->subband[0]->my0 * line_stride_float;
	sub2_data	= sub2_data - 2;

	sub3_data	= resolution->tile_component->tile_memory2 + resolution->subband[1]->mx0 +
				  resolution->subband[1]->my0 * line_stride_float;
	if(evenhl){
		sub3_data 	= sub3_data - 1;
	}else{
		sub3_data 	= sub3_data - 2;
	}

	sub4_data 	= resolution->tile_component->tile_memory2 + resolution->subband[2]->mx0 +
				  resolution->subband[2]->my0 * line_stride_float;
	sub4_data 	= sub4_data - 2;

	max_threads = PDC_max_thread();
	*(resolution->tile_component->threadcalls[0]->thread_counter) = 0;

	for(pos_thread = 0; pos_thread < max_threads; pos_thread += 1){
		variable = resolution->tile_component->threadcalls[pos_thread];

		variable->exception				= exception;
		variable->resolution			= resolution;
		variable->linestride_float		= resolution->tile_component->line_stride_float;

		variable->evenhl				= evenhl;
		variable->evenhr				= evenhr;
		variable->evenvl				= evenvl;
		variable->evenvr				= evenvr;
		variable->sub1_data				= sub1_data;
		variable->sub2_data				= sub2_data;
		variable->sub3_data				= sub3_data;
		variable->sub4_data				= sub4_data;
		variable->size_high_horizontal	= highh_size;
		variable->size_high_vertical	= highv_size;
		variable->size_low_horizontal	= lowh_size;
		variable->size_low_vertical		= lowv_size;
		variable->out_size_horizontal	= out_size1;
		variable->out_size_vertical		= out_size2;

		pthread_create(&(variable->pthread_id), NULL, &PDC_threadcall_func, variable);
	}

	for(pos_thread = 0; pos_thread < max_threads; pos_thread += 1){
		pthread_join(variable->pthread_id, NULL);
	}

/*
	stop 		= resolution->subband[0]->my1 - resolution->subband[0]->my0;
	start		= 0;

	if(evenhl){
		sub1_data -= line_stride_float;
		out_data1 -= line_stride_float;
	}



	extend_vertical_low(exception,
						sub1_data,
						lowh_size,
						line_stride_float,
						0,
						lowv_size,
						evenhl,
						evenhr);

	extend_vertical_high(	exception,
							sub2_data,
							highh_size,
							line_stride_float,
							0,
							lowv_size,
							evenhl,
							evenhr);

	PDC_td_start_v3_vertical(	exception,
								resolution->tile_component->transformer_97_decoder,
								out_data1, sub2_data, sub1_data,
								0, out_size,
								1,  evenhl,
								0, line_stride_float,
								0, line_stride_float,
								stop, start,
								line_stride_float, line_stride_float, line_stride_float);

	stop 		= resolution->subband[1]->my1 - resolution->subband[1]->my0;
	start		= 0;

	extend_vertical_low(exception,
						sub3_data,
						lowh_size,
						line_stride_float,
						0,
						highv_size,
						evenhl,
						evenhr);

	extend_vertical_high(	exception,
							sub4_data,
							highh_size,
							line_stride_float,
							0,
							highv_size,
							evenhl,
							evenhr);

	PDC_td_start_v3_vertical(	exception,
								resolution->tile_component->transformer_97_decoder,
								out_data2, sub4_data, sub3_data,
								0, out_size,
								1,  evenhl,
								0, line_stride_float,
								0, line_stride_float,
								stop, start,
								line_stride_float, line_stride_float, line_stride_float);

	if(uwe_count == 0 ){
			int posx, posy, endx, endy;
			endx = resolution->mx1 - resolution->mx0;
			endy = resolution->my1 - resolution->my0;
			out_data1	= resolution->tile_component->tile_memory2;

			if(evenvl){
				out_data1 -= 1;
			}

			if(evenhl){
				out_data1 -= line_stride_float;
			}

			// fprintf(DEBUG_FILE,"endx = %d endy = %d \n", endx, endy);
			for(posy = 0; posy < endy; posy += 1){
				out_data2 = out_data1 + (posy * line_stride_float);
				for(posx = 0; posx < endx; posx += 1){
					fprintf(DEBUG_FILE," %12.6f ", out_data2[posx]);
				}
				fprintf(DEBUG_FILE,"\n");
			}
			uwe_count +=1;
		}



	out_size	= resolution->try1 - resolution->try0;
*/
	/*
	sub1_data	= resolution->tile_component->tile_memory2 - 2 * line_stride_float;

	sub2_data	= resolution->tile_component->tile_memory2 + resolution->subband[1]->mx0 +
				  resolution->subband[1]->my0 * line_stride_float;
	sub2_data	= sub2_data - 2 * line_stride_float;
	*/

	/*
	out_data1	= resolution->tile_component->tile_memory2;
	sub1_data	= out_data1 - 2 * line_stride_float;
	sub2_data	= out_data2 - 2 * line_stride_float;

	if(evenvl){
		sub1_data -= 1;
		sub2_data -= 1;
		out_data1 -= 1;
	}

	//stop 		= resolution->subband[1]->mx1 - resolution->subband[1]->mx0;
	stop		= resolution->mx1 - resolution->mx0;
	start		= 0;

	extend_horizontal_low(	exception,
							sub1_data,
							lowv_size,
							line_stride_float,
							start,
							stop,
							evenvl,
							evenvr);

	extend_horizontal_high(	exception,
							sub2_data,
							highv_size,
							line_stride_float,
							start,
							stop,
							evenvl,
							evenvr);

	PDC_td_start_v3_horizontal(	exception,
								resolution->tile_component->transformer_97_decoder,
								out_data1, sub2_data, sub1_data,
								0, out_size,
								line_stride_float,  evenvl,
								0, line_stride_float,
								0, line_stride_float,
								stop, start, line_stride_float,line_stride_float,
								line_stride_float);

	*/

/*
	if(uwe_count == 0 && resolution->n == 1 ){
		int posx, posy, endx, endy;
		endx = resolution->mx1 - resolution->mx0;
		endy = resolution->my1 - resolution->my0;
		out_data1	= resolution->tile_component->tile_memory2;

		if(evenvl){
			out_data1 -= 1;
		}

		if(evenhl){
			out_data1 -= line_stride_float;
		}

		// fprintf(DEBUG_FILE,"endx = %d endy = %d \n", endx, endy);
		for(posy = 0; posy < endy; posy += 1){
			out_data2 = out_data1 + (posy * line_stride_float);
			for(posx = 0; posx < endx; posx += 1){
				fprintf(DEBUG_FILE," %6.1f", out_data2[posx]);
			}
			fprintf(DEBUG_FILE,"\n");
		}
		uwe_count +=1;
	}
*/

	return resolution;
}


// orange
void extend_vertical_low( PDC_Threadcall *variable)
{
//	PDC_Exception *exception	= variable->exception;
	float *in					= variable->sub1_data;
	PDC_int size				= variable->size_low_horizontal;
	PDC_int linestride_float	= variable->linestride_float;
	PDC_int start_row			= variable->start_row;
	PDC_int	end_row				= variable->end_row;
	PDC_bool evenl				= variable->evenhl;
	PDC_bool evenr				= variable->evenhr;

	float *work, * workend, *inr;

	if(evenl){
		inr 	= in + size ;
		workend = in + linestride_float * end_row;
		if(size > 1){
			for(work = in + linestride_float * start_row; work < workend; work += linestride_float){
				work[0] = work[2];
			}
		}else{
			for(work = in + linestride_float * start_row; work < workend; work += linestride_float){
				work[0] = work[1];
			}
		}

	}else{
		inr		= in + size + 1;
		workend = in + linestride_float * end_row;
		if(size > 1){
			for(work = in + linestride_float * start_row; work < workend; work += linestride_float){
				work[0] = work[3];
				work[1] = work[2];
			}
		}else{
			for(work = in + linestride_float * start_row; work < workend; work += linestride_float){
				work[0] = work[3] = work[1] = work[2];
			}
		}
	}

	if(evenr){
		workend = inr + linestride_float * end_row;
		if(size > 1){
			for(work = inr + linestride_float * start_row; work < workend; work += linestride_float){
				work[1] = work[-1];
			}
		}else{
			for(work = inr + linestride_float * start_row; work < workend; work += linestride_float){
				work[1] = work[0];
			}
		}

	}else{
		workend = inr + linestride_float * end_row;
		if(size > 1){
			for(work = inr + linestride_float * start_row; work < workend; work += linestride_float){
				work[1] = work[0];
				work[2] = work[-1];
			}
		}else{
			for(work = inr + linestride_float * start_row; work < workend; work += linestride_float){
				work[1] = work[0];
				work[2] = work[0];
			}
		}
	}

}

//green
void extend_vertical_high( PDC_Threadcall *variable)
{
	//PDC_Exception *exception	= variable->exception;
	float *in					= variable->sub2_data;
	PDC_int size				= variable->size_high_horizontal;
	PDC_int linestride_float	= variable->linestride_float;
	PDC_int start_row			= variable->start_row;
	PDC_int	end_row				= variable->end_row;
	PDC_bool evenl				= variable->evenhl;
	PDC_bool evenr				= variable->evenhr;

	float *work, * workend, *inr;

	if(evenl){
		inr	= in + size + 1;
		if(size > 2){
			workend = in + end_row * linestride_float;
			for(work = in + start_row * linestride_float; work < workend; work += linestride_float){
				work[0] = work[3];
				work[1] = work[2];
			}
		}else{
			workend = in + end_row * linestride_float;
			for(work = in + start_row * linestride_float; work < workend; work += linestride_float){
				work[0] = work[2];
				work[1] = work[2];
			}
		}

	}else{
		inr	= in + size + 1;
		if(size > 2){
			workend = in + end_row * linestride_float;
			for(work = in + start_row * linestride_float; work < workend; work += linestride_float){
				work[0] = work[4];
				work[1] = work[3];
			}
		}else{
			workend = in + end_row * linestride_float;
			for(work = in + start_row * linestride_float; work < workend; work += linestride_float){
				work[0] = work[2];
				work[1] = work[2];
			}
		}
	}

	if(evenr){
		if(size > 2){
			workend = inr + end_row * linestride_float;
			for(work = inr + start_row * linestride_float; work < workend; work += linestride_float){
				work[1] = work[0];
				work[2] = work[-1];
			}
		}else{
			workend = inr + end_row * linestride_float;
			for(work = inr + start_row * linestride_float; work < workend; work += linestride_float){
				work[1] = work[0];
				work[2] = work[0];
			}
		}
	}else{
		if(size > 2){
			workend = inr + end_row * linestride_float;
			for(work = inr + start_row * linestride_float; work < workend; work += linestride_float){
				work[1] = work[-1];
				work[2] = work[-2];
			}
		}else{
			workend = inr + end_row * linestride_float;
			for(work = inr + start_row * linestride_float; work < workend; work += linestride_float){
				work[1] = work[0];
				work[2] = work[0];
			}
		}
	}
}

// orange
void extend_horizontal_low( PDC_Threadcall *variable)
{
	//PDC_Exception *exception	= variable->exception;
	float *in					= variable->sub1_data;
	PDC_int size				= variable->size_low_vertical;
	PDC_int linestride_float	= variable->linestride_float;
	PDC_int start_col			= variable->start_col;
	PDC_int	end_col				= variable->end_col;
	PDC_bool evenl				= variable->evenvl;
	PDC_bool evenr				= variable->evenvr;

	float *work, * workend, *inr;
	PDC_int linestride_float_1 = linestride_float;
	PDC_int linestride_float_2 = linestride_float * 2;
	PDC_int linestride_float_3 = linestride_float * 3;
	//PDC_int linestride_float_4 = linestride_float * 4;


	if(evenl){
		inr 	= in + size * linestride_float ;

		workend = in + end_col;
		if(size > 1){
			for(work = in + start_col; work < workend; work += 1){
				work[0] = work[linestride_float_2];
			}
		}else{
			for(work = in + start_col; work < workend; work += 1){
				work[0] = work[linestride_float_1];
			}
		}
	}else{
		inr		= in + (size + 1) * linestride_float;
		workend = in + end_col;
		if(size > 1){
			for(work = in + start_col; work < workend; work += 1){
				work[0] 					= work[linestride_float_3];
				work[linestride_float_1] 	= work[linestride_float_2];
			}
		}else{
			for(work = in +  start_col; work < workend; work += 1){
				work[0] = work[linestride_float_1] = work[linestride_float_2];
			}
		}
	}

	if(evenr){
		workend = inr +  end_col;
		if(size > 1){
			for(work = inr +  start_col; work < workend; work += 1){
				work[linestride_float_1] = work[-linestride_float_1];
			}
		}else{
			for(work = inr + start_col; work < workend; work += 1){
				work[linestride_float_1] = work[0];
			}
		}

	}else{
		workend = inr + end_col;
		if(size > 1){
			for(work = inr + start_col; work < workend; work += 1){
				work[linestride_float_1] = work[0];
				work[linestride_float_2] = work[-linestride_float_1];
			}
		}else{
			for(work = inr + start_col; work < workend; work += 1){
				work[linestride_float_1] = work[0];
				work[linestride_float_2] = work[0];
			}
		}
	}
}


void extend_horizontal_high(PDC_Threadcall *variable){

	//PDC_Exception *exception	= variable->exception;
	float *in					= variable->sub2_data;
	PDC_int size				= variable->size_high_vertical;
	PDC_int linestride_float	= variable->linestride_float;
	PDC_int start_col			= variable->start_col;
	PDC_int	end_col				= variable->end_col;
	PDC_bool evenl				= variable->evenvl;
	PDC_bool evenr				= variable->evenvr;

	float *work, *workend, *inr;
	PDC_int linestride_float_1 = linestride_float;
	PDC_int linestride_float_2 = linestride_float * 2;
	PDC_int linestride_float_3 = linestride_float * 3;
	PDC_int linestride_float_4 = linestride_float * 4;

	if(evenl){
		inr	= in + (size + 1) * linestride_float;
		if(size > 2){
			workend = in + end_col;
			for(work = in + start_col; work < workend; work += 1){
				work[0] 					= work[linestride_float_3];
				work[linestride_float_1]	= work[linestride_float_2];
			}
		}else{
			workend = in + end_col ;
			for(work = in + start_col ; work < workend; work += 1){
				work[0]						= work[linestride_float_2];
				work[linestride_float_1]	= work[linestride_float_2];
			}
		}

	}else{
		inr	= in + (size + 1) * linestride_float;
		if(size > 2){
			workend = in + end_col;
			for(work = in + start_col; work < workend; work += 1){
				work[0] 					= work[linestride_float_4];
				work[linestride_float_1]	= work[linestride_float_3];
			}
		}else{
			workend = in + end_col;
			for(work = in + start_col; work < workend; work += 1){
				work[0] 					= work[linestride_float_2];
				work[linestride_float_1]	= work[linestride_float_2];
			}
		}
	}

	if(evenr){
		if(size > 2){
			workend = inr + end_col;
			for(work = inr + start_col ; work < workend; work += 1){
				work[linestride_float_1]	= work[0];
				work[linestride_float_2]	= work[-linestride_float_1];
			}
		}else{
			workend = inr + end_col;
			for(work = inr + start_col; work < workend; work += 1){
				work[linestride_float_1]	= work[0];
				work[linestride_float_1]	= work[0];
			}
		}
	}else{
		if(size > 2){
			workend = inr + end_col;
			for(work = inr + start_col; work < workend; work += 1){
				work[linestride_float_1]	= work[-linestride_float_1];
				work[linestride_float_2]	= work[-linestride_float_2];
			}
		}else{
			workend = inr + end_col;
			for(work = inr + start_col; work < workend; work += 1){
				work[linestride_float_1] = work[0];
				work[linestride_float_2] = work[0];
			}
		}
	}
}

/*
 *
 */
PDC_Threadcall* new_PDC_Threadcall_01(PDC_Exception	*exception)
{
	PDC_Threadcall *threadcall;

	threadcall = (PDC_Threadcall*)malloc(sizeof(PDC_Threadcall));
	if(threadcall == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	threadcall->exception				= NULL;
	threadcall->resolution				= NULL;
	threadcall->thread_id				= 0;
	threadcall->thread_number			= 0;
	threadcall->thread_counter			= NULL;
	threadcall->mutex_counter			= NULL;
	threadcall->cond_counter			= NULL;

	threadcall->sub1_data				= NULL;
	threadcall->sub2_data				= NULL;
	threadcall->sub3_data				= NULL;
	threadcall->sub4_data				= NULL;
	threadcall->linestride_float		= 0;

	threadcall->size_low_horizontal		= 0;
	threadcall->size_high_horizontal	= 0;
	threadcall->start_row				= 0;
	threadcall->end_row					= 0;
	threadcall->evenhl					= 0;
	threadcall->evenhr					= 0;

	threadcall->size_low_vertical		= 0;
	threadcall->size_high_vertical		= 0;
	threadcall->start_col				= 0;
	threadcall->end_col					= 0;
	threadcall->evenvl					= 0;
	threadcall->evenvr					= 0;

	threadcall->decoder					= NULL;
	threadcall->out_size_horizontal		= 0;
	threadcall->out_size_vertical		= 0;
	threadcall->end_row					= 0;
	threadcall->start_row				= 0;

	return threadcall;
}

/*
 *
 */
PDC_Threadcall* new_PDC_Threadcall_02(
		PDC_Exception	*exception,
		PDC_int thread_id,
		PDC_int thread_number,
		PDC_int maxSize)
{
	PDC_Threadcall *threadcall;

	threadcall = new_PDC_Threadcall_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return NULL;
	}

	threadcall->decoder = new_PDC_Transformation_97_decoder(exception, maxSize);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return NULL;
	}

	threadcall->thread_id		= thread_id;
	threadcall->thread_number	= thread_number;

	return threadcall;
}

/*
 *
 */
void delete_PDC_Threadcall(
		PDC_Exception *exception,
		PDC_Threadcall* threadcall)
{
	if(threadcall != NULL){
		delete_PDC_Transformation_97_decoder(exception, threadcall->decoder);
		free(threadcall);
	}
}

/*
 *
 */
void *PDC_threadcall_func(void *in)
{
	PDC_Threadcall *variable 	= (PDC_Threadcall*)in;
	PDC_Resolution* resolution	= variable->resolution;

	PDC_int	size1, size2, start, stop;
	float 	*sub1_data, *sub2_data, *sub3_data, *sub4_data, *out_data1, *out_data2;


	sub1_data 	= variable->sub1_data;
	sub2_data 	= variable->sub2_data;
	sub3_data 	= variable->sub3_data;
	sub4_data 	= variable->sub4_data;

	size1 = resolution->subband[0]->my1 - resolution->subband[0]->my0;

	size2	= PDC_i_ceiling( size1 , variable->thread_number);
	start	= size2 * variable->thread_id;
	stop	= start + size2;
	out_data1 = variable->out_data1 = resolution->tile_component->tile_memory2;

	if(start < size1){
		if(stop > size1){
			stop = size1;
		}
		variable->start_row = start;
		variable->end_row	= stop;



		if(variable->evenhl){
			variable->sub1_data -= variable->linestride_float;
			variable->out_data1 -= variable->linestride_float;
		}

		extend_vertical_low(variable);
		extend_vertical_high(variable);
		PDC_td_start_v3_vertical(variable);
	}

	size1 = resolution->subband[1]->my1 - resolution->subband[1]->my0;

	size2	= PDC_i_ceiling( size1 , variable->thread_number);
	start	= size2 * variable->thread_id;
	stop	= start + size2;
	out_data2 = variable->out_data1	= out_data1 + resolution->subband[1]->my0 * variable->linestride_float;

	if(start < size1){
		if(stop > size1){
			stop = size1;
		}
		variable->start_row = start;
		variable->end_row	= stop;



		variable->sub1_data	= sub3_data;
		variable->sub2_data = sub4_data;

		extend_vertical_low(variable);
		extend_vertical_high(variable);
		PDC_td_start_v3_vertical(variable);
	}

	/*
	if(uwe_count == 0 ){
		int posx, posy, endx, endy;
		endx = resolution->mx1 - resolution->mx0;
		endy = resolution->my1 - resolution->my0;
		out_data1	= resolution->tile_component->tile_memory2;

		if(variable->evenvl){
			out_data1 -= 1;
		}

		if(variable->evenhl){
			out_data1 -= variable->linestride_float;
		}

		// fprintf(DEBUG_FILE,"endx = %d endy = %d \n", endx, endy);
		for(posy = 0; posy < endy; posy += 1){
			out_data2 = out_data1 + (posy * variable->linestride_float);
			for(posx = 0; posx < endx; posx += 1){
				fprintf(DEBUG_FILE2," %12.6f ", out_data2[posx]);
			}
			fprintf(DEBUG_FILE2,"\n");
		}
	}
	*/

	/*
	 * All threads have to sync here.
	 */
	pthread_mutex_lock(variable->mutex_counter);
	*(variable->thread_counter) += 1;
	if(*(variable->thread_counter) == variable->thread_number){
		pthread_mutex_unlock(variable->mutex_counter);
		pthread_cond_broadcast(variable->cond_counter);
	}else{
		pthread_cond_wait(variable->cond_counter, variable->mutex_counter);
		pthread_mutex_unlock(variable->mutex_counter);
	}

	variable->out_data1	= resolution->tile_component->tile_memory2;
	variable->sub1_data	= out_data1 - 2 * variable->linestride_float;
	variable->sub2_data	= out_data2 - 2 * variable->linestride_float;

	if(variable->evenhl){
		variable->sub1_data -= 1;
		variable->sub2_data -= 1;
		variable->out_data1 -= 1;
	}


	size1	= resolution->mx1 - resolution->mx0;
	size2	= PDC_i_ceiling( size1 , variable->thread_number);
	start	= size2 * variable->thread_id;
	stop	= start + size2;

	if(start < size1){
		if(stop > size1){
			stop = size1;
		}
		variable->start_col = start;
		variable->end_col	= stop;

		extend_horizontal_low(	variable);
		extend_horizontal_high(	variable);
		PDC_td_start_v3_horizontal(	variable );

	}
	return NULL;
}

STOP_C

