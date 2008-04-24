
#include "Filter97_encoder.h"


namespace BDK
{

	float Filter97_encoder::alpha	= -1.586134342059924f;
	float Filter97_encoder::beta	= -0.052980118572961f;
	float Filter97_encoder::gamma	=  0.882911075530934f;
	float Filter97_encoder::delta	=  0.443506852043971f;
	float Filter97_encoder::K		=  1.230174104914001f; 
	float Filter97_encoder::K1		=  1.0f/Filter97_encoder::K;

	Filter97_encoder::Filter97_encoder(int maxSize)
	{
		if(maxSize > 4){
			this->maxSize = maxSize;
		}else{
			this->maxSize = 5;
		}
		
		greenSize	= BDK_i_ceiling(this->maxSize, 2) + 4;
		pinkSize	= greenSize;
		orangeSize	= greenSize;
		brownSize	= greenSize;
		
		workbuffer	= new float[this->maxSize + 8];
		green		= new float[greenSize];
		pink		= new float[pinkSize];
		orange		= new float[orangeSize];
		brown		= new float[brownSize];
		
	}


	void Filter97_encoder::start(	float *in, float *out_high, float* out_low, 
									int in_start, int in_size, int in_plus, bool even, 
									int out_high_start, int out_high_plus,
									int out_low_start, int out_low_plus)
	{
		int i_help1, i_help2, in_plus_2, i_help1_end, greensize, orangesize, pinksize, out_1;

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
						i_help1_end = 2 + BDK_i_ceiling(in_size , 2);
						greensize	= 4 + BDK_i_ceiling(in_size , 2); 
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
						i_help1_end = 2 + BDK_i_floor(in_size, 2);
						greensize	= 4 + BDK_i_floor(in_size, 2); 
						for(i_help1 = 2, i_help2 = in_start + in_plus; i_help1 < i_help1_end; i_help1 += 1, i_help2 += in_plus_2){
							green[i_help1] = in[i_help2];
						}
						green[i_help1]		= green[i_help1 - 1];
						green[i_help1 + 1]	= green[i_help1 - 2];
						green[0]			= green[3];
						green[1]			= green[2];

						i_help1_end = 1 + BDK_i_ceiling(in_size , 2);
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
						return;
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
						return;
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
				pink[i_help1] = pink[i_help1 + 1] + gamma * ( orange[i_help1] + orange[i_help1 + 1]);
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
					i_help2 = BDK_i_ceiling( in_size , 2);
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
					i_help2 = BDK_i_floor(in_size, 2);
					out_1 = out_low_start;
					
					for(i_help1 = 0; i_help1 < i_help2; i_help1 += 1, out_1 += out_low_plus){
						out_low[out_1] = orange[i_help1] * K1;
					}
	
					i_help2 = BDK_i_ceiling(in_size, 2);
					out_1 = out_high_start;
					for(i_help1 = 0; i_help1 < i_help2; i_help1 += 1, out_1 += out_high_plus){
						out_high[out_1] = pink[i_help1] * K; 
					}
				} 
			}
		}else{
			throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "in_size > maxSize " );
		}
	}
	
	unsigned int Filter97_encoder::low_lenght(bool even, unsigned int in_length)
	{
		unsigned int length = BDK_i_floor(in_length, 2);

		if(in_length % 2 != 0){
			if(even){
				length++;
			}
		}
		return length;
	}
}