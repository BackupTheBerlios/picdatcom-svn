// Subband.h
//
// This header file defines the interfaces to the class Subband
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

#ifndef __SUBBAND_H__
#define __SUBBAND_H__

#include <math.h>
#include <vector>

namespace BDK
{
	class Subband;
}

#include "Quantization_default_QCD.h"
#include "Resolution.h"
#include "Codeblock.h"
#include "Data.h"

namespace BDK
{
	typedef enum{SUBBAND_HH, SUBBAND_HL, SUBBAND_LH, SUBBAND_LL} Subbandtype;

	class Subband{
	private:
	  int calc(int tc, int high, int x);
	  int size_u, size_v;
	  Data *data;
	  Quantization_default_QCD		*qcd;
	  Quantization_of_values_SPqcc	*spqcc;
	  Resolution					*resolution;

	  void customint_to_float();

	public:
	  virtual ~Subband();
	public:
	  int tbx0;// subband coordinates

	  int tbx1;// subband coordinates

	  int tby0;// subband coordinates

	  int tby1;// subband coordinates

	  int maximum_value;// biggest value in this subband

	  int cn0;// Codeblock coordinate 

	  int cn1;// Codeblock coordinate

	  int cm0;// Codeblock coordinate

	  int cm1;// Codeblock coordinate
		
	  int xcb, ycb;

	  vector<Codeblock*>	codeblocks;
	  Subbandtype			subbandtype;
	  int M;
	public:
	  Subband(Resolution* resolution, int x0b, int y0b, Subbandtype subbandtype);
	  void initData(Data *in_data, unsigned int offsetX, unsigned int offsetY);
	  void set_QCD();
	  void	inverse_quantization_irreversible();
	  
	};
}
#endif // defined __SUBBAND_H__
