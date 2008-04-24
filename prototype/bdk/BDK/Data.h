// Data.h
//
// This header file defines the interfaces to the class Data
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

#ifndef __DATA_H__
#define __DATA_H__

#include <iostream>
#include <cstdlib>
#include "Arithmetic_entropy_encoder.h"
#include "Arithmetic_entropy_decoder.h"
#include "Filter97_decoder.h"
#include "Filter97_encoder.h"
using namespace std;

namespace BDK
{

	#define SIGNIFICANT_BIT		0x0100
	#define ISCODED_BIT			0x0200
	#define REFINEMENT_BIT		0x0400
	#define D0_BIT				0x0080
	#define D1_BIT				0x0040
	#define D2_BIT				0x0020
	#define	D3_BIT				0x0010
	#define H0_BIT				0x0008
	#define H1_BIT				0x0004
	#define V0_BIT				0x0002
	#define	V1_BIT				0x0001
    #define H0_sign_BIT			0x8000	
	#define H1_sign_BIT			0x4000
	#define V0_sign_BIT			0x2000
	#define V1_sign_BIT			0x1000
	#define SIGN_BIT			0x80000000
	#define UNIFORM				(unsigned char)0
	#define RUNLENGTH			(unsigned char)1
	#define MAGNITUT_STATE1		(unsigned char)16	
	#define MAGNITUT_STATE2		(unsigned char)17	
	#define MAGNITUT_STATE3		(unsigned char)18	
	#define BITSTUFFING			false

	typedef enum{SIGNIFICANCE_PROPAGATION_DECODING_PASS, MAGNITUDE_REFINEMENT_DECODING_PASS, CLEANUP_DECODING_PASS}Decodepass;

	class Data{
	private:
	public:
	  virtual ~Data();
	private:
	  unsigned __int16* state;// |H0 sign  | H1 sign | V0 sign | V1 sign | X | refinement | iscoded | significant |D0|D1|D2|D3|H0|H1|V0|V1
		
	  unsigned int work_bitplane;// The next coding pass work on this bitplane
	  unsigned int numb_bitplane;
	  
	  Decodepass decodepass;
	  unsigned int nr_passes;

	  Arithmetic_entropy_encoder *encoder;
	  Arithmetic_entropy_decoder *decoder;
	  bool	initdecoder;
	  ByteBuffer *codeword;

	  //unsigned int pos_buffer;

	  static unsigned char state_propagation[3][256];
	  static unsigned char state_signbit[256];
	  static unsigned char state_XORBit[256];

	  bool evenH, evenV;
	  
	  unsigned int SETBIT1;
	  unsigned int SETBIT2;
	  unsigned int UNSETBIT;

	public:

	  ByteBuffer *d_buffer;
	  ByteBuffer *cx_buffer;

	  void* free_pointer;// If the memory free the free_pointer is used.

	  float* data_float;// Use the date as float

	  __int32* data_int;// Use the data as integer.

	  unsigned __int32* data_uint;
		
	  unsigned int total_size;
	  unsigned int start_pointer;
	  unsigned int end_pointer;
	  unsigned int line_feed;
	  unsigned int nr_subband;

	  unsigned int total_sizeX;// The size of the complete memory area.

	  unsigned int total_sizeY;// The size of the complete memory area.

	  unsigned int work_x0;// Size of the working area.

	  unsigned int work_x1;// Size of the working area.

	  unsigned int work_y0;// Size of the working area.

	  unsigned int work_y1;// Size of the working area.

	  unsigned int size_x;
	  unsigned int size_y;

	  bool free_void;// If true, free the free_pointer with this deconstructor.

	  int maximumValue_int;

	private:
	  void significance_propagation_encoding_pass();
	  void significance_propagation_decoding_pass();
	  void sign_bit_encoding();
	  void sign_bit_decoding();
	  void magnitude_refinement_encoding_pass();
	  void magnitude_refinement_decoding_pass();
	  void cleanup_encoding_pass();
	  void cleanup_decoding_pass();
	  void set_state_zero();
	  void reset_is_coded();
	  void set_state(unsigned int sign,unsigned int x, unsigned int y, unsigned int run_pointer, unsigned int offset_D0, unsigned int offset_D1, unsigned int offset_D2, unsigned int offset_D3, unsigned int offset_H0, unsigned int offset_H1, unsigned int offset_V0, unsigned int offset_V1);
	  void initDate(unsigned int sizeX, unsigned int sizeY, unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1);
	  void initDate(Data *data, unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1);
	  int npasses;
	
	

	public:
	  Data(unsigned int sizeX, unsigned int sizeY);
	  Data(unsigned int sizeX, unsigned int sizeY, unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1);
	  Data(Data *data, unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1);
	  void random_fill();
	  void random_fill_float();
	  void zero_fill();
	  void start_encode_Coefficient_bit_modeling();
	  void start_decode_Coefficient_bit_modeling();
	  void start_decode_Coefficient_bit_modeling(int passes);
	  void inttocustomint();
	  void custominttoint();
	  void showData();
	  void showData_float();
	  void setmaximumValue();
	  void setnumb_bitplane();
	  void initBuffer();
	  void initBuffer(ByteBuffer*);
	  void set_numb_bitplane(unsigned int);
	  unsigned int get_numb_bitplane();
	  void set_subband(unsigned int);
	  void compare(Data *);
	  void fill_buffer(unsigned char* buffer, unsigned int width, unsigned int height);
	  void setdecoder(ByteBuffer *codeword);
	  void customint_to_float(float deltab);
	  void filter_encode(Filter97_encoder *encoder);
	  void filter_decode(Filter97_decoder *decoder);
	  void set_even(int h, int v);
	  void fill_RGBbuffer_Y(unsigned char* buffer);
	  void fill_RGBbuffer_Cr(unsigned char* buffer);
	  void fill_RGBbuffer_Cb(unsigned char* buffer);
	  static void fill_RGBbuffer(Data *dataY, Data *dataCb, Data *dataCr, unsigned char *buffer);
	};
}

#endif // defined __DATA_H__
