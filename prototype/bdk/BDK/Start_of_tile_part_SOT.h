// Start_of_tile_part_SOT.h
//
// This header file defines the interfaces to the class Start_of_tile_part_SOT
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

#ifndef __START_OF_TILE_PART_SOT_H__
#define __START_OF_TILE_PART_SOT_H__

#include "Parameter.h"

namespace BDK
{
	class Start_of_tile_part_SOT{
	private:
	public:
	  virtual ~Start_of_tile_part_SOT();
	public:
	  unsigned short Lsot;// Length of marker segment in bytesl

	  unsigned short Isot;// Tile index.

	  unsigned int Psot;// Length, in bytes, from the beginning of the first byte of SOT marker segment of the tile-part to the end of the data of that tile-part.

	  unsigned char TPsot;// Tile-part index. 

	  unsigned char TNsot;// Number of tile-parts of a tile in the codestream.


	public:
	   Start_of_tile_part_SOT(const unsigned short length, const unsigned char* in);
	   Start_of_tile_part_SOT();
	   static unsigned int get_Isot(const unsigned char * in);
	   static unsigned int get_Psot(const unsigned char * in);
	};
}
#endif // defined __START_OF_TILE_PART_SOT_H__
