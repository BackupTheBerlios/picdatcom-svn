// Default_Exceptionhandler.h
//
// This header file defines the interfaces to the class Default_Exceptionhandler
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

#ifndef __DEFAULT_EXCEPTIONHANDLER_H__
#define __DEFAULT_EXCEPTIONHANDLER_H__

#include <sstream>
#include <string>
using namespace std;


class Default_Exceptionhandler{
private:
  ostringstream out;

public:
  Default_Exceptionhandler(string file, int line, string info);
public:
  virtual ~Default_Exceptionhandler();
public:
  string file;
  string info;
  int line;

public:
  string toString();

};

#endif // defined __DEFAULT_EXCEPTIONHANDLER_H__
