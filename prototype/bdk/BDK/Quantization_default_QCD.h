// Quantization_default_QCD.h
//
// This header file defines the interfaces to the class Quantization_default_QCD
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

#ifndef __QUANTIZATION_DEFAULT_QCD_H__
#define __QUANTIZATION_DEFAULT_QCD_H__

namespace BDK
{
	class  Quantization_default_QCD;
}

#include "Quantization_of_values_SPqcc.h"
#include "Coding_style_component_COC.h"
#include "Parameter.h"
#include "Default_Exceptionhandler.h"
#include <vector>
using namespace std;

namespace BDK
{
	class Quantization_default_QCD{
	private:
	public:
	  Quantization_default_QCD();
	  virtual ~Quantization_default_QCD();
	public:
	  unsigned short Lqcd;
	  BDK_use_in use_in;// Use in Tile-part or Main Header.

	  BDK_Quantization_style quantization_style;// Either scalar derived or scalar expounded.

	  unsigned char number_of_guardbits;

	  vector<Quantization_of_values_SPqcc *> quantization_of_values_SPqcc;

	public:
	   Quantization_default_QCD(const unsigned char* input, const unsigned short length, const Coding_style_component_COC* coc);

	};
}
#endif // defined __QUANTIZATION_DEFAULT_QCD_H__
