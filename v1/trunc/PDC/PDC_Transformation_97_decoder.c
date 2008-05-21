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

START_C


float alpha	= -1.586134342059924f;
float beta	= -0.052980118572961f;
float gamma	=  0.882911075530934f;
float delta	=  0.443506852043971f;
float K		=  1.230174104914001f; 
float K1	=  1.0f/1.230174104914001f;

/*
 *
 */
PDC_Transformation_97_decoder* new_PDC_Transformation_97_decoder(PDC_uint_32 maxSize)
{
	PDC_Transformation_97_decoder* decoder = NULL;

	decoder = malloc(sizeof(PDC_Transformation_97_decoder));
	if(decoder == NULL){
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
	


	decoder->green = malloc(sizeof(float) * decoder->greenSize);
	if(decoder->green == NULL){
		decoder = delete_PDC_Transformation_97_decoder(decoder);
		return NULL;
	}

	decoder->orange	= malloc(sizeof(float) * decoder->orangeSize);
	if(decoder->orange == NULL){
		decoder = delete_PDC_Transformation_97_decoder(decoder);
		return NULL;
	}

	decoder->pink	= malloc(sizeof(float) * decoder->pinkSize);
	if(decoder->pink == NULL){
		decoder = delete_PDC_Transformation_97_decoder(decoder);
		return NULL;
	}

	decoder->brown	= malloc(sizeof(float) * decoder->brownSize);
	if(decoder->brown == NULL){
		decoder = delete_PDC_Transformation_97_decoder(decoder);
		return NULL;
	}

	decoder->workbuffer	= malloc(sizeof(float) * maxSize);
	if(decoder->workbuffer == NULL){
		decoder = delete_PDC_Transformation_97_decoder(decoder);
		return NULL;
	}

	return decoder;
}


/*
 *
 */
PDC_Transformation_97_decoder* delete_PDC_Transformation_97_decoder(PDC_Transformation_97_decoder* decoder)
{
	if(decoder != NULL){
		if(decoder->brown != NULL){
			free(decoder->brown);
		}
		if(decoder->green != NULL){
			free(decoder->green);
		}
		if(decoder->orange != NULL){
			free(decoder->orange);
		}
		if(decoder->pink != NULL){
			free(decoder->pink);
		}
		if(decoder->workbuffer != NULL){
			free(decoder->workbuffer);
		}
		
		delete_PDC_Exception(decoder->exception);

		free(decoder);
	}

	return NULL;
}

/*
 *
 */
PDC_Transformation_97_decoder* PDC_td_start(	PDC_Transformation_97_decoder* decoder,
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
	PDC_uint_32		greenSize;
	PDC_uint_32		pinkSize;
	PDC_uint_32		orangeSize;
	PDC_uint_32		brownSize;
	PDC_uint_32		maxSize;

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

		
		if(even){
			if(out_size % 2 == 0){
				i_help1 = 0;
				out_1		= out_start;
				out_1end	= out_size * out_plus;
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
				out_1end	= out_size * out_plus;
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
				out_1end	= out_size * out_plus;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}else{
				i_help1 = 0;
				out_1		= out_start + out_plus;
				out_1end	= out_size * out_plus;
				out_plus2	= 2 * out_plus;
				for(i_help2 = 1;out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = orange[i_help2];
				}

				out_1		= out_start ;
				out_1end	= out_size * out_plus;
				for(i_help2 = 0; out_1 < out_1end; out_1 += out_plus2, i_help2 += 1){
					out[out_1] = green[i_help2];
				}
			}
		}
	}else{
		PDC_Exception_error(decoder->exception, NULL, PDC_EXCEPTION_OUT_OF_SIZE, __LINE__, __FILE__);
	}
	return decoder;
}



STOP_C

