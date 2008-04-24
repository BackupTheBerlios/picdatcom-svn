// Start_of_tile_part_SOT.cpp
//
// This header file defines the implementation of the class Start_of_tile_part_SOT
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
#include "Start_of_tile_part_SOT.h"


BDK::Start_of_tile_part_SOT::~Start_of_tile_part_SOT()
{
}

//  Operation: Start_of_tile_part_SOT
//
//  Description:
//   
//  Parameters:
//      length	
//      in	
//

BDK::Start_of_tile_part_SOT::Start_of_tile_part_SOT(const unsigned short length, const unsigned char* in)
{
	this->Lsot	= length;
	this->Isot	= get_Isot(in);
	this->Psot	= get_Psot(in);
	this->TPsot	= in[6];
	this->TNsot	= in[7];

}


BDK::Start_of_tile_part_SOT::Start_of_tile_part_SOT()
{
}


unsigned int BDK::Start_of_tile_part_SOT::get_Isot(const unsigned char * in)
{
	return bytetoshort(in,0);

}

unsigned int BDK::Start_of_tile_part_SOT::get_Psot(const unsigned char * in)
{
	return bytetouint(in, 2);

}