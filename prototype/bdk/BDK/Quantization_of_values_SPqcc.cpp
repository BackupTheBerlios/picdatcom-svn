// Quantization_of_values_SPqcc.cpp
//
// This header file defines the implementation of the class Quantization_of_values_SPqcc
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
// Quantization values for the SPqcc
//
#include "Quantization_of_values_SPqcc.h"


BDK::Quantization_of_values_SPqcc::Quantization_of_values_SPqcc()
{
}
BDK::Quantization_of_values_SPqcc::~Quantization_of_values_SPqcc()
{
}

//  Operation: Quantization_of_values_SPgcc
//
//  Description:
//   
//  Parameters:
//      in	
//

BDK::Quantization_of_values_SPqcc::Quantization_of_values_SPqcc(const unsigned char in)
{
	this->exponent = (in & MASK_EXPONENT2) >> 3;
	this->mantissa = 0;
}

//  Operation: Quantization_of_values_SPgcc
//
//  Description:
//   
//  Parameters:
//      unsigned short	
//

BDK::Quantization_of_values_SPqcc::Quantization_of_values_SPqcc(const unsigned short in)
{
	this->exponent = (in & MASK_EXPONENT) >> 11;
	this->mantissa = (in & MASK_MANTISSA);
}


BDK::Quantization_of_values_SPqcc::Quantization_of_values_SPqcc(int NL, int nb, Quantization_of_values_SPqcc* in )
{
	this->exponent = in->exponent - NL + nb;
	this->mantissa = in->mantissa;
}
