// Resolution.cpp
//
// This header file defines the implementation of the class Resolution
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
#include "Resolution.h"



BDK::Resolution::~Resolution()
{
}

//  Operation: Resolution
//
//  Description:
//   
//  Parameters:
//      resolution	
//

BDK::Resolution::Resolution(Resolution* resolution)
{
	this->component = resolution->component;
	this->r			= resolution->r - 1;
	init();
	if(this->r != 0){
		this->lower = resolution;
		this->top	= new Resolution(this);
	}else{
		this->lower = resolution;
		this->top	= NULL;
	}
}

//  Operation: Resolution
//
//  Description:
//   
//  Parameters:
//      component	
//

BDK::Resolution::Resolution(Component* component)
{
	this->component	= component;
	this->r			= component->ptr_COD->spcoc->number_of_decomposition_level;
	init();

	if(this->r != 0){
		this->lower = NULL;
		this->top	= new Resolution(this);
	}else{
		this->lower = NULL;
		this->top	= NULL;
	}
}

void BDK::Resolution::init()

{
	int twohigh;
	int NL		= component->ptr_COD->spcoc->number_of_decomposition_level;
	int		codeblock_x, codeblock_y;
	bool	even = true;
	
	unsigned int offsetX, offsetY;

	xcb		= component->ptr_COD->spcoc->codeblock_width_value_xcb;
	ycb		= component->ptr_COD->spcoc->codeblock_width_value_ycb;	

	twohigh = 1 << (NL - r);
	this->trx0 = BDK_i_ceiling(component->tcx0, twohigh);
	this->trx1 = BDK_i_ceiling(component->tcx1, twohigh);
	this->try0 = BDK_i_ceiling(component->tcy0, twohigh);
	this->try1 = BDK_i_ceiling(component->tcy1, twohigh);

	if(r == 0){
		n = NL - r;
		this->precinct_size = component->ptr_COD->spcoc->precinct_size[n - 1];	
	}else{
		n = NL - r + 1;
		this->precinct_size = component->ptr_COD->spcoc->precinct_size[n - 1];
	}

	this->tpn0 = BDK_i_floor(this->trx0 , (1 << precinct_size->PPx));
	this->tpn1 = BDK_i_ceiling(this->trx1  , (1 << precinct_size->PPx));
	this->tpm0 = BDK_i_floor(this->try0 , (1 << precinct_size->PPy));
	this->tpm1 = BDK_i_ceiling(this->try1 , (1 << precinct_size->PPy));

	xcb = BDK_i_min(xcb, precinct_size->PPx - 1);
	ycb = BDK_i_min(ycb, precinct_size->PPy - 1);

	codeblock_x = 1 << (xcb + 1);
	codeblock_y = 1 << (ycb + 1);

	this->cn0 = BDK_i_floor(trx0, codeblock_x);
	this->cn1 = BDK_i_ceiling(trx1, codeblock_x);
	this->cm0 = BDK_i_floor(try0, codeblock_y);
	this->cm1 = BDK_i_ceiling(try1, codeblock_y);
	
	if(r == 0){
		subband.push_back(new Subband(this,0,0, SUBBAND_LL));  // Subband LL
		subband[0]->initData(component->data, 0, 0);
		subband[0]->set_QCD();
		data = NULL;
	}else{
		subband.push_back(new Subband(this,1,0, SUBBAND_HL));  // Subband HL
		subband.push_back(new Subband(this,0,1, SUBBAND_LH));  // Subband LH
		subband.push_back(new Subband(this,1,1, SUBBAND_HH));  // Subband HH

		offsetX = subband[1]->tbx1 - subband[1]->tbx0;
		offsetY = subband[0]->tby1 - subband[0]->tby0;

		subband[0]->initData(component->data, offsetX, 0);
		subband[1]->initData(component->data, 0, offsetY);
		subband[2]->initData(component->data, offsetX, offsetY);

		subband[0]->set_QCD();
		subband[1]->set_QCD();
		subband[2]->set_QCD();

		data = new Data(component->data,	component->data->work_x0, component->data->work_x0 + trx1 - trx0,
											component->data->work_y0, component->data->work_y0 + try1 - try0);
		data->set_even(trx0, try0);
	}
	
	for(int m = tpm0; m < tpm1; m++ ){
		for(int n = tpn0; n < tpn1; n++){
			precinct.push_back(new Precinct(this,n,m));
		}
	}
	numberprecinct = (int)precinct.size();

}

int BDK::Resolution::get_Numprecincts(int r)
{
	int back = 0;

	if(this->r == r){
		back = this->numberprecinct;
	}else{
		back = this->top->get_Numprecincts(r);
	}
	return back;
}

void BDK::Resolution::decode_packet(int r_resolution, int l_layer, int k_precinct, ByteBuffer* bytebuffer)
{
	if(this->r == r_resolution){
		precinct[k_precinct]->decode_packet(l_layer, bytebuffer);

	}else if(this->r > 0){
		this->top->decode_packet(r_resolution, l_layer, k_precinct, bytebuffer);
	}else{
		throw new Default_Exceptionhandler(__FILE__, __LINE__, "Unexpected resolution");
	}

}


void BDK::Resolution::decode_codeword(int r_resolution, int l_layer, int k_precinct)
{
	if(this->r == r_resolution){
		precinct[k_precinct]->decode_codeword(l_layer);

	}else if(this->r > 0){
		this->top->decode_codeword(r_resolution, l_layer, k_precinct);
	}else{
		throw new Default_Exceptionhandler(__FILE__, __LINE__, "Unexpected resolution");
	}
}

void BDK::Resolution::decode_codeword(int r_resolution, int k_precinct)
{
	if(this->r == r_resolution){
		precinct[k_precinct]->decode_codeword();

	}else if(this->r > 0){
		this->top->decode_codeword(r_resolution, k_precinct);
	}else{
		throw new Default_Exceptionhandler(__FILE__, __LINE__, "Unexpected resolution");
	}
}

void BDK::Resolution::set_QCD()
{
	
	if(r == 0){
		subband[0]->set_QCD();
	}else{
		top->set_QCD();
		subband[0]->set_QCD();
		subband[1]->set_QCD();
		subband[2]->set_QCD();
		
	}
}

void BDK::Resolution::inverse_quantization_irreversible()
{
	if(r == 0){
		subband[0]->inverse_quantization_irreversible();
	}else{
		top->inverse_quantization_irreversible();
		subband[0]->inverse_quantization_irreversible();
		subband[1]->inverse_quantization_irreversible();
		subband[2]->inverse_quantization_irreversible();
	}
}


void BDK::Resolution::start_Filter97_decoder(Filter97_decoder *decoder)
{
	if(r == 0){
		
	}else{
		top->start_Filter97_decoder(decoder);
		data->filter_decode(decoder);
	}
}