// Arithmetic_entropy_decoder.h
//
// This header file defines the interfaces to the class Arithmetic_entropy_decoder
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

#ifndef __ARITHMETIC_ENTROPY_DECODER_H__
#define __ARITHMETIC_ENTROPY_DECODER_H__

#include "ByteBuffer.h"
#include <fstream>

namespace BDK
{
	#define CHIGH(i) ((i >> 16) & 0xFFFF)
	#define SETCHIGH(c, ch) (c = (c & 0xFFFF) | ((ch << 16)& 0xFFFF0000))

	class Arithmetic_entropy_decoder{
	private:
	  //static fstream *file;
	  //static int count;
	  //static int id_count;
	  //int id;
	public:
	  Arithmetic_entropy_decoder();
	public:
	  virtual ~Arithmetic_entropy_decoder();
	protected:
	  unsigned char d;
	  unsigned char cx;
	  unsigned int c_register;
	  unsigned int a_register;
	  static unsigned int qe[];
	  static unsigned int nmps[];
	  static unsigned int nlps[];
	  static unsigned int switcher[];
	  unsigned char* mps;
	  unsigned int* index;
	  int ct;
	  ByteBuffer* bytebuffer;
	  unsigned int b;
	  unsigned int b1;
	  unsigned int ii, qee;
	  unsigned int chigh;
	protected:
	  virtual void decode();
	  void mps_exchange();
	  void lps_exchange();
	  void renormd();
	  virtual void bytein();
	public:
	  unsigned char decoder(unsigned char cx_in);
	  virtual void initdec(ByteBuffer* bytebuffer, const int length, const unsigned int* default_mps, const unsigned int* default_index);

	};
}
#endif // defined __ARITHMETIC_ENTROPY_DECODER_H__
