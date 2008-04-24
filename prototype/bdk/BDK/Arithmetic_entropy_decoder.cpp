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
#include "Arithmetic_entropy_decoder.h"
#include <string>

using namespace std;

namespace BDK
{

	unsigned int Arithmetic_entropy_decoder::qe[] = {
							0x5601, 0x3401, 0x1801, 0x0ac1, 0x0521, 0x0221, 0x5601,
							0x5401, 0x4801, 0x3801, 0x3001, 0x2401, 0x1c01, 0x1601, 
							0x5601, 0x5401, 0x5101, 0x4801, 0x3801, 0x3401, 0x3001,
							0x2801, 0x2401, 0x2201, 0x1c01, 0x1801, 0x1601, 0x1401,
							0x1201, 0x1101, 0x0ac1, 0x09c1, 0x08a1, 0x0521, 0x0441,
							0x02a1, 0x0221, 0x0141, 0x0111, 0x0085, 0x0049, 0x0025,
							0x0015, 0x0009, 0x0005, 0x0001, 0x5601 };

    
	unsigned int Arithmetic_entropy_decoder::nmps[] = {	
							1 , 2, 3, 4, 5,38, 7, 8, 9,10,11,12,13,29,15,16,17,
							18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,
							35,36,37,38,39,40,41,42,43,44,45,45,46 };

	unsigned int Arithmetic_entropy_decoder::nlps[] = {	
							1 , 6, 9,12,29,33, 6,14,14,14,17,18,20,21,14,14,15,
							16,17,18,19,19,20,21,22,23,24,25,26,27,28,29,30,31,
							32,33,34,35,36,37,38,39,40,41,42,43,46 };

	unsigned int Arithmetic_entropy_decoder::switcher[] = {	
							1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
							0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };


	Arithmetic_entropy_decoder::Arithmetic_entropy_decoder()
	{
		mps			= NULL;
		index		= NULL;
		bytebuffer	= NULL;
		b			= 0;
		//id			= id_count;
		//id_count++;
	}
	Arithmetic_entropy_decoder::~Arithmetic_entropy_decoder()
	{
	}

	//  Operation: decode
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_decoder::decode()
	{
		ii		= index[cx];
		qee		= qe[ii];
		chigh	= CHIGH(c_register);

		a_register -= qee;
		if(chigh < qee){
			lps_exchange();
			renormd();
		}else{
			chigh -= qee;
			SETCHIGH(c_register, chigh);
			if((a_register & 0x8000) == 0){
				mps_exchange();
				renormd();
			}else{
				d = mps[cx];
			}
		}
	}



	//  Operation: decoder
	//
	//  Description:
	//   
	//  Parameters:
	//      cx	
	//
	//int Arithmetic_entropy_decoder::count		= 0;
	//int Arithmetic_entropy_decoder::id_count	= 0;
	//fstream* Arithmetic_entropy_decoder::file	= new fstream("C:\\Dokumente und Einstellungen\\uwe_work\\Eigene Dateien\\Visual Studio 2005\\Projects\\BDK_V1\\cppdedocder.txt",ios::out );

	unsigned char Arithmetic_entropy_decoder::decoder(unsigned char cx_in)
	{
		//int c_in = c_register;

		cx = cx_in;
		decode();
		/*
		if(true){
			(*file)<<dec<<" "<<count<<" "<<(int)d<< " "<<(int)cx_in<<"\n"; 
			
		}
		count += 1;
		*/
		return d;
	}

	//  Operation: mps_exchange
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_decoder::mps_exchange()
	{
		ii	= index[cx];
		qee	= qe[ii];
		
		if(a_register < qee){
			d = 1 - mps[cx];
			if(switcher[ii] == 1){
				mps[cx] = 1 - mps[cx];
			}
			index[cx] = nlps[ii];
		}else{
			d			= mps[cx];
			index[cx]	= nmps[ii];
		}
	}

	//  Operation: lps_exchange
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_decoder::lps_exchange()
	{
		ii	= index[cx];
		qee	= qe[ii];
		
		if(a_register < qee){
			a_register	= qee;
			d			= mps[cx];
			index[cx]	= nmps[ii];
		}else{
			a_register	= qee;
			d			= 1 - mps[cx];
			if(switcher[ii] == 1){
				mps[cx] = 1 - mps[cx]; 
			}
			index[cx]	= nlps[ii];
		}

	}

	//  Operation: renormd
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_decoder::renormd()
	{
		do{
			if(ct == 0){
				bytein();
			}
			a_register	<<= 1;
			c_register	<<= 1;
			ct			-= 1;
		}while((a_register & 0x8000) == 0);

	}

	//  Operation: bytein
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Arithmetic_entropy_decoder::bytein()
	{
		if(b == 0xff){
			b1 = bytebuffer->get_next_byte();
			bytebuffer->read_byte_pos--;

			if(b1 > 0x8f){
				c_register += 0xFF00;
				ct = 8;
			}else{
				b = bytebuffer->get_next_byte();
				c_register += (b << 9);
				ct = 7;
			}
		}else{
			b = bytebuffer->get_next_byte();
			c_register += (b << 8);
			ct = 8;
		}
	}


	//  Operation: initdec
	//
	//  Description:
	//   
	//  Parameters:
	//      bytebuffer	
	//

	void Arithmetic_entropy_decoder::initdec(ByteBuffer* bytebuffer, const int length, const unsigned int* default_mps, const unsigned int* default_index)
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
		c_register = b << 16;
		bytein();
		c_register	<<= 7;
		ct			-=	7;
		a_register	= 0x8000;
	}

}
