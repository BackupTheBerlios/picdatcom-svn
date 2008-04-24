#ifndef __LAYER_H__
#define __LAYER_H__

#include "Default_Exceptionhandler.h"
#include <vector>

namespace BDK
{
	class Layer
	{
	public:
		Layer(int id_layer);
		
		int id_layer;
		int number_of_codeword_segments;
		int number_of_coding_passes;
		vector<int>	codeword_segment_length;

		void set_codeword_segment_length(int length);
	};
}
#endif