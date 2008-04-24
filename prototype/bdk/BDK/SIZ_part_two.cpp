// SIZ_part_two.cpp
//
// This header file defines the implementation of the class SIZ_part_two
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
// 
//
#include "SIZ_part_two.h"


BDK::SIZ_part_two::SIZ_part_two(unsigned char *ptr_char, unsigned int offset)
{
	Ssiz	= ptr_char[offset];
	XRsiz	= ptr_char[offset+1];
	YRsiz	= ptr_char[offset+1];
}
BDK::SIZ_part_two::~SIZ_part_two()
{
}
