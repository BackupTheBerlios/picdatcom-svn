// SPcoc.h
//
// This header file defines the interfaces to the class SPcoc
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

#ifndef __SPCOC_H__
#define __SPCOC_H__

namespace BDK
{
	class SPcoc;
}

#include "Parameter.h"
#include "Coding_style_component_COC.h"
#include "Default_Exceptionhandler.h"
#include "Precinct_size.h"
#include <vector>
using namespace std;

namespace BDK
{
	class SPcoc{
	public:
	  SPcoc(const unsigned char* information, Coding_style_component_COC *coc);
	public:
	  virtual ~SPcoc();
	public:
	  unsigned char number_of_decomposition_level;// Number of decomposition levels NL, Zero implies nor transformation

	  unsigned char codeblock_width_value_xcb;// value = xcb - 2

	  unsigned char codeblock_width_value_ycb;// value = ycb - 2

	  bool use_selective_arithmetic_coding_bypass;
	  bool use_reset_of_context_probabilities_on_coding_pass;
	  bool use_termination_on_each_coding_pass;
	  bool use_vertical_causal_context;
	  bool use_predictiable_termination;
	  bool use_segmentation_symbols;
	  BDK_Multiple_component_transformation_type transformation;// NineSeven_irreverible_filter FiveThree_reversible_filter

	  vector<Precinct_size *> precinct_size;


	};
}
#endif // defined __SPCOC_H__
