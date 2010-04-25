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
#include <pthread.h>

START_C

	struct str_PDC_Resolution;
	typedef struct str_PDC_Resolution PDC_Resolution;

	struct str_PDC_Threadcall;
	typedef struct str_PDC_Threadcall PDC_Threadcall;


	#include "PDC_Tile_Component.h"
	#include "PDC_Subband.h"
	#include "PDC_COD_Segment.h"
	#include "PDC_Precinct.h"
	#include "PDC_Transformation_97_decoder.h"

	struct str_PDC_Resolution
	{
		PDC_Tile_Component* tile_component;
		PDC_Resolution*		resolution_big;
		PDC_Resolution*		resolution_small;
		PDC_Precinct**		precinct;

		PDC_Subband*		subband[3];
		/*
		PDC_Subband*		subband_ll;
		PDC_Subband*		subband_hl;
		PDC_Subband*		subband_lh;
		PDC_Subband*		subband_hh;
		*/
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

		PDC_int				mx0;
		PDC_int				mx1;
		PDC_int				my0;
		PDC_int				my1;
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

	/*
	 *
	 */
	PDC_uint PDC_Resolution_get_codeblock_position(	PDC_Exception* exception,
													PDC_Resolution* resolution,
													PDC_uint pos_x,
													PDC_uint pos_y);

	/*
	 *
	 */
	PDC_Precinct* PDC_Resolution_get_precinct(	PDC_Exception*	exception,
												PDC_Resolution*	resolution,
												PDC_uint		precinct_pos);

	/*
	 *
	 */
	PDC_Resolution* PDC_Resolution_inverse_quantization(PDC_Exception* exception,
														PDC_Resolution* resolution);

	/*
	 *
	 */
	PDC_Resolution* PDC_Resolution_inverse_transformation_97(	PDC_Exception* exception,
																PDC_Resolution* resolution);

	/*
	 *
	 */
	PDC_Resolution* PDC_Resolution_inverse_transformation_97_v2(	PDC_Exception* exception,
																	PDC_Resolution* resolution);

	/*
	 *
	 */
	PDC_Resolution* PDC_Resolution_inverse_transformation_97_v3(	PDC_Exception* exception,
																	PDC_Resolution* resolution);


	/*
	 *
	 */
	void extend_vertical_low(  PDC_Threadcall *variable);

	/*
	 *
	 */
	void extend_vertical_high(	 PDC_Threadcall *variable);

	/*
	 *
	 */
	void extend_horizontal_low(	 PDC_Threadcall *variable);

	/*
	 *
	 */
	void extend_horizontal_high(	 PDC_Threadcall *variable);


	struct str_PDC_Threadcall{
		PDC_Exception	*exception;
		PDC_Resolution	*resolution;
		PDC_int			thread_id;
		PDC_int			thread_number;
		PDC_int			*thread_counter;
		pthread_t		pthread_id;
		pthread_mutex_t	*mutex_counter;
		pthread_cond_t	*cond_counter;





		float			*sub1_data;
		float			*sub2_data;
		float			*sub3_data;
		float			*sub4_data;
		float			*out_data1;
		PDC_int			linestride_float;

		PDC_int			size_low_horizontal;
		PDC_int			size_high_horizontal;
		PDC_int			start_row;
		PDC_int			end_row;
		PDC_bool		evenhl;
		PDC_bool		evenhr;

		PDC_int			size_low_vertical;
		PDC_int			size_high_vertical;
		PDC_int			start_col;
		PDC_int			end_col;
		PDC_bool		evenvl;
		PDC_bool		evenvr;

		PDC_Transformation_97_decoder* 	decoder;
		PDC_int 						out_size_horizontal;
		PDC_int 						out_size_vertical;


	};

	/*
	 *
	 */
	PDC_Threadcall* new_PDC_Threadcall_01(PDC_Exception	*exception);

	/*
	 *
	 */
	PDC_Threadcall* new_PDC_Threadcall_02(	PDC_Exception	*exception,
											PDC_int thread_id,
											PDC_int thread_number,
											PDC_int maxSize);

	/*
	 *
	 */
	void delete_PDC_Threadcall(PDC_Exception *exception, PDC_Threadcall* threadcall);

	/*
	 *
	 */
	void *PDC_threadcall_func(void *in);

STOP_C
#endif
