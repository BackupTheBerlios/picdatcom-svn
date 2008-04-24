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

#include "Default_Exceptionhandler.h"
#include <iostream>
#include <vector>
using namespace std;

struct context_label{
	unsigned char context;
	unsigned char symbol;
};

#define SIGNIFICANTBIT			0x01
#define ISCODEDBIT				0x02
#define SIGNIFICANTISCODEDBIT	0x03
#define FIRSTREFINEMENTBIT		0x04
#define UNIFORM					17
#define RUNLENGTH				16


class Data{
private:
public:
  virtual ~Data();
private:
  static Default_Exceptionhandler* ptr_exception;
  unsigned int work_bitplane;// The next coding pass work on this bitplane
  /*
   * First_Refinement = 1 --> false
   * Fisrt_Refinement = 0 --> true
   */
   unsigned __int8* state;// | X | X | X | X | X| First_Refinement | iscoded | significant |
 int *significant_context;
public:
  void* free_pointer;// If the memory free the free_pointer is used.

  float* data_float;// Use the date as float

  __int32* data_int;// Use the data as integer.

  unsigned __int32* data_uint;

  unsigned int total_sizeX;// The size of the complete memory area.

  unsigned int total_sizeY;// The size of the complete memory area.

  int work_x0;// Size of the working area.

  int work_x1;// Size of the working area.

  int work_y0;// Size of the working area.

  int work_y1;// Size of the working area.

  bool free_void;// If true, free the free_pointer with this deconstructor.

  int maximumValue_int;

private:
  void significance_propagation_encoding_pass(vector<struct context_label> &buffer);
  void significance_propagation_decoding_pass();
  void sign_bit_encoding(int X, int Y, vector<struct context_label> &buffer);
  void sign_bit_decoding();
  void magnitude_refinement_encoding_pass();
  void magnitude_refinement_decoding_pass();
  void cleanup_encoding_pass(vector<struct context_label>& buffer);
  void cleanup_decoding_pass();
  void set_max_abs_int();
  void get_Context_label(int X, int Y, int *intern_Context);

public:
  Data(unsigned int sizeX, unsigned int sizeY);
  Data(Data*);
  void random_fill();
  void start_encode_Coefficient_bit_modeling();
  void start_decode_Coefficient_bit_modeling();
  bool compare(Data*);
  void inttocustomint();
  void custominttoint();
};

#endif // defined __DATA_H__
