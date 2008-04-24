// Decoder.h
//
// This header file defines the interfaces to the class Decoder
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

#ifndef __DECODER_H__
#define __DECODER_H__


#include "BDK_entry_point.h"
#include "Parameter.h"
#include "Default_Exceptionhandler.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;




namespace BDK
{
	typedef enum{decoder_main, decoder_tile}decoder_state;

	class Decoder: public BDK_entry_point{
		private:
			ifstream *ptr_ifstream;
			bool COD_read;
			bool QCD_need_to_create;
		public:
			virtual ~Decoder();
		public:
			Decoder(ifstream *ptr_ifstream);
			void fill_RGBbuffer(unsigned char* buffer);

		private:
			void createStructure();
			void set_QCD(Quantization_default_QCD* ptr_QCD);
			void set_COD(Coding_style_default_COD* ptr_COD);
			void inverse_quantization_irreversible();
			void start_Filter97_decoder();
			void clearRGBBuffer(unsigned char *buffer);
	};
}
#endif // defined __DECODER_H__
