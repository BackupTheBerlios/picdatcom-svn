// BDK_entry_point.h
//
// This header file defines the interfaces to the class BDK_entry_point
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

#ifndef __BDK_ENTRY_POINT_H__
#define __BDK_ENTRY_POINT_H__

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

namespace BDK
{
	class BDK_entry_point;
}
#include "SIZ_part_one.h"
#include "Coding_style_default_COD.h"
#include "Quantization_default_QCD.h"
#include "Comment.h"
#include "Tile.h"
//#include "Tile.h"

namespace BDK
{

	class BDK_entry_point{
	public:
		unsigned int numXtiles;
		unsigned int numYtiles;

		SIZ_part_one				*ptr_SIZ_part_one;
		Coding_style_default_COD	*ptr_COD;
		Quantization_default_QCD	*ptr_QCD;
		Comment						*ptr_COM;
		vector<Tile*>				tiles;

	public:
		BDK_entry_point();

	public:
		virtual ~BDK_entry_point();

	};
}
#endif // defined __BDK_ENTRY_POINT_H__
