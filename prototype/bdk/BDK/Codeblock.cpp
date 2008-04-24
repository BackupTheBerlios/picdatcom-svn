// Codeblock.cpp
//
// This header file defines the implementation of the class Codeblock
//
// This file was generate from a Dia Diagram using the xslt script file dia-uml2cpp.xsl
// which is copyright(c) Dave Klotzbach <dklotzbach@foxvalley.net>
//
// The author asserts no additional copyrights on the derived product. Limitations
// on the uses of this file are the right and responsibility of authors of the source 
// diagram.
// 
// The dia-uml2cpp.xsl script is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for 
// more details.
//
// A copy of the GNU General Public License is available by writing to the 
// Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, 
// MA 02111-1307, USA.
//
// 
//
#include "Codeblock.h"


double BDK::Codeblock::log_help = log(2.0);

BDK::Codeblock::~Codeblock()
{
}

//  Operation: Codeblock
//
//  Description:
//   
//  Parameters:
//      subband	
//      n	
//      m	
//

void BDK::Codeblock::init(Subband* subband, int n, int m, bool empty)
{
	int		codeblock_x, codeblock_y;

	data							= NULL;
	empty							= empty;
	codeblock_include				= false;
	//number_of_codeword_segments		= 1;
	Lblock							= 3;
	this->subband					= subband;
	//number_of_coding_passes_point	= 0;

	codeblock_x = 1 << subband->xcb;
	codeblock_y = 1 << subband->ycb;

	cx0 = codeblock_x * n;
	cx1 = cx0 + codeblock_x;
	cy0 = codeblock_y * m;
	cy1 = cy0 + codeblock_y;

	if(!empty){
		cx0 = BDK_i_max(cx0, subband->tbx0);
		cx1 = BDK_i_min(cx1, subband->tbx1);
		cy0 = BDK_i_max(cy0, subband->tby0);
		cy1 = BDK_i_min(cy1, subband->tby1);
	}
}

BDK::Codeblock::Codeblock(Subband* subband, int n, int m, bool empty)
{
	init(subband, n, m, empty);
}

/*
BDK::Codeblock::Codeblock(bool empty)
{
	init(empty);
}
*/

void BDK::Codeblock::set_Zero_bitplane_information(int Zero_bitplane_information)
{
	this->Zero_bitplane_information = Zero_bitplane_information;
	number_codeword = 1;
	active_codeword	= 0;
	if(data != NULL){
		data->set_numb_bitplane(subband->M - Zero_bitplane_information);
	}
	for(int i = 0; i < number_codeword; i++){
		codeword.push_back(new ByteBuffer());
	}
	data->setdecoder(codeword[0]);
}

void BDK::Codeblock::set_number_of_coding_passes(int number_of_coding_passes)
{
	current_layer->number_of_coding_passes = number_of_coding_passes; 
	//active_codeword = 0;
	current_layer->number_of_codeword_segments = 1;
}

int	BDK::Codeblock::get_number_of_codeword_segments()
{
	return current_layer->number_of_codeword_segments;
}


int	BDK::Codeblock::get_number_of_coding_passes_segment()
{
/*
	int back = 0;
	if(pos == 0){
		back = current_layer->number_of_coding_passes;
	}else{
		throw new Default_Exceptionhandler(__FILE__, __LINE__,"is not implement jet");
	}
*/
	return current_layer->number_of_coding_passes;
}

void BDK::Codeblock::set_codeword_segment_length(int pos, ByteBuffer* bytebuffer)
{
	double d_number_of_coding_passes_segment = (double)get_number_of_coding_passes_segment();
	int number_bit = (int)floor(log(d_number_of_coding_passes_segment)/ log_help);
	number_bit += Lblock;
	if(number_bit > 31 || number_bit < 3){
		throw new Default_Exceptionhandler(__FILE__, __LINE__,"To much bit");
	}
	//codeword_segment_length[pos] = bytebuffer->readbit(number_bit, 0, true);
	current_layer->set_codeword_segment_length(bytebuffer->readbit(number_bit, 0, true));
}


void BDK::Codeblock::set_Lblock(ByteBuffer* bytebuffer)
{
	unsigned char bit;
	do{
		bit = bytebuffer->get_next_bit(true);
		if(bit != 0){
			Lblock++;
		}
	}while(bit != 0);
}

void BDK::Codeblock::set_codeword_segment_data(ByteBuffer* bytebuffer)
{
	int nr_segment, length_segment;
	int fm_active_codeword = active_codeword;
	ByteBuffer* work_buffer;
	if(codeblock_include_segments == true){
		nr_segment = get_number_of_codeword_segments();
		for(int i = 0; i < nr_segment; i++, fm_active_codeword++){
			work_buffer = codeword[fm_active_codeword];
			length_segment = get_codeword_segment_length(i);
			work_buffer->add_bytes(bytebuffer, length_segment);
			//this->data->start_decode_Coefficient_bit_modeling(number_of_coding_passes);
		}
	}
}

void BDK::Codeblock::initData(Data *data, int offsetX, int offsetY)
{
	this->data = new Data(data, cx0 + offsetX, cx1 + offsetX, cy0 + offsetY, cy1 + offsetY);
	switch(this->subband->subbandtype){
		case SUBBAND_HH:
			this->data->nr_subband = 2;
			break;
		case SUBBAND_HL:
			this->data->nr_subband = 1;
			break;
		case SUBBAND_LH:
			this->data->nr_subband = 0;
			break;
		case SUBBAND_LL:
			this->data->nr_subband = 0;
			break;
	}
}

void BDK::Codeblock::bits_decode()
{


}

void BDK::Codeblock::decode_codeword()
{
	int num_layer = (int)layer.size();

	for(int i = 0; i < num_layer; i++){
		decode_codeword(i);	
	}
}


void BDK::Codeblock::decode_codeword(int l_layer)
{
	set_current_layer(l_layer);
	int number_of_coding_passes = current_layer->number_of_coding_passes;
	if(current_layer->number_of_coding_passes != 0){
		this->data->start_decode_Coefficient_bit_modeling(number_of_coding_passes);
	}
}

void BDK::Codeblock::create_Layer(int l_layer)
{
	if(l_layer == layer.size()){
		current_layer = new Layer(l_layer);
		layer.push_back(current_layer);
	}
}


int BDK::Codeblock::get_codeword_segment_length(int pos)
{
	int back = 0;
	if((unsigned int)pos <= current_layer->codeword_segment_length.size()){
		back = current_layer->codeword_segment_length[pos];
	}else{
		throw new Default_Exceptionhandler(__FILE__, __LINE__,"codeword_segment_length no pos");
	}
	return back;
}

void BDK::Codeblock::set_current_layer(int l_layer)
{
	unsigned int i;
	current_layer = NULL;
	for(i = 0; i < layer.size(); i++){
		if(layer[i]->id_layer == l_layer){
			current_layer = layer[i];
			break;
		}
	}
	if(current_layer == NULL){
		throw new Default_Exceptionhandler(__FILE__, __LINE__,"No layer found");
	}
}