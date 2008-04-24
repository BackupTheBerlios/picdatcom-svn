// Tilepart.h
//
// This header file defines the interfaces to the class Tilepart
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

#ifndef __TILEPART_H__
#define __TILEPART_H__

#include <vector>
#include "Start_of_tile_part_SOT.h"
//#include "Progression_order_change_POC.h"

using namespace std;

namespace BDK
{
	class Tilepart{
	private:
	public:
	  virtual ~Tilepart();
	public:
	  vector<Start_of_tile_part_SOT*> start_of_tile_part_SOT;
	//  Progression_order_change_POC progression_order_change_POC;

	public:
	  void set_Start_of_tile_part_SOT(const unsigned short length, const unsigned char* in);
	//  void set_Progression_order_change_POC(const unsigned short length, const unsigned char* in);
	   Tilepart();

	};
}
#endif // defined __TILEPART_H__
