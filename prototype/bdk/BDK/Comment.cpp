// Comment.cpp
//
// This header file defines the implementation of the class Comment
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
#include "Comment.h"


BDK::Comment::~Comment()
{
}

//  Operation: Comment
//
//  Description:
//   
//  Parameters:
//

BDK::Comment::Comment()
{
}

//  Operation: Comment
//
//  Description:
//   
//  Parameters:
//      length	
//      in	
//

BDK::Comment::Comment(unsigned short length, unsigned char* in)
{
	this->Lcom = length;
	this->Rcom = bytetoshort(in, 0);
	if(length > 4){
		this->Ccom = new char[length - 4];
	}else{
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "To short comment." );
	}
}


