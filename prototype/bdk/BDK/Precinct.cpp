// Precinct.cpp
//
// This header file defines the implementation of the class Precinct
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
#include "Precinct.h"


BDK::Precinct::~Precinct()
{
}

//  Operation: Precinct
//
//  Description:
//   
//  Parameters:
//      resolution	
//      n	
//      n	
//

BDK::Precinct::Precinct(Resolution* resolution, int n, int m)
{
	int nr_codeblocks_x;
	int nr_codeblocks_y;
	int high_x;
	int high_y;
	int cn0, cn1, cm0, cm1;

	this->resolution = resolution;

	high_x = resolution->precinct_size->PPx - resolution->xcb + 1;
	high_y = resolution->precinct_size->PPy - resolution->ycb + 1;
	
	if(high_x < 0 || high_y < 0){
		throw new Default_Exceptionhandler(__FILE__, __LINE__,"Precinct and codeblock size do not fit");
	}

	nr_codeblocks_x = 1 << high_x;
	nr_codeblocks_y = 1 << high_y;

	cn0 = nr_codeblocks_x * n;
	cn1 = cn0 + nr_codeblocks_x;
	cm0 = nr_codeblocks_y * m;
	cm1 = cm0 + nr_codeblocks_y;

	cn0 = BDK_i_max(cn0, resolution->cn0);
	cn1 = BDK_i_min(cn1, resolution->cn1);
	
	cm0 = BDK_i_max(cm0, resolution->cm0);
	cm1 = BDK_i_min(cm1, resolution->cm1);

	cl0 = cn0 - resolution->cn0;
	cl1 = cn1 - resolution->cn0;

	ck0 = cm0 - resolution->cm0;
	ck1 = cm1 - resolution->cm0;
	
	set_TagTree();
}


void BDK::Precinct::decode_packet(int l_layer, ByteBuffer* bytebuffer)
{

	int nr_subbands;	
	unsigned char bit;

	if(resolution->r != 0){
		nr_subbands = 3;
	}else{
		nr_subbands = 1;
	}

	bit = bytebuffer->get_next_bit(true);
	if(bit != 0){
		for(int i = 0; i < nr_subbands; i++){
			decode_packet(l_layer, bytebuffer, tagtree_Codeblock_inclusion[i], tagtree_Zero_pitplane_inforamtion[i], resolution->subband[i]);
		}
		bytebuffer->go_next_byte_without_padding();
		for(int i = 0; i < nr_subbands; i++){
			read_packet(bytebuffer, resolution->subband[i]);
		}
	}else{
		for(int i = 0; i < nr_subbands; i++){
			set_all_number_of_coding_passes(0, resolution->subband[i]);
		}
	}
}

void BDK::Precinct::decode_codeword(int l_layer)
{
	int nr_subbands;	
	Subband* subband;
	int nr_codeblocks_x = cl1 - cl0;
	Codeblock* codeblock;
	int nr_package;

	if(resolution->r != 0){
		nr_subbands = 3;
	}else{
		nr_subbands = 1;
	}

	for(int i = 0; i < nr_subbands; i++){
		subband = resolution->subband[i];	

		for(int k = ck0; k < ck1; k++){
			nr_package = nr_codeblocks_x * k;
			for( int l = cl0; l < cl1; l++){
				codeblock = subband->codeblocks[nr_package + l];
				codeblock->decode_codeword(l_layer);
			}
		}
	}
}

void BDK::Precinct::decode_codeword()
{
	int nr_subbands;	
	Subband* subband;
	int nr_codeblocks_x = cl1 - cl0;
	Codeblock* codeblock;
	int nr_package;

	if(resolution->r != 0){
		nr_subbands = 3;
	}else{
		nr_subbands = 1;
	}

	for(int i = 0; i < nr_subbands; i++){
		subband = resolution->subband[i];	

		for(int k = ck0; k < ck1; k++){
			nr_package = nr_codeblocks_x * k;
			for( int l = cl0; l < cl1; l++){
				codeblock = subband->codeblocks[nr_package + l];
				codeblock->decode_codeword();
			}
		}
	}
}

void BDK::Precinct::set_all_number_of_coding_passes(int i,  Subband* subband)
{
	int nr_codeblocks_x = cl1 - cl0;
	Codeblock* codeblock;
	int nr_package;

	for(int k = ck0; k < ck1; k++){
		nr_package = nr_codeblocks_x * k;
		for( int l = cl0; l < cl1; l++){
			codeblock = subband->codeblocks[nr_package + l];
			codeblock->set_number_of_coding_passes(i);
		}
	}
}


void BDK::Precinct::decode_packet(int l_layer, ByteBuffer* bytebuffer, TagTree* tagtree_Codeblock_inclusion, TagTree* tagtree_Zero_pitplane_inforamtion, Subband* subband)
{
	int nr_codeblocks_x = cl1 - cl0;
	int nr_codeblocks_y = ck1 - ck0;
	int nr_package, x, y;
	Codeblock* codeblock;
	unsigned char bit;
	bool codeblock_include, codeblock_include_firsttime;
	int nr_codeword_segments;
	
	int count = 0;

	for(int k = ck0; k < ck1; k++){
		nr_package = nr_codeblocks_x * k;
		for( int l = cl0; l < cl1; l++){
			codeblock = subband->codeblocks[nr_package + l];
			codeblock->create_Layer(l_layer);
			codeblock_include = false;
			codeblock_include_firsttime = false;
			if(codeblock->codeblock_include == true){
				bit = bytebuffer->get_next_bit(true);
				if(bit != 0){
					codeblock_include = true;
				}
			}else{
				y = k - ck0;
				x = l - cl0;
				if(tagtree_Codeblock_inclusion->decodeValue(bytebuffer,l_layer, x, y) ){
					codeblock->codeblock_include = true;
					codeblock_include = true;
					codeblock_include_firsttime = true;
					codeblock->Codeblock_inclusion = tagtree_Codeblock_inclusion->getValue(x, y);
				}
			}

			if(codeblock_include){
				codeblock->codeblock_include_segments = true;
				if(codeblock_include_firsttime){
					if(!tagtree_Zero_pitplane_inforamtion->decodeValue(bytebuffer,4000,x, y)){
						throw new Default_Exceptionhandler(__FILE__, __LINE__,"unexpected end of tagtree");
					}
					codeblock->set_Zero_bitplane_information(tagtree_Zero_pitplane_inforamtion->getValue(x, y));
				}					
				codeblock->set_number_of_coding_passes(decode_number_of_coding_passes(bytebuffer));
				nr_codeword_segments = codeblock->get_number_of_codeword_segments();
				codeblock->set_Lblock(bytebuffer);
				for(int i = 0; i < nr_codeword_segments; i++){
					codeblock->set_codeword_segment_length(i, bytebuffer);
					//count = codeblock->codeword_segment_length[0];
				}

			}else{
				codeblock->codeblock_include_segments = false;
				codeblock->set_number_of_coding_passes(0);
			}
		}
	}
	
	// bytebuffer->go_next_byte_without_padding();
}



void BDK::Precinct::set_TagTree()
{
	int nr_codeblocks_x = cl1 - cl0;
	int nr_codeblocks_y = ck1 - ck0;
	int nr_subbands;	
	

	if(resolution->r != 0){
		nr_subbands = 3;
	}else{
		nr_subbands = 1;
	}

	for(int i = 0; i < nr_subbands; i++){
		tagtree_Codeblock_inclusion.push_back(new TagTree(nr_codeblocks_x, nr_codeblocks_y));
		tagtree_Zero_pitplane_inforamtion.push_back(new TagTree(nr_codeblocks_x, nr_codeblocks_y));
	}
}


int  BDK::Precinct::decode_number_of_coding_passes(ByteBuffer* bytebuffer)
{
	int back = 0;
	unsigned char bit = bytebuffer->get_next_bit(true);
	unsigned int value = 0;

	if(bit == 0){
		back = 1;
	}else{
		bit = bytebuffer->get_next_bit(true);
		if(bit == 0){
			back = 2;
		}else{
			value = bytebuffer->readbit(2, value, true);
			if(value == 3){
				value = bytebuffer->readbit(5, 0, true);
				if(value == 31){
					value = bytebuffer->readbit(7, 0, true);
					back = value + 37;
				}else{
					back = value + 6;
				}

			}else{
				back = value + 3;
			}
		}

	}
	return back;
}

void BDK::Precinct::read_packet(ByteBuffer* bytebuffer, Subband* subband)
{
	int nr_codeblocks_x = cl1 - cl0;
	int nr_codeblocks_y = ck1 - ck0;
	int nr_package;
	Codeblock *codeblock;

	for(int k = ck0; k < ck1; k++){
		nr_package = nr_codeblocks_x * k;
		for( int l = cl0; l < cl1; l++){
			codeblock = subband->codeblocks[nr_package + l];
			codeblock->set_codeword_segment_data(bytebuffer);
		}
	}
}

