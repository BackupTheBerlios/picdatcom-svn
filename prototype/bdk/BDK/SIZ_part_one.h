// SIZ_part_one.h
//
// This header file defines the interfaces to the class SIZ_part_one
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

#ifndef __SIZ_PART_ONE_H__
#define __SIZ_PART_ONE_H__


#include "SIZ_part_two.h"
#include "Parameter.h"
#include "Default_Exceptionhandler.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

namespace BDK
{
	class SIZ_part_one{
		private:
		public:
		  SIZ_part_one(unsigned char *ptr_char);
		  void set_SIZ_part_two(unsigned char *ptr_char);
		public:
		  virtual ~SIZ_part_one();
		public:
		  unsigned short Lsiz;// Length of marker segment in bytes. Lsiz = 38 + 3 * Csiz

		  unsigned short Rsiz;// Denotes capabilities that a decoder needs to properly decode the codestream

		  unsigned int Xsiz;// Width of the refernce grid

		  unsigned int Ysiz;// Height of reference grid

		  unsigned int XOsiz;// Horizontal offset


		  unsigned int YOsiz;// Vertical offset

		  unsigned int XTsiz;// Width of on reference tile

		  unsigned int YTsiz;// Height of one reference tile 

		  unsigned int XTOsiz;// Horizontal offset first tile

		  unsigned int YTOsiz;// Vertical offset for tile

		  unsigned char Csiz;// Number of components in the image

		  vector<SIZ_part_two *> siz_part_two;

	};
}
#endif // defined __SIZ_PART_ONE_H__
