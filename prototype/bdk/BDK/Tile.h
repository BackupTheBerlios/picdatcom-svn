// Tile.h
//
// This header file defines the interfaces to the class Tile
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

#ifndef __TILE_H__
#define __TILE_H__

namespace BDK
{
	class Tile;
}

//#include "Region_of_interest_RGN.h"
//#include "Component.h"
#include "Tilepart.h"
#include "BDK_entry_point.h"
#include "Parameter.h"
#include "Coding_style_default_COD.h"
#include "Quantization_default_QCD.h"
#include "Component.h"
#include "ByteBuffer.h"
#include <vector>
#include <math.h>

namespace BDK
{
	class Tile{
	private:
		bool firstsetCodestream;
		int	 get_Numprecincts(int r, int i);
		void decode_packet(int i_componete, int r_resolution, int l_layer, int k_precinct, ByteBuffer* bytebuffer);
	public:
	  virtual ~Tile();
	public:
		int tx0;// The coordinates of a particular tile

		int tx1;// The coordinates of a particular tile

		int ty0;// The coordinates of a particular tile

		int ty1;// The coordinates of a particular tile

		BDK_entry_point* entry_point;
		vector<Tilepart*> tileparts;
		vector<Component*> components;
		Coding_style_default_COD* ptr_COD;
		Quantization_default_QCD* ptr_QCD;

		bool COD_read;

	public:
		Tile();
		Tile(BDK_entry_point* entry_point, unsigned int t_tileindex);
		void set_Tilepart(const unsigned short length, unsigned char* in);
		void set_Codestream(const unsigned short length, unsigned char* in, ByteBuffer* bytebuffer);
		void start_decode_resolution_level_layer_component_position(const unsigned short length, unsigned char* in, ByteBuffer* bytebuffer);
		void set_COD(Coding_style_default_COD* ptr_COD);
		void set_QCD(Quantization_default_QCD* ptr_QCD);
		void inverse_quantization_irreversible();
		void start_Filter97_decoder();
		void fill_RGBbuffer(unsigned char* buffer);
	};
}
#endif // defined __TILE_H__
