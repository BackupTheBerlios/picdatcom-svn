#include "Filter97_decoder.h"

namespace BDK{


	float Filter97_decoder::alpha	= -1.586134342059924f;
	float Filter97_decoder::beta	= -0.052980118572961f;
	float Filter97_decoder::gamma	=  0.882911075530934f;
	float Filter97_decoder::delta	=  0.443506852043971f;
	float Filter97_decoder::K		=  1.230174104914001f; 
	float Filter97_decoder::K1		=  1.0f/Filter97_decoder::K;

	Filter97_decoder::Filter97_decoder(int maxSize)
	{
		this->maxSize = maxSize;
		greenSize	= BDK_i_ceiling(this->maxSize, 2) + 4;
		orangeSize	= greenSize;

		green	= new float[greenSize];
		orange	= new float[orangeSize];

	}

	void Filter97_decoder::start(	float *out, float *in_high, float* in_low, 
									int out_start, int out_size, int out_plus, bool even, 
									int in_high_start, int in_high_plus,
									int in_low_start, int in_low_plus)
	{
		int i_help1, i_help2, i_help1_end, greensize, orangesize, out_1, out_1end, out_plus2;
		
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
						i_help1_end	= i_help1 + BDK_i_ceiling(out_size , 2);
						i_help2		= in_low_start;
						for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
							orange[i_help1] = in_low[i_help2];
						}
						orange[0]			= orange[2];
						orange[i_help1]		= orange[i_help1 - 2];
						

						i_help1		= 2;
						i_help1_end	= i_help1 + BDK_i_ceiling(out_size , 2) - 1;
						i_help2		= in_high_start;
						for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
							green[i_help1] = in_high[i_help2];
						}
						green[0]			= green[3];
						green[1]			= green[2];
						green[i_help1]		= green[i_help1 - 1];
						green[i_help1 + 1]	= green[i_help1 - 2];

						greensize			= BDK_i_floor( out_size , 2) + 4;
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
						i_help1_end	= i_help1 + BDK_i_floor(out_size, 2);
						i_help2		= in_low_start;
						for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_low_plus){
							orange[i_help1] = in_low[i_help2];
						}
						orange[0]			= orange[3];
						orange[1]			= orange[2];
						orange[i_help1]		= orange[i_help1 - 1];
						orange[i_help1 + 1]	= orange[i_help1 - 2];

						i_help1		= 2;
						i_help1_end	= i_help1 + BDK_i_ceiling(out_size, 2);
						i_help2		= in_high_start;
						for(;i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_high_plus){
							green[i_help1] = in_high[i_help2];
						}
						green[0]			= green[4];
						green[1]			= green[3];
						green[i_help1]		= green[i_help1 - 2];
						green[i_help1 + 1]	= green[i_help1 - 3];
						greensize			= BDK_i_ceiling(out_size, 2) + 4;
						orangesize			= greensize - 1;
					}
				}
			}else{
				if(even){
					if(out_size == 1){
						out[out_start] = in_low[in_low_start]; 
						return;
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
						return;
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
			throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "out_size > maxSize " );
		}
	}
}