// Arithmetic_entropy_decoder.cpp
//
// This header file defines the implementation of the class Arithmetic_entropy_decoder
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
#include "Arithmetic_entropy_decoder_Software.h"


namespace BDK
{

	Arithmetic_entropy_decoder_Software::Arithmetic_entropy_decoder_Software()
	{
		mps			= NULL;
		index		= NULL;
		bytebuffer	= NULL;
		b			= 0;
	}

	void Arithmetic_entropy_decoder_Software::decode()
	{
		ii		= index[cx];
		qee		= qe[ii];
		chigh	= CHIGH(c_register);


		a_register -= qee;

		if(chigh < a_register){
			if((a_register & 0x8000) == 0){
				mps_exchange();
				renormd();
			}else{
				d = mps[cx];
			}
		}else{
			chigh -= a_register;
			SETCHIGH(c_register, chigh);
			lps_exchange();
			renormd();
		}
	}


	void Arithmetic_entropy_decoder_Software::bytein()
	{
		if(b == 0xFF){
			b1 = bytebuffer->get_next_byte();
			bytebuffer->read_byte_pos--;

			if(b1 > 0x8f){
				ct = 8;
			}else{
				b = bytebuffer->get_next_byte();
				c_register += (0xFE00 - (b << 9));
				ct = 7;
			}
		}else{
			b = bytebuffer->get_next_byte();
			c_register += (0xFF00 - (b << 8));
			ct = 8;
		}
	}


	void Arithmetic_entropy_decoder_Software::initdec(ByteBuffer* bytebuffer, const int length, const unsigned int* default_mps, const unsigned int* default_index)
	{
		if(mps == NULL && index == NULL){
			mps		= new unsigned char[length];
			index	= new unsigned int[length]; 
		}

		for(int i = 0; i < length; i++){
			mps[i]		= default_mps[i];
			index[i]	= default_index[i];
		}
		this->bytebuffer = bytebuffer;
		b = this->bytebuffer->get_next_byte();
		c_register = (b ^ 0xFF) << 16;
		bytein();
		c_register	<<= 7;
		ct			-=	7;
		a_register	= 0x8000;	
	}


}