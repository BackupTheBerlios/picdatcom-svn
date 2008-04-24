// Precinct_size.cpp
//
// This header file defines the implementation of the class Precinct_size
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
#include "Precinct_size.h"


BDK::Precinct_size::~Precinct_size()
{
}

//  Operation: Precinct_size
//
//  Description:
//   
//  Parameters:
//      PPx	
//      PPy	
//

BDK::Precinct_size::Precinct_size(const unsigned char PPx, const unsigned char PPy)
{
	this->PPx = PPx;
	this->PPy = PPy;
}

BDK::Precinct_size::Precinct_size(const unsigned char info)
{
	this->PPx = info & 0x0F;
	this->PPy = (info >> 4) & 0x0F;
}
