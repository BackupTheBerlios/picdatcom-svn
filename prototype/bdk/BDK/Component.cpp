// Component.cpp
//
// This header file defines the implementation of the class Component
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
#include "Component.h"


BDK::Component::~Component()
{
}

//  Operation: Component
//
//  Description:
//   
//  Parameters:
//      tile	
//      siz	
//

BDK::Component::Component(const Tile* tile, SIZ_part_two* siz)
{
	int XRsiz = siz->XRsiz;
	int YRsiz = siz->YRsiz;
	unsigned int sizeX, sizeY;

	ptr_SIZ_part_two = siz;

	tcx0 = BDK_i_ceiling(tile->tx0, XRsiz);
	tcx1 = BDK_i_ceiling(tile->tx1, XRsiz);
	tcy0 = BDK_i_ceiling(tile->ty0, YRsiz);
	tcy1 = BDK_i_ceiling(tile->ty1, YRsiz);

	sizeX = tcx1 - tcx0;
	sizeY = tcy1 - tcy0;

	data = new Data(sizeX, sizeY);
}


void BDK::Component::set_COD(Coding_style_default_COD* ptr_COD)
{
	this->ptr_COD = ptr_COD;
}

void BDK::Component::set_QCD(Quantization_default_QCD* ptr_QCD)
{
	this->ptr_QCD = ptr_QCD;
	if(resolution != NULL){
		
	}
}

void BDK::Component::set_Resolution()
{
	this->resolution = new Resolution(this);
}

int BDK::Component::get_Numprecincts(int r)
{
	int back = 0;
	if(resolution->r < r){
		throw new Default_Exceptionhandler(__FILE__, __LINE__, "Unexpected resolution");
	}else{
		back = resolution->get_Numprecincts(r);
	}
	return back;
}

void BDK::Component::decode_packet(int r_resolution, int l_layer, int k_precinct, ByteBuffer* bytebuffer)
{
	resolution->decode_packet(r_resolution, l_layer, k_precinct, bytebuffer);
}

void BDK::Component::decode_codeword(int r_resolution, int l_layer, int k_precinct)
{
	resolution->decode_codeword(r_resolution, l_layer, k_precinct);

}

void BDK::Component::decode_codeword(int r_resolution, int k_precinct)
{
	resolution->decode_codeword(r_resolution, k_precinct);
}


void BDK::Component::inverse_quantization_irreversible()
{
	resolution->inverse_quantization_irreversible();
}

void BDK::Component::start_Filter97_decoder()
{
	int size1 = tcx1 - tcx0;
	int size2 = tcy1 - tcy0;

	if(size1 < size2){
		size1 = size2;
	}
	Filter97_decoder *decoder = new Filter97_decoder(size1);
	resolution->start_Filter97_decoder(decoder);
	decoder->~Filter97_decoder();
}