// Tile.cpp
//
// This header file defines the implementation of the class Tile
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
#include "Tile.h"


BDK::Tile::~Tile()
{
}

//  Operation: Tile
//
//  Description:
//   
//  Parameters:
//

BDK::Tile::Tile()
{
}

//  Operation: Tile
//
//  Description:
//   
//  Parameters:
//      entry_point	
//      t_tileindex	See page 45
//

BDK::Tile::Tile(BDK_entry_point* entry_point, unsigned int t_tileindex)
{
	unsigned int nrComponents = entry_point->ptr_SIZ_part_one->Csiz;

	this->entry_point = entry_point;
	unsigned int p, q;
	unsigned int numXtiles	= entry_point->numXtiles;
	unsigned int numYtiles	= entry_point->numYtiles;
	unsigned int XTOsiz		= entry_point->ptr_SIZ_part_one->XTOsiz;
	unsigned int XTsiz		= entry_point->ptr_SIZ_part_one->XTsiz;
	unsigned int XOsiz		= entry_point->ptr_SIZ_part_one->XOsiz;
	unsigned int YTOsiz		= entry_point->ptr_SIZ_part_one->YTOsiz;
	unsigned int YTsiz		= entry_point->ptr_SIZ_part_one->YTsiz;
	unsigned int YOsiz		= entry_point->ptr_SIZ_part_one->YOsiz;
	unsigned int Xsiz		= entry_point->ptr_SIZ_part_one->Xsiz;
	unsigned int Ysiz		= entry_point->ptr_SIZ_part_one->Ysiz;

	p = t_tileindex % numXtiles;
	q = (unsigned int)ceil((double)t_tileindex / (double)numXtiles);
	
	this->tx0 = BDK_ui_max(XTOsiz + p * XTsiz, XOsiz);
	this->ty0 = BDK_ui_max(YTOsiz + q * YTsiz, YOsiz);
	this->tx1 = BDK_ui_min(XTOsiz + (p + 1) * XTsiz, Xsiz);
	this->ty1 = BDK_ui_min(YTOsiz + (q + 1) * YTsiz, Ysiz);
	ptr_COD = NULL;
	COD_read = false;

	for(unsigned int i = 0; i < nrComponents; i++)
	{
		components.push_back(new Component(this, entry_point->ptr_SIZ_part_one->siz_part_two[i]));
	}

}

//  Operation: set_Tilepart
//
//  Description:
//   
//  Parameters:
//      length	
//      in	
//

void BDK::Tile::set_Tilepart(const unsigned short length, unsigned char* in)
{
	firstsetCodestream = true;
	Tilepart* tilepart = new Tilepart();
	tilepart->set_Start_of_tile_part_SOT(length, in);

	tileparts.push_back(tilepart);


}


void BDK::Tile::set_Codestream(const unsigned short length, unsigned char* in, ByteBuffer* bytebuffer)
{
	Tilepart* tilepart;
	tilepart = tileparts.back();

	if(firstsetCodestream == true){
		firstsetCodestream = false;
		for(unsigned int i = 0; i < this->components.size(); i++){
			this->components[i]->set_Resolution();
		}
	}

	int i = 0;
	if(ptr_COD->progression_order == layer_resolution_level_component_position){
		i = 1;
	}else if(ptr_COD->progression_order == resolution_level_layer_component_position){
		start_decode_resolution_level_layer_component_position(length, in, bytebuffer);
	}else if(ptr_COD->progression_order == resolution_level_position_component_layer){
		i = 3;
	}else if(ptr_COD->progression_order == position_component_resolution_level_layer){
		i = 4;
	}else if(ptr_COD->progression_order == component_position_resolution_level_layer){
		i = 5;
	}else{
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Unknow progression_order" );
	}

}


void BDK::Tile::start_decode_resolution_level_layer_component_position(const unsigned short length, unsigned char* in, ByteBuffer* bytebuffer)
{
	Tilepart* tilepart;
	tilepart = tileparts.back();
	


	int r, Nmax;
	int l, L;
	int i, Csiz;
	int k, numprecincts;

	Nmax			= ptr_COD->spcoc->number_of_decomposition_level;
	L				= ptr_COD->number_of_Layer;
	Csiz			= (int) entry_point->ptr_SIZ_part_one->Csiz ;
	numprecincts	= 0;
	k				= 0;

	for(r = 0; r <= Nmax; r++){
		for(l = 0; l < L; l++){
			for(i = 0; i < Csiz; i++){
				numprecincts = get_Numprecincts(r, i);
				for(k = 0; k < numprecincts; k++){
					components[i]->decode_packet(r, l, k, bytebuffer);
				}
			}
		}
	}

	/*
	for(r = 0; r <= Nmax; r++){
		for(l = 0; l < L; l++){
			for(i = 0; i < Csiz; i++){
				numprecincts = get_Numprecincts(r, i);
				for(k = 0; k < numprecincts; k++){
					components[i]->decode_codeword(r, l, k);
				}
			}
		}
	}
	*/

	
	for(i = 0; i < Csiz; i++){
		for(r = 0; r <= Nmax; r++){
			numprecincts = get_Numprecincts(r, i);
			for(k = 0; k < numprecincts; k++){
				components[i]->decode_codeword(r, k);
			}
		}
	}
	r++;
}

void BDK::Tile::set_COD(Coding_style_default_COD* ptr_COD)
{
	size_t nr_component = this->components.size();
	this->ptr_COD = ptr_COD;
	for(size_t i = 0; i < nr_component; i++){
		components[i]->set_COD(ptr_COD);
	}
}

void BDK::Tile::set_QCD(Quantization_default_QCD* ptr_QCD)
{
	size_t nr_component = this->components.size();
	this->ptr_QCD = ptr_QCD;
	for(size_t i = 0; i < nr_component; i++){
		components[i]->set_QCD(ptr_QCD);
	}
}

int	 BDK::Tile::get_Numprecincts(int r, int i)
{
	int back = 0;

	back = components[i]->get_Numprecincts(r);

	return back;
}

void BDK::Tile::decode_packet(int i_componete, int r_resolution, int l_layer, int k_precinct, ByteBuffer* bytebuffer)
{
	components[i_componete]->decode_packet(r_resolution, l_layer,k_precinct,bytebuffer);
}

void BDK::Tile::inverse_quantization_irreversible()
{
	size_t num_tiles	= this->components.size();
	for(size_t i = 0; i < num_tiles; i++){
		this->components[i]->inverse_quantization_irreversible();
	}

}

void BDK::Tile::start_Filter97_decoder()
{
	size_t num_tiles	= this->components.size();
	for(size_t i = 0; i < num_tiles; i++){
		this->components[i]->start_Filter97_decoder();
	}

}

void BDK::Tile::fill_RGBbuffer(unsigned char* buffer)
{
	size_t num_tiles	= this->components.size();
	if(num_tiles == 3){
		/*
		this->components[0]->data->fill_RGBbuffer_Y(buffer);
		this->components[1]->data->fill_RGBbuffer_Cb(buffer);
		this->components[2]->data->fill_RGBbuffer_Cr(buffer);
		*/
		Data::fill_RGBbuffer(	this->components[0]->data, 
								this->components[1]->data,
								this->components[2]->data,
								buffer);
	}

}
