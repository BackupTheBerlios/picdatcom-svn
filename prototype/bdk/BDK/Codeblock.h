// Codeblock.h
//
// This header file defines the interfaces to the class Codeblock
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

#ifndef __CODEBLOCK_H__
#define __CODEBLOCK_H__


namespace BDK
{
	class Codeblock;
}

#include "Subband.h"
#include "ByteBuffer.h"
#include "Data.h"
#include "Layer.h"
#include <vector>
#include <math.h>

namespace BDK
{
	class Codeblock{
	private:
	  void init(Subband* subband, int n, int m, bool empty);
	  Data *data;
	  Subband *subband;

	public:
	  virtual ~Codeblock();
	public:
	  int maximum_value;
	  int Zero_bitplane_information;	// See ISO/IEC 15444-1:1004   B.10.5
	  int Codeblock_inclusion;			// See ISO/IEC 15444-1:1004   B.10.4
	  int Lblock;						// See ISO/IEC 15444-1:1004   B.10.7

	  vector<ByteBuffer*>	codeword;
	  int					number_codeword;

	  // state variable
	  //vector<int>			number_of_coding_passes;
	  //int					number_of_coding_passes_point;
	  //int					number_of_codeword_segments;
	  vector<Layer*>		layer;
	  Layer*				current_layer;
	  //unsigned int		codeword_segment_length[109];
	  unsigned int			active_codeword;

	  int cx0;
	  int cx1;
	  int cy0;
	  int cy1;
	  
	  static double log_help;

	  bool	empty;
	  bool	codeblock_include;
	  bool	codeblock_include_segments;
	public:
	   Codeblock(Subband* subband, int n, int m, bool empty);
	   //Codeblock(bool empty);
	   void set_Zero_bitplane_information(int Zero_bitplane_information);
	   void set_number_of_coding_passes(int number_of_coding_passes);
	   int	get_number_of_codeword_segments();
	   int	get_number_of_coding_passes_segment();
	   void set_codeword_segment_length(int pos, ByteBuffer* bytebuffer);
	   int get_codeword_segment_length(int pos);
	   void	set_Lblock(ByteBuffer* bytebuffer);
	   void set_codeword_segment_data(ByteBuffer* bytebuffer);
	   void initData(Data *data, int offsetX, int offsetY);
	   void bits_decode();
	   void decode_codeword(int l_layer);
	   void decode_codeword();
	   void create_Layer(int l_layer);
	   void set_current_layer(int l_layer);
	  
	};
}
#endif // defined __CODEBLOCK_H__
