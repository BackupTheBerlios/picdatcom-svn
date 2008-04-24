// Tilepart.cpp
//
// This header file defines the implementation of the class Tilepart
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
#include "Tilepart.h"


BDK::Tilepart::~Tilepart()
{
}

//  Operation: set_Start_of_tile_part_SOT
//
//  Description:
//   
//  Parameters:
//      length	
//      in	
//

void BDK::Tilepart::set_Start_of_tile_part_SOT(const unsigned short length, const unsigned char* in)
{
	Start_of_tile_part_SOT* start_of_tile_part_SOT = new Start_of_tile_part_SOT(length, in);
	
}

//  Operation: set_Progression_order_change_POC
//
//  Description:
//   
//  Parameters:
//      length	
//      in	
//
/*
void BDK::Tilepart::set_Progression_order_change_POC(const unsigned short length, const unsigned char* in)
{
}
*/
//  Operation: Tilepart
//
//  Description:
//   
//  Parameters:
//

BDK::Tilepart::Tilepart()
{
}
