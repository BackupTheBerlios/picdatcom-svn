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

#include "PDC_Transformation_97_decoder.h"
#include <malloc.h>
#include <stdio.h>

START_C

/*
extern FILE* DEBUG_FILE;
extern FILE* DEBUG_FILE2;
*/

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


/*
 *
 */
PDC_Transformation_97_decoder* new_PDC_Transformation_97_decoder(	PDC_Exception* exception,
																	PDC_uint32 maxSize)
{
	long i;

	unsigned long temp_add;

	PDC_Transformation_97_decoder* decoder = NULL;
	PDC_int extrasize = 6;


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

	decoder->alpha		= NULL;
	decoder->beta		= NULL;
	decoder->gamma		= NULL;
	decoder->delta		= NULL;
	decoder->K			= NULL;
	decoder->K1			= NULL;

	decoder->delete_green		= NULL;
	decoder->delete_orange		= NULL;

	decoder->delete_alpha		= NULL;
	decoder->delete_beta		= NULL;
	decoder->delete_gamma		= NULL;
	decoder->delete_delta		= NULL;
	decoder->delete_K			= NULL;
	decoder->delete_K1			= NULL;

	decoder->maxSize = maxSize;
	decoder->pinkSize =
	decoder->brownSize =
	decoder->greenSize =
	decoder->orangeSize = PDC_i_ceiling(maxSize, 2) + 4;


	decoder->delete_green = (float*)malloc(16 + sizeof(float) * (decoder->greenSize + extrasize) * 4);
	if(decoder->delete_green == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	temp_add = (unsigned long)decoder->delete_green;
	decoder->green = (float*)(temp_add + 16 - (temp_add % 16));

	decoder->delete_orange	=(float*)malloc(16 + sizeof(float) * (decoder->orangeSize + extrasize) * 4);
	if(decoder->delete_orange == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	temp_add = (unsigned long)decoder->delete_orange;
	decoder->orange = (float*)(temp_add + 16 - (temp_add % 16));


	decoder->delete_alpha	= (float*)malloc(16 + sizeof(float) * 4);
	if(decoder->delete_alpha == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	temp_add = (unsigned long)decoder->delete_alpha;
	decoder->alpha = (float*)(temp_add + 16 - (temp_add % 16));


	decoder->delete_beta	= (float*)malloc(16 + sizeof(float) * 4);
	if(decoder->delete_beta == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	temp_add = (unsigned long)decoder->delete_beta;
	decoder->beta = (float*)(temp_add + 16 - (temp_add % 16));


	decoder->delete_gamma	= (float*)malloc(16 + sizeof(float) * 4);
	if(decoder->delete_gamma == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	temp_add = (unsigned long)decoder->delete_gamma;
	decoder->gamma = (float*)(temp_add + 16 - (temp_add % 16));

	decoder->delete_delta	= (float*)malloc(16 + sizeof(float) * 4);
	if(decoder->delete_delta == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	temp_add = (unsigned long)decoder->delete_delta;
	decoder->delta = (float*)(temp_add + 16 - (temp_add % 16));


	decoder->delete_K	= (float*)malloc(16 + sizeof(float) * 4);
	if(decoder->delete_K == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	temp_add = (unsigned long)decoder->delete_K;
	decoder->K = (float*)(temp_add + 16 - (temp_add % 16));

	decoder->delete_K1	= (float*)malloc(16 + sizeof(float) * 4);
	if(decoder->delete_K1 == NULL){
		decoder = delete_PDC_Transformation_97_decoder(exception, decoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	temp_add = (unsigned long)decoder->delete_K1;
	decoder->K1 = (float*)(temp_add + 16 - (temp_add % 16));


	for(i = 0; i < 4; i++){
		decoder->alpha[i]	=	d_ALPHA;
		decoder->beta[i]	=	d_BETA;
		decoder->gamma[i]	=	d_GAMMA;
		decoder->delta[i]	=	d_DELTA;
		decoder->K[i]		=	d_K;
		decoder->K1[i]		=	d_K1;
	}

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
			free(decoder->brown);
		}
		if(decoder->delete_green != NULL){
			free(decoder->delete_green);
		}
		if(decoder->delete_orange != NULL){
			free(decoder->delete_orange);
		}
		if(decoder->pink != NULL){
			free(decoder->pink);
		}
		if(decoder->workbuffer != NULL){
			free(decoder->workbuffer);
		}

		if(decoder->delete_alpha != NULL){
			free(decoder->delete_alpha);
		}

		if(decoder->delete_beta != NULL){
			free(decoder->delete_beta);
		}

		if(decoder->delete_gamma != NULL){
			free(decoder->delete_gamma);
		}

		if(decoder->delete_delta != NULL){
			free(decoder->delete_delta);
		}

		if(decoder->delete_K != NULL){
			free(decoder->delete_K);
		}

		if(decoder->delete_K1 != NULL){
			free(decoder->delete_K1);
		}


		//delete_PDC_Exception(decoder->exception);

		free(decoder);
	}

	return NULL;
}


//extern int uwe_count;

/*
 *
 */
PDC_Transformation_97_decoder* PDC_td_start_v1(	PDC_Exception* exception,
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

		/*
		if(uwe_count == 0){
			for(i_help1 = 0; i_help1 < greensize; i_help1 += 1){
				fprintf(DEBUG_FILE,"%6d green   %13.2f \n",i_help1, green[i_help1]);
			}

			for(i_help1 = 0; i_help1 < orangesize; i_help1 += 1){
				fprintf(DEBUG_FILE,"%6d orange   %13.2f \n",i_help1, orange[i_help1]);
			}
			uwe_count += 1;
		}
		 */
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
													PDC_uint out_start, PDC_uint out_size,
													PDC_uint out_plus,  PDC_bool even,
													PDC_uint in_high_start, PDC_uint in_high_plus,
													PDC_uint in_low_start, PDC_uint in_low_plus,
													PDC_uint num_rows, PDC_uint high_stride, PDC_uint low_stride,
													PDC_uint out_stride)
{
	// PDC_uint temp_numLoops, temp_numLoopsunrolled, tem_restLoop;
	PDC_uint i_help1, i_help2, i_help1_end, greensize, orangesize, greensize_temp, orangesize_temp, out_1, out_1end, out_plus2;
	PDC_uint low_stride2, low_stride3, low_stride4;
	PDC_uint high_stride2, high_stride3, high_stride4;
	PDC_uint out_stride2, out_stride3, out_stride4;

	float			*workbuffer;
	float			*green1, * green2, *green3, *green4;
	float			*pink;
	float			*orange1, *orange2, *orange3, *orange4;
	float			*brown;
	float			*in_high1;
	float			*in_low1;
	PDC_uint32		greenSize;
	PDC_uint32		pinkSize;
	PDC_uint32		orangeSize;
	PDC_uint32		brownSize;
	PDC_uint32		maxSize;


	if(num_rows == 4){
		in_high1	= in_high;
		in_low1		= in_low;

		low_stride2	= low_stride;
		low_stride3	= low_stride * 2;
		low_stride4	= low_stride * 3;

		high_stride2	= high_stride;
		high_stride3	= high_stride * 2;
		high_stride4	= high_stride * 3;

		out_stride2	= out_stride;
		out_stride3 = out_stride * 2;
		out_stride4	= out_stride * 3;

	}else if(num_rows == 3){
		in_high1	= in_high;
		in_low1		= in_low;

		low_stride2	= low_stride;
		low_stride3	= low_stride * 2;
		low_stride4	= 0;

		high_stride2	= high_stride;
		high_stride3	= high_stride * 2;
		high_stride4	= 0;

		out_stride2	= out_stride;
		out_stride3 = out_stride * 2;
		out_stride4	= 0;

	}else if(num_rows == 2){
		in_high1	= in_high;
		in_low1		= in_low;

		low_stride2	= low_stride;
		low_stride3	= 0;
		low_stride4	= 0;

		high_stride2	= high_stride;
		high_stride3	= 0;
		high_stride4	= 0;

		out_stride2	= out_stride;
		out_stride3 = 0;
		out_stride4	= 0;

	}else if(num_rows == 1){
		in_high1	= in_high;
		in_low1		= in_low;

		low_stride2	= 0;
		low_stride3	= 0;
		low_stride4	= 0;

		high_stride2	= 0;
		high_stride3	= 0;
		high_stride4	= 0;

		out_stride2	= 0;
		out_stride3 = 0;
		out_stride4	= 0;

	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_DECODER, __LINE__, __FILE__);
		return decoder;
	}

	greensize	= 0;
	orangesize	= 0;
	workbuffer	= decoder->workbuffer;
	green1		= decoder->green;
	green2		= decoder->green + 1;
	green3		= decoder->green + 2;
	green4		= decoder->green + 3;
	pink		= decoder->pink;
	orange1		= decoder->orange;
	orange2		= decoder->orange + 1;
	orange3		= decoder->orange + 2;
	orange4		= decoder->orange + 3;
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
					i_help1		= 4;								//i_help1		= 1;
					i_help1_end	= (1 + out_size / 2) * 4;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_low_plus){
						orange1[i_help1] = in_low1[i_help2];
						orange2[i_help1] = in_low1[i_help2 + low_stride2];
						orange3[i_help1] = in_low1[i_help2 + low_stride3];
						orange4[i_help1] = in_low1[i_help2 + low_stride4];
					}
					orange1[0]				= orange1[8];				// orange[0]			= orange[2];
					orange1[i_help1]		= orange1[i_help1 - 4];		// orange[i_help1]		= orange[i_help1 - 1];
					orange1[i_help1 + 4]	= orange1[i_help1 - 8];		// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange2[0]				= orange2[8];				// orange[0]			= orange[2];
					orange2[i_help1]		= orange2[i_help1 - 4];		// orange[i_help1]		= orange[i_help1 - 1];
					orange2[i_help1 + 4]	= orange2[i_help1 - 8];		// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange3[0]				= orange3[8];				// orange[0]			= orange[2];
					orange3[i_help1]		= orange3[i_help1 - 4];		// orange[i_help1]		= orange[i_help1 - 1];
					orange3[i_help1 + 4]	= orange3[i_help1 - 8];		// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange4[0]				= orange4[8];				// orange[0]			= orange[2];
					orange4[i_help1]		= orange4[i_help1 - 4];		// orange[i_help1]		= orange[i_help1 - 1];
					orange4[i_help1 + 4]	= orange4[i_help1 - 8];		// orange[i_help1 + 1]	= orange[i_help1 - 2];


					i_help1 	= 8; 									//i_help1		= 2;
					i_help1_end	= (2 + out_size / 2) * 4;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_high_plus){
						green1[i_help1] = in_high1[i_help2];
						green2[i_help1] = in_high1[i_help2 + high_stride2];
						green3[i_help1] = in_high1[i_help2 + high_stride3];
						green4[i_help1] = in_high1[i_help2 + high_stride4];
					}
					green1[0]			= green1[12];					//green[0]			= green[3];
					green1[4]			= green1[8];						//green[1]			= green[2];
					green1[i_help1]		= green1[i_help1 - 8];			//green[i_help1]		= green[i_help1 - 2];
					green1[i_help1 + 4]	= green1[i_help1 - 12];			//green[i_help1 + 1]	= green[i_help1 - 3];

					green2[0]			= green2[12];					//green[0]			= green[3];
					green2[4]			= green2[8];						//green[1]			= green[2];
					green2[i_help1]		= green2[i_help1 - 8];			//green[i_help1]		= green[i_help1 - 2];
					green2[i_help1 + 4]	= green2[i_help1 - 12];			//green[i_help1 + 1]	= green[i_help1 - 3];

					green3[0]			= green3[12];					//green[0]			= green[3];
					green3[4]			= green3[8];						//green[1]			= green[2];
					green3[i_help1]		= green3[i_help1 - 8];			//green[i_help1]		= green[i_help1 - 2];
					green3[i_help1 + 4]	= green3[i_help1 - 12];			//green[i_help1 + 1]	= green[i_help1 - 3];

					green4[0]			= green4[12];					//green[0]			= green[3];
					green4[4]			= green4[8];						//green[1]			= green[2];
					green4[i_help1]		= green4[i_help1 - 8];			//green[i_help1]		= green[i_help1 - 2];
					green4[i_help1 + 4]	= green4[i_help1 - 12];			//green[i_help1 + 1]	= green[i_help1 - 3];

					greensize			= out_size / 2 + 4;
					orangesize			= greensize - 1;
				}else{
					i_help1		= 4;
					i_help1_end	= (1 + PDC_i_ceiling(out_size , 2)) * 4;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_low_plus){
						orange1[i_help1] = in_low1[i_help2];
						orange2[i_help1] = in_low1[i_help2 + low_stride2];
						orange3[i_help1] = in_low1[i_help2 + low_stride3];
						orange4[i_help1] = in_low1[i_help2 + low_stride4];
					}
					orange1[0]			= orange1[8];				//orange[0]			= orange[2];
					orange1[i_help1]	= orange1[i_help1 - 8];		//orange[i_help1]		= orange[i_help1 - 2];

					orange2[0]			= orange2[8];				//orange[0]			= orange[2];
					orange2[i_help1]	= orange2[i_help1 - 8];		//orange[i_help1]		= orange[i_help1 - 2];

					orange3[0]			= orange3[8];				//orange[0]			= orange[2];
					orange3[i_help1]	= orange3[i_help1 - 8];		//orange[i_help1]		= orange[i_help1 - 2];

					orange4[0]			= orange4[8];				//orange[0]			= orange[2];
					orange4[i_help1]	= orange4[i_help1 - 8];		//orange[i_help1]		= orange[i_help1 - 2];


					i_help1		= 8;
					i_help1_end	= (2 + PDC_i_ceiling(out_size , 2) - 1) * 4;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_high_plus){
						green1[i_help1] = in_high1[i_help2];
						green2[i_help1] = in_high1[i_help2 + high_stride2];
						green3[i_help1] = in_high1[i_help2 + high_stride3];
						green4[i_help1] = in_high1[i_help2 + high_stride4];
					}
					green1[0]			= green1[12];				//green[0]			= green[3];
					green1[4]			= green1[8];				//green[1]			= green[2];
					green1[i_help1]		= green1[i_help1 - 4];		//green[i_help1]		= green[i_help1 - 1];
					green1[i_help1 + 4]	= green1[i_help1 - 8];		//green[i_help1 + 1]	= green[i_help1 - 2];

					green2[0]			= green2[12];				//green[0]			= green[3];
					green2[4]			= green2[8];				//green[1]			= green[2];
					green2[i_help1]		= green2[i_help1 - 4];		//green[i_help1]		= green[i_help1 - 1];
					green2[i_help1 + 4]	= green2[i_help1 - 8];		//green[i_help1 + 1]	= green[i_help1 - 2];

					green3[0]			= green3[12];				//green[0]			= green[3];
					green3[4]			= green3[8];				//green[1]			= green[2];
					green3[i_help1]		= green3[i_help1 - 4];		//green[i_help1]		= green[i_help1 - 1];
					green3[i_help1 + 4]	= green3[i_help1 - 8];		//green[i_help1 + 1]	= green[i_help1 - 2];

					green4[0]			= green4[12];				//green[0]			= green[3];
					green4[4]			= green4[8];				//green[1]			= green[2];
					green4[i_help1]		= green4[i_help1 - 4];		//green[i_help1]		= green[i_help1 - 1];
					green4[i_help1 + 4]	= green4[i_help1 - 8];		//green[i_help1 + 1]	= green[i_help1 - 2];

					greensize			= PDC_i_floor( out_size , 2) + 4;
					orangesize			= greensize - 1;
				}
			}else{
				if(out_size % 2 == 0){
					i_help1		= 8;
					i_help1_end	= (2 + out_size / 2) * 4;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_low_plus){
						orange1[i_help1] = in_low1[i_help2];
						orange2[i_help1] = in_low1[i_help2 + low_stride2];
						orange3[i_help1] = in_low1[i_help2 + low_stride3];
						orange4[i_help1] = in_low1[i_help2 + low_stride4];

					}
					orange1[0]			= orange1[12];					// orange[0]			= orange[3];
					orange1[4]			= orange1[8];					// orange[1]			= orange[2];
					orange1[i_help1]	= orange1[i_help1 - 8];			// orange[i_help1]		= orange[i_help1 - 2];

					orange2[0]			= orange2[12];					// orange[0]			= orange[3];
					orange2[4]			= orange2[8];					// orange[1]			= orange[2];
					orange2[i_help1]	= orange2[i_help1 - 8];			// orange[i_help1]		= orange[i_help1 - 2];

					orange3[0]			= orange3[12];					// orange[0]			= orange[3];
					orange3[4]			= orange3[8];					// orange[1]			= orange[2];
					orange3[i_help1]	= orange3[i_help1 - 8];			// orange[i_help1]		= orange[i_help1 - 2];

					orange4[0]			= orange4[12];					// orange[0]			= orange[3];
					orange4[4]			= orange4[8];					// orange[1]			= orange[2];
					orange4[i_help1]	= orange4[i_help1 - 8];			// orange[i_help1]		= orange[i_help1 - 2];


					i_help1		= 8;
					i_help1_end	= (2 + out_size / 2) * 4;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_high_plus){
						green1[i_help1] = in_high1[i_help2];
						green2[i_help1] = in_high1[i_help2 + high_stride2];
						green3[i_help1] = in_high1[i_help2 + high_stride3];
						green4[i_help1] = in_high1[i_help2 + high_stride4];
					}
					green1[0]			= green1[16];					// green[0]			= green[4];
					green1[4]			= green1[12];					// green[1]			= green[3];
					green1[i_help1]		= green1[i_help1 - 4];			// green[i_help1]		= green[i_help1 - 1];
					green1[i_help1 + 4]	= green1[i_help1 - 8];			// green[i_help1 + 1]	= green[i_help1 - 2];

					green2[0]			= green2[16];					// green[0]			= green[4];
					green2[4]			= green2[12];					// green[1]			= green[3];
					green2[i_help1]		= green2[i_help1 - 4];			// green[i_help1]		= green[i_help1 - 1];
					green2[i_help1 + 4]	= green2[i_help1 - 8];			// green[i_help1 + 1]	= green[i_help1 - 2];

					green3[0]			= green3[16];					// green[0]			= green[4];
					green3[4]			= green3[12];					// green[1]			= green[3];
					green3[i_help1]		= green3[i_help1 - 4];			// green[i_help1]		= green[i_help1 - 1];
					green3[i_help1 + 4]	= green3[i_help1 - 8];			// green[i_help1 + 1]	= green[i_help1 - 2];

					green4[0]			= green4[16];					// green[0]			= green[4];
					green4[4]			= green4[12];					// green[1]			= green[3];
					green4[i_help1]		= green4[i_help1 - 4];			// green[i_help1]		= green[i_help1 - 1];
					green4[i_help1 + 4]	= green4[i_help1 - 8];			// green[i_help1 + 1]	= green[i_help1 - 2];

					greensize			= out_size / 2 + 4;
					orangesize			= greensize - 1;
				}else{
					i_help1		= 8;
					i_help1_end	= (2 + PDC_i_floor(out_size, 2)) * 4;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_low_plus){
						orange1[i_help1] = in_low1[i_help2];
						orange2[i_help1] = in_low1[i_help2 + low_stride2];
						orange3[i_help1] = in_low1[i_help2 + low_stride3];
						orange4[i_help1] = in_low1[i_help2 + low_stride4];
					}
					orange1[0]				= orange1[12];					// orange[0]			= orange[3];
					orange1[4]				= orange1[8];					// orange[1]			= orange[2];
					orange1[i_help1]		= orange1[i_help1 - 4];			// orange[i_help1]		= orange[i_help1 - 1];
					orange1[i_help1 + 4]	= orange1[i_help1 - 8];			// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange2[0]				= orange2[12];					// orange[0]			= orange[3];
					orange2[4]				= orange2[8];					// orange[1]			= orange[2];
					orange2[i_help1]		= orange2[i_help1 - 4];			// orange[i_help1]		= orange[i_help1 - 1];
					orange2[i_help1 + 4]	= orange2[i_help1 - 8];			// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange3[0]				= orange3[12];					// orange[0]			= orange[3];
					orange3[4]				= orange3[8];					// orange[1]			= orange[2];
					orange3[i_help1]		= orange3[i_help1 - 4];			// orange[i_help1]		= orange[i_help1 - 1];
					orange3[i_help1 + 4]	= orange3[i_help1 - 8];			// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange4[0]				= orange4[12];					// orange[0]			= orange[3];
					orange4[4]				= orange4[8];					// orange[1]			= orange[2];
					orange4[i_help1]		= orange4[i_help1 - 4];			// orange[i_help1]		= orange[i_help1 - 1];
					orange4[i_help1 + 4]	= orange4[i_help1 - 8];			// orange[i_help1 + 1]	= orange[i_help1 - 2];

					i_help1		= 8;
					i_help1_end	= (2 + PDC_i_ceiling(out_size, 2)) * 4;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_high_plus){
						green1[i_help1] = in_high1[i_help2];
						green2[i_help1] = in_high1[i_help2 + high_stride2];
						green3[i_help1] = in_high1[i_help2 + high_stride3];
						green4[i_help1] = in_high1[i_help2 + high_stride4];
					}

					green1[0]			= green1[16];						// green[0]			= green[4];
					green1[4]			= green1[12];						// green[1]			= green[3];
					green1[i_help1]		= green1[i_help1 - 8];				// green[i_help1]		= green[i_help1 - 2];
					green1[i_help1 + 4]	= green1[i_help1 - 12];				// green[i_help1 + 1]	= green[i_help1 - 3];

					green2[0]			= green2[16];						// green[0]			= green[4];
					green2[4]			= green2[12];						// green[1]			= green[3];
					green2[i_help1]		= green2[i_help1 - 8];				// green[i_help1]		= green[i_help1 - 2];
					green2[i_help1 + 4]	= green2[i_help1 - 12];				// green[i_help1 + 1]	= green[i_help1 - 3];

					green3[0]			= green3[16];						// green[0]			= green[4];
					green3[4]			= green3[12];						// green[1]			= green[3];
					green3[i_help1]		= green3[i_help1 - 8];				// green[i_help1]		= green[i_help1 - 2];
					green3[i_help1 + 4]	= green3[i_help1 - 12];				// green[i_help1 + 1]	= green[i_help1 - 3];

					green4[0]			= green4[16];						// green[0]			= green[4];
					green4[4]			= green4[12];						// green[1]			= green[3];
					green4[i_help1]		= green4[i_help1 - 8];				// green[i_help1]		= green[i_help1 - 2];
					green4[i_help1 + 4]	= green4[i_help1 - 12];				// green[i_help1 + 1]	= green[i_help1 - 3];

					greensize			= PDC_i_ceiling(out_size, 2) + 4;
					orangesize			= greensize - 1;
				}
			}
		}else{
			if(even){
				if(out_size == 1){
					out[out_start] = in_low[in_low_start];
					out[out_start + out_stride2] = in_low[in_low_start + low_stride2];
					out[out_start + out_stride3] = in_low[in_low_start + low_stride3];
					out[out_start + out_stride4] = in_low[in_low_start + low_stride4];
					return decoder;
				}else if(out_size == 2){
					// green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					green1[0] = green1[4] = green1[8] = green1[12] = green1[16] = in_high[in_high_start];
					green2[0] = green2[4] = green2[8] = green2[12] = green2[16] = in_high[in_high_start + high_stride2];
					green3[0] = green3[4] = green3[8] = green3[12] = green3[16] = in_high[in_high_start + high_stride3];
					green4[0] = green4[4] = green4[8] = green4[12] = green4[16] = in_high[in_high_start + high_stride4];

					// orange[0] = orange[1] = orange[2] = orange[3] = in_low[in_low_start];
					orange1[0] = orange1[4] = orange1[8] = orange1[12] = in_low[in_low_start];
					orange2[0] = orange2[4] = orange2[8] = orange2[12] = in_low[in_low_start + low_stride2];
					orange3[0] = orange3[4] = orange3[8] = orange3[12] = in_low[in_low_start + low_stride3];
					orange4[0] = orange4[4] = orange4[8] = orange4[12] = in_low[in_low_start + low_stride4];

					greensize = 5;
					orangesize = 4;
				}else if(out_size == 3){
					// green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					green1[0] = green1[4] = green1[8] = green1[12] = green1[16] = in_high[in_high_start];
					green2[0] = green2[4] = green2[8] = green2[12] = green2[16] = in_high[in_high_start + high_stride2];
					green3[0] = green3[4] = green3[8] = green3[12] = green3[16] = in_high[in_high_start + high_stride3];
					green4[0] = green4[4] = green4[8] = green4[12] = green4[16] = in_high[in_high_start + high_stride4];

					// orange[0] = orange[2] = in_low[in_low_start + in_low_plus];
					orange1[0] = orange1[8] = in_low[in_low_start + in_low_plus];
					orange2[0] = orange2[8] = in_low[in_low_start + in_low_plus + low_stride2];
					orange3[0] = orange3[8] = in_low[in_low_start + in_low_plus + low_stride3];
					orange4[0] = orange4[8] = in_low[in_low_start + in_low_plus + low_stride4];

					// orange[1] = orange[3] = in_low[in_low_start];
					orange1[4] = orange1[12] = in_low[in_low_start];
					orange2[4] = orange2[12] = in_low[in_low_start + low_stride2];
					orange3[4] = orange3[12] = in_low[in_low_start + low_stride3];
					orange4[4] = orange4[12] = in_low[in_low_start + low_stride4];

					greensize = 5;
					orangesize = 4;
				}else if(out_size == 4){
					// green[0] = green[3] = in_high[in_high_start + in_high_plus];
					green1[0] = green1[3] = in_high[in_high_start + in_high_plus];
					green2[0] = green2[3] = in_high[in_high_start + in_high_plus + high_stride2];
					green3[0] = green3[3] = in_high[in_high_start + in_high_plus + high_stride3];
					green4[0] = green4[3] = in_high[in_high_start + in_high_plus + high_stride4];

					// green[1] = green[2] = green[4] = green[5] = in_high[in_high_start];
					green1[4] = green1[8] = green1[16] = green1[20] = in_high[in_high_start];
					green2[4] = green2[8] = green2[16] = green2[20] = in_high[in_high_start + high_stride2];
					green3[4] = green3[8] = green3[16] = green3[20] = in_high[in_high_start + high_stride3];
					green4[4] = green4[8] = green4[16] = green4[20] = in_high[in_high_start + high_stride4];

					// orange[0] = orange[2] = orange[3] = in_low[in_low_start + in_low_plus];
					orange1[0] = orange1[8] = orange1[12] = in_low[in_low_start + in_low_plus];
					orange2[0] = orange2[8] = orange2[12] = in_low[in_low_start + in_low_plus + low_stride2];
					orange3[0] = orange3[8] = orange3[12] = in_low[in_low_start + in_low_plus + low_stride3];
					orange4[0] = orange4[8] = orange4[12] = in_low[in_low_start + in_low_plus + low_stride4];

					// orange[1] = orange[4] = in_low[in_low_start];
					orange1[4] = orange1[16] = in_low[in_low_start];
					orange2[4] = orange2[16] = in_low[in_low_start + low_stride2];
					orange3[4] = orange3[16] = in_low[in_low_start + low_stride3];
					orange4[4] = orange4[16] = in_low[in_low_start + low_stride4];

					greensize = 6;
					orangesize = 5;
				}
			}else{
				if(out_size == 1){
					out[out_start] 					= in_low[in_low_start];
					out[out_start + out_stride2]	= in_low[in_low_start + low_stride2];
					out[out_start + out_stride3]	= in_low[in_low_start + low_stride3];
					out[out_start + out_stride4]	= in_low[in_low_start + low_stride4];
					return decoder;
				}else if(out_size == 2){
					// green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					green1[0] = green1[4] = green1[8] = green1[12] = green1[16]	= in_high[in_high_start];
					green2[0] = green2[4] = green2[8] = green2[12] = green2[16]	= in_high[in_high_start + high_stride2];
					green3[0] = green3[4] = green3[8] = green3[12] = green3[16]	= in_high[in_high_start + high_stride3];
					green4[0] = green4[4] = green4[8] = green4[12] = green4[16]	= in_high[in_high_start + high_stride4];

					// orange[0] = orange[1] = orange[2] = orange[3] = in_low[in_low_start];
					orange1[0] = orange1[4] = orange1[8] = orange1[12] = in_low[in_low_start];
					orange2[0] = orange2[4] = orange2[8] = orange2[12] = in_low[in_low_start + low_stride2];
					orange3[0] = orange3[4] = orange3[8] = orange3[12] = in_low[in_low_start + low_stride3];
					orange4[0] = orange4[4] = orange4[8] = orange4[12] = in_low[in_low_start + low_stride4];

					greensize = 5;
					orangesize = 4;
				}else if(out_size == 3){
					// green[0] = green[2] = green[4] = in_high[in_high_start];
					green1[0] = green1[8] = green1[16] = in_high[in_high_start];
					green2[0] = green2[8] = green2[16] = in_high[in_high_start + high_stride2];
					green3[0] = green3[8] = green3[16] = in_high[in_high_start + high_stride3];
					green4[0] = green4[8] = green4[16] = in_high[in_high_start + high_stride4];

					// green[1] = green[3] = green[5] = in_high[in_high_start + in_high_plus];
					green1[4] = green1[12] = green1[20] = in_high[in_high_start + in_high_plus];
					green2[4] = green2[12] = green2[20] = in_high[in_high_start + in_high_plus + high_stride2];
					green3[4] = green3[12] = green3[20] = in_high[in_high_start + in_high_plus + high_stride3];
					green4[4] = green4[12] = green4[20] = in_high[in_high_start + in_high_plus + high_stride4];

					//orange[0] = orange[1] = orange[2] = orange[3] = orange[4] = in_low[in_low_start];
					orange1[0] = orange1[4] = orange1[8] = orange1[12] = orange1[16] = in_low[in_low_start];
					orange2[0] = orange2[4] = orange2[8] = orange2[12] = orange2[16] = in_low[in_low_start + low_stride2];
					orange3[0] = orange3[4] = orange3[8] = orange3[12] = orange3[16] = in_low[in_low_start + low_stride3];
					orange4[0] = orange4[4] = orange4[8] = orange4[12] = orange4[16] = in_low[in_low_start + low_stride4];

					greensize = 6;
					orangesize = 5;
				}else if(out_size == 4){
					// green[0] = green[1] = green[3] = green[4] = in_high[in_high_start + in_high_plus];
					green1[0] = green1[4] = green1[12] = green1[16] = in_high[in_high_start + in_high_plus];
					green2[0] = green2[4] = green2[12] = green2[16] = in_high[in_high_start + in_high_plus + high_stride2];
					green3[0] = green3[4] = green3[12] = green3[16] = in_high[in_high_start + in_high_plus + high_stride3];
					green4[0] = green4[4] = green4[12] = green4[16] = in_high[in_high_start + in_high_plus + high_stride4];

					// green[2] = green[5] = in_high[in_high_start];
					green1[8] = green1[20] = in_high[in_high_start];
					green2[8] = green2[20] = in_high[in_high_start + high_stride2];
					green3[8] = green3[20] = in_high[in_high_start + high_stride3];
					green4[8] = green4[20] = in_high[in_high_start + high_stride4];

					// orange[0] = orange[3] = in_low[in_low_start + in_low_plus];
					orange1[0] = orange1[12] = in_low[in_low_start + in_low_plus];
					orange2[0] = orange2[12] = in_low[in_low_start + in_low_plus + low_stride2];
					orange3[0] = orange3[12] = in_low[in_low_start + in_low_plus + low_stride3];
					orange4[0] = orange4[12] = in_low[in_low_start + in_low_plus + low_stride4];

					// orange[1] = orange[2] = orange[4] = in_low[in_low_start];
					orange1[4] = orange1[8] = orange1[16] = in_low[in_low_start];
					orange2[4] = orange2[8] = orange2[16] = in_low[in_low_start + low_stride2];
					orange3[4] = orange3[8] = orange3[16] = in_low[in_low_start + low_stride3];
					orange4[4] = orange4[8] = orange4[16] = in_low[in_low_start + low_stride4];


					greensize = 6;
					orangesize =5;
				}
			}
		}

		/*
		if(uwe_count == 0){
			for(i_help1 = 0; i_help1 < greensize; i_help1 += 1){
				fprintf(DEBUG_FILE2,"%6d green   %13.2f \n",i_help1, green2[i_help1 * 4]);
			}

			for(i_help1 = 0; i_help1 < orangesize; i_help1 += 1){
				fprintf(DEBUG_FILE2,"%6d orange   %13.2f \n",i_help1, orange2[i_help1 * 4]);
			}
			uwe_count += 1;
		}
		 */

		orangesize_temp	= orangesize * 4;
		greensize_temp	= greensize	* 4;
		for(i_help1 = 0; i_help1 < greensize_temp; i_help1 += 4){
			green1[i_help1] *= K1;
			green2[i_help1] *= K1;
			green3[i_help1] *= K1;
			green4[i_help1] *= K1;
		}
		for(i_help1 = 0; i_help1 < orangesize_temp; i_help1 += 4){
			orange1[i_help1] *= K;
			orange2[i_help1] *= K;
			orange3[i_help1] *= K;
			orange4[i_help1] *= K;
		}

		for(i_help1 = 0, i_help2 = 4; i_help1 < orangesize_temp;){
			orange1[i_help1] = orange1[i_help1] - delta * ( green1[i_help1] + green1[i_help2]);
			orange2[i_help1] = orange2[i_help1] - delta * ( green2[i_help1] + green2[i_help2]);
			orange3[i_help1] = orange3[i_help1] - delta * ( green3[i_help1] + green3[i_help2]);
			orange4[i_help1] = orange4[i_help1] - delta * ( green4[i_help1] + green4[i_help2]);

			i_help1 = i_help2;
			i_help2 += 4;
		}

		greensize_temp = orangesize_temp - 4;
		for(i_help1 = 0, i_help2 = 4; i_help1 < greensize_temp;){
			green1[i_help1] = green1[i_help2] - f_gamma * ( orange1[i_help1] + orange1[i_help2]);
			green2[i_help1] = green2[i_help2] - f_gamma * ( orange2[i_help1] + orange2[i_help2]);
			green3[i_help1] = green3[i_help2] - f_gamma * ( orange3[i_help1] + orange3[i_help2]);
			green4[i_help1] = green4[i_help2] - f_gamma * ( orange4[i_help1] + orange4[i_help2]);

			i_help1 = i_help2;
			i_help2 += 4;
		}

		orangesize_temp = greensize_temp - 4;
		for(i_help1 = 0, i_help2 = 4; i_help1 < orangesize_temp;){
			orange1[i_help1] = orange1[i_help2] - beta * ( green1[i_help1] + green1[i_help2]);
			orange2[i_help1] = orange2[i_help2] - beta * ( green2[i_help1] + green2[i_help2]);
			orange3[i_help1] = orange3[i_help2] - beta * ( green3[i_help1] + green3[i_help2]);
			orange4[i_help1] = orange4[i_help2] - beta * ( green4[i_help1] + green4[i_help2]);
			i_help1 = i_help2;
			i_help2 += 4;
		}

		greensize_temp = orangesize_temp - 4;
		for(i_help1 = 0, i_help2 = 4; i_help1 < greensize_temp;){
			green1[i_help1] = green1[i_help2] - alpha * ( orange1[i_help1] + orange1[i_help2]);
			green2[i_help1] = green2[i_help2] - alpha * ( orange2[i_help1] + orange2[i_help2]);
			green3[i_help1] = green3[i_help2] - alpha * ( orange3[i_help1] + orange3[i_help2]);
			green4[i_help1] = green4[i_help2] - alpha * ( orange4[i_help1] + orange4[i_help2]);
			i_help1 = i_help2;
			i_help2 += 4;
		}

		if(even){
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 0;out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= orange1[i_help2]; //out[out_1] = orange[i_help2];
					out[out_1 + out_stride2] 	= orange2[i_help2]; //out[out_1] = orange[i_help2];
					out[out_1 + out_stride3] 	= orange3[i_help2]; //out[out_1] = orange[i_help2];
					out[out_1 + out_stride4] 	= orange4[i_help2]; //out[out_1] = orange[i_help2];
				}

				out_1		= out_start + out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= green1[i_help2];		//out[out_1] = green[i_help2];
					out[out_1 + out_stride2]	= green2[i_help2];		//out[out_1] = green[i_help2];
					out[out_1 + out_stride3]	= green3[i_help2];		//out[out_1] = green[i_help2];
					out[out_1 + out_stride4]	= green4[i_help2];		//out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 0;out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= orange1[i_help2];		//out[out_1] = orange[i_help2];
					out[out_1 + out_stride2]	= orange2[i_help2];		//out[out_1] = orange[i_help2];
					out[out_1 + out_stride3]	= orange3[i_help2];		//out[out_1] = orange[i_help2];
					out[out_1 + out_stride4]	= orange4[i_help2];		//out[out_1] = orange[i_help2];
				}

				out_1		= out_start + out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= green1[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride2]	= green2[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride3]	= green3[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride4]	= green4[i_help2];		// out[out_1] = green[i_help2];
				}
			}
		}else{
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= orange1[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride2]	= orange2[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride3]	= orange3[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride4]	= orange4[i_help2];		// out[out_1] = orange[i_help2];
				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus  + out_start;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= green1[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride2]	= green2[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride3]	= green3[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride4]	= green4[i_help2];		// out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= orange1[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride2]	= orange2[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride3]	= orange3[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride4]	= orange4[i_help2];		// out[out_1] = orange[i_help2];

				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus + out_start;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= green1[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride2]	= green2[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride3]	= green3[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride4]	= green4[i_help2];		// out[out_1] = green[i_help2];
				}
			}
		}
	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_SIZE, __LINE__, __FILE__);
	}
	return decoder;
}

#if defined(AMD64)

/*
 *
 */
PDC_Transformation_97_decoder* PDC_td_start_v2_sse2(	PDC_Exception* exception,
														PDC_Transformation_97_decoder* decoder,
														float *out, float *in_high, float* in_low,
														PDC_uint out_start, PDC_uint out_size,
														PDC_uint out_plus,  PDC_bool even,
														PDC_uint in_high_start, PDC_uint in_high_plus,
														PDC_uint in_low_start, PDC_uint in_low_plus,
														PDC_uint num_rows, PDC_uint high_stride, PDC_uint low_stride,
														PDC_uint out_stride)
{
	PDC_uint temp_numLoops, temp_numLoopsunrolled, temp_restLoop;
	PDC_uint i_help1, i_help2, i_help1_end, greensize, orangesize, out_1, out_1end, out_plus2;
	PDC_uint low_stride2, low_stride3, low_stride4;
	PDC_uint high_stride2, high_stride3, high_stride4;
	PDC_uint out_stride2, out_stride3, out_stride4;

	float			*workbuffer;
	float			*green1, * green2, *green3, *green4;
	float			*pink;
	float			*orange1, *orange2, *orange3, *orange4;
	float			*brown;
	float			*in_high1;
	float			*in_low1;
	PDC_uint		greenSize;
	PDC_uint32		pinkSize;
	PDC_uint		orangeSize;
	PDC_uint32		brownSize;
	PDC_uint32		maxSize;


	if(num_rows == 4){
		in_high1	= in_high;
		in_low1		= in_low;

		low_stride2	= low_stride;
		low_stride3	= low_stride * 2;
		low_stride4	= low_stride * 3;

		high_stride2	= high_stride;
		high_stride3	= high_stride * 2;
		high_stride4	= high_stride * 3;

		out_stride2	= out_stride;
		out_stride3 = out_stride * 2;
		out_stride4	= out_stride * 3;

	}else if(num_rows == 3){
		in_high1	= in_high;
		in_low1		= in_low;

		low_stride2	= low_stride;
		low_stride3	= low_stride * 2;
		low_stride4	= 0;

		high_stride2	= high_stride;
		high_stride3	= high_stride * 2;
		high_stride4	= 0;

		out_stride2	= out_stride;
		out_stride3 = out_stride * 2;
		out_stride4	= 0;

	}else if(num_rows == 2){
		in_high1	= in_high;
		in_low1		= in_low;

		low_stride2	= low_stride;
		low_stride3	= 0;
		low_stride4	= 0;

		high_stride2	= high_stride;
		high_stride3	= 0;
		high_stride4	= 0;

		out_stride2	= out_stride;
		out_stride3 = 0;
		out_stride4	= 0;

	}else if(num_rows == 1){
		in_high1	= in_high;
		in_low1		= in_low;

		low_stride2	= 0;
		low_stride3	= 0;
		low_stride4	= 0;

		high_stride2	= 0;
		high_stride3	= 0;
		high_stride4	= 0;

		out_stride2	= 0;
		out_stride3 = 0;
		out_stride4	= 0;

	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_DECODER, __LINE__, __FILE__);
		return decoder;
	}

	greensize	= 0;
	orangesize	= 0;
	workbuffer	= decoder->workbuffer;
	green1		= decoder->green;
	green2		= decoder->green + 1;
	green3		= decoder->green + 2;
	green4		= decoder->green + 3;
	pink		= decoder->pink;
	orange1		= decoder->orange;
	orange2		= decoder->orange + 1;
	orange3		= decoder->orange + 2;
	orange4		= decoder->orange + 3;
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
					i_help1		= 4;								//i_help1		= 1;
					i_help1_end	= (1 + out_size / 2) * 4;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_low_plus){
						orange1[i_help1] = in_low1[i_help2];
						orange2[i_help1] = in_low1[i_help2 + low_stride2];
						orange3[i_help1] = in_low1[i_help2 + low_stride3];
						orange4[i_help1] = in_low1[i_help2 + low_stride4];
					}
					orange1[0]				= orange1[8];				// orange[0]			= orange[2];
					orange1[i_help1]		= orange1[i_help1 - 4];		// orange[i_help1]		= orange[i_help1 - 1];
					orange1[i_help1 + 4]	= orange1[i_help1 - 8];		// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange2[0]				= orange2[8];				// orange[0]			= orange[2];
					orange2[i_help1]		= orange2[i_help1 - 4];		// orange[i_help1]		= orange[i_help1 - 1];
					orange2[i_help1 + 4]	= orange2[i_help1 - 8];		// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange3[0]				= orange3[8];				// orange[0]			= orange[2];
					orange3[i_help1]		= orange3[i_help1 - 4];		// orange[i_help1]		= orange[i_help1 - 1];
					orange3[i_help1 + 4]	= orange3[i_help1 - 8];		// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange4[0]				= orange4[8];				// orange[0]			= orange[2];
					orange4[i_help1]		= orange4[i_help1 - 4];		// orange[i_help1]		= orange[i_help1 - 1];
					orange4[i_help1 + 4]	= orange4[i_help1 - 8];		// orange[i_help1 + 1]	= orange[i_help1 - 2];


					i_help1 	= 8; 									//i_help1		= 2;
					i_help1_end	= (2 + out_size / 2) * 4;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_high_plus){
						green1[i_help1] = in_high1[i_help2];
						green2[i_help1] = in_high1[i_help2 + high_stride2];
						green3[i_help1] = in_high1[i_help2 + high_stride3];
						green4[i_help1] = in_high1[i_help2 + high_stride4];
					}
					green1[0]			= green1[12];					//green[0]			= green[3];
					green1[4]			= green1[8];						//green[1]			= green[2];
					green1[i_help1]		= green1[i_help1 - 8];			//green[i_help1]		= green[i_help1 - 2];
					green1[i_help1 + 4]	= green1[i_help1 - 12];			//green[i_help1 + 1]	= green[i_help1 - 3];

					green2[0]			= green2[12];					//green[0]			= green[3];
					green2[4]			= green2[8];						//green[1]			= green[2];
					green2[i_help1]		= green2[i_help1 - 8];			//green[i_help1]		= green[i_help1 - 2];
					green2[i_help1 + 4]	= green2[i_help1 - 12];			//green[i_help1 + 1]	= green[i_help1 - 3];

					green3[0]			= green3[12];					//green[0]			= green[3];
					green3[4]			= green3[8];						//green[1]			= green[2];
					green3[i_help1]		= green3[i_help1 - 8];			//green[i_help1]		= green[i_help1 - 2];
					green3[i_help1 + 4]	= green3[i_help1 - 12];			//green[i_help1 + 1]	= green[i_help1 - 3];

					green4[0]			= green4[12];					//green[0]			= green[3];
					green4[4]			= green4[8];						//green[1]			= green[2];
					green4[i_help1]		= green4[i_help1 - 8];			//green[i_help1]		= green[i_help1 - 2];
					green4[i_help1 + 4]	= green4[i_help1 - 12];			//green[i_help1 + 1]	= green[i_help1 - 3];

					greensize			= out_size / 2 + 4;
					orangesize			= greensize - 1;
				}else{
					i_help1		= 4;
					i_help1_end	= (1 + PDC_i_ceiling(out_size , 2)) * 4;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_low_plus){
						orange1[i_help1] = in_low1[i_help2];
						orange2[i_help1] = in_low1[i_help2 + low_stride2];
						orange3[i_help1] = in_low1[i_help2 + low_stride3];
						orange4[i_help1] = in_low1[i_help2 + low_stride4];
					}
					orange1[0]			= orange1[8];				//orange[0]			= orange[2];
					orange1[i_help1]	= orange1[i_help1 - 8];		//orange[i_help1]		= orange[i_help1 - 2];

					orange2[0]			= orange2[8];				//orange[0]			= orange[2];
					orange2[i_help1]	= orange2[i_help1 - 8];		//orange[i_help1]		= orange[i_help1 - 2];

					orange3[0]			= orange3[8];				//orange[0]			= orange[2];
					orange3[i_help1]	= orange3[i_help1 - 8];		//orange[i_help1]		= orange[i_help1 - 2];

					orange4[0]			= orange4[8];				//orange[0]			= orange[2];
					orange4[i_help1]	= orange4[i_help1 - 8];		//orange[i_help1]		= orange[i_help1 - 2];


					i_help1		= 8;
					i_help1_end	= (2 + PDC_i_ceiling(out_size , 2) - 1) * 4;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_high_plus){
						green1[i_help1] = in_high1[i_help2];
						green2[i_help1] = in_high1[i_help2 + high_stride2];
						green3[i_help1] = in_high1[i_help2 + high_stride3];
						green4[i_help1] = in_high1[i_help2 + high_stride4];
					}
					green1[0]			= green1[12];				//green[0]			= green[3];
					green1[4]			= green1[8];				//green[1]			= green[2];
					green1[i_help1]		= green1[i_help1 - 4];		//green[i_help1]		= green[i_help1 - 1];
					green1[i_help1 + 4]	= green1[i_help1 - 8];		//green[i_help1 + 1]	= green[i_help1 - 2];

					green2[0]			= green2[12];				//green[0]			= green[3];
					green2[4]			= green2[8];				//green[1]			= green[2];
					green2[i_help1]		= green2[i_help1 - 4];		//green[i_help1]		= green[i_help1 - 1];
					green2[i_help1 + 4]	= green2[i_help1 - 8];		//green[i_help1 + 1]	= green[i_help1 - 2];

					green3[0]			= green3[12];				//green[0]			= green[3];
					green3[4]			= green3[8];				//green[1]			= green[2];
					green3[i_help1]		= green3[i_help1 - 4];		//green[i_help1]		= green[i_help1 - 1];
					green3[i_help1 + 4]	= green3[i_help1 - 8];		//green[i_help1 + 1]	= green[i_help1 - 2];

					green4[0]			= green4[12];				//green[0]			= green[3];
					green4[4]			= green4[8];				//green[1]			= green[2];
					green4[i_help1]		= green4[i_help1 - 4];		//green[i_help1]		= green[i_help1 - 1];
					green4[i_help1 + 4]	= green4[i_help1 - 8];		//green[i_help1 + 1]	= green[i_help1 - 2];

					greensize			= PDC_i_floor( out_size , 2) + 4;
					orangesize			= greensize - 1;
				}
			}else{
				if(out_size % 2 == 0){
					i_help1		= 8;
					i_help1_end	= (2 + out_size / 2) * 4;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_low_plus){
						orange1[i_help1] = in_low1[i_help2];
						orange2[i_help1] = in_low1[i_help2 + low_stride2];
						orange3[i_help1] = in_low1[i_help2 + low_stride3];
						orange4[i_help1] = in_low1[i_help2 + low_stride4];

					}
					orange1[0]			= orange1[12];					// orange[0]			= orange[3];
					orange1[4]			= orange1[8];					// orange[1]			= orange[2];
					orange1[i_help1]	= orange1[i_help1 - 8];			// orange[i_help1]		= orange[i_help1 - 2];

					orange2[0]			= orange2[12];					// orange[0]			= orange[3];
					orange2[4]			= orange2[8];					// orange[1]			= orange[2];
					orange2[i_help1]	= orange2[i_help1 - 8];			// orange[i_help1]		= orange[i_help1 - 2];

					orange3[0]			= orange3[12];					// orange[0]			= orange[3];
					orange3[4]			= orange3[8];					// orange[1]			= orange[2];
					orange3[i_help1]	= orange3[i_help1 - 8];			// orange[i_help1]		= orange[i_help1 - 2];

					orange4[0]			= orange4[12];					// orange[0]			= orange[3];
					orange4[4]			= orange4[8];					// orange[1]			= orange[2];
					orange4[i_help1]	= orange4[i_help1 - 8];			// orange[i_help1]		= orange[i_help1 - 2];


					i_help1		= 8;
					i_help1_end	= (2 + out_size / 2) * 4;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_high_plus){
						green1[i_help1] = in_high1[i_help2];
						green2[i_help1] = in_high1[i_help2 + high_stride2];
						green3[i_help1] = in_high1[i_help2 + high_stride3];
						green4[i_help1] = in_high1[i_help2 + high_stride4];
					}
					green1[0]			= green1[16];					// green[0]			= green[4];
					green1[4]			= green1[12];					// green[1]			= green[3];
					green1[i_help1]		= green1[i_help1 - 4];			// green[i_help1]		= green[i_help1 - 1];
					green1[i_help1 + 4]	= green1[i_help1 - 8];			// green[i_help1 + 1]	= green[i_help1 - 2];

					green2[0]			= green2[16];					// green[0]			= green[4];
					green2[4]			= green2[12];					// green[1]			= green[3];
					green2[i_help1]		= green2[i_help1 - 4];			// green[i_help1]		= green[i_help1 - 1];
					green2[i_help1 + 4]	= green2[i_help1 - 8];			// green[i_help1 + 1]	= green[i_help1 - 2];

					green3[0]			= green3[16];					// green[0]			= green[4];
					green3[4]			= green3[12];					// green[1]			= green[3];
					green3[i_help1]		= green3[i_help1 - 4];			// green[i_help1]		= green[i_help1 - 1];
					green3[i_help1 + 4]	= green3[i_help1 - 8];			// green[i_help1 + 1]	= green[i_help1 - 2];

					green4[0]			= green4[16];					// green[0]			= green[4];
					green4[4]			= green4[12];					// green[1]			= green[3];
					green4[i_help1]		= green4[i_help1 - 4];			// green[i_help1]		= green[i_help1 - 1];
					green4[i_help1 + 4]	= green4[i_help1 - 8];			// green[i_help1 + 1]	= green[i_help1 - 2];

					greensize			= out_size / 2 + 4;
					orangesize			= greensize - 1;
				}else{
					i_help1		= 8;
					i_help1_end	= (2 + PDC_i_floor(out_size, 2)) * 4;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_low_plus){
						orange1[i_help1] = in_low1[i_help2];
						orange2[i_help1] = in_low1[i_help2 + low_stride2];
						orange3[i_help1] = in_low1[i_help2 + low_stride3];
						orange4[i_help1] = in_low1[i_help2 + low_stride4];
					}
					orange1[0]				= orange1[12];					// orange[0]			= orange[3];
					orange1[4]				= orange1[8];					// orange[1]			= orange[2];
					orange1[i_help1]		= orange1[i_help1 - 4];			// orange[i_help1]		= orange[i_help1 - 1];
					orange1[i_help1 + 4]	= orange1[i_help1 - 8];			// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange2[0]				= orange2[12];					// orange[0]			= orange[3];
					orange2[4]				= orange2[8];					// orange[1]			= orange[2];
					orange2[i_help1]		= orange2[i_help1 - 4];			// orange[i_help1]		= orange[i_help1 - 1];
					orange2[i_help1 + 4]	= orange2[i_help1 - 8];			// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange3[0]				= orange3[12];					// orange[0]			= orange[3];
					orange3[4]				= orange3[8];					// orange[1]			= orange[2];
					orange3[i_help1]		= orange3[i_help1 - 4];			// orange[i_help1]		= orange[i_help1 - 1];
					orange3[i_help1 + 4]	= orange3[i_help1 - 8];			// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange4[0]				= orange4[12];					// orange[0]			= orange[3];
					orange4[4]				= orange4[8];					// orange[1]			= orange[2];
					orange4[i_help1]		= orange4[i_help1 - 4];			// orange[i_help1]		= orange[i_help1 - 1];
					orange4[i_help1 + 4]	= orange4[i_help1 - 8];			// orange[i_help1 + 1]	= orange[i_help1 - 2];

					i_help1		= 8;
					i_help1_end	= (2 + PDC_i_ceiling(out_size, 2)) * 4;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_high_plus){
						green1[i_help1] = in_high1[i_help2];
						green2[i_help1] = in_high1[i_help2 + high_stride2];
						green3[i_help1] = in_high1[i_help2 + high_stride3];
						green4[i_help1] = in_high1[i_help2 + high_stride4];
					}

					green1[0]			= green1[16];						// green[0]			= green[4];
					green1[4]			= green1[12];						// green[1]			= green[3];
					green1[i_help1]		= green1[i_help1 - 8];				// green[i_help1]		= green[i_help1 - 2];
					green1[i_help1 + 4]	= green1[i_help1 - 12];				// green[i_help1 + 1]	= green[i_help1 - 3];

					green2[0]			= green2[16];						// green[0]			= green[4];
					green2[4]			= green2[12];						// green[1]			= green[3];
					green2[i_help1]		= green2[i_help1 - 8];				// green[i_help1]		= green[i_help1 - 2];
					green2[i_help1 + 4]	= green2[i_help1 - 12];				// green[i_help1 + 1]	= green[i_help1 - 3];

					green3[0]			= green3[16];						// green[0]			= green[4];
					green3[4]			= green3[12];						// green[1]			= green[3];
					green3[i_help1]		= green3[i_help1 - 8];				// green[i_help1]		= green[i_help1 - 2];
					green3[i_help1 + 4]	= green3[i_help1 - 12];				// green[i_help1 + 1]	= green[i_help1 - 3];

					green4[0]			= green4[16];						// green[0]			= green[4];
					green4[4]			= green4[12];						// green[1]			= green[3];
					green4[i_help1]		= green4[i_help1 - 8];				// green[i_help1]		= green[i_help1 - 2];
					green4[i_help1 + 4]	= green4[i_help1 - 12];				// green[i_help1 + 1]	= green[i_help1 - 3];

					greensize			= PDC_i_ceiling(out_size, 2) + 4;
					orangesize			= greensize - 1;
				}
			}
		}else{
			if(even){
				if(out_size == 1){
					out[out_start] = in_low[in_low_start];
					out[out_start + out_stride2] = in_low[in_low_start + low_stride2];
					out[out_start + out_stride3] = in_low[in_low_start + low_stride3];
					out[out_start + out_stride4] = in_low[in_low_start + low_stride4];
					return decoder;
				}else if(out_size == 2){
					// green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					green1[0] = green1[4] = green1[8] = green1[12] = green1[16] = in_high[in_high_start];
					green2[0] = green2[4] = green2[8] = green2[12] = green2[16] = in_high[in_high_start + high_stride2];
					green3[0] = green3[4] = green3[8] = green3[12] = green3[16] = in_high[in_high_start + high_stride3];
					green4[0] = green4[4] = green4[8] = green4[12] = green4[16] = in_high[in_high_start + high_stride4];

					// orange[0] = orange[1] = orange[2] = orange[3] = in_low[in_low_start];
					orange1[0] = orange1[4] = orange1[8] = orange1[12] = in_low[in_low_start];
					orange2[0] = orange2[4] = orange2[8] = orange2[12] = in_low[in_low_start + low_stride2];
					orange3[0] = orange3[4] = orange3[8] = orange3[12] = in_low[in_low_start + low_stride3];
					orange4[0] = orange4[4] = orange4[8] = orange4[12] = in_low[in_low_start + low_stride4];

					greensize = 5;
					orangesize = 4;
				}else if(out_size == 3){
					// green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					green1[0] = green1[4] = green1[8] = green1[12] = green1[16] = in_high[in_high_start];
					green2[0] = green2[4] = green2[8] = green2[12] = green2[16] = in_high[in_high_start + high_stride2];
					green3[0] = green3[4] = green3[8] = green3[12] = green3[16] = in_high[in_high_start + high_stride3];
					green4[0] = green4[4] = green4[8] = green4[12] = green4[16] = in_high[in_high_start + high_stride4];

					// orange[0] = orange[2] = in_low[in_low_start + in_low_plus];
					orange1[0] = orange1[8] = in_low[in_low_start + in_low_plus];
					orange2[0] = orange2[8] = in_low[in_low_start + in_low_plus + low_stride2];
					orange3[0] = orange3[8] = in_low[in_low_start + in_low_plus + low_stride3];
					orange4[0] = orange4[8] = in_low[in_low_start + in_low_plus + low_stride4];

					// orange[1] = orange[3] = in_low[in_low_start];
					orange1[4] = orange1[12] = in_low[in_low_start];
					orange2[4] = orange2[12] = in_low[in_low_start + low_stride2];
					orange3[4] = orange3[12] = in_low[in_low_start + low_stride3];
					orange4[4] = orange4[12] = in_low[in_low_start + low_stride4];

					greensize = 5;
					orangesize = 4;
				}else if(out_size == 4){
					// green[0] = green[3] = in_high[in_high_start + in_high_plus];
					green1[0] = green1[3] = in_high[in_high_start + in_high_plus];
					green2[0] = green2[3] = in_high[in_high_start + in_high_plus + high_stride2];
					green3[0] = green3[3] = in_high[in_high_start + in_high_plus + high_stride3];
					green4[0] = green4[3] = in_high[in_high_start + in_high_plus + high_stride4];

					// green[1] = green[2] = green[4] = green[5] = in_high[in_high_start];
					green1[4] = green1[8] = green1[16] = green1[20] = in_high[in_high_start];
					green2[4] = green2[8] = green2[16] = green2[20] = in_high[in_high_start + high_stride2];
					green3[4] = green3[8] = green3[16] = green3[20] = in_high[in_high_start + high_stride3];
					green4[4] = green4[8] = green4[16] = green4[20] = in_high[in_high_start + high_stride4];

					// orange[0] = orange[2] = orange[3] = in_low[in_low_start + in_low_plus];
					orange1[0] = orange1[8] = orange1[12] = in_low[in_low_start + in_low_plus];
					orange2[0] = orange2[8] = orange2[12] = in_low[in_low_start + in_low_plus + low_stride2];
					orange3[0] = orange3[8] = orange3[12] = in_low[in_low_start + in_low_plus + low_stride3];
					orange4[0] = orange4[8] = orange4[12] = in_low[in_low_start + in_low_plus + low_stride4];

					// orange[1] = orange[4] = in_low[in_low_start];
					orange1[4] = orange1[16] = in_low[in_low_start];
					orange2[4] = orange2[16] = in_low[in_low_start + low_stride2];
					orange3[4] = orange3[16] = in_low[in_low_start + low_stride3];
					orange4[4] = orange4[16] = in_low[in_low_start + low_stride4];

					greensize = 6;
					orangesize = 5;
				}
			}else{
				if(out_size == 1){
					out[out_start] 					= in_low[in_low_start];
					out[out_start + out_stride2]	= in_low[in_low_start + low_stride2];
					out[out_start + out_stride3]	= in_low[in_low_start + low_stride3];
					out[out_start + out_stride4]	= in_low[in_low_start + low_stride4];
					return decoder;
				}else if(out_size == 2){
					// green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					green1[0] = green1[4] = green1[8] = green1[12] = green1[16]	= in_high[in_high_start];
					green2[0] = green2[4] = green2[8] = green2[12] = green2[16]	= in_high[in_high_start + high_stride2];
					green3[0] = green3[4] = green3[8] = green3[12] = green3[16]	= in_high[in_high_start + high_stride3];
					green4[0] = green4[4] = green4[8] = green4[12] = green4[16]	= in_high[in_high_start + high_stride4];

					// orange[0] = orange[1] = orange[2] = orange[3] = in_low[in_low_start];
					orange1[0] = orange1[4] = orange1[8] = orange1[12] = in_low[in_low_start];
					orange2[0] = orange2[4] = orange2[8] = orange2[12] = in_low[in_low_start + low_stride2];
					orange3[0] = orange3[4] = orange3[8] = orange3[12] = in_low[in_low_start + low_stride3];
					orange4[0] = orange4[4] = orange4[8] = orange4[12] = in_low[in_low_start + low_stride4];

					greensize = 5;
					orangesize = 4;
				}else if(out_size == 3){
					// green[0] = green[2] = green[4] = in_high[in_high_start];
					green1[0] = green1[8] = green1[16] = in_high[in_high_start];
					green2[0] = green2[8] = green2[16] = in_high[in_high_start + high_stride2];
					green3[0] = green3[8] = green3[16] = in_high[in_high_start + high_stride3];
					green4[0] = green4[8] = green4[16] = in_high[in_high_start + high_stride4];

					// green[1] = green[3] = green[5] = in_high[in_high_start + in_high_plus];
					green1[4] = green1[12] = green1[20] = in_high[in_high_start + in_high_plus];
					green2[4] = green2[12] = green2[20] = in_high[in_high_start + in_high_plus + high_stride2];
					green3[4] = green3[12] = green3[20] = in_high[in_high_start + in_high_plus + high_stride3];
					green4[4] = green4[12] = green4[20] = in_high[in_high_start + in_high_plus + high_stride4];

					//orange[0] = orange[1] = orange[2] = orange[3] = orange[4] = in_low[in_low_start];
					orange1[0] = orange1[4] = orange1[8] = orange1[12] = orange1[16] = in_low[in_low_start];
					orange2[0] = orange2[4] = orange2[8] = orange2[12] = orange2[16] = in_low[in_low_start + low_stride2];
					orange3[0] = orange3[4] = orange3[8] = orange3[12] = orange3[16] = in_low[in_low_start + low_stride3];
					orange4[0] = orange4[4] = orange4[8] = orange4[12] = orange4[16] = in_low[in_low_start + low_stride4];

					greensize = 6;
					orangesize = 5;
				}else if(out_size == 4){
					// green[0] = green[1] = green[3] = green[4] = in_high[in_high_start + in_high_plus];
					green1[0] = green1[4] = green1[12] = green1[16] = in_high[in_high_start + in_high_plus];
					green2[0] = green2[4] = green2[12] = green2[16] = in_high[in_high_start + in_high_plus + high_stride2];
					green3[0] = green3[4] = green3[12] = green3[16] = in_high[in_high_start + in_high_plus + high_stride3];
					green4[0] = green4[4] = green4[12] = green4[16] = in_high[in_high_start + in_high_plus + high_stride4];

					// green[2] = green[5] = in_high[in_high_start];
					green1[8] = green1[20] = in_high[in_high_start];
					green2[8] = green2[20] = in_high[in_high_start + high_stride2];
					green3[8] = green3[20] = in_high[in_high_start + high_stride3];
					green4[8] = green4[20] = in_high[in_high_start + high_stride4];

					// orange[0] = orange[3] = in_low[in_low_start + in_low_plus];
					orange1[0] = orange1[12] = in_low[in_low_start + in_low_plus];
					orange2[0] = orange2[12] = in_low[in_low_start + in_low_plus + low_stride2];
					orange3[0] = orange3[12] = in_low[in_low_start + in_low_plus + low_stride3];
					orange4[0] = orange4[12] = in_low[in_low_start + in_low_plus + low_stride4];

					// orange[1] = orange[2] = orange[4] = in_low[in_low_start];
					orange1[4] = orange1[8] = orange1[16] = in_low[in_low_start];
					orange2[4] = orange2[8] = orange2[16] = in_low[in_low_start + low_stride2];
					orange3[4] = orange3[8] = orange3[16] = in_low[in_low_start + low_stride3];
					orange4[4] = orange4[8] = orange4[16] = in_low[in_low_start + low_stride4];


					greensize = 6;
					orangesize =5;
				}
			}
		}

		/*
		if(uwe_count == 0){
			for(i_help1 = 0; i_help1 < greensize; i_help1 += 1){
				fprintf(DEBUG_FILE2,"%6d green   %13.2f \n",i_help1, green2[i_help1 * 4]);
			}

			for(i_help1 = 0; i_help1 < orangesize; i_help1 += 1){
				fprintf(DEBUG_FILE2,"%6d orange   %13.2f \n",i_help1, orange2[i_help1 * 4]);
			}
			uwe_count += 1;
		}
		 */

	asm volatile (
	"	mov		rcx,	%2					/* 			*/" "\n\t"
	"	cmp		rcx,	0					/* 			*/" "\n\t"
	"	je		9f							/* if greensize == 0 jump out 			*/" "\n\t"

	"	xor		rdx,	rdx					/* 			*/" "\n\t"
	" 	mov		rax,	rcx					/* 			*/" "\n\t"
	"	mov		rbx,	4					/* 			*/" "\n\t"
	"	div		rbx							/* 			*/" "\n\t"
	"	mov		rcx,	rax					/* 			*/" "\n\t"
	"										/* 			*/" "\n\t"
	"										/* 			*/" "\n\t"

	"	mov		rax,	%3					/* 			*/" "\n\t"
	"	movaps	xmm6,	[rax]				/* load k			*/" "\n\t"
	"	mov		rax,	%4					/* 					*/" "\n\t"
	"	movaps	xmm7,	[rax]				/* load k1			*/" "\n\t"
	"	mov		rax,	%0					/* load orange pointer  			*/" "\n\t"
	"	mov		rbx,	%1					/* load green pointer				*/" "\n\t"
	"	xor		rsi,	rsi					/* 			*/" "\n\t"
	"	prefetcht0	[rax + 64]				/* 			*/" "\n\t"
	"	prefetcht0	[rbx + 64]				/* 			*/" "\n\t"
	"	prefetcht0	[rax + 128]				/* 			*/" "\n\t"
	"	prefetcht0	[rbx + 128]				/* 			*/" "\n\t"

	"0:										/* 			*/" "\n\t"
	"	movaps	xmm0,	[rax]				/* 			*/" "\n\t"
	"	movaps	xmm1,	[rbx]				/* 			*/" "\n\t"
	"	movaps	xmm2,	[rax + 16]			/* 			*/" "\n\t"
	"	movaps	xmm3,	[rbx + 16]			/* 			*/" "\n\t"
	"	movaps	xmm4,	[rax + 32]			/* 			*/" "\n\t"
	"	movaps	xmm5,	[rbx + 32]			/* 			*/" "\n\t"

	"	mulps	xmm0,	xmm6				/* 			*/" "\n\t"
	"	mulps	xmm1,	xmm7				/* 			*/" "\n\t"
	"	movaps	[rax],	xmm0				/* 			*/" "\n\t"
	"	movaps	[rbx],	xmm1				/* 			*/" "\n\t"

	"	movaps	xmm0,	[rax + 48]			/* 			*/" "\n\t"
	"	movaps	xmm1,	[rbx + 48]			/* 			*/" "\n\t"
	"	mulps	xmm2,	xmm6				/* 			*/" "\n\t"
	"	mulps	xmm3,	xmm7				/* 			*/" "\n\t"
	"	mulps	xmm4,	xmm6				/* 			*/" "\n\t"
	"	mulps	xmm5,	xmm7				/* 			*/" "\n\t"
	"	mulps	xmm0,	xmm6				/* 			*/" "\n\t"
	"	mulps	xmm1,	xmm7				/* 			*/" "\n\t"

	"	movaps	[rax + 16],	xmm2				/* 			*/" "\n\t"
	"	movaps	[rbx + 16],	xmm3				/* 			*/" "\n\t"
	"	movaps	[rax + 32],	xmm4				/* 			*/" "\n\t"
	"	movaps	[rbx + 32],	xmm5				/* 			*/" "\n\t"
	"	movaps	[rax + 48],	xmm0				/* 			*/" "\n\t"
	"	movaps	[rbx + 48],	xmm1				/* 			*/" "\n\t"

	"	add		rax,	64					/* 			*/" "\n\t"
	"	add		rbx,	64					/* 			*/" "\n\t"


	"	prefetcht0	[rax + 128]				/* 			*/" "\n\t"
	"	prefetcht0	[rbx + 128]				/* 			*/" "\n\t"
	"	dec		rcx							/* 			*/" "\n\t"
	"	cmp		rcx,	0					/* 			*/" "\n\t"
	"	jne		0b							/* 			*/" "\n\t"

	"	mov		rcx,	rdx					/* 			*/" "\n\t"
	"	cmp		rcx,	0					/* 			*/" "\n\t"
	"	je		2f							/* 			*/" "\n\t"
	"1:					/* 			*/" "\n\t"
	"	movaps	xmm0,	[rax]				/* 			*/" "\n\t"
	"	movaps	xmm1,	[rbx]				/* 			*/" "\n\t"
	"	mulps	xmm0,	xmm6				/* 			*/" "\n\t"
	"	mulps	xmm1,	xmm7				/* 			*/" "\n\t"
	"	movaps	[rax],	xmm0				/* 			*/" "\n\t"
	"	movaps	[rbx],	xmm1				/* 			*/" "\n\t"
	"	add		rax,	16					/* 			*/" "\n\t"
	"	add		rbx,	16					/* 			*/" "\n\t"
	"	dec		rcx							/* 			*/" "\n\t"
	"	cmp		rcx,	0					/* 			*/" "\n\t"
	"	jne		1b							/* 			*/" "\n\t"
	"2:					/* 			*/" "\n\t"

	"			/*	#################################################	*/" "\n\t"
	"			/*	############	Start Second part ###############	*/" "\n\t"
	"			/*	#################################################	*/" "\n\t"
	"	mov		rax,	%2					/* 			*/" "\n\t"
	"	sub		rax,	1					/* 			*/" "\n\t"
	"	xor		rdx,	rdx					/* 			*/" "\n\t"
	"	mov		rbx,	4					/* 			*/" "\n\t"
	"	div		rbx							/* 			*/" "\n\t"
	"	mov		rsi,	rdx					/* 			*/" "\n\t"
	"	mov		rcx,	rax					/* 			*/" "\n\t"
	"	mov		rax,	%8					/* delta pointer			*/" "\n\t"
	"	movaps	xmm7,	[rax]				/* 							*/" "\n\t"
	"	mov		rbx,	%9					/* gamma pointer			*/" "\n\t"
	"	movaps	xmm6,	[rbx]				/* 							*/" "\n\t"
	"	mov		rax,	%0					/* load orange pointer  			*/" "\n\t"
	"	mov		rbx,	%1					/* load green pointer				*/" "\n\t"

	"/* orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);			*/" "\n\t"

	"	movaps	xmm5,	[rbx]				/* 			*/" "\n\t"
	"										/* 			*/" "\n\t"
	"	movaps	xmm0,	xmm5				/* 			*/" "\n\t"
	"	movaps	xmm4,	xmm5				/* 			*/" "\n\t"
	"	movaps	xmm5,	[rbx + 16]			/* 			*/" "\n\t"
	"	movaps	xmm1,	[rax]				/* 			*/" "\n\t"

	"	addps	xmm0,	xmm5				/* 			*/" "\n\t"
	"	mulps	xmm0,	xmm7				/* 			*/" "\n\t"
	"	subps	xmm1,	xmm0				/* 			*/" "\n\t"

	"	movaps	[rax],	xmm1				/* 			*/" "\n\t"
	"	movaps	xmm3,	xmm1				/* 	save orange			*/" "\n\t"
	"	add		rax,	16					/* 						*/" "\n\t"

	"	prefetcht0	[rax + 64]				/* 						*/" "\n\t"
	"	prefetcht0	[rax + 128]				/* 						*/" "\n\t"
	"	prefetcht0	[rbx + 64]				/* 						*/" "\n\t"
	"	prefetcht0	[rbx + 128]				/* 						*/" "\n\t"


	"1:		/* Start main loop 				*/" "\n\t"
				"/* orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);			*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm5,	[rbx + 32]			/* load green			*/" "\n\t"
				"	movaps	xmm1,	[rax]				/* load orange 			*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 			*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 			*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 			*/" "\n\t"

				"	movaps	[rax], 	xmm1				/* sav orange		*/" "\n\t"

				"/* 	green[i_help1] = green[i_help2] - gamma * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[rbx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		rbx,	16					/* 			*/" "\n\t"
				"	add		rax,	16					/* 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);			*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm5,	[rbx + 32]			/* load green			*/" "\n\t"
				"	movaps	xmm1,	[rax]				/* load orange 			*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 			*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 			*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 			*/" "\n\t"

				"	movaps	[rax], 	xmm1				/* sav orange		*/" "\n\t"

				"/* 	green[i_help1] = green[i_help2] - gamma * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[rbx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		rbx,	16					/* 			*/" "\n\t"
				"	add		rax,	16					/* 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);			*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm5,	[rbx + 32]			/* load green			*/" "\n\t"
				"	movaps	xmm1,	[rax]				/* load orange 			*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 			*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 			*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 			*/" "\n\t"

				"	movaps	[rax], 	xmm1				/* sav orange		*/" "\n\t"

				"/* 	green[i_help1] = green[i_help2] - gamma * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[rbx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		rbx,	16					/* 			*/" "\n\t"
				"	add		rax,	16					/* 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);			*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm5,	[rbx + 32]			/* load green			*/" "\n\t"
				"	movaps	xmm1,	[rax]				/* load orange 			*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 			*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 			*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 			*/" "\n\t"

				"	movaps	[rax], 	xmm1				/* sav orange		*/" "\n\t"

				"/* 	green[i_help1] = green[i_help2] - gamma * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[rbx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		rbx,	16					/* 			*/" "\n\t"
				"	add		rax,	16					/* 			*/" "\n\t"

	"	prefetcht0	[rax + 128]				/* 			*/" "\n\t"
	"	prefetcht0	[rbx + 128]				/* 			*/" "\n\t"
	"	dec		rcx							/* 			*/" "\n\t"
	"	cmp		rcx, 0						/* 			*/" "\n\t"
	"	jne		1b							/* 			*/" "\n\t"

	"	mov		rcx,	rsi				/* 			*/" "\n\t"
	"	cmp		rcx,	0				/* 			*/" "\n\t"
	"	je		3f				/* 			*/" "\n\t"

	"2:					/* 			*/" "\n\t"
				"/* orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);			*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm5,	[rbx + 32]			/* load green			*/" "\n\t"
				"	movaps	xmm1,	[rax]				/* load orange 			*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 			*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 			*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 			*/" "\n\t"

				"	movaps	[rax], 	xmm1				/* sav orange		*/" "\n\t"

				"/* 	green[i_help1] = green[i_help2] - gamma * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[rbx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		rbx,	16					/* 			*/" "\n\t"
				"	add		rax,	16					/* 			*/" "\n\t"

	"	dec		rcx						/* 			*/" "\n\t"
	"	cmp		rcx,	0				/* 			*/" "\n\t"
	"	jne		2b						/* 			*/" "\n\t"
	"3:					/* 			*/" "\n\t"


	"			/*	#################################################	*/" "\n\t"
	"			/*	############	Start Third part ###############	*/" "\n\t"
	"			/*	#################################################	*/" "\n\t"
	"	mov		rax,	%2					/* 			*/" "\n\t"
	"	sub		rax,	1					/* 			*/" "\n\t"
	"	xor		rdx,	rdx					/* 			*/" "\n\t"
	"	mov		rbx,	4					/* 			*/" "\n\t"
	"	div		rbx							/* 			*/" "\n\t"
	"	mov		rsi,	rbx					/* 			*/" "\n\t"
	"	mov		rcx,	rax					/* 			*/" "\n\t"
	"	mov		rax,	%10					/* beta pointer						*/" "\n\t"
	"	movaps	xmm7,	[rax]				/* 									*/" "\n\t"
	"	mov		rbx,	%11					/* alpha pointer					*/" "\n\t"
	"	movaps	xmm6,	[rbx]				/* 									*/" "\n\t"
	"	mov		rax,	%0					/* load orange pointer  			*/" "\n\t"
	"	mov		rbx,	%1					/* load green pointer				*/" "\n\t"


	"/* orange[i_help1] = orange[i_help2] - beta * (green[i_help1] + green[i_help2])		*/" "\n\t"

	"	movaps	xmm5,	[rbx]				/* preload green[i_help1]			*/" "\n\t"
	"										/* 									*/" "\n\t"
	"	movaps	xmm0,	xmm5				/* 									*/" "\n\t"
	"	movaps	xmm4,	xmm5				/* 									*/" "\n\t"
	"	movaps	xmm5,	[rbx + 16]			/* load green[i_help2]				*/" "\n\t"
	"	movaps	xmm1,	[rax + 16]			/* load orange[i_help2]				*/" "\n\t"

	"	addps	xmm0,	xmm5				/* 									*/" "\n\t"
	"	mulps	xmm0,	xmm7				/* 									*/" "\n\t"
	"	subps	xmm1,	xmm0				/* 									*/" "\n\t"

	"	movaps	[rax],	xmm1				/* 									*/" "\n\t"
	"	movaps	xmm3,	xmm1				/* 	save orange			*/" "\n\t"
	"	add		rax,	16					/* 						*/" "\n\t"

	"	prefetcht0	[rax + 64]				/* 						*/" "\n\t"
	"	prefetcht0	[rax + 128]				/* 						*/" "\n\t"
	"	prefetcht0	[rbx + 64]				/* 						*/" "\n\t"
	"	prefetcht0	[rbx + 128]				/* 						*/" "\n\t"

	"	cmp		rcx, 	0					/* 			*/" "\n\t"
	"	je		2f							/* 			*/" "\n\t"

	"1:					/* Start main loop 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help2] - beta * (green[i_help1] + green[i_help2])		*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm5,	[rbx + 32]			/* load green[i_help2]				*/" "\n\t"
				"	movaps	xmm1,	[rax + 16]			/* load orange[i_help2]				*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 									*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 									*/" "\n\t"

				"	movaps	[rax],	xmm1				/* 	save orange									*/" "\n\t"

				"/* 	green[i_help1] = green[i_help2] - alpha * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[rbx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		rbx,	16					/* 			*/" "\n\t"
				"	add		rax,	16					/* 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help2] - beta * (green[i_help1] + green[i_help2])		*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm5,	[rbx + 32]			/* load green[i_help2]				*/" "\n\t"
				"	movaps	xmm1,	[rax + 16]			/* load orange[i_help2]				*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 									*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 									*/" "\n\t"

				"	movaps	[rax],	xmm1				/* 	save orange									*/" "\n\t"


				"/* 	green[i_help1] = green[i_help2] - alpha * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[rbx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		rbx,	16					/* 			*/" "\n\t"
				"	add		rax,	16					/* 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help2] - beta * (green[i_help1] + green[i_help2])		*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm5,	[rbx + 32]			/* load green[i_help2]				*/" "\n\t"
				"	movaps	xmm1,	[rax + 16]			/* load orange[i_help2]				*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 									*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 									*/" "\n\t"

				"	movaps	[rax],	xmm1				/* 	save orange									*/" "\n\t"


				"/* 	green[i_help1] = green[i_help2] - alpha * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[rbx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		rbx,	16					/* 			*/" "\n\t"
				"	add		rax,	16					/* 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help2] - beta * (green[i_help1] + green[i_help2])		*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm5,	[rbx + 32]			/* load green[i_help2]				*/" "\n\t"
				"	movaps	xmm1,	[rax + 16]			/* load orange[i_help2]				*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 									*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 									*/" "\n\t"

				"	movaps	[rax],	xmm1				/* 	save orange									*/" "\n\t"


				"/* 	green[i_help1] = green[i_help2] - alpha * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[rbx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		rbx,	16					/* 			*/" "\n\t"
				"	add		rax,	16					/* 			*/" "\n\t"


	"	prefetcht0	[rax + 128]				/* 						*/" "\n\t"
	"	prefetcht0	[rbx + 128]				/* 						*/" "\n\t"
	"	dec		rcx							/* 			*/" "\n\t"
	"	cmp		rcx,	0					/* 			*/" "\n\t"
	"	jne		1b							/* 			*/" "\n\t"
	"2:					/* 			*/" "\n\t"
	"					/* 			*/" "\n\t"
	"					/* 			*/" "\n\t"
	"					/* 			*/" "\n\t"

	"					/* 			*/" "\n\t"
	"9:					/* 			*/" "\n\t"

	"/*( %0 orange1),( %1 green1), (%2 greensize), (%3 k), (%4 k1), (%5 temp_numLoops), (%6 temp_numLoopsunrolled), (%7 tem_restLoop), (%8 delta), (%9 gamma) (%10 beta) (%11 alpha) */" "\n\t"
		 :
		 :	"m"(orange1), "m"(green1), "m"(greensize), "m"(decoder->K ), "m"(decoder->K1), "m"(temp_numLoops),  "m"(temp_numLoopsunrolled), "m"(temp_restLoop), "m"(decoder->delta), "m"(decoder->gamma), "m"(decoder->beta), "m"(decoder->alpha)
		 : 	"memory", "rbx", "rsi", "rdx", "rax", "rcx", "xmm6", "xmm7", "xmm0", "xmm1"
		);

		if(even){
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 0;out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= orange1[i_help2]; //out[out_1] = orange[i_help2];
					out[out_1 + out_stride2] 	= orange2[i_help2]; //out[out_1] = orange[i_help2];
					out[out_1 + out_stride3] 	= orange3[i_help2]; //out[out_1] = orange[i_help2];
					out[out_1 + out_stride4] 	= orange4[i_help2]; //out[out_1] = orange[i_help2];
				}

				out_1		= out_start + out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= green1[i_help2];		//out[out_1] = green[i_help2];
					out[out_1 + out_stride2]	= green2[i_help2];		//out[out_1] = green[i_help2];
					out[out_1 + out_stride3]	= green3[i_help2];		//out[out_1] = green[i_help2];
					out[out_1 + out_stride4]	= green4[i_help2];		//out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 0;out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= orange1[i_help2];		//out[out_1] = orange[i_help2];
					out[out_1 + out_stride2]	= orange2[i_help2];		//out[out_1] = orange[i_help2];
					out[out_1 + out_stride3]	= orange3[i_help2];		//out[out_1] = orange[i_help2];
					out[out_1 + out_stride4]	= orange4[i_help2];		//out[out_1] = orange[i_help2];
				}

				out_1		= out_start + out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= green1[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride2]	= green2[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride3]	= green3[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride4]	= green4[i_help2];		// out[out_1] = green[i_help2];
				}
			}
		}else{
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= orange1[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride2]	= orange2[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride3]	= orange3[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride4]	= orange4[i_help2];		// out[out_1] = orange[i_help2];
				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus  + out_start;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= green1[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride2]	= green2[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride3]	= green3[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride4]	= green4[i_help2];		// out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= orange1[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride2]	= orange2[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride3]	= orange3[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride4]	= orange4[i_help2];		// out[out_1] = orange[i_help2];

				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus + out_start;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= green1[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride2]	= green2[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride3]	= green3[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride4]	= green4[i_help2];		// out[out_1] = green[i_help2];
				}
			}
		}
	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_SIZE, __LINE__, __FILE__);
	}
	return decoder;
}

#elif defined(I386)

/*
 *
 */
PDC_Transformation_97_decoder* PDC_td_start_v2_sse2(	PDC_Exception* exception,
														PDC_Transformation_97_decoder* decoder,
														float *out, float *in_high, float* in_low,
														PDC_uint out_start, PDC_uint out_size,
														PDC_uint out_plus,  PDC_bool even,
														PDC_uint in_high_start, PDC_uint in_high_plus,
														PDC_uint in_low_start, PDC_uint in_low_plus,
														PDC_uint num_rows, PDC_uint high_stride, PDC_uint low_stride,
														PDC_uint out_stride)
{
	PDC_uint temp_numLoops, temp_numLoopsunrolled, temp_restLoop;
	PDC_uint i_help1, i_help2, i_help1_end, greensize, orangesize, out_1, out_1end, out_plus2;
	PDC_uint low_stride2, low_stride3, low_stride4;
	PDC_uint high_stride2, high_stride3, high_stride4;
	PDC_uint out_stride2, out_stride3, out_stride4;

	float			*workbuffer;
	float			*green1, * green2, *green3, *green4;
	float			*pink;
	float			*orange1, *orange2, *orange3, *orange4;
	float			*brown;
	float			*in_high1;
	float			*in_low1;
	PDC_uint		greenSize;
	PDC_uint32		pinkSize;
	PDC_uint		orangeSize;
	PDC_uint32		brownSize;
	PDC_uint32		maxSize;


	if(num_rows == 4){
		in_high1	= in_high;
		in_low1		= in_low;

		low_stride2	= low_stride;
		low_stride3	= low_stride * 2;
		low_stride4	= low_stride * 3;

		high_stride2	= high_stride;
		high_stride3	= high_stride * 2;
		high_stride4	= high_stride * 3;

		out_stride2	= out_stride;
		out_stride3 = out_stride * 2;
		out_stride4	= out_stride * 3;

	}else if(num_rows == 3){
		in_high1	= in_high;
		in_low1		= in_low;

		low_stride2	= low_stride;
		low_stride3	= low_stride * 2;
		low_stride4	= 0;

		high_stride2	= high_stride;
		high_stride3	= high_stride * 2;
		high_stride4	= 0;

		out_stride2	= out_stride;
		out_stride3 = out_stride * 2;
		out_stride4	= 0;

	}else if(num_rows == 2){
		in_high1	= in_high;
		in_low1		= in_low;

		low_stride2	= low_stride;
		low_stride3	= 0;
		low_stride4	= 0;

		high_stride2	= high_stride;
		high_stride3	= 0;
		high_stride4	= 0;

		out_stride2	= out_stride;
		out_stride3 = 0;
		out_stride4	= 0;

	}else if(num_rows == 1){
		in_high1	= in_high;
		in_low1		= in_low;

		low_stride2	= 0;
		low_stride3	= 0;
		low_stride4	= 0;

		high_stride2	= 0;
		high_stride3	= 0;
		high_stride4	= 0;

		out_stride2	= 0;
		out_stride3 = 0;
		out_stride4	= 0;

	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_DECODER, __LINE__, __FILE__);
		return decoder;
	}

	greensize	= 0;
	orangesize	= 0;
	workbuffer	= decoder->workbuffer;
	green1		= decoder->green;
	green2		= decoder->green + 1;
	green3		= decoder->green + 2;
	green4		= decoder->green + 3;
	pink		= decoder->pink;
	orange1		= decoder->orange;
	orange2		= decoder->orange + 1;
	orange3		= decoder->orange + 2;
	orange4		= decoder->orange + 3;
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
					i_help1		= 4;								//i_help1		= 1;
					i_help1_end	= (1 + out_size / 2) * 4;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_low_plus){
						orange1[i_help1] = in_low1[i_help2];
						orange2[i_help1] = in_low1[i_help2 + low_stride2];
						orange3[i_help1] = in_low1[i_help2 + low_stride3];
						orange4[i_help1] = in_low1[i_help2 + low_stride4];
					}
					orange1[0]				= orange1[8];				// orange[0]			= orange[2];
					orange1[i_help1]		= orange1[i_help1 - 4];		// orange[i_help1]		= orange[i_help1 - 1];
					orange1[i_help1 + 4]	= orange1[i_help1 - 8];		// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange2[0]				= orange2[8];				// orange[0]			= orange[2];
					orange2[i_help1]		= orange2[i_help1 - 4];		// orange[i_help1]		= orange[i_help1 - 1];
					orange2[i_help1 + 4]	= orange2[i_help1 - 8];		// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange3[0]				= orange3[8];				// orange[0]			= orange[2];
					orange3[i_help1]		= orange3[i_help1 - 4];		// orange[i_help1]		= orange[i_help1 - 1];
					orange3[i_help1 + 4]	= orange3[i_help1 - 8];		// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange4[0]				= orange4[8];				// orange[0]			= orange[2];
					orange4[i_help1]		= orange4[i_help1 - 4];		// orange[i_help1]		= orange[i_help1 - 1];
					orange4[i_help1 + 4]	= orange4[i_help1 - 8];		// orange[i_help1 + 1]	= orange[i_help1 - 2];


					i_help1 	= 8; 									//i_help1		= 2;
					i_help1_end	= (2 + out_size / 2) * 4;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_high_plus){
						green1[i_help1] = in_high1[i_help2];
						green2[i_help1] = in_high1[i_help2 + high_stride2];
						green3[i_help1] = in_high1[i_help2 + high_stride3];
						green4[i_help1] = in_high1[i_help2 + high_stride4];
					}
					green1[0]			= green1[12];					//green[0]			= green[3];
					green1[4]			= green1[8];						//green[1]			= green[2];
					green1[i_help1]		= green1[i_help1 - 8];			//green[i_help1]		= green[i_help1 - 2];
					green1[i_help1 + 4]	= green1[i_help1 - 12];			//green[i_help1 + 1]	= green[i_help1 - 3];

					green2[0]			= green2[12];					//green[0]			= green[3];
					green2[4]			= green2[8];						//green[1]			= green[2];
					green2[i_help1]		= green2[i_help1 - 8];			//green[i_help1]		= green[i_help1 - 2];
					green2[i_help1 + 4]	= green2[i_help1 - 12];			//green[i_help1 + 1]	= green[i_help1 - 3];

					green3[0]			= green3[12];					//green[0]			= green[3];
					green3[4]			= green3[8];						//green[1]			= green[2];
					green3[i_help1]		= green3[i_help1 - 8];			//green[i_help1]		= green[i_help1 - 2];
					green3[i_help1 + 4]	= green3[i_help1 - 12];			//green[i_help1 + 1]	= green[i_help1 - 3];

					green4[0]			= green4[12];					//green[0]			= green[3];
					green4[4]			= green4[8];						//green[1]			= green[2];
					green4[i_help1]		= green4[i_help1 - 8];			//green[i_help1]		= green[i_help1 - 2];
					green4[i_help1 + 4]	= green4[i_help1 - 12];			//green[i_help1 + 1]	= green[i_help1 - 3];

					greensize			= out_size / 2 + 4;
					orangesize			= greensize - 1;
				}else{
					i_help1		= 4;
					i_help1_end	= (1 + PDC_i_ceiling(out_size , 2)) * 4;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_low_plus){
						orange1[i_help1] = in_low1[i_help2];
						orange2[i_help1] = in_low1[i_help2 + low_stride2];
						orange3[i_help1] = in_low1[i_help2 + low_stride3];
						orange4[i_help1] = in_low1[i_help2 + low_stride4];
					}
					orange1[0]			= orange1[8];				//orange[0]			= orange[2];
					orange1[i_help1]	= orange1[i_help1 - 8];		//orange[i_help1]		= orange[i_help1 - 2];

					orange2[0]			= orange2[8];				//orange[0]			= orange[2];
					orange2[i_help1]	= orange2[i_help1 - 8];		//orange[i_help1]		= orange[i_help1 - 2];

					orange3[0]			= orange3[8];				//orange[0]			= orange[2];
					orange3[i_help1]	= orange3[i_help1 - 8];		//orange[i_help1]		= orange[i_help1 - 2];

					orange4[0]			= orange4[8];				//orange[0]			= orange[2];
					orange4[i_help1]	= orange4[i_help1 - 8];		//orange[i_help1]		= orange[i_help1 - 2];


					i_help1		= 8;
					i_help1_end	= (2 + PDC_i_ceiling(out_size , 2) - 1) * 4;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_high_plus){
						green1[i_help1] = in_high1[i_help2];
						green2[i_help1] = in_high1[i_help2 + high_stride2];
						green3[i_help1] = in_high1[i_help2 + high_stride3];
						green4[i_help1] = in_high1[i_help2 + high_stride4];
					}
					green1[0]			= green1[12];				//green[0]			= green[3];
					green1[4]			= green1[8];				//green[1]			= green[2];
					green1[i_help1]		= green1[i_help1 - 4];		//green[i_help1]		= green[i_help1 - 1];
					green1[i_help1 + 4]	= green1[i_help1 - 8];		//green[i_help1 + 1]	= green[i_help1 - 2];

					green2[0]			= green2[12];				//green[0]			= green[3];
					green2[4]			= green2[8];				//green[1]			= green[2];
					green2[i_help1]		= green2[i_help1 - 4];		//green[i_help1]		= green[i_help1 - 1];
					green2[i_help1 + 4]	= green2[i_help1 - 8];		//green[i_help1 + 1]	= green[i_help1 - 2];

					green3[0]			= green3[12];				//green[0]			= green[3];
					green3[4]			= green3[8];				//green[1]			= green[2];
					green3[i_help1]		= green3[i_help1 - 4];		//green[i_help1]		= green[i_help1 - 1];
					green3[i_help1 + 4]	= green3[i_help1 - 8];		//green[i_help1 + 1]	= green[i_help1 - 2];

					green4[0]			= green4[12];				//green[0]			= green[3];
					green4[4]			= green4[8];				//green[1]			= green[2];
					green4[i_help1]		= green4[i_help1 - 4];		//green[i_help1]		= green[i_help1 - 1];
					green4[i_help1 + 4]	= green4[i_help1 - 8];		//green[i_help1 + 1]	= green[i_help1 - 2];

					greensize			= PDC_i_floor( out_size , 2) + 4;
					orangesize			= greensize - 1;
				}
			}else{
				if(out_size % 2 == 0){
					i_help1		= 8;
					i_help1_end	= (2 + out_size / 2) * 4;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_low_plus){
						orange1[i_help1] = in_low1[i_help2];
						orange2[i_help1] = in_low1[i_help2 + low_stride2];
						orange3[i_help1] = in_low1[i_help2 + low_stride3];
						orange4[i_help1] = in_low1[i_help2 + low_stride4];

					}
					orange1[0]			= orange1[12];					// orange[0]			= orange[3];
					orange1[4]			= orange1[8];					// orange[1]			= orange[2];
					orange1[i_help1]	= orange1[i_help1 - 8];			// orange[i_help1]		= orange[i_help1 - 2];

					orange2[0]			= orange2[12];					// orange[0]			= orange[3];
					orange2[4]			= orange2[8];					// orange[1]			= orange[2];
					orange2[i_help1]	= orange2[i_help1 - 8];			// orange[i_help1]		= orange[i_help1 - 2];

					orange3[0]			= orange3[12];					// orange[0]			= orange[3];
					orange3[4]			= orange3[8];					// orange[1]			= orange[2];
					orange3[i_help1]	= orange3[i_help1 - 8];			// orange[i_help1]		= orange[i_help1 - 2];

					orange4[0]			= orange4[12];					// orange[0]			= orange[3];
					orange4[4]			= orange4[8];					// orange[1]			= orange[2];
					orange4[i_help1]	= orange4[i_help1 - 8];			// orange[i_help1]		= orange[i_help1 - 2];


					i_help1		= 8;
					i_help1_end	= (2 + out_size / 2) * 4;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_high_plus){
						green1[i_help1] = in_high1[i_help2];
						green2[i_help1] = in_high1[i_help2 + high_stride2];
						green3[i_help1] = in_high1[i_help2 + high_stride3];
						green4[i_help1] = in_high1[i_help2 + high_stride4];
					}
					green1[0]			= green1[16];					// green[0]			= green[4];
					green1[4]			= green1[12];					// green[1]			= green[3];
					green1[i_help1]		= green1[i_help1 - 4];			// green[i_help1]		= green[i_help1 - 1];
					green1[i_help1 + 4]	= green1[i_help1 - 8];			// green[i_help1 + 1]	= green[i_help1 - 2];

					green2[0]			= green2[16];					// green[0]			= green[4];
					green2[4]			= green2[12];					// green[1]			= green[3];
					green2[i_help1]		= green2[i_help1 - 4];			// green[i_help1]		= green[i_help1 - 1];
					green2[i_help1 + 4]	= green2[i_help1 - 8];			// green[i_help1 + 1]	= green[i_help1 - 2];

					green3[0]			= green3[16];					// green[0]			= green[4];
					green3[4]			= green3[12];					// green[1]			= green[3];
					green3[i_help1]		= green3[i_help1 - 4];			// green[i_help1]		= green[i_help1 - 1];
					green3[i_help1 + 4]	= green3[i_help1 - 8];			// green[i_help1 + 1]	= green[i_help1 - 2];

					green4[0]			= green4[16];					// green[0]			= green[4];
					green4[4]			= green4[12];					// green[1]			= green[3];
					green4[i_help1]		= green4[i_help1 - 4];			// green[i_help1]		= green[i_help1 - 1];
					green4[i_help1 + 4]	= green4[i_help1 - 8];			// green[i_help1 + 1]	= green[i_help1 - 2];

					greensize			= out_size / 2 + 4;
					orangesize			= greensize - 1;
				}else{
					i_help1		= 8;
					i_help1_end	= (2 + PDC_i_floor(out_size, 2)) * 4;
					i_help2		= in_low_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_low_plus){
						orange1[i_help1] = in_low1[i_help2];
						orange2[i_help1] = in_low1[i_help2 + low_stride2];
						orange3[i_help1] = in_low1[i_help2 + low_stride3];
						orange4[i_help1] = in_low1[i_help2 + low_stride4];
					}
					orange1[0]				= orange1[12];					// orange[0]			= orange[3];
					orange1[4]				= orange1[8];					// orange[1]			= orange[2];
					orange1[i_help1]		= orange1[i_help1 - 4];			// orange[i_help1]		= orange[i_help1 - 1];
					orange1[i_help1 + 4]	= orange1[i_help1 - 8];			// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange2[0]				= orange2[12];					// orange[0]			= orange[3];
					orange2[4]				= orange2[8];					// orange[1]			= orange[2];
					orange2[i_help1]		= orange2[i_help1 - 4];			// orange[i_help1]		= orange[i_help1 - 1];
					orange2[i_help1 + 4]	= orange2[i_help1 - 8];			// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange3[0]				= orange3[12];					// orange[0]			= orange[3];
					orange3[4]				= orange3[8];					// orange[1]			= orange[2];
					orange3[i_help1]		= orange3[i_help1 - 4];			// orange[i_help1]		= orange[i_help1 - 1];
					orange3[i_help1 + 4]	= orange3[i_help1 - 8];			// orange[i_help1 + 1]	= orange[i_help1 - 2];

					orange4[0]				= orange4[12];					// orange[0]			= orange[3];
					orange4[4]				= orange4[8];					// orange[1]			= orange[2];
					orange4[i_help1]		= orange4[i_help1 - 4];			// orange[i_help1]		= orange[i_help1 - 1];
					orange4[i_help1 + 4]	= orange4[i_help1 - 8];			// orange[i_help1 + 1]	= orange[i_help1 - 2];

					i_help1		= 8;
					i_help1_end	= (2 + PDC_i_ceiling(out_size, 2)) * 4;
					i_help2		= in_high_start;
					for(;i_help1 < i_help1_end; i_help1 += 4, i_help2 += in_high_plus){
						green1[i_help1] = in_high1[i_help2];
						green2[i_help1] = in_high1[i_help2 + high_stride2];
						green3[i_help1] = in_high1[i_help2 + high_stride3];
						green4[i_help1] = in_high1[i_help2 + high_stride4];
					}

					green1[0]			= green1[16];						// green[0]			= green[4];
					green1[4]			= green1[12];						// green[1]			= green[3];
					green1[i_help1]		= green1[i_help1 - 8];				// green[i_help1]		= green[i_help1 - 2];
					green1[i_help1 + 4]	= green1[i_help1 - 12];				// green[i_help1 + 1]	= green[i_help1 - 3];

					green2[0]			= green2[16];						// green[0]			= green[4];
					green2[4]			= green2[12];						// green[1]			= green[3];
					green2[i_help1]		= green2[i_help1 - 8];				// green[i_help1]		= green[i_help1 - 2];
					green2[i_help1 + 4]	= green2[i_help1 - 12];				// green[i_help1 + 1]	= green[i_help1 - 3];

					green3[0]			= green3[16];						// green[0]			= green[4];
					green3[4]			= green3[12];						// green[1]			= green[3];
					green3[i_help1]		= green3[i_help1 - 8];				// green[i_help1]		= green[i_help1 - 2];
					green3[i_help1 + 4]	= green3[i_help1 - 12];				// green[i_help1 + 1]	= green[i_help1 - 3];

					green4[0]			= green4[16];						// green[0]			= green[4];
					green4[4]			= green4[12];						// green[1]			= green[3];
					green4[i_help1]		= green4[i_help1 - 8];				// green[i_help1]		= green[i_help1 - 2];
					green4[i_help1 + 4]	= green4[i_help1 - 12];				// green[i_help1 + 1]	= green[i_help1 - 3];

					greensize			= PDC_i_ceiling(out_size, 2) + 4;
					orangesize			= greensize - 1;
				}
			}
		}else{
			if(even){
				if(out_size == 1){
					out[out_start] = in_low[in_low_start];
					out[out_start + out_stride2] = in_low[in_low_start + low_stride2];
					out[out_start + out_stride3] = in_low[in_low_start + low_stride3];
					out[out_start + out_stride4] = in_low[in_low_start + low_stride4];
					return decoder;
				}else if(out_size == 2){
					// green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					green1[0] = green1[4] = green1[8] = green1[12] = green1[16] = in_high[in_high_start];
					green2[0] = green2[4] = green2[8] = green2[12] = green2[16] = in_high[in_high_start + high_stride2];
					green3[0] = green3[4] = green3[8] = green3[12] = green3[16] = in_high[in_high_start + high_stride3];
					green4[0] = green4[4] = green4[8] = green4[12] = green4[16] = in_high[in_high_start + high_stride4];

					// orange[0] = orange[1] = orange[2] = orange[3] = in_low[in_low_start];
					orange1[0] = orange1[4] = orange1[8] = orange1[12] = in_low[in_low_start];
					orange2[0] = orange2[4] = orange2[8] = orange2[12] = in_low[in_low_start + low_stride2];
					orange3[0] = orange3[4] = orange3[8] = orange3[12] = in_low[in_low_start + low_stride3];
					orange4[0] = orange4[4] = orange4[8] = orange4[12] = in_low[in_low_start + low_stride4];

					greensize = 5;
					orangesize = 4;
				}else if(out_size == 3){
					// green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					green1[0] = green1[4] = green1[8] = green1[12] = green1[16] = in_high[in_high_start];
					green2[0] = green2[4] = green2[8] = green2[12] = green2[16] = in_high[in_high_start + high_stride2];
					green3[0] = green3[4] = green3[8] = green3[12] = green3[16] = in_high[in_high_start + high_stride3];
					green4[0] = green4[4] = green4[8] = green4[12] = green4[16] = in_high[in_high_start + high_stride4];

					// orange[0] = orange[2] = in_low[in_low_start + in_low_plus];
					orange1[0] = orange1[8] = in_low[in_low_start + in_low_plus];
					orange2[0] = orange2[8] = in_low[in_low_start + in_low_plus + low_stride2];
					orange3[0] = orange3[8] = in_low[in_low_start + in_low_plus + low_stride3];
					orange4[0] = orange4[8] = in_low[in_low_start + in_low_plus + low_stride4];

					// orange[1] = orange[3] = in_low[in_low_start];
					orange1[4] = orange1[12] = in_low[in_low_start];
					orange2[4] = orange2[12] = in_low[in_low_start + low_stride2];
					orange3[4] = orange3[12] = in_low[in_low_start + low_stride3];
					orange4[4] = orange4[12] = in_low[in_low_start + low_stride4];

					greensize = 5;
					orangesize = 4;
				}else if(out_size == 4){
					// green[0] = green[3] = in_high[in_high_start + in_high_plus];
					green1[0] = green1[3] = in_high[in_high_start + in_high_plus];
					green2[0] = green2[3] = in_high[in_high_start + in_high_plus + high_stride2];
					green3[0] = green3[3] = in_high[in_high_start + in_high_plus + high_stride3];
					green4[0] = green4[3] = in_high[in_high_start + in_high_plus + high_stride4];

					// green[1] = green[2] = green[4] = green[5] = in_high[in_high_start];
					green1[4] = green1[8] = green1[16] = green1[20] = in_high[in_high_start];
					green2[4] = green2[8] = green2[16] = green2[20] = in_high[in_high_start + high_stride2];
					green3[4] = green3[8] = green3[16] = green3[20] = in_high[in_high_start + high_stride3];
					green4[4] = green4[8] = green4[16] = green4[20] = in_high[in_high_start + high_stride4];

					// orange[0] = orange[2] = orange[3] = in_low[in_low_start + in_low_plus];
					orange1[0] = orange1[8] = orange1[12] = in_low[in_low_start + in_low_plus];
					orange2[0] = orange2[8] = orange2[12] = in_low[in_low_start + in_low_plus + low_stride2];
					orange3[0] = orange3[8] = orange3[12] = in_low[in_low_start + in_low_plus + low_stride3];
					orange4[0] = orange4[8] = orange4[12] = in_low[in_low_start + in_low_plus + low_stride4];

					// orange[1] = orange[4] = in_low[in_low_start];
					orange1[4] = orange1[16] = in_low[in_low_start];
					orange2[4] = orange2[16] = in_low[in_low_start + low_stride2];
					orange3[4] = orange3[16] = in_low[in_low_start + low_stride3];
					orange4[4] = orange4[16] = in_low[in_low_start + low_stride4];

					greensize = 6;
					orangesize = 5;
				}
			}else{
				if(out_size == 1){
					out[out_start] 					= in_low[in_low_start];
					out[out_start + out_stride2]	= in_low[in_low_start + low_stride2];
					out[out_start + out_stride3]	= in_low[in_low_start + low_stride3];
					out[out_start + out_stride4]	= in_low[in_low_start + low_stride4];
					return decoder;
				}else if(out_size == 2){
					// green[0] = green[1] = green[2] = green[3] = green[4] = in_high[in_high_start];
					green1[0] = green1[4] = green1[8] = green1[12] = green1[16]	= in_high[in_high_start];
					green2[0] = green2[4] = green2[8] = green2[12] = green2[16]	= in_high[in_high_start + high_stride2];
					green3[0] = green3[4] = green3[8] = green3[12] = green3[16]	= in_high[in_high_start + high_stride3];
					green4[0] = green4[4] = green4[8] = green4[12] = green4[16]	= in_high[in_high_start + high_stride4];

					// orange[0] = orange[1] = orange[2] = orange[3] = in_low[in_low_start];
					orange1[0] = orange1[4] = orange1[8] = orange1[12] = in_low[in_low_start];
					orange2[0] = orange2[4] = orange2[8] = orange2[12] = in_low[in_low_start + low_stride2];
					orange3[0] = orange3[4] = orange3[8] = orange3[12] = in_low[in_low_start + low_stride3];
					orange4[0] = orange4[4] = orange4[8] = orange4[12] = in_low[in_low_start + low_stride4];

					greensize = 5;
					orangesize = 4;
				}else if(out_size == 3){
					// green[0] = green[2] = green[4] = in_high[in_high_start];
					green1[0] = green1[8] = green1[16] = in_high[in_high_start];
					green2[0] = green2[8] = green2[16] = in_high[in_high_start + high_stride2];
					green3[0] = green3[8] = green3[16] = in_high[in_high_start + high_stride3];
					green4[0] = green4[8] = green4[16] = in_high[in_high_start + high_stride4];

					// green[1] = green[3] = green[5] = in_high[in_high_start + in_high_plus];
					green1[4] = green1[12] = green1[20] = in_high[in_high_start + in_high_plus];
					green2[4] = green2[12] = green2[20] = in_high[in_high_start + in_high_plus + high_stride2];
					green3[4] = green3[12] = green3[20] = in_high[in_high_start + in_high_plus + high_stride3];
					green4[4] = green4[12] = green4[20] = in_high[in_high_start + in_high_plus + high_stride4];

					//orange[0] = orange[1] = orange[2] = orange[3] = orange[4] = in_low[in_low_start];
					orange1[0] = orange1[4] = orange1[8] = orange1[12] = orange1[16] = in_low[in_low_start];
					orange2[0] = orange2[4] = orange2[8] = orange2[12] = orange2[16] = in_low[in_low_start + low_stride2];
					orange3[0] = orange3[4] = orange3[8] = orange3[12] = orange3[16] = in_low[in_low_start + low_stride3];
					orange4[0] = orange4[4] = orange4[8] = orange4[12] = orange4[16] = in_low[in_low_start + low_stride4];

					greensize = 6;
					orangesize = 5;
				}else if(out_size == 4){
					// green[0] = green[1] = green[3] = green[4] = in_high[in_high_start + in_high_plus];
					green1[0] = green1[4] = green1[12] = green1[16] = in_high[in_high_start + in_high_plus];
					green2[0] = green2[4] = green2[12] = green2[16] = in_high[in_high_start + in_high_plus + high_stride2];
					green3[0] = green3[4] = green3[12] = green3[16] = in_high[in_high_start + in_high_plus + high_stride3];
					green4[0] = green4[4] = green4[12] = green4[16] = in_high[in_high_start + in_high_plus + high_stride4];

					// green[2] = green[5] = in_high[in_high_start];
					green1[8] = green1[20] = in_high[in_high_start];
					green2[8] = green2[20] = in_high[in_high_start + high_stride2];
					green3[8] = green3[20] = in_high[in_high_start + high_stride3];
					green4[8] = green4[20] = in_high[in_high_start + high_stride4];

					// orange[0] = orange[3] = in_low[in_low_start + in_low_plus];
					orange1[0] = orange1[12] = in_low[in_low_start + in_low_plus];
					orange2[0] = orange2[12] = in_low[in_low_start + in_low_plus + low_stride2];
					orange3[0] = orange3[12] = in_low[in_low_start + in_low_plus + low_stride3];
					orange4[0] = orange4[12] = in_low[in_low_start + in_low_plus + low_stride4];

					// orange[1] = orange[2] = orange[4] = in_low[in_low_start];
					orange1[4] = orange1[8] = orange1[16] = in_low[in_low_start];
					orange2[4] = orange2[8] = orange2[16] = in_low[in_low_start + low_stride2];
					orange3[4] = orange3[8] = orange3[16] = in_low[in_low_start + low_stride3];
					orange4[4] = orange4[8] = orange4[16] = in_low[in_low_start + low_stride4];


					greensize = 6;
					orangesize =5;
				}
			}
		}

		/*
		if(uwe_count == 0){
			for(i_help1 = 0; i_help1 < greensize; i_help1 += 1){
				fprintf(DEBUG_FILE2,"%6d green   %13.2f \n",(int)i_help1, green2[i_help1 * 4]);
			}

			for(i_help1 = 0; i_help1 < orangesize; i_help1 += 1){
				fprintf(DEBUG_FILE2,"%6d orange   %13.2f \n",(int)i_help1, orange2[i_help1 * 4]);
			}
			uwe_count += 1;
		}
		*/

		__asm__ volatile (
	"	mov		ecx,	%2					/* 			*/" "\n\t"
	"	cmp		ecx,	0					/* 			*/" "\n\t"
	"	je		9f							/* if greensize == 0 jump out 			*/" "\n\t"

	"	xor		edx,	edx					/* 			*/" "\n\t"
	" 	mov		eax,	ecx					/* 			*/" "\n\t"
	"	mov		ebx,	4					/* 			*/" "\n\t"
	"	div		ebx							/* 			*/" "\n\t"
	"	mov		ecx,	eax					/* 			*/" "\n\t"
	"										/* 			*/" "\n\t"
	"										/* 			*/" "\n\t"

	"	mov		eax,	%3					/* 			*/" "\n\t"
	"	movaps	xmm6,	[eax]				/* load k			*/" "\n\t"
	"	mov		eax,	%4					/* 					*/" "\n\t"
	"	movaps	xmm7,	[eax]				/* load k1			*/" "\n\t"
	"	mov		eax,	%0					/* load orange pointer  			*/" "\n\t"
	"	mov		ebx,	%1					/* load green pointer				*/" "\n\t"
	"	xor		esi,	esi					/* 			*/" "\n\t"
	"	prefetcht0	[eax + 64]				/* 			*/" "\n\t"
	"	prefetcht0	[ebx + 64]				/* 			*/" "\n\t"
	"	prefetcht0	[eax + 128]				/* 			*/" "\n\t"
	"	prefetcht0	[ebx + 128]				/* 			*/" "\n\t"

	"0:										/* 			*/" "\n\t"
	"	movaps	xmm0,	[eax]				/* 			*/" "\n\t"
	"	movaps	xmm1,	[ebx]				/* 			*/" "\n\t"
	"	movaps	xmm2,	[eax + 16]			/* 			*/" "\n\t"
	"	movaps	xmm3,	[ebx + 16]			/* 			*/" "\n\t"
	"	movaps	xmm4,	[eax + 32]			/* 			*/" "\n\t"
	"	movaps	xmm5,	[ebx + 32]			/* 			*/" "\n\t"

	"	mulps	xmm0,	xmm6				/* 			*/" "\n\t"
	"	mulps	xmm1,	xmm7				/* 			*/" "\n\t"
	"	movaps	[eax],	xmm0				/* 			*/" "\n\t"
	"	movaps	[ebx],	xmm1				/* 			*/" "\n\t"

	"	movaps	xmm0,	[eax + 48]			/* 			*/" "\n\t"
	"	movaps	xmm1,	[ebx + 48]			/* 			*/" "\n\t"
	"	mulps	xmm2,	xmm6				/* 			*/" "\n\t"
	"	mulps	xmm3,	xmm7				/* 			*/" "\n\t"
	"	mulps	xmm4,	xmm6				/* 			*/" "\n\t"
	"	mulps	xmm5,	xmm7				/* 			*/" "\n\t"
	"	mulps	xmm0,	xmm6				/* 			*/" "\n\t"
	"	mulps	xmm1,	xmm7				/* 			*/" "\n\t"

	"	movaps	[eax + 16],	xmm2				/* 			*/" "\n\t"
	"	movaps	[ebx + 16],	xmm3				/* 			*/" "\n\t"
	"	movaps	[eax + 32],	xmm4				/* 			*/" "\n\t"
	"	movaps	[ebx + 32],	xmm5				/* 			*/" "\n\t"
	"	movaps	[eax + 48],	xmm0				/* 			*/" "\n\t"
	"	movaps	[ebx + 48],	xmm1				/* 			*/" "\n\t"

	"	add		eax,	64					/* 			*/" "\n\t"
	"	add		ebx,	64					/* 			*/" "\n\t"


	"	prefetcht0	[eax + 128]				/* 			*/" "\n\t"
	"	prefetcht0	[ebx + 128]				/* 			*/" "\n\t"
	"	dec		ecx							/* 			*/" "\n\t"
	"	cmp		ecx,	0					/* 			*/" "\n\t"
	"	jne		0b							/* 			*/" "\n\t"

	"	mov		ecx,	edx					/* 			*/" "\n\t"
	"	cmp		ecx,	0					/* 			*/" "\n\t"
	"	je		2f							/* 			*/" "\n\t"
	"1:					/* 			*/" "\n\t"
	"	movaps	xmm0,	[eax]				/* 			*/" "\n\t"
	"	movaps	xmm1,	[ebx]				/* 			*/" "\n\t"
	"	mulps	xmm0,	xmm6				/* 			*/" "\n\t"
	"	mulps	xmm1,	xmm7				/* 			*/" "\n\t"
	"	movaps	[eax],	xmm0				/* 			*/" "\n\t"
	"	movaps	[ebx],	xmm1				/* 			*/" "\n\t"
	"	add		eax,	16					/* 			*/" "\n\t"
	"	add		ebx,	16					/* 			*/" "\n\t"
	"	dec		ecx							/* 			*/" "\n\t"
	"	cmp		ecx,	0					/* 			*/" "\n\t"
	"	jne		1b							/* 			*/" "\n\t"
	"2:					/* 			*/" "\n\t"

	"			/*	#################################################	*/" "\n\t"
	"			/*	############	Start Second part ###############	*/" "\n\t"
	"			/*	#################################################	*/" "\n\t"
	"	mov		eax,	%2					/* 			*/" "\n\t"
	"	sub		eax,	1					/* 			*/" "\n\t"
	"	xor		edx,	edx					/* 			*/" "\n\t"
	"	mov		ebx,	4					/* 			*/" "\n\t"
	"	div		ebx							/* 			*/" "\n\t"
	"	mov		esi,	ebx					/* 			*/" "\n\t"
	"	mov		ecx,	eax					/* 			*/" "\n\t"
	"	mov		eax,	%8					/* delta pointer			*/" "\n\t"
	"	movaps	xmm7,	[eax]				/* 							*/" "\n\t"
	"	mov		ebx,	%9					/* gamma pointer			*/" "\n\t"
	"	movaps	xmm6,	[ebx]				/* 							*/" "\n\t"
	"	mov		eax,	%0					/* load orange pointer  			*/" "\n\t"
	"	mov		ebx,	%1					/* load green pointer				*/" "\n\t"

	"/* orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);			*/" "\n\t"

	"	movaps	xmm5,	[ebx]				/* 			*/" "\n\t"
	"										/* 			*/" "\n\t"
	"	movaps	xmm0,	xmm5				/* 			*/" "\n\t"
	"	movaps	xmm4,	xmm5				/* 			*/" "\n\t"
	"	movaps	xmm5,	[ebx + 16]			/* 			*/" "\n\t"
	"	movaps	xmm1,	[eax]				/* 			*/" "\n\t"

	"	addps	xmm0,	xmm5				/* 			*/" "\n\t"
	"	mulps	xmm0,	xmm7				/* 			*/" "\n\t"
	"	subps	xmm1,	xmm0				/* 			*/" "\n\t"

	"	movaps	[eax],	xmm1				/* 			*/" "\n\t"
	"	movaps	xmm3,	xmm1				/* 	save orange			*/" "\n\t"
	"	add		eax,	16					/* 						*/" "\n\t"

	"	prefetcht0	[eax + 64]				/* 						*/" "\n\t"
	"	prefetcht0	[eax + 128]				/* 						*/" "\n\t"
	"	prefetcht0	[ebx + 64]				/* 						*/" "\n\t"
	"	prefetcht0	[ebx + 128]				/* 						*/" "\n\t"


	"1:		/* Start main loop 				*/" "\n\t"
				"/* orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);			*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm5,	[ebx + 32]			/* load green			*/" "\n\t"
				"	movaps	xmm1,	[eax]				/* load orange 			*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 			*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 			*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 			*/" "\n\t"

				"	movaps	[eax], 	xmm1				/* sav orange		*/" "\n\t"

				"/* 	green[i_help1] = green[i_help2] - gamma * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[ebx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		ebx,	16					/* 			*/" "\n\t"
				"	add		eax,	16					/* 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);			*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm5,	[ebx + 32]			/* load green			*/" "\n\t"
				"	movaps	xmm1,	[eax]				/* load orange 			*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 			*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 			*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 			*/" "\n\t"

				"	movaps	[eax], 	xmm1				/* sav orange		*/" "\n\t"

				"/* 	green[i_help1] = green[i_help2] - gamma * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[ebx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		ebx,	16					/* 			*/" "\n\t"
				"	add		eax,	16					/* 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);			*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm5,	[ebx + 32]			/* load green			*/" "\n\t"
				"	movaps	xmm1,	[eax]				/* load orange 			*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 			*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 			*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 			*/" "\n\t"

				"	movaps	[eax], 	xmm1				/* sav orange		*/" "\n\t"

				"/* 	green[i_help1] = green[i_help2] - gamma * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[ebx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		ebx,	16					/* 			*/" "\n\t"
				"	add		eax,	16					/* 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);			*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm5,	[ebx + 32]			/* load green			*/" "\n\t"
				"	movaps	xmm1,	[eax]				/* load orange 			*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 			*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 			*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 			*/" "\n\t"

				"	movaps	[eax], 	xmm1				/* sav orange		*/" "\n\t"

				"/* 	green[i_help1] = green[i_help2] - gamma * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[ebx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		ebx,	16					/* 			*/" "\n\t"
				"	add		eax,	16					/* 			*/" "\n\t"

	"	prefetcht0	[eax + 128]				/* 			*/" "\n\t"
	"	prefetcht0	[ebx + 128]				/* 			*/" "\n\t"
	"	dec		ecx							/* 			*/" "\n\t"
	"	cmp		ecx, 0						/* 			*/" "\n\t"
	"	jne		1b							/* 			*/" "\n\t"

	"	mov		ecx,	esi				/* 			*/" "\n\t"
	"	cmp		ecx,	0				/* 			*/" "\n\t"
	"	je		3f				/* 			*/" "\n\t"

	"2:					/* 			*/" "\n\t"
				"/* orange[i_help1] = orange[i_help1] - delta * ( green[i_help1] + green[i_help2]);			*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 						*/" "\n\t"
				"	movaps	xmm5,	[ebx + 32]			/* load green			*/" "\n\t"
				"	movaps	xmm1,	[eax]				/* load orange 			*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 			*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 			*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 			*/" "\n\t"

				"	movaps	[eax], 	xmm1				/* sav orange		*/" "\n\t"

				"/* 	green[i_help1] = green[i_help2] - gamma * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[ebx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		ebx,	16					/* 			*/" "\n\t"
				"	add		eax,	16					/* 			*/" "\n\t"

	"	dec		ecx						/* 			*/" "\n\t"
	"	cmp		ecx,	0				/* 			*/" "\n\t"
	"	jne		2b						/* 			*/" "\n\t"
	"3:					/* 			*/" "\n\t"


	"			/*	#################################################	*/" "\n\t"
	"			/*	############	Start Third part ###############	*/" "\n\t"
	"			/*	#################################################	*/" "\n\t"
	"	mov		eax,	%2					/* 			*/" "\n\t"
	"	sub		eax,	1					/* 			*/" "\n\t"
	"	xor		edx,	edx					/* 			*/" "\n\t"
	"	mov		ebx,	4					/* 			*/" "\n\t"
	"	div		ebx							/* 			*/" "\n\t"
	"	mov		esi,	edx					/* 			*/" "\n\t"
	"	mov		ecx,	eax					/* 			*/" "\n\t"
	"	mov		eax,	%10					/* beta pointer						*/" "\n\t"
	"	movaps	xmm7,	[eax]				/* 									*/" "\n\t"
	"	mov		ebx,	%11					/* alpha pointer					*/" "\n\t"
	"	movaps	xmm6,	[ebx]				/* 									*/" "\n\t"
	"	mov		eax,	%0					/* load orange pointer  			*/" "\n\t"
	"	mov		ebx,	%1					/* load green pointer				*/" "\n\t"


	"/* orange[i_help1] = orange[i_help2] - beta * (green[i_help1] + green[i_help2])		*/" "\n\t"

	"	movaps	xmm5,	[ebx]				/* preload green[i_help1]			*/" "\n\t"
	"										/* 									*/" "\n\t"
	"	movaps	xmm0,	xmm5				/* 									*/" "\n\t"
	"	movaps	xmm4,	xmm5				/* 									*/" "\n\t"
	"	movaps	xmm5,	[ebx + 16]			/* load green[i_help2]				*/" "\n\t"
	"	movaps	xmm1,	[eax + 16]			/* load orange[i_help2]				*/" "\n\t"

	"	addps	xmm0,	xmm5				/* 									*/" "\n\t"
	"	mulps	xmm0,	xmm7				/* 									*/" "\n\t"
	"	subps	xmm1,	xmm0				/* 									*/" "\n\t"

	"	movaps	[eax],	xmm1				/* 									*/" "\n\t"
	"	movaps	xmm3,	xmm1				/* 	save orange			*/" "\n\t"
	"	add		eax,	16					/* 						*/" "\n\t"

	"	prefetcht0	[eax + 64]				/* 						*/" "\n\t"
	"	prefetcht0	[eax + 128]				/* 						*/" "\n\t"
	"	prefetcht0	[ebx + 64]				/* 						*/" "\n\t"
	"	prefetcht0	[ebx + 128]				/* 						*/" "\n\t"

	"	cmp		ecx, 	0					/* 			*/" "\n\t"
	"	je		2f							/* 			*/" "\n\t"

	"1:					/* Start main loop 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help2] - beta * (green[i_help1] + green[i_help2])		*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm5,	[ebx + 32]			/* load green[i_help2]				*/" "\n\t"
				"	movaps	xmm1,	[eax + 16]			/* load orange[i_help2]				*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 									*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 									*/" "\n\t"

				"	movaps	[eax],	xmm1				/* 	save orange									*/" "\n\t"

				"/* 	green[i_help1] = green[i_help2] - alpha * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[ebx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		ebx,	16					/* 			*/" "\n\t"
				"	add		eax,	16					/* 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help2] - beta * (green[i_help1] + green[i_help2])		*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm5,	[ebx + 32]			/* load green[i_help2]				*/" "\n\t"
				"	movaps	xmm1,	[eax + 16]			/* load orange[i_help2]				*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 									*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 									*/" "\n\t"

				"	movaps	[eax],	xmm1				/* 	save orange									*/" "\n\t"


				"/* 	green[i_help1] = green[i_help2] - alpha * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[ebx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		ebx,	16					/* 			*/" "\n\t"
				"	add		eax,	16					/* 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help2] - beta * (green[i_help1] + green[i_help2])		*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm5,	[ebx + 32]			/* load green[i_help2]				*/" "\n\t"
				"	movaps	xmm1,	[eax + 16]			/* load orange[i_help2]				*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 									*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 									*/" "\n\t"

				"	movaps	[eax],	xmm1				/* 	save orange									*/" "\n\t"


				"/* 	green[i_help1] = green[i_help2] - alpha * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[ebx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		ebx,	16					/* 			*/" "\n\t"
				"	add		eax,	16					/* 			*/" "\n\t"

				"/* orange[i_help1] = orange[i_help2] - beta * (green[i_help1] + green[i_help2])		*/" "\n\t"
				"	movaps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm4,	xmm5				/* 									*/" "\n\t"
				"	movaps	xmm5,	[ebx + 32]			/* load green[i_help2]				*/" "\n\t"
				"	movaps	xmm1,	[eax + 16]			/* load orange[i_help2]				*/" "\n\t"

				"	addps	xmm0,	xmm5				/* 									*/" "\n\t"
				"	mulps	xmm0,	xmm7				/* 									*/" "\n\t"
				"	subps	xmm1,	xmm0				/* 									*/" "\n\t"

				"	movaps	[eax],	xmm1				/* 	save orange									*/" "\n\t"


				"/* 	green[i_help1] = green[i_help2] - alpha * ( orange[i_help1] + orange[i_help2]);		*/" "\n\t"
				"	addps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	mulps	xmm3,	xmm6				/* 			*/" "\n\t"
				"	subps	xmm4,	xmm3				/* 			*/" "\n\t"

				"	movaps	[ebx],	xmm4				/* save green 			*/" "\n\t"
				"	movaps	xmm3,	xmm1				/* 			*/" "\n\t"
				"	add		ebx,	16					/* 			*/" "\n\t"
				"	add		eax,	16					/* 			*/" "\n\t"


	"	prefetcht0	[eax + 128]				/* 						*/" "\n\t"
	"	prefetcht0	[ebx + 128]				/* 						*/" "\n\t"
	"	dec		ecx							/* 			*/" "\n\t"
	"	cmp		ecx,	0					/* 			*/" "\n\t"
	"	jne		1b							/* 			*/" "\n\t"
	"2:					/* 			*/" "\n\t"
	"					/* 			*/" "\n\t"
	"					/* 			*/" "\n\t"
	"					/* 			*/" "\n\t"

	"					/* 			*/" "\n\t"
	"9:					/* 			*/" "\n\t"

	"/*( %0 orange),( %1 green), (%2 greensize), (%3 k), (%4 k1), (%5 temp_numLoops), (%6 temp_numLoopsunrolled), (%7 tem_restLoop), (%8 delta), (%9 gamma) (%10 beta) (%11 alpha) */" "\n\t"
		 :
		 :	"m"(orange1), "m"(green1), "m"(greensize), "m"(decoder->K ), "m"(decoder->K1), "m"(temp_numLoops),  "m"(temp_numLoopsunrolled), "m"(temp_restLoop), "m"(decoder->delta), "m"(decoder->gamma), "m"(decoder->beta), "m"(decoder->alpha)
		 : 	"memory",  "esi", "edx", "eax", "ecx", "xmm6", "xmm7", "xmm0", "xmm1"
		);

		if(even){
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 0;out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= orange1[i_help2]; //out[out_1] = orange[i_help2];
					out[out_1 + out_stride2] 	= orange2[i_help2]; //out[out_1] = orange[i_help2];
					out[out_1 + out_stride3] 	= orange3[i_help2]; //out[out_1] = orange[i_help2];
					out[out_1 + out_stride4] 	= orange4[i_help2]; //out[out_1] = orange[i_help2];
				}

				out_1		= out_start + out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= green1[i_help2];		//out[out_1] = green[i_help2];
					out[out_1 + out_stride2]	= green2[i_help2];		//out[out_1] = green[i_help2];
					out[out_1 + out_stride3]	= green3[i_help2];		//out[out_1] = green[i_help2];
					out[out_1 + out_stride4]	= green4[i_help2];		//out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 0;out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= orange1[i_help2];		//out[out_1] = orange[i_help2];
					out[out_1 + out_stride2]	= orange2[i_help2];		//out[out_1] = orange[i_help2];
					out[out_1 + out_stride3]	= orange3[i_help2];		//out[out_1] = orange[i_help2];
					out[out_1 + out_stride4]	= orange4[i_help2];		//out[out_1] = orange[i_help2];
				}

				out_1		= out_start + out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= green1[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride2]	= green2[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride3]	= green3[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride4]	= green4[i_help2];		// out[out_1] = green[i_help2];
				}
			}
		}else{
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= orange1[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride2]	= orange2[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride3]	= orange3[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride4]	= orange4[i_help2];		// out[out_1] = orange[i_help2];
				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus  + out_start;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= green1[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride2]	= green2[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride3]	= green3[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride4]	= green4[i_help2];		// out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus  + out_start;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= orange1[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride2]	= orange2[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride3]	= orange3[i_help2];		// out[out_1] = orange[i_help2];
					out[out_1 + out_stride4]	= orange4[i_help2];		// out[out_1] = orange[i_help2];

				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus + out_start;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 4){
					out[out_1] 					= green1[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride2]	= green2[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride3]	= green3[i_help2];		// out[out_1] = green[i_help2];
					out[out_1 + out_stride4]	= green4[i_help2];		// out[out_1] = green[i_help2];
				}
			}
		}
	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_SIZE, __LINE__, __FILE__);
	}
	return decoder;
}



#else
/*
 *
 */
PDC_Transformation_97_decoder* PDC_td_start_v2_sse2(	PDC_Exception* exception,
														PDC_Transformation_97_decoder* decoder,
														float *out, float *in_high, float* in_low,
														PDC_uint out_start, PDC_uint out_size,
														PDC_uint out_plus,  PDC_bool even,
														PDC_uint in_high_start, PDC_uint in_high_plus,
														PDC_uint in_low_start, PDC_uint in_low_plus,
														PDC_uint num_rows, PDC_uint high_stride, PDC_uint low_stride,
														PDC_uint out_stride){

	return PDC_td_start_v2( 	exception,
								decoder,
								out, in_high,  in_low,
								out_start, out_size,
								out_plus,  even,
								in_high_start, in_high_plus,
								in_low_start, in_low_plus,
								num_rows, high_stride, low_stride,
								out_stride);

}


/*
 *
 */
PDC_Transformation_97_decoder* PDC_td_start_v3_vertical(	PDC_Threadcall *variable ){
	//PDC_Exception* exception				= variable->exception;
	PDC_Transformation_97_decoder* decoder	= variable->decoder;
	float *out								= variable->out_data1;
	float *in_high							= variable->sub2_data;
	float* in_low							= variable->sub1_data;
	//PDC_int out_start;
	PDC_int out_size						= variable->out_size_horizontal;
	//PDC_int out_plus,
	PDC_bool even							= variable->evenhl;
	//PDC_int in_high_start, PDC_int in_high_plus,
	//PDC_int in_low_start, PDC_int in_low_plus,
	PDC_int end_row							= variable->end_row;
	PDC_int start_row						= variable->start_row;
	PDC_int high_stride						= variable->linestride_float;
	PDC_int low_stride						= variable->linestride_float;
	PDC_int out_stride						= variable->linestride_float;

	PDC_int		pos_row, low_pos, high_pos, size, temp_size, i_help1, i_help2,
				out_pos1, out_pos2;
	float		*orange, *green;
	PDC_bool 	even_left, even_right;
	float		delta_K1, temp1, temp2;

	orange	= decoder->orange;
	green 	= decoder->green;

	size = PDC_i_floor(out_size, 2) + 4;
	even_left	= even;
	if(even_left == PDC_true){
		if(out_size % 2 == 0){
			even_right = PDC_false;
		}else{
			even_right = PDC_true;
		}
	}else{
		if(out_size % 2 != 0){
			even_right = PDC_false;
		}else{
			size = PDC_i_ceiling(out_size, 2) + 4;
			even_right = PDC_true;
		}
	}

	// green = high
	delta_K1 = delta * K1;
	for(pos_row = start_row; pos_row < end_row; pos_row += 1){
		temp_size 	= size - 1;
		high_pos	= pos_row * high_stride;
		low_pos		= pos_row * low_stride;
		/*
		for(i_help1 = 0; i_help1 < greensize; i_help1 += 1){
			green[i_help1] *= K1;
		}
		for(i_help1 = 0; i_help1 < orangesize; i_help1 += 1){
			orange[i_help1] *= K;
		}
		*/
		temp2	= in_high[high_pos];
		high_pos 	+= 1;
		for(i_help1 = 0; i_help1 < temp_size; i_help1 += 1, low_pos += 1, high_pos += 1){
			temp1 = temp2;
			temp2 = in_high[high_pos];
			orange[i_help1] = K * in_low[low_pos] - delta_K1 * ( temp1 + temp2);
		}

		high_pos	= pos_row * high_stride + 1;
		temp_size 	= size - 2;
		for(i_help1 = 0, i_help2 = 1; i_help1 < temp_size;high_pos += 1){
			green[i_help1] = K1 * in_high[high_pos] - f_gamma * ( orange[i_help1] + orange[i_help2]);
			i_help1 = i_help2;
			i_help2 += 1;
		}

		out_pos1 = pos_row * out_stride;
		if(even){
			out_pos1 -= 1;
		}
		temp_size 	= size - 3;
		for(i_help1 = 0, i_help2 = 1; i_help1 < temp_size; out_pos1 += 2){
			out[out_pos1] = orange[i_help2] - beta * ( green[i_help1] + green[i_help2]);

			i_help1 = i_help2;
			i_help2 += 1;
		}

		out_pos1 = pos_row * out_stride + 1;
		out_pos2 = out_pos1 - 1;
		if(even){
			out_pos1 -= 1;
			out_pos2 -= 1;
		}
		temp2 = out[out_pos2];
		out_pos2 += 2;
		temp_size 	= size - 4;
		for(i_help1 = 0, i_help2 = 1; i_help1 < temp_size;out_pos1 += 2, out_pos2 += 2){
			temp1 = temp2;
			temp2 = out[out_pos2];
			out[out_pos1] = green[i_help2] - alpha * ( temp1 + temp2);


			i_help1 = i_help2;
			i_help2 += 1;
		}
	}

	return decoder;
}


/*
 *
 */
PDC_Transformation_97_decoder* PDC_td_start_v3_horizontal(	PDC_Threadcall *variable ){
	//PDC_Exception* exception				= variable->exception;
	PDC_Transformation_97_decoder* decoder	= variable->decoder;
	float *out								= variable->out_data1;
	float *in_high							= variable->sub2_data;
	float* in_low							= variable->sub1_data;
	//PDC_uint out_start						= variable->out_data;
	PDC_uint out_size						= variable->out_size_vertical;
	//PDC_uint out_plus						= variable->linestride_float;
	PDC_bool even							= variable->evenvl;
	PDC_uint in_high_start					= 0;
	PDC_uint in_high_plus					= variable->linestride_float;
	PDC_uint in_low_start					= 0;
	PDC_uint in_low_plus					= variable->linestride_float;
	PDC_int end_col							= variable->end_col;
	PDC_int start_col						= variable->start_col;
	//PDC_uint high_stride					= variable->linestride_float;
	//PDC_uint low_stride						= variable->linestride_float;
	PDC_uint out_stride						= variable->linestride_float;

	PDC_int	pos_col, high_pos, low_pos, temp_size, size, out_stride_2, out_pos1, out_pos2, i_help1;
	float	*orange, *green,  *in_high_work, *in_low_work;
	float	temp1, temp2, delta_K1;

	out_stride_2 = out_stride * 2;

	orange	= decoder->orange;
	green	= decoder->green;

	delta_K1 = delta * K1;

	size = PDC_i_floor(out_size, 2) + 4;
	if(even != PDC_true){
		if(out_size % 2 == 0){
			size = PDC_i_ceiling(out_size, 2) + 4;
		}
	}

	for(pos_col = start_col; pos_col < end_col; pos_col += 1){
		in_high_work 	= in_high + pos_col;
		in_low_work		= in_low +  pos_col;

/*
		for(i_help1 = 0; i_help1 < greensize; i_help1 += 1){
			green[i_help1] *= K1;
		}
		for(i_help1 = 0; i_help1 < orangesize; i_help1 += 1){
			orange[i_help1] *= K;
		}
*/

		high_pos 	= in_high_start;
		low_pos		= in_low_start;
		temp2 		= in_high_work[high_pos];
		high_pos	+= in_high_plus;
		temp_size	= size - 1;

		for(i_help1 = 0; i_help1 < temp_size; i_help1 += 1, high_pos += in_high_plus, low_pos += in_low_plus){
			temp1	= temp2;
			temp2	= in_high_work[high_pos];

			orange[i_help1] = K * in_low_work[low_pos] - delta_K1 * ( temp1 + temp2);

		}


		temp_size 	= size - 1;
		i_help1 	= 0;
		temp2		= orange[i_help1];
		i_help1		+= 1;
		high_pos	= in_high_start + in_high_plus;

		for(; i_help1 < temp_size; i_help1 += 1, high_pos += in_high_plus ){
			temp1 	= temp2;
			temp2	= orange[i_help1];
			green[i_help1 - 1] = K1 * in_high_work[high_pos] - f_gamma * ( temp1 + temp2);

		}

		out_pos1 = pos_col ;
		if(even){
			out_pos1 -= out_stride;
		}
		temp_size	= size - 2;
		temp2		= green[0];
		for(i_help1 = 1; i_help1 < temp_size; i_help1 += 1, out_pos1 += out_stride_2){
			temp1	= temp2;
			temp2	= green[i_help1];
			out[out_pos1] = orange[i_help1] - beta * ( temp1 + temp2);
		}

		out_pos1 = pos_col ;
		out_pos2 = pos_col + out_stride;
		if(even){
			out_pos1 -= out_stride;
			out_pos2 -= out_stride;
		}
		temp_size 	= size - 3;
		temp2 		= out[out_pos1];
		for(i_help1 = 1, out_pos1 += out_stride_2; i_help1 < temp_size; i_help1 += 1, out_pos1 += out_stride_2, out_pos2 += out_stride_2){
			temp1	= temp2;
			temp2	= out[out_pos1];
			out[out_pos2] = green[i_help1] - alpha * ( temp1 + temp2);
		}
	}


	return decoder;
}

#endif


STOP_C
