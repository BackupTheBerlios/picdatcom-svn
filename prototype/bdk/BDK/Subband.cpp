// Subband.cpp
//
// This header file defines the implementation of the class Subband
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
#include "Subband.h"


BDK::Subband::~Subband()
{
}

//  Operation: Subband
//
//  Description:
//   
//  Parameters:
//      resolution	
//      x0b	
//      y0b	
//

BDK::Subband::Subband(Resolution* resolution, int x0b, int y0b, Subbandtype subbandtype)
{
	int		twohigh = 1 << resolution->n;
	int		codeblock_x, codeblock_y;

	this->resolution	= resolution;
	this->subbandtype	= subbandtype;

	xcb		= resolution->component->ptr_COD->spcoc->codeblock_width_value_xcb;
	ycb		= resolution->component->ptr_COD->spcoc->codeblock_width_value_ycb;	

	xcb = BDK_i_min(xcb, resolution->precinct_size->PPx - 1);
	ycb = BDK_i_min(ycb, resolution->precinct_size->PPy - 1);

	tbx0 = calc(resolution->component->tcx0,twohigh, x0b);
	tbx1 = calc(resolution->component->tcx1,twohigh, x0b);
	tby0 = calc(resolution->component->tcy0,twohigh, y0b);
	tby1 = calc(resolution->component->tcy1,twohigh, y0b);

	codeblock_x = 1 << xcb;
	codeblock_y = 1 << ycb;

	this->cn0 = BDK_i_floor(tbx0, codeblock_x);
	this->cn1 = BDK_i_ceiling(tbx1, codeblock_x);
	this->cm0 = BDK_i_floor(tby0, codeblock_y);
	this->cm1 = BDK_i_ceiling(tby1, codeblock_y);
	
	size_u	= resolution->cn1 - resolution->cn0;
	size_v	= resolution->cm1 - resolution->cm0;

	for(int m = resolution->cm0; m < resolution->cm1; m++){
		for(int n = resolution->cn0; n < resolution->cn1; n++){
			
			if(m < cm0 || m >= cm1 || n < cn0 || n >= cn1){
				codeblocks.push_back(new Codeblock(this, n, m, true) );
			}else{
				codeblocks.push_back(new Codeblock(this, n, m, false) );
			}
		}
	}
	data = NULL;
}

int BDK::Subband::calc(int tc_in, int high_in, int x_in)
{
	double tc	= (double)tc_in;
	double high	= (double)high_in;
	double back;
	
	if(x_in == 1){
		back = ceil( (tc / high)- 0.5 );
	}else{
		back = ceil( (tc / high));
	}
	return (int)back;
}

void BDK::Subband::initData(Data *in_data, unsigned int offsetX, unsigned int offsetY)
{
	unsigned int sizeX, sizeY;
	int iWork, iWork_max, offX, offY;
	sizeX = tbx1 - tbx0;
	sizeY = tby1 - tby0;

	data = new Data(in_data, offsetX, offsetX + sizeX, offsetY, offsetY + sizeY);
	
	offX = (int)offsetX - tbx0;
	offY = (int)offsetY - tby0;

	iWork_max = (int)codeblocks.size();
	for(iWork = 0; iWork < iWork_max; iWork ++){
		codeblocks[iWork]->initData(data, offX, offY);
	}

}


void BDK::Subband::set_QCD()
{
	int point = 0;
	Quantization_of_values_SPqcc *ptr_SPqcc;
	if(this->resolution->r == 0){
		point = 0;
	}else{
		point = this->resolution->r * 3 - 2;
		if(subbandtype ==  SUBBAND_LH){
			point += 1;
		}else if( subbandtype ==  SUBBAND_HH){
			point += 2;
		}
	}
	ptr_SPqcc = this->resolution->component->ptr_QCD->quantization_of_values_SPqcc[point];
	M = ptr_SPqcc->exponent + resolution->component->ptr_QCD->number_of_guardbits - 1;	
	spqcc = ptr_SPqcc;

}

void BDK::Subband::customint_to_float()
{
	float deltab = 0.0;
	int Rb = (this->resolution->component->ptr_SIZ_part_two->Ssiz & 0x7F) + 1;
	int eb = this->spqcc->exponent;
	float yb = (float)this->spqcc->mantissa;


	switch(this->subbandtype){
		case SUBBAND_HH:
			Rb += 2;
			break;
		case SUBBAND_HL:
			Rb += 1;
			break;
		case SUBBAND_LH:
			Rb += 1;
			break;
		case SUBBAND_LL:
			break;
	}
	deltab = ((float)(1<<Rb))/((float)(1<<eb));
	deltab = deltab * ( 1 + yb/((float)(1<<11)));
	data->customint_to_float(deltab);
}

void	BDK::Subband::inverse_quantization_irreversible()
{
	customint_to_float();
}