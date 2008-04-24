#include "Layer.h"

namespace BDK
{

	Layer::Layer(int id_layer)
	{
		number_of_codeword_segments	= 0;
		number_of_coding_passes		= 0;
		this->id_layer				= id_layer;
	}

	void Layer::set_codeword_segment_length(int length)
	{
		codeword_segment_length.push_back(length);

	}
}