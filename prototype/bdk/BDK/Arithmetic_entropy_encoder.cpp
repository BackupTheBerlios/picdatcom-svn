// Arithmetic_entropy_encoder.cpp
//
// This header file defines the implementation of the class Arithmetic_entropy_encoder
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
#include "Arithmetic_entropy_encoder.h"

namespace BDK
{
	unsigned int Arithmetic_entropy_encoder::j2000_length = 19;

	unsigned int Arithmetic_entropy_encoder::j2000_index[] = {	
							46, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0,
							0, 0, 0, 0, 0, 0, 0, 0};

	unsigned int Arithmetic_entropy_encoder::j2000_mps[] = {	
							0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							0, 0, 0, 0, 0, 0, 0, 0};

	unsigned int Arithmetic_entropy_encoder::qe[] = {
							0x5601, 0x3401, 0x1801, 0x0ac1, 0x0521, 0x0221, 0x5601,
							0x5401, 0x4801, 0x3801, 0x3001, 0x2401, 0x1c01, 0x1601, 
							0x5601, 0x5401, 0x5101, 0x4801, 0x3801, 0x3401, 0x3001,
							0x2801, 0x2401, 0x2201, 0x1c01, 0x1801, 0x1601, 0x1401,
							0x1201, 0x1101, 0x0ac1, 0x09c1, 0x08a1, 0x0521, 0x0441,
							0x02a1, 0x0221, 0x0141, 0x0111, 0x0085, 0x0049, 0x0025,
							0x0015, 0x0009, 0x0005, 0x0001, 0x5601 };

    
	unsigned int Arithmetic_entropy_encoder::nmps[] = {	
							1 , 2, 3, 4, 5,38, 7, 8, 9,10,11,12,13,29,15,16,17,
							18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
							35,36,37,38,39,40,41,42,43,44,45,45,46 };

	unsigned int Arithmetic_entropy_encoder::nlps[] = {	
							1 , 6, 9,12,29,33, 6,14,14,14,17,18,20,21,14,14,15,
							16,17,18,19,19,20,21,22,23,24,25,26,27,28,29,30,31,
							32,33,34,35,36,37,38,39,40,41,42,43,46 };

	unsigned int Arithmetic_entropy_encoder::switcher[] = {	
							1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
							0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	Arithmetic_entropy_encoder::Arithmetic_entropy_encoder()
	{
		mps			= NULL;
		index		= NULL;
		bytebuffer	= new ByteBuffer();
		b			= 0;
		first_run	= true;
	}

	Arithmetic_entropy_encoder::~Arithmetic_entropy_encoder()
	{
	}

	//  Operation: setbits
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_encoder::setbits()
	{
		temp		= c_register + a_register;
		c_register	|= 0xFFFF;
		if(c_register >= temp){
			c_register -= 0x8000;
		}
	}

	//  Operation: flush
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_encoder::flush()
	{
		setbits();
		c_register = c_register << ct;
		byteout();
		c_register = c_register << ct;
		byteout();
		//b = bytebuffer->buffer[bytebuffer->write_byte_pos - 1];
		if(b == 0xff){
			bytebuffer->write_byte_pos -= 1;
		}
	}

	//  Operation: initenc
	//
	//  Description:
	//   
	//  Parameters:
	//      length	
	//      default_mps	
	//      default_index	
	//

	void Arithmetic_entropy_encoder::initenc(const int length, const unsigned int* default_mps, const unsigned int* default_index)
	{
		if(mps == NULL && index == NULL){
			mps		= new unsigned char[length];
			index	= new unsigned int[length]; 
		}

		for(int i = 0; i < length; i++){
			mps[i]		= default_mps[i];
			index[i]	= default_index[i];
		}
		
		a_register			= 0x8000;
		c_register			= 0;
		ct					= 12;
		bp					= bytebuffer->write_byte_pos - 1;
		

		if((bp & 0xFFFFFFF0) != 0xFFFFFFF0){
			if(bytebuffer->buffer[bp] == 0xFF){
				ct = 13;
			}
		}
	}

	//  Operation: byteout
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_encoder::byteout()
	{
		if(!first_run){
			if(b == 0xFF){
				b			= c_register >> 20;
				c_register	= c_register & 0xFFFFFF;
				ct			= 7;
				bytebuffer->add_byte(b);
			}else{
				if(c_register < 0x8000000){

					b			= c_register >> 19;
					c_register	= c_register & 0x7FFFF;
					ct			= 8;
					bytebuffer->add_byte(b);
				}else{
					b += 1;
					bytebuffer->buffer[bytebuffer->write_byte_pos - 1] = b;
					if(b == 0xFF){
						c_register	&= 0x7FFFFFF;
						b			= c_register >> 20;
						c_register	= c_register & 0xFFFFF;
						ct			= 7;
						bytebuffer->add_byte(b);
					}else{
						b			= (c_register >> 19);
						c_register	= c_register & 0x7FFFF;
						ct			= 8;
						bytebuffer->add_byte(b);
					}

				}
			}
		}else{
				b			= c_register >> 19;
				c_register	= c_register & 0x7FFFF;
				ct			= 8;
				bytebuffer->add_byte(b);
				first_run	= false;
		}
	}

	//  Operation: renorme
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_encoder::renorme()
	{
		do{
			a_register <<= 1;
			c_register <<= 1;
			ct -= 1;
			if(ct == 0){
				byteout();
			}
		}while((a_register & 0x8000) == 0);
	}

	//  Operation: codemps
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_encoder::codemps()
	{
		ii = index[cx];
		qee = qe[ii];

		a_register -= qee;

		if((a_register & 0x8000) == 0){
			if(a_register < qee){
				a_register = qee;
			}else{
				c_register += qee;
			}
			index[cx] = nmps[ii];
			renorme();
		}else{
			c_register += qee;
		}

	}

	//  Operation: codelps
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_encoder::codelps()
	{
		ii = index[cx];
		qee = qe[ii];

		a_register -= qee;

		if(a_register < qee){
			c_register += qee;
		}else{
			a_register = qee;
		}

		if(switcher[ii] == 1){
			mps[cx] = 1 - mps[cx];
		}

		index[cx] = nlps[ii];

		renorme();
	}

	//  Operation: code0
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_encoder::code0()
	{
		if(mps[cx] == 0){
			codemps();
		}else{
			codelps();
		}
	}

	//  Operation: code1
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_encoder::code1()
	{
		if(mps[cx] == 1){
			codemps();
		}else{
			codelps();
		}
	}

	//  Operation: encode
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_encoder::encode()
	{
		if(d == 0){
			code0();
		}else{
			code1();
		}
	}

	//  Operation: start_encode
	//
	//  Description:
	//   
	//  Parameters:
	//      length	
	//      d_indices	
	//      cx_indices	
	//

	void Arithmetic_entropy_encoder::start_encode(const int length, const unsigned char* d_indices, const unsigned char* cx_indices)
	{

		int iWork1;
		for(iWork1 = 0; iWork1 < length; iWork1++){
			d	= d_indices[iWork1];
			cx	= cx_indices[iWork1];
			encode();
		}
	}

	ByteBuffer* Arithmetic_entropy_encoder::getByteBuffer()
	{
		return bytebuffer;
	}
}