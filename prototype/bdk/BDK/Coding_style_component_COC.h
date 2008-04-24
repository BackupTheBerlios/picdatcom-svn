// Coding_style_component_COC.h
//
// This header file defines the interfaces to the class Coding_style_component_COC
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

#ifndef __CODING_STYLE_COMPONENT_COC_H__
#define __CODING_STYLE_COMPONENT_COC_H__

namespace BDK
{
	class Coding_style_component_COC;
}

#include "SPcoc.h"
#include "Precinct_size.h"
#include "Parameter.h"
#include "SPcoc.h"
#include <vector>
using namespace std;

namespace BDK
{
	class Coding_style_component_COC{
	private:
	public:
	  virtual ~Coding_style_component_COC();
	public:
	  SPcoc* spcoc;

	  unsigned short Lcox;// Length of marker segment in bytes. Either Lcod or Lcoc

	  unsigned short Ccoc;// The index of the component to which this marker this segment relates.

	  bool use_default_PPx_PPy;// PPx = PPy = 15

	  BDK_use_in use_in;// Either use in main header or tile-part header.

	  
	public:
	   Coding_style_component_COC(const unsigned char* in, const unsigned short length, const BDK_use_in use_in);
	   Coding_style_component_COC();
	};
}
#endif // defined __CODING_STYLE_COMPONENT_COC_H__
