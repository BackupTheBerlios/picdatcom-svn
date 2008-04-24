// Resolution.h
//
// This header file defines the interfaces to the class Resolution
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

#ifndef __RESOLUTION_H__
#define __RESOLUTION_H__

#include <vector>

namespace BDK
{
	class Resolution;
}

#include "Component.h"
#include "Subband.h"
#include "Parameter.h"
#include "Precinct.h"
#include "Default_Exceptionhandler.h"
#include "Data.h"

namespace BDK
{
	class Resolution{
	private:
	  Resolution*		lower;
	  Resolution*		top;
	  vector<Precinct*>	precinct;
	  Quantization_default_QCD *qcd;
	  Data *data;

	public:
	  virtual ~Resolution();
	  void init();

	public:
	  int trx0;// Tile-component coordinate.

	  int trx1;// Tile-component coordinate.

	  int try0;// Tile-component coordinate.

	  int try1;// Tile-component coordinate.

	  int n;
	  int r;// Resolution level

	  int tpn0;// Precinct position horizontal.

	  int tpn1;// Precinct position horizontal.

	  int tpm0;// Precinct position vertical.

	  int tpm1;// Precinct position vertical.

	  int numberprecinct;// Number of precinct in this Resolution

	  Component* component;

	  int cn0;
	  int cn1;
	  int cm0;
	  int cm1;

	  int xcb, ycb;

	  Precinct_size*	precinct_size;
	  vector<Subband*>	subband;
	public:
	   Resolution(Resolution* resolution);
	   Resolution(Component* component);
	   int get_Numprecincts(int r);
	   void decode_packet(int r_resolution, int l_layer, int k_precinct, ByteBuffer* bytebuffer);
	   void decode_codeword(int r_resolution, int l_layer, int k_precinct);
	   void decode_codeword(int r_resolution, int k_precinct);
	   void set_QCD();
	   void	inverse_quantization_irreversible();
	   void start_Filter97_decoder(Filter97_decoder *decoder);

	};
}
#endif // defined __RESOLUTION_H__
