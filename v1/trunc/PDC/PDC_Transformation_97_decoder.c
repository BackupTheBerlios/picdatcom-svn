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

#include "PDC_Transformation_97_decoder.h"

START_C

#define d_ALPHA	-1.586134342f
#define d_BETA	-0.05298011854f
#define d_GAMMA	0.8829110762f
#define d_DELTA 0.4435068522f
#define d_K1	0.8128930655f
#define d_K		1.230174106f

/*
float alpha	= -1.586134342059924f;
float beta	= -0.052980118572961f;
float gamma	=  0.882911075530934f;
float delta	=  0.443506852043971f;
float K		=  1.230174104914001f;
float K1	=  1.0f/1.230174104914001f;
*/
float alpha	= d_ALPHA;
float beta	= d_BETA;
float f_gamma	= d_GAMMA;
float delta	= d_DELTA;
float K1	= d_K1;
float K		= d_K;

float ptr_alpha[]	= {d_ALPHA, d_ALPHA, d_ALPHA, d_ALPHA};
float ptr_beta[]	= {d_BETA, d_BETA, d_BETA, d_BETA};
float ptr_gamma[]	= {d_GAMMA, d_GAMMA, d_GAMMA, d_GAMMA};
float ptr_delta[]	= {d_DELTA, d_DELTA, d_DELTA, d_DELTA};
float ptr_K1[]		= {d_K1, d_K1, d_K1, d_K1};
float ptr_K[]		= {d_K, d_K, d_K, d_K};


/*
 *
 */
PDC_Transformation_97_decoder* new_PDC_Transformation_97_decoder(	PDC_Exception* exception,
																	PDC_uint32 maxSize)
{
	PDC_Transformation_97_decoder* decoder = NULL;
	PDC_int extrasize = 6;
	PDC_int modpointer = 16;

	decoder = malloc(sizeof(PDC_Transformation_97_decoder));
	if(decoder == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	decoder->exception	= NULL;
	decoder->workbuffer	= NULL;
	decoder->green		= NULL;
	decoder->pink		= NULL;
	decoder->orange		= NULL;
	decoder->brown		= NULL;

	decoder->maxSize = maxSize;
	decoder->pinkSize =
	decoder->brownSize =
	decoder->greenSize =
	decoder->orangeSize = PDC_i_ceiling(maxSize, 2) + 4;



	decoder->del_green = malloc(sizeof(float) * (decoder->greenSize + extrasize));
	if(decoder->del_green == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	decoder->green = (float*)((PDC_uint)(decoder->del_green) + ((PDC_uint)(decoder->del_green) % modpointer));

	decoder->del_orange	= malloc(sizeof(float) * (decoder->orangeSize + extrasize));
	if(decoder->del_orange == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	decoder->orange = (float*) ((PDC_uint)(decoder->del_orange) + ((PDC_uint)(decoder->del_orange) % modpointer));

	decoder->del_pink	= malloc(sizeof(float) * (decoder->pinkSize + extrasize));
	if(decoder->del_pink == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	decoder->pink = (float*)((PDC_uint)(decoder->del_pink) + ( (PDC_uint)(decoder->del_pink) % modpointer));

	decoder->del_brown	= malloc(sizeof(float) * (decoder->brownSize +extrasize));
	if(decoder->del_brown == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	decoder->brown = (float*) ((PDC_uint)(decoder->del_brown) + ((PDC_uint)(decoder->del_brown) % modpointer));

	decoder->del_workbuffer	= malloc(sizeof(float) * (maxSize + extrasize));
	if(decoder->del_workbuffer == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	decoder->workbuffer = (float*)((PDC_uint)(decoder->del_workbuffer) + ((PDC_uint)(decoder->del_workbuffer) % modpointer));

	return decoder;
}


/*
 *
 */
PDC_Transformation_97_decoder* delete_PDC_Transformation_97_decoder(	PDC_Exception* exception,
																		PDC_Transformation_97_decoder* decoder)
{
	if(decoder != NULL){
		if(decoder->brown != NULL){
			free(decoder->del_brown);
		}
		if(decoder->green != NULL){
			free(decoder->del_green);
		}
		if(decoder->orange != NULL){
			free(decoder->del_orange);
		}
		if(decoder->pink != NULL){
			free(decoder->del_pink);
		}
		if(decoder->workbuffer != NULL){
			free(decoder->del_workbuffer);
		}

		delete_PDC_Exception(decoder->exception);

		free(decoder);
	}

	return NULL;
}

/*
 *
 */
PDC_Transformation_97_decoder* PDC_td_start(	PDC_Exception* exception,
												PDC_Transformation_97_decoder* decoder,
												float *out, float *in_high, float* in_low,
												PDC_uint out_start, PDC_uint out_size, PDC_uint out_plus, PDC_bool even,
												PDC_uint in_high_start, PDC_uint in_high_plus,
												PDC_uint in_low_start, PDC_uint in_low_plus)
{

	PDC_uint i_help1, i_help2, i_help1_end, greensize, orangesize, out_1, out_1end, out_plus2;

	float			*workbuffer;
	float			*green;
	float			*pink;
	float			*orange;
	float			*brown;
	PDC_uint32		greenSize;
	PDC_uint32		pinkSize;
	PDC_uint32		orangeSize;
	PDC_uint32		brownSize;
	PDC_uint32		maxSize;

	greensize	= 0;
	orangesize	= 0;
	workbuffer	= decoder->workbuffer;
	green		= decoder->green;
	pink		= decoder->pink;
	orange		= decoder->orange;
	brown		= decoder->brown;
	greenSize	= decoder->greenSize;
	pinkSize	= decoder->pinkSize;
	orangeSize	= decoder->orangeSize;
	brownSize	= decoder->brownSize;
	maxSize		= decoder->maxSize;


	if(out_size <= maxSize){
		if(out_size > 4){
			if(even){
				if(out_size % 2 == 0){
					i_help1		= 1;
					i_help1_end	= i_help1 + out_size / 2;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
						orange[i_help1] = in_low[i_help2];
					}
					orange[0]			= orange[2];
					orange[i_help1]		= orange[i_help1 - 1];
					orange[i_help1 + 1]	= orange[i_help1 - 2];

					i_help1		= 2;
					i_help1_end	= i_help1 + out_size / 2;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
						green[i_help1] = in_high[i_help2];
					}
					green[0]			= green[3];
					green[1]			= green[2];
					green[i_help1]		= green[i_help1 - 2];
					green[i_help1 + 1]	= green[i_help1 - 3];
					greensize			= out_size / 2 + 4;
					orangesize			= greensize - 1;
				}else{
					i_help1		= 1;
					i_help1_end	= i_help1 + PDC_i_ceiling(out_size , 2);
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
						orange[i_help1] = in_low[i_help2];
					}
					orange[0]			= orange[2];
					orange[i_help1]		= orange[i_help1 - 2];


					i_help1		= 2;
					i_help1_end	= i_help1 + PDC_i_ceiling(out_size , 2) - 1;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
						green[i_help1] = in_high[i_help2];
					}
					green[0]			= green[3];
					green[1]			= green[2];
					green[i_help1]		= green[i_help1 - 1];
					green[i_help1 + 1]	= green[i_help1 - 2];

					greensize			= PDC_i_floor( out_size , 2) + 4;
					orangesize			= greensize - 1;
				}
			}else{
				if(out_size % 2 == 0){
					i_help1		= 2;
					i_help1_end	= i_help1 + out_size / 2;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
						orange[i_help1] = in_low[i_help2];
					}
					orange[0]			= orange[3];
					orange[1]			= orange[2];
					orange[i_help1]		= orange[i_help1 - 2];

					i_help1		= 2;
					i_help1_end	= i_help1 + out_size / 2;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
						green[i_help1] = in_high[i_help2];
					}
					green[0]			= green[4];
					green[1]			= green[3];
					green[i_help1]		= green[i_help1 - 1];
					green[i_help1 + 1]	= green[i_help1 - 2];
					greensize			= out_size / 2 + 4;
					orangesize			= greensize - 1;
				}else{
					i_help1		= 2;
					i_help1_end	= i_help1 + PDC_i_floor(out_size, 2);
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
						orange[i_help1] = in_low[i_help2];
					}
					orange[0]			= orange[3];
					orange[1]			= orange[2];
					orange[i_help1]		= orange[i_help1 - 1];
					orange[i_help1 + 1]	= orange[i_help1 - 2];

					i_help1		= 2;
					i_help1_end	= i_help1 + PDC_i_ceiling(out_size, 2);
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
						green[i_help1] = in_high[i_help2];
					}
					green[0]			= green[4];
					green[1]			= green[3];
					green[i_help1]		= green[i_help1 - 2];
					green[i_help1 + 1]	= green[i_help1 - 3];
					greensize			= PDC_i_ceiling(out_size, 2) + 4;
					orangesize			= greensize - 1;
				}
			}
		}else{
			if(even){
				if(out_size == 1){
					out[out_start] = in_low[in_low_start];
					return decoder;
				}else if(out_size == 2){
					green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					orange[0] = orange[1] = orange[2] = orange[3] = in_low[in_low_start];
					greensize = 5;
					orangesize = 4;
				}else if(out_size == 3){
					green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					orange[0] = orange[2] = in_low[in_low_start + in_low_plus];
					orange[1] = orange[3] = in_low[in_low_start];
					greensize = 5;
					orangesize = 4;
				}else if(out_size == 4){
					green[0] = green[3] = in_high[in_high_start + in_high_plus];
					green[1] = green[2] = green[4] = green[5] = in_high[in_high_start];
					orange[0] = orange[2] = orange[3] = in_low[in_low_start + in_low_plus];
					orange[1] = orange[4] = in_low[in_low_start];
					greensize = 6;
					orangesize = 5;
				}
			}else{
				if(out_size == 1){
					out[out_start] = in_low[in_low_start];
					return decoder;
				}else if(out_size == 2){
					green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					orange[0] = orange[1] = orange[2] = orange[3] = in_low[in_low_start];
					greensize = 5;
					orangesize = 4;
				}else if(out_size == 3){
					green[0] = green[2] = green[4] = in_high[in_high_start];
					green[1] = green[3] = green[5] = in_high[in_high_start + in_high_plus];
					orange[0] = orange[1] = orange[2] = orange[3] = orange[4] = in_low[in_low_start];
					greensize = 6;
					orangesize = 5;
				}else if(out_size == 4){
					green[0] = green[1] = green[3] = green[4] = in_high[in_high_start + in_high_plus];
					green[2] = green[5] = in_high[in_high_start];
					orange[0] = orange[3] = in_low[in_low_start + in_low_plus];
					orange[1] = orange[2] = orange[4] = in_low[in_low_start];
					greensize = 6;
					orangesize =5;
				}
			}
		}

		for(i_help1 = 0; i_help1 < greensize; i_help1 += 1){
			green[i_help1] *= K1;
		}
		for(i_help1 = 0; i_help1 < orangesize; i_help1 += 1){
			orange[i_help1] *= K;
		}

		for(i_help1 = 0, i_help2 = 1; i_help1 < orangesize;){
			orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}

		greensize = orangesize - 1;
		for(i_help1 = 0, i_help2 = 1; i_help1 < greensize;){
			green[i_help1] = green[i_help2] - f_gamma * ( orange[i_help1] + orange[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}

		orangesize = greensize - 1;
		for(i_help1 = 0, i_help2 = 1; i_help1 < orangesize;){
			orange[i_help1] = orange[i_help2] - beta * ( green[i_help1] + green[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}

		greensize = orangesize - 1;
		for(i_help1 = 0, i_help2 = 1; i_help1 < greensize;){
			green[i_help1] = green[i_help2] - alpha * ( orange[i_help1] + orange[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}


		if(even){
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 0;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start + out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 0;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start + out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}
		}else{
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus  + out_start;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus + out_start;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}
		}
	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_SIZE, __LINE__, __FILE__);
	}
	return decoder;
}


/*
 *
 */
PDC_Transformation_97_decoder* PDC_td_start_v2(	PDC_Exception* exception,
													PDC_Transformation_97_decoder* decoder,
													float *out, float *in_high, float* in_low,
													PDC_uint out_start, PDC_uint out_size, PDC_uint out_plus, PDC_bool even,
													PDC_uint in_high_start, PDC_uint in_hight_plus,
													PDC_uint in_low_start, PDC_uint in_low_plus,
													PDC_uint num_rows, PDC_uint high_row_stride, PDC_uint low_row_stride,
													PDC_uint out_row_stride)
{

	PDC_uint i_help1, i_help2, i_help1_end, greensize, orangesize, out_1, out_1end, out_plus2;

	float			*workbuffer;
	float			*green;
	float			*pink;
	float			*orange;
	float			*brown;
	PDC_uint32		greenSize;
	PDC_uint32		pinkSize;
	PDC_uint32		orangeSize;
	PDC_uint32		brownSize;
	PDC_uint32		maxSize;

	greensize	= 0;
	orangesize	= 0;
	workbuffer	= decoder->workbuffer;
	green		= decoder->green;
	pink		= decoder->pink;
	orange		= decoder->orange;
	brown		= decoder->brown;
	greenSize	= decoder->greenSize;
	pinkSize	= decoder->pinkSize;
	orangeSize	= decoder->orangeSize;
	brownSize	= decoder->brownSize;
	maxSize		= decoder->maxSize;


	if(out_size <= maxSize){
		if(out_size > 4){
			if(even){
				if(out_size % 2 == 0){
					i_help1		= 1;
					i_help1_end	= i_help1 + out_size / 2;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
						orange[i_help1] = in_low[i_help2];
					}
					orange[0]			= orange[2];
					orange[i_help1]		= orange[i_help1 - 1];
					orange[i_help1 + 1]	= orange[i_help1 - 2];

					i_help1		= 2;
					i_help1_end	= i_help1 + out_size / 2;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
						green[i_help1] = in_high[i_help2];
					}
					green[0]			= green[3];
					green[1]			= green[2];
					green[i_help1]		= green[i_help1 - 2];
					green[i_help1 + 1]	= green[i_help1 - 3];
					greensize			= out_size / 2 + 4;
					orangesize			= greensize - 1;
				}else{
					i_help1		= 1;
					i_help1_end	= i_help1 + PDC_i_ceiling(out_size , 2);
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
						orange[i_help1] = in_low[i_help2];
					}
					orange[0]			= orange[2];
					orange[i_help1]		= orange[i_help1 - 2];


					i_help1		= 2;
					i_help1_end	= i_help1 + PDC_i_ceiling(out_size , 2) - 1;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
						green[i_help1] = in_high[i_help2];
					}
					green[0]			= green[3];
					green[1]			= green[2];
					green[i_help1]		= green[i_help1 - 1];
					green[i_help1 + 1]	= green[i_help1 - 2];

					greensize			= PDC_i_floor( out_size , 2) + 4;
					orangesize			= greensize - 1;
				}
			}else{
				if(out_size % 2 == 0){
					i_help1		= 2;
					i_help1_end	= i_help1 + out_size / 2;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
						orange[i_help1] = in_low[i_help2];
					}
					orange[0]			= orange[3];
					orange[1]			= orange[2];
					orange[i_help1]		= orange[i_help1 - 2];

					i_help1		= 2;
					i_help1_end	= i_help1 + out_size / 2;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
						green[i_help1] = in_high[i_help2];
					}
					green[0]			= green[4];
					green[1]			= green[3];
					green[i_help1]		= green[i_help1 - 1];
					green[i_help1 + 1]	= green[i_help1 - 2];
					greensize			= out_size / 2 + 4;
					orangesize			= greensize - 1;
				}else{
					i_help1		= 2;
					i_help1_end	= i_help1 + PDC_i_floor(out_size, 2);
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
						orange[i_help1] = in_low[i_help2];
					}
					orange[0]			= orange[3];
					orange[1]			= orange[2];
					orange[i_help1]		= orange[i_help1 - 1];
					orange[i_help1 + 1]	= orange[i_help1 - 2];

					i_help1		= 2;
					i_help1_end	= i_help1 + PDC_i_ceiling(out_size, 2);
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
						green[i_help1] = in_high[i_help2];
					}
					green[0]			= green[4];
					green[1]			= green[3];
					green[i_help1]		= green[i_help1 - 2];
					green[i_help1 + 1]	= green[i_help1 - 3];
					greensize			= PDC_i_ceiling(out_size, 2) + 4;
					orangesize			= greensize - 1;
				}
			}
		}else{
			if(even){
				if(out_size == 1){
					out[out_start] = in_low[in_low_start];
					return decoder;
				}else if(out_size == 2){
					green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					orange[0] = orange[1] = orange[2] = orange[3] = in_low[in_low_start];
					greensize = 5;
					orangesize = 4;
				}else if(out_size == 3){
					green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					orange[0] = orange[2] = in_low[in_low_start + in_low_plus];
					orange[1] = orange[3] = in_low[in_low_start];
					greensize = 5;
					orangesize = 4;
				}else if(out_size == 4){
					green[0] = green[3] = in_high[in_high_start + in_high_plus];
					green[1] = green[2] = green[4] = green[5] = in_high[in_high_start];
					orange[0] = orange[2] = orange[3] = in_low[in_low_start + in_low_plus];
					orange[1] = orange[4] = in_low[in_low_start];
					greensize = 6;
					orangesize = 5;
				}
			}else{
				if(out_size == 1){
					out[out_start] = in_low[in_low_start];
					return decoder;
				}else if(out_size == 2){
					green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					orange[0] = orange[1] = orange[2] = orange[3] = in_low[in_low_start];
					greensize = 5;
					orangesize = 4;
				}else if(out_size == 3){
					green[0] = green[2] = green[4] = in_high[in_high_start];
					green[1] = green[3] = green[5] = in_high[in_high_start + in_high_plus];
					orange[0] = orange[1] = orange[2] = orange[3] = orange[4] = in_low[in_low_start];
					greensize = 6;
					orangesize = 5;
				}else if(out_size == 4){
					green[0] = green[1] = green[3] = green[4] = in_high[in_high_start + in_high_plus];
					green[2] = green[5] = in_high[in_high_start];
					orange[0] = orange[3] = in_low[in_low_start + in_low_plus];
					orange[1] = orange[2] = orange[4] = in_low[in_low_start];
					greensize = 6;
					orangesize =5;
				}
			}
		}

		for(i_help1 = 0; i_help1 < greensize; i_help1 += 1){
			green[i_help1] *= K1;
		}
		for(i_help1 = 0; i_help1 < orangesize; i_help1 += 1){
			orange[i_help1] *= K;
		}

		for(i_help1 = 0, i_help2 = 1; i_help1 < orangesize;){
			orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}

		greensize = orangesize - 1;
		for(i_help1 = 0, i_help2 = 1; i_help1 < greensize;){
			green[i_help1] = green[i_help2] - f_gamma * ( orange[i_help1] + orange[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}

		orangesize = greensize - 1;
		for(i_help1 = 0, i_help2 = 1; i_help1 < orangesize;){
			orange[i_help1] = orange[i_help2] - beta * ( green[i_help1] + green[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}

		greensize = orangesize - 1;
		for(i_help1 = 0, i_help2 = 1; i_help1 < greensize;){
			green[i_help1] = green[i_help2] - alpha * ( orange[i_help1] + orange[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}


		if(even){
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 0;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start + out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 0;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start + out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}
		}else{
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus  + out_start;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus + out_start;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}
		}
	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_SIZE, __LINE__, __FILE__);
	}
	return decoder;
}



/*
 *
 */
PDC_Transformation_97_decoder* PDC_td_start_sse2(	PDC_Exception* exception,
													PDC_Transformation_97_decoder* decoder,
													float *out, float *in_high, float* in_low,
													PDC_uint out_start, PDC_uint out_size, PDC_uint out_plus, PDC_bool even,
													PDC_uint in_high_start, PDC_uint in_high_plus,
													PDC_uint in_low_start, PDC_uint in_low_plus)
{

	PDC_uint i_help1, i_help2, i_help1_end, greensize, orangesize, out_1, out_1end, out_plus2;

	float			*workbuffer;
	float			*green;
	float			*pink;
	float			*orange;
	float			*brown;
	PDC_uint32		greenSize;
	PDC_uint32		pinkSize;
	PDC_uint32		orangeSize;
	PDC_uint32		brownSize;
	PDC_uint32		maxSize;

	workbuffer	= decoder->workbuffer;
	green		= decoder->green;
	pink		= decoder->pink;
	orange		= decoder->orange;
	brown		= decoder->brown;
	greenSize	= decoder->greenSize;
	pinkSize	= decoder->pinkSize;
	orangeSize	= decoder->orangeSize;
	brownSize	= decoder->brownSize;
	maxSize		= decoder->maxSize;


	if(out_size <= maxSize){
		if(out_size > 4){
			if(even){
				if(out_size % 2 == 0){
					i_help1		= 1;
					i_help1_end	= i_help1 + out_size / 2;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
						orange[i_help1] = in_low[i_help2];
					}
					orange[0]			= orange[2];
					orange[i_help1]		= orange[i_help1 - 1];
					orange[i_help1 + 1]	= orange[i_help1 - 2];

					i_help1		= 2;
					i_help1_end	= i_help1 + out_size / 2;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
						green[i_help1] = in_high[i_help2];
					}
					green[0]			= green[3];
					green[1]			= green[2];
					green[i_help1]		= green[i_help1 - 2];
					green[i_help1 + 1]	= green[i_help1 - 3];
					greensize			= out_size / 2 + 4;
					orangesize			= greensize - 1;
				}else{
					i_help1		= 1;
					i_help1_end	= i_help1 + PDC_i_ceiling(out_size , 2);
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
						orange[i_help1] = in_low[i_help2];
					}
					orange[0]			= orange[2];
					orange[i_help1]		= orange[i_help1 - 2];


					i_help1		= 2;
					i_help1_end	= i_help1 + PDC_i_ceiling(out_size , 2) - 1;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
						green[i_help1] = in_high[i_help2];
					}
					green[0]			= green[3];
					green[1]			= green[2];
					green[i_help1]		= green[i_help1 - 1];
					green[i_help1 + 1]	= green[i_help1 - 2];

					greensize			= PDC_i_floor( out_size , 2) + 4;
					orangesize			= greensize - 1;
				}
			}else{
				if(out_size % 2 == 0){
					i_help1		= 2;
					i_help1_end	= i_help1 + out_size / 2;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
						orange[i_help1] = in_low[i_help2];
					}
					orange[0]			= orange[3];
					orange[1]			= orange[2];
					orange[i_help1]		= orange[i_help1 - 2];

					i_help1		= 2;
					i_help1_end	= i_help1 + out_size / 2;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
						green[i_help1] = in_high[i_help2];
					}
					green[0]			= green[4];
					green[1]			= green[3];
					green[i_help1]		= green[i_help1 - 1];
					green[i_help1 + 1]	= green[i_help1 - 2];
					greensize			= out_size / 2 + 4;
					orangesize			= greensize - 1;
				}else{
					i_help1		= 2;
					i_help1_end	= i_help1 + PDC_i_floor(out_size, 2);
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
						orange[i_help1] = in_low[i_help2];
					}
					orange[0]			= orange[3];
					orange[1]			= orange[2];
					orange[i_help1]		= orange[i_help1 - 1];
					orange[i_help1 + 1]	= orange[i_help1 - 2];

					i_help1		= 2;
					i_help1_end	= i_help1 + PDC_i_ceiling(out_size, 2);
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
						green[i_help1] = in_high[i_help2];
					}
					green[0]			= green[4];
					green[1]			= green[3];
					green[i_help1]		= green[i_help1 - 2];
					green[i_help1 + 1]	= green[i_help1 - 3];
					greensize			= PDC_i_ceiling(out_size, 2) + 4;
					orangesize			= greensize - 1;
				}
			}
		}else{
			if(even){
				if(out_size == 1){
					out[out_start] = in_low[in_low_start];
					return decoder;
				}else if(out_size == 2){
					green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					orange[0] = orange[1] = orange[2] = orange[3] = in_low[in_low_start];
					greensize = 5;
					orangesize = 4;
				}else if(out_size == 3){
					green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					orange[0] = orange[2] = in_low[in_low_start + in_low_plus];
					orange[1] = orange[3] = in_low[in_low_start];
					greensize = 5;
					orangesize = 4;
				}else if(out_size == 4){
					green[0] = green[3] = in_high[in_high_start + in_high_plus];
					green[1] = green[2] = green[4] = green[5] = in_high[in_high_start];
					orange[0] = orange[2] = orange[3] = in_low[in_low_start + in_low_plus];
					orange[1] = orange[4] = in_low[in_low_start];
					greensize = 6;
					orangesize = 5;
				}
			}else{
				if(out_size == 1){
					out[out_start] = in_low[in_low_start];
					return decoder;
				}else if(out_size == 2){
					green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					orange[0] = orange[1] = orange[2] = orange[3] = in_low[in_low_start];
					greensize = 5;
					orangesize = 4;
				}else if(out_size == 3){
					green[0] = green[2] = green[4] = in_high[in_high_start];
					green[1] = green[3] = green[5] = in_high[in_high_start + in_high_plus];
					orange[0] = orange[1] = orange[2] = orange[3] = orange[4] = in_low[in_low_start];
					greensize = 6;
					orangesize = 5;
				}else if(out_size == 4){
					green[0] = green[1] = green[3] = green[4] = in_high[in_high_start + in_high_plus];
					green[2] = green[5] = in_high[in_high_start];
					orange[0] = orange[3] = in_low[in_low_start + in_low_plus];
					orange[1] = orange[2] = orange[4] = in_low[in_low_start];
					greensize = 6;
					orangesize =5;
				}
			}
		}

		/*

		PDC_td_start_sse2_kernel(	workbuffer,
									green,
									pink,
									orange,
									brown,
									greenSize,
									pinkSize,
									orangeSize,
									brownSize,
									maxSize,
									ptr_alpha,
									ptr_beta,
									ptr_gamma,
									ptr_delta,
									ptr_K1,
									ptr_K);


		for(i_help1 = 0; i_help1 < greensize; i_help1 += 1){
			green[i_help1] *= K1;
		}
		for(i_help1 = 0; i_help1 < orangesize; i_help1 += 1){
			orange[i_help1] *= K;
		}

		for(i_help1 = 0, i_help2 = 1; i_help1 < orangesize;){
			orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}

		greensize = orangesize - 1;
		for(i_help1 = 0, i_help2 = 1; i_help1 < greensize;){
			green[i_help1] = green[i_help2] - gamma * ( orange[i_help1] + orange[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}

		orangesize = greensize - 1;
		for(i_help1 = 0, i_help2 = 1; i_help1 < orangesize;){
			orange[i_help1] = orange[i_help2] - beta * ( green[i_help1] + green[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}

		greensize = orangesize - 1;
		for(i_help1 = 0, i_help2 = 1; i_help1 < greensize;){
			green[i_help1] = green[i_help2] - alpha * ( orange[i_help1] + orange[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}
		*/

		if(even){
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 0;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start + out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 0;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start + out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}
		}else{
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus  + out_start;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus + out_start;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}
		}
	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_SIZE, __LINE__, __FILE__);
	}
	return decoder;
}
STOP_C

