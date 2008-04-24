// Component.h
//
// This header file defines the interfaces to the class Component
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

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

namespace BDK
{
	class Component;
}

//#include "Resolution.h"
#include "Coding_style_component_COC.h"
#include "Quantization_default_QCD.h"
#include "Tile.h"
#include "SIZ_part_two.h"
#include "Parameter.h"
#include "Resolution.h"
#include "Data.h"

namespace BDK
{
	class Component{
	private:
		
		//void create_Resolution
		Resolution* resolution;
		

	public:
		Component(const Tile* tile, SIZ_part_two* siz);
		virtual ~Component();
		
		SIZ_part_two* ptr_SIZ_part_two;
		Data	*data;
		int tcx0;// The tile domain coordinates.
		int tcx1;// The tile domain coordinates.
		int tcy0;// The tile domain coordinates.
		int tcy1;// The tile domain coordinates.

		BDK_use_in use_in;

		Coding_style_default_COD* ptr_COD;
		Quantization_default_QCD* ptr_QCD;

		void	set_COD(Coding_style_default_COD* ptr_COD);
		void	set_QCD(Quantization_default_QCD* ptr_QCD);
		void	set_Resolution();
		int		get_Numprecincts(int r);
		void	decode_packet(int r_resolution, int l_layer, int k_precinct, ByteBuffer* bytebuffer);
		void	decode_codeword(int r_resolution, int l_layer, int k_precinct);
		void	decode_codeword(int r_resolution, int k_precinct);
		void	inverse_quantization_irreversible();
		void	start_Filter97_decoder();
	};
}
#endif // defined __COMPONENT_H__
