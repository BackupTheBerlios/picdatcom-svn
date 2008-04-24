// Arithmetic_entropy_encoder.h
//
// This header file defines the interfaces to the class Arithmetic_entropy_encoder
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

#ifndef __ARITHMETIC_ENTROPY_ENCODER_H__
#define __ARITHMETIC_ENTROPY_ENCODER_H__


#include "ByteBuffer.h"

namespace BDK
{
	class Arithmetic_entropy_encoder{
	private:
	public:
	  Arithmetic_entropy_encoder();
	public:
	  virtual ~Arithmetic_entropy_encoder();

	private:
	  bool first_run;
	  unsigned char d;
	  unsigned char cx;
	  unsigned int c_register;
	  unsigned int a_register;
	  unsigned int temp;
	  static unsigned int qe[];
	  static unsigned int nmps[];
	  static unsigned int nlps[];
	  static unsigned int switcher[];
	  unsigned char* mps;
	  unsigned int* index;
	  int ct;
	  unsigned int bp;
	  unsigned int ii, qee;
	  ByteBuffer* bytebuffer;
	  unsigned char b;

	public:
	  static unsigned int j2000_index[];
	  static unsigned int j2000_mps[];
	  static unsigned int j2000_length;
	private:
	  void setbits();
	  void byteout();
	  void renorme();
	  void codemps();
	  void codelps();
	  void code0();
	  void code1();
	public:
	  void initenc(const int length, const unsigned int* default_mps, const unsigned int* default_index);
	  void encode();
	  void flush();
	  void start_encode(const int length, const unsigned char* d_indices,  const unsigned char* cx_indices);
	  ByteBuffer* getByteBuffer();

	};
}

#endif // defined __ARITHMETIC_ENTROPY_ENCODER_H__
