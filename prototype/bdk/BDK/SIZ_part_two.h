// SIZ_part_two.h
//
// This header file defines the interfaces to the class SIZ_part_two
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

#ifndef __SIZ_PART_TWO_H__
#define __SIZ_PART_TWO_H__

#include <iostream>
#include <fstream>
using namespace std;

namespace BDK
{
	class SIZ_part_two{
	private:
	public:
	  SIZ_part_two(unsigned char *ptr_char, unsigned int offset);
	public:
	  virtual ~SIZ_part_two();
	public:
	  unsigned char Ssiz;// Precision (depth) in bits and sign on the component sample

	  unsigned char XRsiz;// Horizontal separation of a sample of this component

	  unsigned char YRsiz;// Vertical seperation of sample of this componente
	};
}
#endif // defined __SIZ_PART_TWO_H__
