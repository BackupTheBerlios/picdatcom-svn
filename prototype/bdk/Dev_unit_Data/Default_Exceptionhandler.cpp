// Default_Exceptionhandler.cpp
//
// This header file defines the implementation of the class Default_Exceptionhandler
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
#include "Default_Exceptionhandler.h"


Default_Exceptionhandler::Default_Exceptionhandler(string file, int line, string info)
{
	this->file.append(file);
	this->info.append(info);
	this->line = line;
}


Default_Exceptionhandler::~Default_Exceptionhandler()
{
}

//  Operation: toString
//
//  Description:
//   
//  Parameters:
//

string Default_Exceptionhandler::toString()
{
  out<<file<<" "<<line<<" "<<info<<endl;
  return out.str();
}
