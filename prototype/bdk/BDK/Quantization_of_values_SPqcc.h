// Quantization_of_values_SPqcc.h
//
// This header file defines the interfaces to the class Quantization_of_values_SPqcc
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

#ifndef __QUANTIZATION_OF_VALUES_SPQCC_H__
#define __QUANTIZATION_OF_VALUES_SPQCC_H__


// Quantization values for the SPqcc


#define MASK_MANTISSA  0x07Ff
#define MASK_EXPONENT  0xF800
#define MASK_EXPONENT2 0xF8

namespace BDK
{
	class Quantization_of_values_SPqcc{
	private:
	public:
	   Quantization_of_values_SPqcc();
	   Quantization_of_values_SPqcc(const unsigned char in);
	   Quantization_of_values_SPqcc(const unsigned short in);
	   Quantization_of_values_SPqcc(int NL, int nb, Quantization_of_values_SPqcc* in );
	public:
	  virtual ~Quantization_of_values_SPqcc();
	public:
	  unsigned int mantissa;
	  unsigned int exponent;

	public:


	};
}
#endif // defined __QUANTIZATION_OF_VALUES_SPQCC_H__
