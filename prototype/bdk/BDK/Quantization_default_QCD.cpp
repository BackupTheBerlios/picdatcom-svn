// Quantization_default_QCD.cpp
//
// This header file defines the implementation of the class Quantization_default_QCD
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
#include "Quantization_default_QCD.h"




BDK::Quantization_default_QCD::Quantization_default_QCD()
{
}


BDK::Quantization_default_QCD::~Quantization_default_QCD()
{
}

//  Operation: Quantization_default_QCD
//
//  Description:
//   
//  Parameters:
//      input	
//      length	
//      coc	
//

BDK::Quantization_default_QCD::Quantization_default_QCD(const unsigned char* input, const unsigned short length, const Coding_style_component_COC* coc)
{
	int	number_of_decomposition_level = coc->spcoc->number_of_decomposition_level;
	unsigned char temp;
	int number_of_subband = number_of_decomposition_level * 3 + 1;
	int subband, nb;
	int subband_end;
	this->Lqcd	= length;

	this->number_of_guardbits = input[0] >> 5;

	temp = input[0] & 0x1F;
	if(temp == SCALAR_EXPOUNDED){
		if(this->Lqcd == (5 + 6 * number_of_decomposition_level)){
			this->quantization_style = scalar_expounded;
			subband_end = number_of_subband * 2;
			for(subband = 0; subband < subband_end; subband+=2){
				quantization_of_values_SPqcc.push_back(new Quantization_of_values_SPqcc(bytetoshort(&input[1], subband)  ));
			}
		}else{
			throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Lqcd is not correct." );
		}
	}else if(temp == SCALAR_DERIVED){
		if(this->Lqcd == 5){
			this->quantization_style = scalar_derived;
			quantization_of_values_SPqcc.push_back(new Quantization_of_values_SPqcc(bytetoshort(&input[1], 0)  ));
			for(nb = number_of_decomposition_level; nb >= 1; nb--){
				quantization_of_values_SPqcc.push_back(new Quantization_of_values_SPqcc(number_of_decomposition_level, nb, quantization_of_values_SPqcc[0]) );
				quantization_of_values_SPqcc.push_back(new Quantization_of_values_SPqcc(number_of_decomposition_level, nb, quantization_of_values_SPqcc[0]) );
				quantization_of_values_SPqcc.push_back(new Quantization_of_values_SPqcc(number_of_decomposition_level, nb, quantization_of_values_SPqcc[0]) );
			}
		}else{
			throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Lqcd is not correct." );
		}
	}else if(temp == NO_QUANTIZATION){
		if(this->Lqcd == (5 + 3 * number_of_decomposition_level)){
			this->quantization_style = no_quantization;
			subband_end = number_of_subband;
			for(subband = 0; subband < number_of_subband; subband+=2){
				quantization_of_values_SPqcc.push_back(new Quantization_of_values_SPqcc(input[1 + subband]));
			}
		}else{
			throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Lqcd is not correct." );
		}
	}else{
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Unknow Quantization style" );
	}
}
