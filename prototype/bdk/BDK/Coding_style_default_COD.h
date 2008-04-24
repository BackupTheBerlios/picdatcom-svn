// Coding_style_default_COD.h
//
// This header file defines the interfaces to the class Coding_style_default_COD
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

#ifndef __CODING_STYLE_DEFAULT_COD_H__
#define __CODING_STYLE_DEFAULT_COD_H__


#include "Coding_style_component_COC.h"

namespace BDK
{
	class Coding_style_default_COD: public Coding_style_component_COC{
	public:
	  Coding_style_default_COD(const unsigned char* informaition, const unsigned short length, BDK_use_in use_in);
	  virtual ~Coding_style_default_COD();
	public:
	  bool use_SOP;
	  bool use_EPH;
	  BDK_Progression_order progression_order;// Either Layer-resolution level-component-position progression, Resolution level-layer-component-position progression, Resolution level-position-component-layer, Position-componetn-resolution level-layer progression or Component-position-resolution level-layer progression.

	  unsigned short number_of_Layer;
	  bool multiple_component_transformation;// Either no multiple component transformation specified or Component transformation used on component 0, 1, 2.

	public:
	};
}
#endif // defined __CODING_STYLE_DEFAULT_COD_H__
