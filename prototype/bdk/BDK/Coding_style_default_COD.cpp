// Coding_style_default_COD.cpp
//
// This header file defines the implementation of the class Coding_style_default_COD
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
#include "Coding_style_default_COD.h"
#include "Default_Exceptionhandler.h"

BDK::Coding_style_default_COD::~Coding_style_default_COD()
{
}

//  Operation: Coding_style_default_COD
//
//  Description:
//   
//  Parameters:
//      informaition	
//      length	
//      use_in	
//

BDK::Coding_style_default_COD::Coding_style_default_COD(const unsigned char* information, const unsigned short length, BDK_use_in use_in)
{
	unsigned char scod;
	if(length >= 12){
		this->Lcox		= length;
		this->Ccoc		= CCOC_DEFAULT;
		this->use_in	= use_in;

		scod	= information[0];
		if((scod & DEFAULTPRECINCTSIZEBIT) != DEFAULTPRECINCTSIZEBIT){
			this->use_default_PPx_PPy = true;
		}else{
			this->use_default_PPx_PPy = false;
		}
		
		if((scod & SOPBIT) == SOPBIT){
			this->use_SOP = true;
		}else{
			this->use_SOP = false;
		}

		this->progression_order = (BDK_Progression_order)information[1];
		
		this->number_of_Layer = information[2];
		this->number_of_Layer <<= 8;
		this->number_of_Layer |= information[3];
		
		if((MULTIPLE_TRANSFORMATION & information[4] ) == MULTIPLE_TRANSFORMATION){
			this->multiple_component_transformation = true;
		}else{
			this->multiple_component_transformation = false;
		}

		spcoc = new SPcoc(&information[5], this);
	}else{
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Lcod to small." );
	}
}
