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

#include "PDC_Transformation_97_encoder.h"

START_C

extern float alpha;
extern float beta;
extern float f_gamma;
extern float delta;
extern float K;
extern float K1;

/*
 *
 */
PDC_Transformation_97_encoder* new_PDC_Transformation_97_encoder(PDC_Exception* exception, PDC_uint32 maxSize)
{
	PDC_Transformation_97_encoder* encoder = NULL;

	encoder = malloc(sizeof(PDC_Transformation_97_encoder));
	if(encoder == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	encoder->workbuffer	= NULL;
	encoder->green		= NULL;
	encoder->pink		= NULL;
	encoder->orange		= NULL;
	encoder->brown		= NULL;
	encoder->exception	= NULL;

	encoder->maxSize = maxSize;
	encoder->pinkSize =
	encoder->brownSize =
	encoder->greenSize =
	encoder->orangeSize = PDC_i_ceiling(maxSize, 2) + 4;



	encoder->green = malloc(sizeof(float) * encoder->greenSize);
	if(encoder->green == NULL){
		delete_PDC_Transformation_97_encoder(exception, encoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	encoder->orange	= malloc(sizeof(float) * encoder->orangeSize);
	if(encoder->orange == NULL){
		delete_PDC_Transformation_97_encoder(exception, encoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	encoder->pink	= malloc(sizeof(float) * encoder->pinkSize);
	if(encoder->pink == NULL){
		delete_PDC_Transformation_97_encoder(exception, encoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	encoder->brown	= malloc(sizeof(float) * encoder->brownSize);
	if(encoder->brown == NULL){
		delete_PDC_Transformation_97_encoder(exception, encoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	encoder->workbuffer	= malloc(sizeof(float) * maxSize);
	if(encoder->workbuffer == NULL){
		delete_PDC_Transformation_97_encoder(exception, encoder);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	return encoder;
}

/*
 *
 */
PDC_Transformation_97_encoder* delete_PDC_Transformation_97_encoder(PDC_Exception* exception, PDC_Transformation_97_encoder* encoder)
{
	if(encoder != NULL){
		if(encoder->brown != NULL){
			free(encoder->brown);
		}
		if(encoder->green != NULL){
			free(encoder->green);
		}
		if(encoder->orange != NULL){
			free(encoder->orange);
		}
		if(encoder->pink != NULL){
			free(encoder->pink);
		}
		if(encoder->workbuffer != NULL){
			free(encoder->workbuffer);
		}

		free(encoder);
	}

	return NULL;
}

/*
 *
 */
PDC_Transformation_97_encoder* PDC_te_start(	PDC_Exception* exception,
												PDC_Transformation_97_encoder* encoder,
												float *in, float *out_high, float* out_low,
												PDC_uint32 in_start, PDC_uint32 in_size, PDC_uint32 in_plus, PDC_bool even,
												PDC_uint32 out_high_start, PDC_uint32 out_high_plus,
												PDC_uint32 out_low_start, PDC_uint32 out_low_plus)
{
	PDC_uint i_help1, i_help2, in_plus_2, i_help1_end, greensize, orangesize, pinksize, out_1;

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

	pinksize  	= 0;
	workbuffer	= encoder->workbuffer;
	green		= encoder->green;
	pink		= encoder->pink;
	orange		= encoder->orange;
	brown		= encoder->brown;
	greenSize	= encoder->greenSize;
	pinkSize	= encoder->pinkSize;
	orangeSize	= encoder->orangeSize;
	brownSize	= encoder->brownSize;
	maxSize		= encoder->maxSize;

	if(in_size <= maxSize){
		if(in_size > 4){
			if(even){
				if(in_size % 2 == 0){
					in_plus_2	= in_plus * 2;
					i_help1_end = 2 + (in_size / 2);
					greensize	= 4 + (in_size / 2);
					for(i_help1 = 2, i_help2 = in_start; i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_plus_2){
						green[i_help1] = in[i_help2];
					}
					green[i_help1]		= green[i_help1 - 1];
					green[i_help1 + 1]	= green[i_help1 - 2];
					green[0]			= green[4];
					green[1]			= green[3];

					i_help1_end = 2 + (in_size / 2);
					for(i_help1 = 2, i_help2 = in_start + in_plus ; i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_plus_2){
						pink[i_help1] = in[i_help2];
					}
					pink[0] = pink[3];
					pink[1]	= pink[2];
					pink[i_help1]		= pink[i_help1 - 2];
					pinksize = greensize - 1;
				}else{
					in_plus_2	= in_plus * 2;
					i_help1_end = 2 + PDC_i_ceiling(in_size , 2);
					greensize	= 4 + PDC_i_ceiling(in_size , 2);
					for(i_help1 = 2, i_help2 = in_start; i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_plus_2){
						green[i_help1] = in[i_help2];
					}
					green[i_help1]		= green[i_help1 - 2];
					green[i_help1 + 1]	= green[i_help1 - 3];
					green[0]			= green[4];
					green[1]			= green[3];

					i_help1_end = 2 + (in_size / 2);
					for(i_help1 = 2, i_help2 = in_start + in_plus ; i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_plus_2){
						pink[i_help1] = in[i_help2];
					}
					pink[0] = pink[3];
					pink[1]	= pink[2];
					pink[i_help1]		= pink[i_help1 - 1];
					pink[i_help1 + 1]		= pink[i_help1 - 2];
					pinksize = greensize - 1;
				}
			}else{
				if(in_size % 2 == 0){
					in_plus_2	= in_plus * 2;
					i_help1_end = 2 + (in_size / 2);
					greensize	= 4 + (in_size / 2);
					for(i_help1 = 2, i_help2 = in_start + in_plus; i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_plus_2){
						green[i_help1] = in[i_help2];
					}
					green[i_help1]		= green[i_help1 - 2];
					green[i_help1 + 1]	= green[i_help1 - 3];
					green[0]			= green[3];
					green[1]			= green[2];

					i_help1_end = 1 + (in_size / 2);
					for(i_help1 = 1, i_help2 = in_start; i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_plus_2){
						pink[i_help1] = in[i_help2];
					}
					pink[0] = pink[2];
					pink[i_help1]		= pink[i_help1 - 1];
					pink[i_help1 + 1]	= pink[i_help1 - 2];
					pinksize = greensize - 1;
				}else{
					in_plus_2	= in_plus * 2;
					i_help1_end = 2 + PDC_i_floor(in_size, 2);
					greensize	= 4 + PDC_i_floor(in_size, 2);
					for(i_help1 = 2, i_help2 = in_start + in_plus; i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_plus_2){
						green[i_help1] = in[i_help2];
					}
					green[i_help1]		= green[i_help1 - 1];
					green[i_help1 + 1]	= green[i_help1 - 2];
					green[0]			= green[3];
					green[1]			= green[2];

					i_help1_end = 1 + PDC_i_ceiling(in_size , 2);
					for(i_help1 = 1, i_help2 = in_start; i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_plus_2){
						pink[i_help1] = in[i_help2];
					}
					pink[0] = pink[2];
					pink[i_help1]	= pink[i_help1 - 2];
					pinksize = greensize - 1;
				}
			}
		}else{
			if(even){
				if(in_size == 1){
					out_low[out_low_start] = in[in_start ];
					return encoder;
				}else if(in_size == 2){
					green[0] = green[1] = green[2] = green[3] = green[4] = in[in_start];
					pink[0] = pink[1] = pink[2] = pink[3] = in[in_start + in_plus];
					greensize = 5;
					pinksize = 4;
				}else if(in_size == 3){
					green[0] = green[2] = green[4] = in[in_start];
					green[1] = green[3] = green[5] = in[in_start + 2 * in_plus];
					pink[0] = pink[1] = pink[2] = pink[3] = pink[4] = in[in_start + in_plus];
					greensize = 6;
					pinksize = 5;
				}else if(in_size == 4){
					green[0] = green[1] = green[3] = green[4] = in[in_start + 2 * in_plus];
					green[2] = green[5] = in[in_start];
					pink[0] = pink[3] = in[in_start + 3 * in_plus];
					pink[1] = pink[2] = pink[4] = in[in_start + in_plus];
					greensize = 6;
					pinksize = 5;
				}

			}else{
				if(in_size == 1){
					out_low[out_low_start] = in[in_start ];
					return encoder;
				}else if(in_size == 2){
					green[0] = green[1] = green[2] = green[3] = green[4] = in[in_start + in_plus];
					pink[0] = pink[1] = pink[2] = pink[3] = in[in_start];
					greensize = 5;
					pinksize = 4;
				}else if(in_size == 3){
					green[0] = green[1] = green[2] = green[3] = green[4] = in[in_start + in_plus];
					pink[0] = pink[2] = in[in_start + 2 * in_plus];
					pink[1] = pink[3] = in[in_start];
					greensize = 5;
					pinksize = 4;
				}else if(in_size == 4){
					green[0] = green[3] = in[in_start + 3 * in_plus];
					green[1] = green[2] = green[4] = green[5] = in[in_start + in_plus];
					pink[0] = pink[2] = pink[3] = in[in_start + 2 * in_plus];
					pink[1] = pink[4] = in[in_start];
					greensize = 6;
					pinksize = 5;
				}
			}
		}

		for(i_help1 = 0; i_help1 < pinksize; i_help1 += 1){
			pink[i_help1] += alpha * ( green[i_help1] + green[i_help1 + 1]);
		}

		orangesize = pinksize - 1;
		for(i_help1 = 0; i_help1 < orangesize; i_help1 += 1){
			orange[i_help1] = green[i_help1 + 1] + beta * ( pink[i_help1] + pink[i_help1 + 1]);
		}

		pinksize = orangesize - 1;
		for(i_help1 = 0; i_help1 < pinksize; i_help1 += 1){
			pink[i_help1] = pink[i_help1 + 1] + f_gamma * ( orange[i_help1] + orange[i_help1 + 1]);
		}
		orangesize = pinksize - 1;
		for(i_help1 = 0; i_help1 < orangesize; i_help1 += 1){
			orange[i_help1] = orange[i_help1 + 1] + delta * ( pink[i_help1] + pink[i_help1 + 1]);
		}

		if(even){
			if(in_size % 2 == 0){
				i_help2 = in_size / 2;
				out_1 = out_low_start;

				for(i_help1 = 0; i_help1 < i_help2; i_help1 += 1, out_1 += out_low_plus){
					out_low[out_1] = orange[i_help1] * K1;
				}

				out_1 = out_high_start;
				i_help2 += 1;
				for(i_help1 = 1; i_help1 < i_help2; i_help1 += 1, out_1 += out_high_plus){
					out_high[out_1] = pink[i_help1] * K;
				}
			}else{
				i_help2 = PDC_i_ceiling( in_size , 2);
				out_1 = out_low_start;

				for(i_help1 = 0; i_help1 < i_help2; i_help1 += 1, out_1 += out_low_plus){
					out_low[out_1] = orange[i_help1] * K1;
				}

				out_1 = out_high_start;
				i_help2 += 1;
				for(i_help1 = 1; i_help1 < i_help2; i_help1 += 1, out_1 += out_high_plus){
					out_high[out_1] = pink[i_help1] * K;
				}
			}
		}else{
			if(in_size % 2 == 0){
				i_help2 = in_size / 2;
				out_1 = out_low_start;

				for(i_help1 = 0; i_help1 < i_help2; i_help1 += 1, out_1 += out_low_plus){
					out_low[out_1] = orange[i_help1] * K1;
				}

				out_1 = out_high_start;
				for(i_help1 = 0; i_help1 < i_help2; i_help1 += 1, out_1 += out_high_plus){
					out_high[out_1] = pink[i_help1] * K;
				}
			}else{
				i_help2 = PDC_i_floor(in_size, 2);
				out_1 = out_low_start;

				for(i_help1 = 0; i_help1 < i_help2; i_help1 += 1, out_1 += out_low_plus){
					out_low[out_1] = orange[i_help1] * K1;
				}

				i_help2 = PDC_i_ceiling(in_size, 2);
				out_1 = out_high_start;
				for(i_help1 = 0; i_help1 < i_help2; i_help1 += 1, out_1 += out_high_plus){
					out_high[out_1] = pink[i_help1] * K;
				}
			}
		}
	}else{
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_SIZE, __LINE__, __FILE__);
	}

	return encoder;
}

STOP_C
