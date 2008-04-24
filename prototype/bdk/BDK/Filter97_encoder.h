
#ifndef __FILTER97_ENCODER_H__
#define __FILTER97_ENCODER_H__

#include "Parameter.h"
#include "Default_Exceptionhandler.h"

namespace BDK
{
	class Filter97_encoder
	{
	private:

		static float alpha;
		static float beta;
		static float gamma;
		static float delta;
		static float K;
		static float K1;

		float	*workbuffer;
		float	*green;
		float	*pink;
		float	*orange;
		float	*brown;
		int		greenSize;
		int		pinkSize;
		int		orangeSize;
		int		brownSize;


		int		maxSize;

	public:
		Filter97_encoder(int maxSize);
		void start(	float *in, float *out_high, float* out_low, 
					int in_start, int in_size, int in_plus, bool even, 
					int out_high_start, int out_hight_plus,
					int out_low_start, int out_low_plus);

		static unsigned int low_lenght(bool even, unsigned int in_length);
	};
}

#endif