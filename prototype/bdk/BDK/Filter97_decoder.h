
#ifndef __FILTER97_DECODER_H__
#define __FILTER97_DECODER_H__

#include "Parameter.h"
#include "Default_Exceptionhandler.h"

namespace BDK
{
	class Filter97_decoder
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

		int maxSize;
	public:
		Filter97_decoder(int maxSize);
		void Filter97_decoder::start(	float *out, float *in_high, float* in_low, 
										int out_start, int out_size, int out_plus, bool even, 
										int in_high_start, int in_hight_plus,
										int in_low_start, int in_low_plus);
	};
}
#endif