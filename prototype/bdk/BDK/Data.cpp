// Data.cpp
//
// This header file defines the implementation of the class Data
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
#include "Data.h"

namespace BDK
{
	unsigned int uwe_wert_dumm = 0;

	unsigned char Data::state_propagation[3][256] = {{		
						 2,  5,  5,  6,  7,  9,  9,  9,  7,  9,  9,  9, 10, 10, 10, 10, 
						 3,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 3,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 4,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 3,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 4,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 4,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 4,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 3,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 4,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 4,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 4,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 4,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 4,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 4,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10, 
						 4,  5,  5,  6,  8,  9,  9,  9,  8,  9,  9,  9, 10, 10, 10, 10
						
					},
					{	
						 2,  7,  7, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 3,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 3,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 4,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 3,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 4,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 4,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 4,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 3,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 4,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 4,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 4,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 4,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 4,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 4,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10, 
						 4,  8,  8, 10,  5,  9,  9, 10,  5,  9,  9, 10,  6,  9,  9, 10
						
					},
					{	
						 2,  3,  3,  4,  3,  4,  4,  4,  3,  4,  4,  4,  4,  4,  4,  4, 
						 5,  6,  6,  7,  6,  7,  7,  7,  6,  7,  7,  7,  7,  7,  7,  7, 
						 5,  6,  6,  7,  6,  7,  7,  7,  6,  7,  7,  7,  7,  7,  7,  7, 
						 8,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 
						 5,  6,  6,  7,  6,  7,  7,  7,  6,  7,  7,  7,  7,  7,  7,  7, 
						 8,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 
						 8,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 
						10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
						 5,  6,  6,  7,  6,  7,  7,  7,  6,  7,  7,  7,  7,  7,  7,  7, 
						 8,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 
						 8,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 
						10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
						 8,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 
						10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
						10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
						10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10
						
					}
	};

	unsigned char Data::state_signbit[256] = {	
						11, 12, 12, 12, 14, 15, 15, 15, 14, 15, 15, 15, 14, 15, 15, 15, 
						11, 12, 12, 11, 14, 13, 15, 14, 14, 13, 15, 14, 14, 13, 15, 14, 
						11, 12, 12, 11, 14, 15, 13, 14, 14, 15, 13, 14, 14, 15, 13, 14, 
						11, 12, 12, 12, 14, 13, 13, 13, 14, 13, 13, 13, 14, 13, 13, 13, 
						11, 12, 12, 12, 14, 13, 13, 13, 14, 15, 15, 15, 11, 12, 12, 12, 
						11, 12, 12, 11, 14, 15, 13, 14, 14, 13, 15, 14, 11, 12, 12, 11, 
						11, 12, 12, 11, 14, 13, 15, 14, 14, 15, 13, 14, 11, 12, 12, 11, 
						11, 12, 12, 12, 14, 15, 15, 15, 14, 13, 13, 13, 11, 12, 12, 12, 
						11, 12, 12, 12, 14, 15, 15, 15, 14, 13, 13, 13, 11, 12, 12, 12, 
						11, 12, 12, 11, 14, 13, 15, 14, 14, 15, 13, 14, 11, 12, 12, 11, 
						11, 12, 12, 11, 14, 15, 13, 14, 14, 13, 15, 14, 11, 12, 12, 11, 
						11, 12, 12, 12, 14, 13, 13, 13, 14, 15, 15, 15, 11, 12, 12, 12, 
						11, 12, 12, 12, 14, 13, 13, 13, 14, 13, 13, 13, 14, 13, 13, 13, 
						11, 12, 12, 11, 14, 15, 13, 14, 14, 15, 13, 14, 14, 15, 13, 14, 
						11, 12, 12, 11, 14, 13, 15, 14, 14, 13, 15, 14, 14, 13, 15, 14, 
						11, 12, 12, 12, 14, 15, 15, 15, 14, 15, 15, 15, 14, 15, 15, 15
						
	};

	unsigned char Data::state_XORBit[256] = {	
						 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
						 0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
						 0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
						 0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
						 0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0, 
						 0,  1,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  0,  0, 
						 0,  0,  1,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  1,  0, 
						 0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1, 
						 0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0, 
						 0,  1,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  1,  0,  0, 
						 0,  0,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  1,  0, 
						 0,  1,  1,  1,  0,  0,  0,  0,  1,  1,  1,  1,  0,  1,  1,  1, 
						 0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
						 0,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
						 0,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
						 0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1					
	};

	Data::~Data()
	{
		if(free_void){
			delete[] state;
			delete[] data_int;
			free_pointer	= NULL;
			data_float		= NULL;	
		}
	}

	//  Operation: Data
	//
	//  Description:
	//   
	//  Parameters:
	//      sizeX	
	//      sizeY	
	//


	Data::Data(unsigned int sizeX, unsigned int sizeY)
	{
		initDate(sizeX, sizeY, 0, sizeX, 0, sizeY);
		zero_fill();
		decoder		= NULL;
		initdecoder = false;
		codeword	= NULL;
	}
	
	Data::Data(unsigned int sizeX, unsigned int sizeY, unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1)
	{
		initDate(sizeX, sizeY, x0, x1, y0, y1);
		zero_fill();
		decoder		= NULL;
		initdecoder	= false;
		codeword	= NULL;
	}

	Data::Data(Data *data, unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1)
	{
		initDate(data, x0, x1, y0, y1);
		decoder		= NULL;
		initdecoder	= false;
		codeword	= NULL;
	}

	void Data::set_state_zero()
	{
		unsigned int end_pointer_row, point;

		for(point = start_pointer; point < end_pointer; point += line_feed){
			end_pointer_row = point + size_x;
			for(;point < end_pointer_row; point++){
				state[point] = 0; 
			}
		}
	}

	//  Operation: random_fill
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Data::random_fill()
	{
		unsigned int end_pointer_row, point;
		srand(8);
		for(point = start_pointer; point < end_pointer; point += line_feed){
			end_pointer_row = point + size_x;
			for(;point < end_pointer_row; point++){
				data_int[point] = (rand() % 3333)  ; 
				if(rand()%2 == 1 && data_int[point] != 0){
					data_int[point] |= 0x80000000;
				}
			}
		}
	}

	//  Operation: random_fill
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Data::random_fill_float()
	{
		unsigned int end_pointer_row, point;
		srand(8);
		for(point = start_pointer; point < end_pointer; point += line_feed){
			end_pointer_row = point + size_x;
			for(;point < end_pointer_row; point++){
				data_float[point] = (float)(rand() % 3333)  ; 
			}
		}
	}

	void Data::zero_fill()
	{
		unsigned int end_pointer_row, point;
		for(point = start_pointer; point < end_pointer; point += line_feed){
			end_pointer_row = point + size_x;
			for(;point < end_pointer_row; point++){
				data_int[point] = 0;
			}
		}
	}

	//  Operation: significance_propagation_encoding_pass
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Data::significance_propagation_encoding_pass()
	{
		unsigned int row_pips, extra_row, offset_D0, offset_D1, offset_D2, offset_D3, offset_V0, offset_V1, offset_H0, offset_H1;
		
		unsigned int start_row, end_row, y, x, row, y_start, y_end, sign_state, sign;
		unsigned int base_pointer, run_pointer;
		unsigned __int16 ui_state;

		row_pips	= size_y / 4;
		extra_row	= size_y % 4;
		offset_D0	= total_sizeX + 1; 
		offset_D1	= total_sizeX - 1; 
		offset_D2	= total_sizeX - 1; 
		offset_D3	= total_sizeX + 1; 
		offset_V0	= total_sizeX;
		offset_V1	= total_sizeX;
		offset_H0	= 1;
		offset_H1	= 1;
		
		
		start_row = 0;
		end_row = row_pips;


		for(row = start_row; row < end_row; row++){
			base_pointer = total_sizeX * (work_y0 + row * 4) + work_x0;
			for(x = work_x0; x < work_x1; x++, base_pointer++){
				run_pointer = base_pointer;
				y_start = row * 4;
				y_end	= y_start + 4;
				for(y = y_start; y < y_end; y++, run_pointer += total_sizeX){
					ui_state = state[run_pointer];
					if((ui_state &  SIGNIFICANT_BIT) == 0){
						if((ui_state & 0xFF) != 0){
							if((data_uint[run_pointer] & (1 << work_bitplane)) != 0){

								d_buffer->add_bit( 1);
								cx_buffer->add_byte( Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
								
								if((data_uint[run_pointer] & SIGN_BIT) != 0){
									d_buffer->add_bit( 1);
									sign = 1;
								}else{
									d_buffer->add_bit( 0);
									sign = 0;
								}
								sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
								cx_buffer->add_byte(Data::state_signbit[sign_state]);
								

								state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;

								
								set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

							}else{
								d_buffer->add_bit( 0);
								cx_buffer->add_byte( Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
								state[run_pointer]		|= ISCODED_BIT;
							}
						}
					}
				}
			}
		}
		if(extra_row != 0){
			base_pointer = total_sizeX * (work_y0 + end_row * 4) + work_x0;
			for(x = work_x0; x < work_x1; x++, base_pointer++){
				run_pointer = base_pointer;
				y_start = end_row * 4;
				y_end	= y_start + extra_row;
				for(y = y_start; y < y_end; y++, run_pointer += total_sizeX){
					ui_state = state[run_pointer];
					if((ui_state &  SIGNIFICANT_BIT) == 0){
						if((ui_state & 0xFF) != 0){
							if((data_uint[run_pointer] & (1 << work_bitplane)) != 0){

								d_buffer->add_bit(1);
								cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
								state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;

								if((data_uint[run_pointer] & SIGN_BIT) != 0){
									d_buffer->add_bit(1);
									sign = 1;
								}else{
									d_buffer->add_bit(0);
									sign = 0;
								}
								sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
								cx_buffer->add_byte(Data::state_signbit[sign_state]);
								

								set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

							}else{
								d_buffer->add_bit(0);
								cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
								state[run_pointer]		|= ISCODED_BIT;
								
							}
						}
					}
				}
			}
		}

	}

	void Data::set_state(unsigned int sign,unsigned int x, unsigned int y, unsigned int run_pointer, unsigned int offset_D0, unsigned int offset_D1, unsigned int offset_D2, unsigned int offset_D3, unsigned int offset_H0, unsigned int offset_H1, unsigned int offset_V0, unsigned int offset_V1)
	{
		unsigned __int16 h0_sign, h1_sign, v0_sign, v1_sign;
		if(sign != 0){
			h0_sign = H0_sign_BIT;
			h1_sign = H1_sign_BIT;
			v0_sign = V0_sign_BIT;
			v1_sign = V1_sign_BIT;

		}else{
			h0_sign = 0;
			h1_sign = 0;
			v0_sign = 0;
			v1_sign = 0;
		}

		if(x > work_x0){
			if(x < work_x1 - 1){
				if(y > work_y0){
					if(y < work_y1 - 1){
						state[run_pointer + offset_D0] |= D0_BIT;
						state[run_pointer + offset_D1] |= D1_BIT;
						state[run_pointer - offset_D2] |= D2_BIT;
						state[run_pointer - offset_D3] |= D3_BIT;
						state[run_pointer + offset_H0] |= H0_BIT | h0_sign;
						state[run_pointer - offset_H1] |= H1_BIT | h1_sign;
						state[run_pointer + offset_V0] |= V0_BIT | v0_sign;
						state[run_pointer - offset_V1] |= V1_BIT | v1_sign;
					}else{
						state[run_pointer - offset_D2] |= D2_BIT;
						state[run_pointer - offset_D3] |= D3_BIT;
						state[run_pointer + offset_H0] |= H0_BIT | h0_sign;
						state[run_pointer - offset_H1] |= H1_BIT | h1_sign;
						state[run_pointer - offset_V1] |= V1_BIT | v1_sign;
					}
				}else{
					if(y < work_y1 - 1){
						state[run_pointer + offset_D0] |= D0_BIT;
						state[run_pointer + offset_D1] |= D1_BIT;
						state[run_pointer + offset_H0] |= H0_BIT | h0_sign;
						state[run_pointer - offset_H1] |= H1_BIT | h1_sign;
						state[run_pointer + offset_V0] |= V0_BIT | v0_sign;
					}else{
						state[run_pointer + offset_H0] |= H0_BIT | h0_sign;
						state[run_pointer - offset_H1] |= H1_BIT | h1_sign;
					}
				}
			}else{
				if(y > work_y0){
					if(y < work_y1 - 1){
						state[run_pointer + offset_D1] |= D1_BIT;
						state[run_pointer - offset_D3] |= D3_BIT;
						state[run_pointer - offset_H1] |= H1_BIT | h1_sign;
						state[run_pointer + offset_V0] |= V0_BIT | v0_sign;
						state[run_pointer - offset_V1] |= V1_BIT | v1_sign;
					}else{
						state[run_pointer - offset_D3] |= D3_BIT;
						state[run_pointer - offset_H1] |= H1_BIT | h1_sign;
						state[run_pointer - offset_V1] |= V1_BIT | v1_sign;
					}
				}else{
					if(y < work_y1 - 1){
						state[run_pointer + offset_D1] |= D1_BIT;
						state[run_pointer - offset_H1] |= H1_BIT | h1_sign;
						state[run_pointer + offset_V0] |= V0_BIT | v0_sign;
					}else{
						state[run_pointer - offset_H1] |= H1_BIT | h1_sign;
					}
				}
			}
		}else{
			if(x < work_x1 - 1){
				if(y > work_y0){
					if(y < work_y1 - 1){
						state[run_pointer + offset_D0] |= D0_BIT;
						state[run_pointer - offset_D2] |= D2_BIT;
						state[run_pointer + offset_H0] |= H0_BIT | h0_sign;
						state[run_pointer + offset_V0] |= V0_BIT | v0_sign;
						state[run_pointer - offset_V1] |= V1_BIT | v1_sign;
					}else{
						state[run_pointer - offset_D2] |= D2_BIT;
						state[run_pointer + offset_H0] |= H0_BIT | h0_sign;
						state[run_pointer - offset_V1] |= V1_BIT | v1_sign;
					}
				}else{
					if(y < work_y1 - 1){
						state[run_pointer + offset_D0] |= D0_BIT;
						state[run_pointer + offset_H0] |= H0_BIT | h0_sign;
						state[run_pointer + offset_V0] |= V0_BIT | v0_sign;
					}else{
						state[run_pointer + offset_H0] |= H0_BIT | h0_sign;
					}
				}
			}else{
				if(y > work_y0){
					if(y < work_y1 - 1){
						state[run_pointer + offset_V0] |= V0_BIT | v0_sign;
						state[run_pointer - offset_V1] |= V1_BIT | v1_sign;
					}else{
						state[run_pointer - offset_V1] |= V1_BIT | v1_sign;
					}
				}else{
					if(y < work_y1 - 1){
						state[run_pointer + offset_V0] |= V0_BIT | v0_sign;
					}else{
						;
					}
				}
			}
		}
	}
	//  Operation: significance_propagation_decoding_pass
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Data::significance_propagation_decoding_pass()
	{
		unsigned int row_pips, extra_row, offset_D0, offset_D1, offset_D2, offset_D3, offset_V0, offset_V1, offset_H0, offset_H1;
		
		unsigned int start_row, end_row, y, x, row, y_start, y_end, sign_state, sign;
		unsigned int base_pointer, run_pointer;
		unsigned __int16 ui_state;
		unsigned char  bit, bit_sign;

		row_pips	= size_y / 4;
		extra_row	= size_y % 4;
		offset_D0	= total_sizeX + 1; 
		offset_D1	= total_sizeX - 1; 
		offset_D2	= total_sizeX - 1; 
		offset_D3	= total_sizeX + 1; 
		offset_V0	= total_sizeX;
		offset_V1	= total_sizeX;
		offset_H0	= 1;
		offset_H1	= 1;
		
		
		start_row = 0;
		end_row = row_pips;


		for(row = start_row; row < end_row; row++){
			base_pointer = total_sizeX * (work_y0 + row * 4) + work_x0;
			for(x = work_x0; x < work_x1; x++, base_pointer++){
				run_pointer = base_pointer;
				y_start = row * 4;
				y_end	= y_start + 4;
				for(y = y_start; y < y_end; y++, run_pointer += total_sizeX){
					ui_state = state[run_pointer];
					if((ui_state &  SIGNIFICANT_BIT) == 0){
						if((ui_state & 0xFF) != 0){						
							//cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
							//bit = d_buffer->get_next_bit(BITSTUFFING);
							bit = decoder->decoder(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
							if(bit != 0){
								data_uint[run_pointer] |= SETBIT1 | SETBIT2; //(1 << work_bitplane);
								sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
								//cx_buffer->add_byte(Data::state_signbit[sign_state]);
								//bit_sign =  d_buffer->get_next_bit(BITSTUFFING);;
								bit_sign = decoder->decoder(Data::state_signbit[sign_state]);
								bit_sign ^= Data::state_XORBit[sign_state];

								if(bit_sign != 0){
									data_uint[run_pointer] |= SIGN_BIT;
								}
								
								sign = bit_sign;
								set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);
								state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;
							}else{
								state[run_pointer]		|= ISCODED_BIT;
							}
						}
					}
				}
			}
		}
		if(extra_row != 0){
			base_pointer = total_sizeX * (work_y0 + end_row * 4) + work_x0;
			for(x = work_x0; x < work_x1; x++, base_pointer++){
				run_pointer = base_pointer;
				y_start = end_row * 4;
				y_end	= y_start + extra_row;
				for(y = y_start; y < y_end; y++, run_pointer += total_sizeX){
					ui_state = state[run_pointer];
					if((ui_state &  SIGNIFICANT_BIT) == 0){
						if((ui_state & 0xFF) != 0){						
							//cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
							//bit =  d_buffer->get_next_bit(BITSTUFFING);
							bit = decoder->decoder(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
							
							if(bit != 0){
								data_uint[run_pointer] |= SETBIT1 | SETBIT2; // (1 << work_bitplane);
								sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
								//cx_buffer->add_byte(Data::state_signbit[sign_state]);
								//bit_sign =  d_buffer->get_next_bit(BITSTUFFING);;
								bit_sign = decoder->decoder(Data::state_signbit[sign_state]);
								bit_sign ^= Data::state_XORBit[sign_state];

								if(bit_sign != 0){
									data_uint[run_pointer] |= SIGN_BIT;
								}
								
								sign = bit_sign;
								set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);
								state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;
							}else{
								state[run_pointer]		|= ISCODED_BIT;
							}
						}
					}
				}
			}
		}
	}

	//  Operation: sign_bit_encoding
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Data::sign_bit_encoding()
	{
	}

	//  Operation: sign_bit_decoding
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Data::sign_bit_decoding()
	{
	}

	//  Operation: magnitude_refinement_encoding_pass
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Data::magnitude_refinement_encoding_pass()
	{
		unsigned int row_pips, extra_row;
		unsigned int start_row, end_row, y, x, row, y_start, y_end;
		unsigned int base_pointer, run_pointer;
		unsigned __int16 ui_state;

		row_pips	= size_y / 4;
		extra_row	= size_y % 4;

		
		
		start_row = 0;
		end_row = row_pips;


		for(row = start_row; row < end_row; row++){
			base_pointer = total_sizeX * (work_y0 + row * 4) + work_x0;
			for(x = work_x0; x < work_x1; x++, base_pointer++){
				run_pointer = base_pointer;
				y_start = row * 4;
				y_end	= y_start + 4;
				for(y = y_start; y < y_end; y++, run_pointer += total_sizeX){
					ui_state = state[run_pointer];
					if((ui_state & (SIGNIFICANT_BIT | ISCODED_BIT)) == SIGNIFICANT_BIT){
						if((ui_state & REFINEMENT_BIT) == REFINEMENT_BIT){
							if((data_uint[run_pointer] & (1 << work_bitplane)) != 0){
								d_buffer->add_bit(1);
							}else{
								d_buffer->add_bit(0);
							}
							cx_buffer->add_byte(MAGNITUT_STATE3);
						
						}else{
							if((data_uint[run_pointer] & (1 << work_bitplane)) != 0){
								d_buffer->add_bit(1);
							}else{
								d_buffer->add_bit(0);
							}
							if((ui_state & 0xFF) == 0){
								cx_buffer->add_byte(MAGNITUT_STATE1);
							}else{
								cx_buffer->add_byte(MAGNITUT_STATE2);
							}
							state[run_pointer] |= REFINEMENT_BIT;
						}
					}
				}
			}
		}
		if(extra_row != 0){
			base_pointer = total_sizeX * (work_y0 + end_row * 4) + work_x0;
			for(x = work_x0; x < work_x1; x++, base_pointer++){
				run_pointer = base_pointer;
				y_start = row_pips * 4;
				y_end	= y_start + extra_row;
				for(y = y_start; y < y_end; y++, run_pointer += total_sizeX){
					ui_state = state[run_pointer];
					if((ui_state & (SIGNIFICANT_BIT | ISCODED_BIT)) == SIGNIFICANT_BIT){
						if((ui_state & REFINEMENT_BIT) == REFINEMENT_BIT){
							if((data_uint[run_pointer] & (1 << work_bitplane)) != 0){
								d_buffer->add_bit(1);
							}else{
								d_buffer->add_bit(0);
							}
							cx_buffer->add_byte(MAGNITUT_STATE3);
							
						}else{
							if((data_uint[run_pointer] & (1 << work_bitplane)) != 0){
								d_buffer->add_bit(1);
							}else{
								d_buffer->add_bit(0);
							}
							if((ui_state & 0xFF) == 0){
								cx_buffer->add_byte(MAGNITUT_STATE1);
							}else{
								cx_buffer->add_byte(MAGNITUT_STATE2);
							}
							state[run_pointer] |= REFINEMENT_BIT;
						}
					}
				}
			}
		}
	}

	//  Operation: magnitude_refinement_decoding_pass
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Data::magnitude_refinement_decoding_pass()
	{
		unsigned int row_pips, extra_row;
		unsigned int start_row, end_row, y, x, row, y_start, y_end;
		unsigned int base_pointer, run_pointer;
		unsigned __int16 ui_state;
		unsigned char  bit;

		row_pips	= size_y / 4;
		extra_row	= size_y % 4;

		
		
		start_row = 0;
		end_row = row_pips;


		for(row = start_row; row < end_row; row++){
			base_pointer = total_sizeX * (work_y0 + row * 4) + work_x0;
			for(x = work_x0; x < work_x1; x++, base_pointer++){
				run_pointer = base_pointer;
				y_start = row * 4;
				y_end	= y_start + 4;
				for(y = y_start; y < y_end; y++, run_pointer += total_sizeX){
					ui_state = state[run_pointer];
					if((ui_state & (SIGNIFICANT_BIT | ISCODED_BIT)) == SIGNIFICANT_BIT){
						if((ui_state & REFINEMENT_BIT) == REFINEMENT_BIT){
							//cx_buffer->add_byte(MAGNITUT_STATE3);
							//bit = d_buffer->get_next_bit(BITSTUFFING);
							bit = decoder->decoder(MAGNITUT_STATE3);

							if(bit  == 1){
								data_uint[run_pointer] |= SETBIT1 | SETBIT2; // (1 << work_bitplane);
							}else{
								data_uint[run_pointer] &= UNSETBIT;
								data_uint[run_pointer] |= SETBIT2;
							}
							
						}else{

							if((ui_state & 0xFF) == 0){
								//cx_buffer->add_byte(MAGNITUT_STATE1);
								//bit = d_buffer->get_next_bit(BITSTUFFING)
								bit = decoder->decoder(MAGNITUT_STATE1);
							}else{
								//cx_buffer->add_byte(MAGNITUT_STATE2);
								//bit = d_buffer->get_next_bit(BITSTUFFING)
								bit = decoder->decoder(MAGNITUT_STATE2);
							}
							if(bit  == 1){
								data_uint[run_pointer] |= SETBIT1 | SETBIT2; // (1 << work_bitplane);
							}else{
								data_uint[run_pointer] &= UNSETBIT;
								data_uint[run_pointer] |= SETBIT2;
							}
							state[run_pointer] |= REFINEMENT_BIT;
						}
					}
				}
			}
		}
		if(extra_row != 0){
			base_pointer = total_sizeX * (work_y0 + row_pips * 4) + work_x0;
			for(x = work_x0; x < work_x1; x++, base_pointer++){
				run_pointer = base_pointer;
				y_start = row_pips * 4;
				y_end	= y_start + extra_row;
				for(y = y_start; y < y_end; y++, run_pointer += total_sizeX){
					ui_state = state[run_pointer];
					if((ui_state & (SIGNIFICANT_BIT | ISCODED_BIT)) == SIGNIFICANT_BIT){
						if((ui_state & REFINEMENT_BIT) == REFINEMENT_BIT){
							//cx_buffer->add_byte(MAGNITUT_STATE3);
							//bit = d_buffer->get_next_bit(BITSTUFFING)
							bit = decoder->decoder(MAGNITUT_STATE3);
							if(bit  == 1){
								data_uint[run_pointer] |= SETBIT1 | SETBIT2; // (1 << work_bitplane);
							}else{
								data_uint[run_pointer] &= UNSETBIT;
								data_uint[run_pointer] |= SETBIT2;
							}
							
						}else{

							if((ui_state & 0xFF) == 0){
								//cx_buffer->add_byte(MAGNITUT_STATE1);
								//bit = d_buffer->get_next_bit(BITSTUFFING)
								bit = decoder->decoder(MAGNITUT_STATE1);
							}else{
								//cx_buffer->add_byte(MAGNITUT_STATE1);
								//bit = d_buffer->get_next_bit(BITSTUFFING)
								bit = decoder->decoder(MAGNITUT_STATE2);
							}
							if(bit  == 1){
								data_uint[run_pointer] |= SETBIT1 | SETBIT2; // (1 << work_bitplane);
							}else{
								data_uint[run_pointer] &= UNSETBIT;
								data_uint[run_pointer] |= SETBIT2;
							}
							state[run_pointer] |= REFINEMENT_BIT;
						}
					}
				}
			}
		}
	}

	//  Operation: cleanup_encoding_pass
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Data::cleanup_encoding_pass()
	{
		unsigned int row_pips, extra_row, offset_D0, offset_D1, offset_D2, offset_D3, offset_V0, offset_V1, offset_H0, offset_H1;

		unsigned int start_row, end_row, y, x, row, y_start, y_end, contexts, ui_help, run_length, sign_state, sign;
		unsigned int base_pointer, run_pointer, base_pointer_1, base_pointer_2, base_pointer_3 ;
		unsigned __int16 ui_state;

		row_pips	= size_y / 4;
		extra_row	= size_y % 4;
		offset_D0	= total_sizeX + 1; 
		offset_D1	= total_sizeX - 1; 
		offset_D2	= total_sizeX - 1; 
		offset_D3	= total_sizeX + 1; 
		offset_V0	= total_sizeX;
		offset_V1	= total_sizeX;
		offset_H0	= 1;
		offset_H1	= 1;
		
		
		start_row = 0;
		end_row = row_pips;


		for(row = start_row; row < end_row; row++){
			base_pointer = total_sizeX * (work_y0 + row * 4) + work_x0;
			for(x = work_x0; x < work_x1; x++, base_pointer++){
				run_pointer = base_pointer;
				y_start = row * 4;
				y_end	= y_start + 4;
				ui_state = state[run_pointer];
				base_pointer_1 = base_pointer + total_sizeX;
				base_pointer_2 = base_pointer_1 + total_sizeX;
				base_pointer_3 = base_pointer_2 + total_sizeX;;

				contexts = (ui_state & 0xFF) + 	(state[base_pointer_1] & 0xFF) + (state[base_pointer_2] & 0xFF)  + (state[base_pointer_3] & 0xFF);

				if(contexts == 0){

					for(y = y_start,run_length = 0; y < y_end; y++, run_pointer += total_sizeX){
						ui_help = 1 << work_bitplane;
						if((data_uint[run_pointer] & ui_help) == 0){
							run_length++;
						}else{
							break;
						}
					}
					run_pointer = base_pointer;

					switch(run_length){
						case 0:
							d_buffer->add_bit(1);
							cx_buffer->add_byte(RUNLENGTH);
							
							d_buffer->add_bit(0);
							cx_buffer->add_byte(UNIFORM);
							
							d_buffer->add_bit(0);
							cx_buffer->add_byte(UNIFORM);
							
							y =  y_start;
							ui_state = state[run_pointer];
							if((data_uint[run_pointer] & SIGN_BIT) != 0){
								d_buffer->add_bit(1);
								sign = 1;
							}else{
								d_buffer->add_bit(0);
								sign = 0;
							}
							sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
							cx_buffer->add_byte(Data::state_signbit[sign_state]);

							state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;

							
							set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

							break;
						case 1:
							d_buffer->add_bit(1);
							cx_buffer->add_byte(RUNLENGTH);
							
							d_buffer->add_bit(0);
							cx_buffer->add_byte(UNIFORM);
							
							d_buffer->add_bit(1);
							cx_buffer->add_byte(UNIFORM);
							
							run_pointer += total_sizeX;
							y =  y_start + 1;
							ui_state = state[run_pointer];
							if((data_uint[run_pointer] & SIGN_BIT) != 0){
								d_buffer->add_bit(1);
								sign = 1;
							}else{
								d_buffer->add_bit(0);
								sign = 0;
							}
							sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
							cx_buffer->add_byte(Data::state_signbit[sign_state]);

							state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;

						
							set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

							break;
						case 2:
							d_buffer->add_bit(1);
							cx_buffer->add_byte(RUNLENGTH);
							
							d_buffer->add_bit(1);
							cx_buffer->add_byte(UNIFORM);
							
							d_buffer->add_bit(0);
							cx_buffer->add_byte(UNIFORM);
							
							run_pointer += 2 * total_sizeX;
							y =  y_start + 2;
							ui_state = state[run_pointer];
							if((data_uint[run_pointer] & SIGN_BIT) != 0){
								d_buffer->add_bit(1);
								sign = 1;
							}else{
								d_buffer->add_bit(0);
								sign = 0;
							}
							sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
							cx_buffer->add_byte(Data::state_signbit[sign_state]);

							state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;

							
							set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

							break;
						case 3:
							d_buffer->add_bit(1);
							cx_buffer->add_byte(RUNLENGTH);
							
							d_buffer->add_bit(1);
							cx_buffer->add_byte(UNIFORM);
							
							d_buffer->add_bit(1);
							cx_buffer->add_byte(UNIFORM);
							
							run_pointer += 3 * total_sizeX;
							y =  y_start + 3;
							ui_state = state[run_pointer];
							if((data_uint[run_pointer] & SIGN_BIT) != 0){
								d_buffer->add_bit(1);
								sign = 1;
							}else{
								d_buffer->add_bit(0);
								sign = 0;
							}
							sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
							cx_buffer->add_byte(Data::state_signbit[sign_state]);

							state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;

							
							set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

							break;
						case 4:
							d_buffer->add_bit(0);
							cx_buffer->add_byte(RUNLENGTH);
							
							break;
					}

					y += 1;
					run_pointer += total_sizeX;
					for(; y < y_end; y++, run_pointer += total_sizeX){
						ui_state = state[run_pointer];
						if((ui_state &  (SIGNIFICANT_BIT | ISCODED_BIT)) == 0){
							if((data_uint[run_pointer] & (1 << work_bitplane)) != 0){

								d_buffer->add_bit(1);
								cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
								state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;
								
								if((data_uint[run_pointer] & SIGN_BIT) != 0){
									d_buffer->add_bit(1);
									sign = 1;
								}else{
									d_buffer->add_bit(0);
									sign = 0;
								}
								sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
								cx_buffer->add_byte(Data::state_signbit[sign_state]);
								

								set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

							}else{
								d_buffer->add_bit(0);
								cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
								state[run_pointer]		|= ISCODED_BIT;
							
							}							
						}
					}	

				}else{
					for(y = y_start ; y < y_end; y++, run_pointer += total_sizeX){
						ui_state = state[run_pointer];
						if((ui_state &  (SIGNIFICANT_BIT | ISCODED_BIT)) == 0){
							if((data_uint[run_pointer] & (1 << work_bitplane)) != 0){

								d_buffer->add_bit(1);
								cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
								state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;
								
								if((data_uint[run_pointer] & SIGN_BIT) != 0){
									d_buffer->add_bit(1);
									sign = 1;
								}else{
									d_buffer->add_bit(0);
									sign = 0;
								}
								sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
								cx_buffer->add_byte(Data::state_signbit[sign_state]);
								

								set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

							}else{
								d_buffer->add_bit(0);
								cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
								state[run_pointer]		|= ISCODED_BIT;
								
							}
						}
					}	
				}
			}
		}
		if(extra_row != 0){
			base_pointer = total_sizeX * (work_y0 + row_pips * 4) + work_x0;
			for(x = work_x0; x < work_x1; x++, base_pointer++){
				run_pointer = base_pointer;
				y_start = row * 4;
				y_end	= y_start + extra_row;
				for(y = y_start ; y < y_end; y++, run_pointer += total_sizeX){
					ui_state = state[run_pointer];
					if((ui_state &  (SIGNIFICANT_BIT | ISCODED_BIT)) == 0){
						if((data_uint[run_pointer] & (1 << work_bitplane)) != 0){

							d_buffer->add_bit(1);
							cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
							state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;
							
							if((data_uint[run_pointer] & SIGN_BIT) != 0){
								d_buffer->add_bit(1);
								sign = 1;
							}else{
								d_buffer->add_bit(0);
								sign = 0;
							}
							sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
							cx_buffer->add_byte(Data::state_signbit[sign_state]);
							
							set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

						}else{
							d_buffer->add_bit(0);
							cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
							state[run_pointer]		|= ISCODED_BIT;
							
						}
					}
				}
			}
		}
	}

	//  Operation: cleanup_decoding_pass
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Data::cleanup_decoding_pass()
	{
		unsigned int row_pips, extra_row, offset_D0, offset_D1, offset_D2, offset_D3, offset_V0, offset_V1, offset_H0, offset_H1;

		unsigned int start_row, end_row, y, x, row, y_start, y_end, contexts, run_length, sign_state, sign;
		unsigned int base_pointer, run_pointer, base_pointer_1, base_pointer_2, base_pointer_3 ;
		unsigned __int16 ui_state;
		unsigned char bit, sign_bit, bit_sign;

		row_pips	= size_y / 4;
		extra_row	= size_y % 4;
		offset_D0	= total_sizeX + 1; 
		offset_D1	= total_sizeX - 1; 
		offset_D2	= total_sizeX - 1; 
		offset_D3	= total_sizeX + 1; 
		offset_V0	= total_sizeX;
		offset_V1	= total_sizeX;
		offset_H0	= 1;
		offset_H1	= 1;
		
		
		start_row = 0;
		end_row = row_pips;


		for(row = start_row; row < end_row; row++){
			base_pointer = total_sizeX * (work_y0 + row * 4) + work_x0;
			for(x = work_x0; x < work_x1; x++, base_pointer++){
				run_pointer = base_pointer;
				y_start = row * 4;
				y_end	= y_start + 4;
				ui_state = state[run_pointer];
				base_pointer_1 = base_pointer + total_sizeX;
				base_pointer_2 = base_pointer_1 + total_sizeX;
				base_pointer_3 = base_pointer_2 + total_sizeX;;

				contexts = (ui_state & 0xFF) + 	(state[base_pointer_1] & 0xFF) + (state[base_pointer_2] & 0xFF)  + (state[base_pointer_3] & 0xFF);

				if(contexts == 0){
					run_length = 0;
					//bit = d_buffer->get_next_bit(BITSTUFFING); ;
					//cx_buffer->add_byte(RUNLENGTH);
					bit = decoder->decoder(RUNLENGTH);

					if(bit != 0){
							
							//cx_buffer->add_byte(UNIFORM);
							//bit = d_buffer->get_next_bit(BITSTUFFING);
							bit = decoder->decoder(UNIFORM);
							if(bit  != 0){
								run_length = 2;
							}
							
							//cx_buffer->add_byte(UNIFORM);
							//bit = d_buffer->get_next_bit(BITSTUFFING);
							bit = decoder->decoder(UNIFORM);
							if(bit != 0){
								run_length |= 1;
							}
					}else{
						run_length = 4;
					}

					switch(run_length){
						case 0:
							y =  y_start;

							sign_state	= (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
							//cx_buffer->add_byte(Data::state_signbit[sign_state]);
							//sign_bit	= d_buffer->get_next_bit(BITSTUFFING); ;
							sign_bit = decoder->decoder(Data::state_signbit[sign_state]);
							bit_sign ^= Data::state_XORBit[sign_state];

							if(sign_bit != 0){
								sign = 1;
								data_uint[run_pointer] |= SIGN_BIT;
							}else{
								sign = 0;
							}
							data_uint[run_pointer] |= SETBIT1 | SETBIT2; // (1 << work_bitplane);
							state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;
							set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

							break;
						case 1:
	
							run_pointer += total_sizeX;
							y =  y_start + 1;


							sign_state	= (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
							//cx_buffer->add_byte(Data::state_signbit[sign_state]);
							//sign_bit	= d_buffer->get_next_bit(BITSTUFFING); ;
							sign_bit = decoder->decoder(Data::state_signbit[sign_state]);
							bit_sign ^= Data::state_XORBit[sign_state];

							if(sign_bit != 0){
								sign = 1;
								data_uint[run_pointer] |= SIGN_BIT;
							}else{
								sign = 0;
							}
							data_uint[run_pointer] |= SETBIT1 | SETBIT2; // (1 << work_bitplane);
							state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;
							set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

							break;
						case 2:

							run_pointer += 2 * total_sizeX;
							y =  y_start + 2;

							sign_state	= (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
							//cx_buffer->add_byte(Data::state_signbit[sign_state]);
							//sign_bit	= d_buffer->get_next_bit(BITSTUFFING); ;
							sign_bit = decoder->decoder(Data::state_signbit[sign_state]);
							bit_sign ^= Data::state_XORBit[sign_state];

							if(sign_bit != 0){
								sign = 1;
								data_uint[run_pointer] |= SIGN_BIT;
							}else{
								sign = 0;
							}
							data_uint[run_pointer] |= SETBIT1 | SETBIT2; // (1 << work_bitplane);
							state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;
							set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

							break;
						case 3:
	
							run_pointer += 3 * total_sizeX;
							y =  y_start + 3;
							sign_state	= (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
							//cx_buffer->add_byte(Data::state_signbit[sign_state]);
							//sign_bit	= d_buffer->get_next_bit(BITSTUFFING); ;
							sign_bit = decoder->decoder(Data::state_signbit[sign_state]);
							bit_sign ^= Data::state_XORBit[sign_state];

							if(sign_bit != 0){
								sign = 1;
								data_uint[run_pointer] |= SIGN_BIT;
							}else{
								sign = 0;
							}
							data_uint[run_pointer] |= SETBIT1 | SETBIT2; // (1 << work_bitplane);
							state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;
							set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);

							break;

						case 4:
							run_pointer += 4 * total_sizeX;
							y =  y_start + 4;
							break;
					}

					y += 1;
					run_pointer += total_sizeX;
					for(; y < y_end; y++, run_pointer += total_sizeX){
						ui_state = state[run_pointer];
						if((ui_state &  (SIGNIFICANT_BIT | ISCODED_BIT)) == 0){
							//cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
							//bit = d_buffer->get_next_bit(BITSTUFFING);;
							bit = decoder->decoder(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);

							if(bit != 0){
								data_uint[run_pointer] |= SETBIT1 | SETBIT2; //  (1 << work_bitplane);
								sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
								//cx_buffer->add_byte(Data::state_signbit[sign_state]);
								//bit_sign = d_buffer->get_next_bit(BITSTUFFING);;
								bit_sign = decoder->decoder(Data::state_signbit[sign_state]);
								bit_sign ^= Data::state_XORBit[sign_state];

								if(bit_sign != 0){
									data_uint[run_pointer] |= SIGN_BIT;
								}
								
								sign = bit_sign;
								set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);
								state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;
							}else{
								state[run_pointer]		|= ISCODED_BIT;
							}						
						}
					}	

				}else{
					for(y = y_start ; y < y_end; y++, run_pointer += total_sizeX){
						ui_state = state[run_pointer];
						if((ui_state &  (SIGNIFICANT_BIT | ISCODED_BIT)) == 0){
							//cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
							//bit = d_buffer->get_next_bit(BITSTUFFING);;
							bit = decoder->decoder(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);

							if(bit != 0){
								data_uint[run_pointer] |= SETBIT1 | SETBIT2; //  (1 << work_bitplane);
								sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
								//cx_buffer->add_byte(Data::state_signbit[sign_state]);
								//bit_sign = d_buffer->get_next_bit(BITSTUFFING);;
								bit_sign = decoder->decoder(Data::state_signbit[sign_state]);
								bit_sign ^= Data::state_XORBit[sign_state];

								if(bit_sign != 0){
									data_uint[run_pointer] |= SIGN_BIT;
								}
								
								sign = bit_sign;
								set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);
								state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;
							}else{
								state[run_pointer]		|= ISCODED_BIT;
							}	
						}
					}	
				}
			}
		}
		if(extra_row != 0){
			base_pointer = total_sizeX * (work_y0 + row_pips * 4) + work_x0;
			for(x = work_x0; x < work_x1; x++, base_pointer++){
				run_pointer = base_pointer;
				y_start = row_pips * 4;
				y_end	= y_start + extra_row;
				for(y = y_start ; y < y_end; y++, run_pointer += total_sizeX){
					ui_state = state[run_pointer];
					if((ui_state &  (SIGNIFICANT_BIT | ISCODED_BIT)) == 0){
						//cx_buffer->add_byte(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);
						//bit = d_buffer->get_next_bit(BITSTUFFING);;
						bit = decoder->decoder(Data::state_propagation[nr_subband][(ui_state & 0xFF)]);

						if(bit != 0){
							data_uint[run_pointer] |= SETBIT1 | SETBIT2; // (1 << work_bitplane);
							sign_state = (ui_state & 0xF) | ((ui_state >> 8) & 0xF0);
							//cx_buffer->add_byte(Data::state_signbit[sign_state]);
							//bit_sign = d_buffer->get_next_bit(BITSTUFFING);;
							bit_sign = decoder->decoder(Data::state_signbit[sign_state]);
							bit_sign ^= Data::state_XORBit[sign_state];

							if(bit_sign != 0){
								data_uint[run_pointer] |= SIGN_BIT;
							}
							
							sign = bit_sign;
							set_state(sign, x, y + work_y0, run_pointer, offset_D0, offset_D1, offset_D2, offset_D3,  offset_H0, offset_H1, offset_V0, offset_V1);
							state[run_pointer]		|= SIGNIFICANT_BIT | ISCODED_BIT;
						}else{
							state[run_pointer]		|= ISCODED_BIT;
						}	
					}
				}
			}
		}
	}

	//  Operation: inttocustomint
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Data::inttocustomint()
	{
	}

	//  Operation: custominttoint
	//
	//  Description:
	//   
	//  Parameters:
	//

	void Data::custominttoint()
	{
	}

	void Data::showData()
	{
		unsigned y,x;
		int value;
		for(y = 0; y < total_sizeY; y++){
			for(x = 0; x < total_sizeX; x++){
				cout.width(3);
				cout<<(int)state[y * total_sizeX + x];
			}
			cout<<endl;
		}
		cout<<endl;

		for(y = 0; y < total_sizeY; y++){
			for(x = 0; x < total_sizeX; x++){
				cout.width(14);
				value = data_int[y * total_sizeX + x] ;
				if((value & SIGN_BIT) == SIGN_BIT){
					value = -1 * (0x7FFFFFFF & value);
				}
				cout<<value;
			}
			cout<<endl;
		}
		cout<<endl;
	}

	void Data::showData_float()
	{
		unsigned y,x;
		float value;

		for(y = 0; y < total_sizeY; y++){
			for(x = 0; x < total_sizeX; x++){
				cout.width(9);
				value = data_float[y * total_sizeX + x] ;
				cout<<value;
			}
			cout<<endl;
		}
		cout<<endl;
	}

	void Data::initDate(unsigned int sizeX, unsigned int sizeY, unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1)
	{
		total_size = sizeX * sizeY;
		total_sizeX = sizeX;
		total_sizeY = sizeY;
		work_x0	= x0;
		work_x1 = x1;
		work_y0	= y0;
		work_y1 = y1;
		size_x	= work_x1 - work_x0;
		size_y	= work_y1 - work_y0;

		numb_bitplane = 0;

		start_pointer	= (work_y0 * total_sizeX) + work_x0;
		end_pointer		= ((work_y1 - 1)* total_sizeX) + work_x1;
		line_feed		= total_sizeX - size_x;

		data_int		= new __int32[total_size];
		free_pointer	= (void*)data_int;
		data_float		= (float*)data_int;
		data_uint		= (unsigned __int32*)data_int;

		state = new unsigned __int16[total_size];

		for(unsigned int i = 0; i <  total_size; i++){
			state[i] = 0;
		}

		free_void = true;
		set_state_zero();

		npasses = 0;
	}

	void Data::initDate(Data *data, unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1)
	{
		total_size	= data->total_size;
		total_sizeX	= data->total_sizeX;
		total_sizeY	= data->total_sizeY;

		numb_bitplane = 0;
		decodepass = CLEANUP_DECODING_PASS;

		if(data->work_x0 <= x0 && data->work_x1 >= x1 && data->work_y0 <= y0 && data->work_y1 >= y1){
			work_x0	= x0;
			work_x1 = x1;
			work_y0	= y0;
			work_y1 = y1;
			size_x	= work_x1 - work_x0;
			size_y	= work_y1 - work_y0;
		}else{
			throw new Default_Exceptionhandler(__FILE__, __LINE__, "Data out of range");
		}

		start_pointer	= (work_y0 * total_sizeX) + work_x0;
		end_pointer		= ((work_y1 - 1)* total_sizeX) + work_x1;
		line_feed		= total_sizeX - size_x;

		data_int		= data->data_int;
		free_pointer	= data->free_pointer;
		data_float		= data->data_float;
		data_uint		= data->data_uint;

		state = data->state;
		free_void = false;
		npasses = 0;
	}

	void Data::setmaximumValue()
	{
		unsigned int end_pointer_row, point;
		int value;
		maximumValue_int = 0;

		for(point = start_pointer; point < end_pointer; point += line_feed){
			end_pointer_row = point + size_x;
			for(;point < end_pointer_row; point++){
				value = data_int[point] & 0x7FFFFFFF;
				if(value > maximumValue_int){
					maximumValue_int = value;
				}
			}
		}

		for(value = 1, numb_bitplane = 0; value < 0x40000000; value <<= 1){
			if(value <= maximumValue_int){
				numb_bitplane += 1;
			}else{
				break;
			}
		}

	}

	void Data::reset_is_coded()
	{
		unsigned int end_pointer_row, point;

		for(point = start_pointer; point < end_pointer; point += line_feed){
			end_pointer_row = point + size_x;
			for(;point < end_pointer_row; point++){
				state[point] &= (0x7FFFFFFF ^ ISCODED_BIT);
			}
		}
	}

	void Data::setnumb_bitplane()
	{
		numb_bitplane = 0;
		int i;
		for(i = 0; i < 31;i++){
			if((maximumValue_int & (1 << i)) != 0){
				numb_bitplane = i + 1;
			}
		}

	}

	void  Data::start_encode_Coefficient_bit_modeling()
	{
		setmaximumValue();
		if(numb_bitplane > 0){
			work_bitplane = numb_bitplane - 1;
			cleanup_encoding_pass();
			reset_is_coded();

			work_bitplane--;
			while(work_bitplane != 0xFFFFFFFF){
				significance_propagation_encoding_pass();
				magnitude_refinement_encoding_pass();
				cleanup_encoding_pass();
				reset_is_coded();
				work_bitplane--;
			}
		}
	}

	void  Data::start_decode_Coefficient_bit_modeling()
	{
		if(numb_bitplane > 0){
			work_bitplane = numb_bitplane - 1;
			cleanup_decoding_pass();
			reset_is_coded();

			work_bitplane--;
			while(work_bitplane != 0xFFFFFFFF){
				significance_propagation_decoding_pass();
				magnitude_refinement_decoding_pass();
				cleanup_decoding_pass();
				reset_is_coded();
				work_bitplane--;
			}
		}
	}

	void  Data::start_decode_Coefficient_bit_modeling(int passes)
	{
		if(numb_bitplane > 0){

			if(initdecoder){		
				decoder->initdec(codeword, Arithmetic_entropy_encoder::j2000_length, Arithmetic_entropy_encoder::j2000_mps, Arithmetic_entropy_encoder::j2000_index);
				initdecoder = false;
			}
			npasses += passes;
			SETBIT1		= 1 << work_bitplane;
			SETBIT2		= 1 << (work_bitplane - 1);
			UNSETBIT	= 0xFFFFFFFF ^ SETBIT1;

			for(int pass = 0; pass < passes; pass++){
				if(work_bitplane != 0xFFFFFFFF){
					switch(decodepass){
						case SIGNIFICANCE_PROPAGATION_DECODING_PASS: 
							significance_propagation_decoding_pass();
							decodepass = MAGNITUDE_REFINEMENT_DECODING_PASS;
							break; 
						case MAGNITUDE_REFINEMENT_DECODING_PASS:
							magnitude_refinement_decoding_pass();
							decodepass = CLEANUP_DECODING_PASS;
							break; 
						case CLEANUP_DECODING_PASS:
							cleanup_decoding_pass();
							reset_is_coded();
							work_bitplane--;
							SETBIT1		= 1 << work_bitplane;
							SETBIT2		= 1 << (work_bitplane - 1);
							UNSETBIT	= 0xFFFFFFFF ^ SETBIT1;
							decodepass = SIGNIFICANCE_PROPAGATION_DECODING_PASS;
							break;
					}
				}else{
					throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "No Bitplane to decode" );
				}
			}
		}
	}

	void Data::initBuffer()
	{

		d_buffer	= new ByteBuffer();
		cx_buffer	= new ByteBuffer();
	}

	void Data::initBuffer(ByteBuffer* d)
	{

		d_buffer	= d;
		cx_buffer	= new ByteBuffer();
		
	}

	  void Data::set_numb_bitplane(unsigned int numb)
	  {
		  numb_bitplane = numb;	
		  work_bitplane = numb_bitplane - 1;
	  }

	  unsigned int Data::get_numb_bitplane()
	  {
			return numb_bitplane;
	  }

	  void Data::set_subband(unsigned int subband)
	  {
			nr_subband = subband;
	  }

	  void Data::compare(Data *data)
	  {
		unsigned int end_pointer_row, point;
		int value = 0;
		for(point = start_pointer; point < end_pointer; point += line_feed){
			end_pointer_row = point + size_x;
			for(;point < end_pointer_row; point++){
				value += data_int[point] - data->data_int[point];
			}
		}
		cout<<"Compare Result = "<<value<<endl;

		value = data->cx_buffer->compare_byte(cx_buffer);
		cout<<"Compare Result Byte Buffer cx = "<<value<<endl;
	  }
	
	  void Data::fill_buffer(unsigned char* buffer, unsigned int width, unsigned int height)
	  {
		  setmaximumValue();
		  unsigned int end_pointer_row, point;
		  unsigned int ptr_out = 0;
		  float difffactor = (float)250 / (float)maximumValue_int * 2;
		  float value;
		  unsigned int ui_value;


		  if(this->size_x == width && this->size_y == height){
			for(point = start_pointer; point < end_pointer; point += line_feed){
				end_pointer_row = point + size_x;
				if(end_pointer_row <= end_pointer){
					for(;point < end_pointer_row; point++){
						ui_value = data_uint[point] & 0x7FFFFFFF;
						value = (float)(ui_value);
						if((data_int[point] & 0x80000000) != 0){
							value *= -1;
						}

						value = (value * difffactor) + 125;
						buffer[ptr_out] = (unsigned char) value;
						ptr_out += 1;
						buffer[ptr_out] = (unsigned char) value;
						ptr_out += 1;
						buffer[ptr_out] = (unsigned char) value;
						ptr_out += 1;
					}
					
				}else{
					point++;
				}
			}			
		  }else{  
			  throw new Default_Exceptionhandler(__FILE__, __LINE__, "Doesn't fit.");
		  }
	  }

	  void Data::setdecoder(ByteBuffer *codeword)
	  {
		decoder			= new Arithmetic_entropy_decoder();
		initdecoder		= true;
		this->codeword	= codeword;
	  }

	  void Data::customint_to_float(float deltab)
	  {
		unsigned int end_pointer_row, point;
		int value = 0;
		float	*out_float	= this->data_float;
		int		*in_int		= this->data_int;
	
		for(point = start_pointer; point < end_pointer; point += line_feed){
			end_pointer_row = point + size_x;
			for(;point < end_pointer_row; point++){
				value = in_int[point] ;	
				out_float[point] = (float)(value & 0x7FFFFFFF) * deltab;
				if((value & SIGN_BIT) != 0){
					out_float[point] *= -1.0;
				}
			}
		}
	  }

	  void Data::filter_encode(Filter97_encoder *encoder)
	  {
		  unsigned int x, y;
		  float *in, *out_high, *out_low;
		  int sizex = work_x1 - work_x0;
		  int sizey = work_y1 - work_y0;
	
		  for(y =  work_y0, x = work_x0; y < work_y1; y++){
			in			= &data_float[y * total_sizeX + x];
			out_low		= in;
			out_high	= in + Filter97_encoder::low_lenght(evenH, sizex);
			encoder->start(	in, out_high, out_low, 
							0, sizex, 1, evenH, 
							0, 1,
							0, 1);
		  }

		  for(x =  work_x0, y = work_y0; x < work_x1; x++){
			in			= &data_float[x];
			out_low		= in;
			out_high	= in + total_sizeX * Filter97_encoder::low_lenght(evenV, sizey);
			encoder->start(	in, out_high, out_low, 
							0, sizey, total_sizeX, evenV, 
							0, total_sizeX,
							0, total_sizeX);
		  }

	  }
	  
	  
	  void Data::filter_decode(Filter97_decoder *decoder)
	  {
		  unsigned int x, y;
		  float *out, *in_high, *in_low;
		  int sizex = work_x1 - work_x0;
		  int sizey = work_y1 - work_y0;
	
		  for(y =  work_y0, x = work_x0; y < work_y1; y++){
			out			= &data_float[y * total_sizeX + x];
			in_low		= out;
			in_high		= out + Filter97_encoder::low_lenght(evenH, sizex);
			decoder->start(	out, in_high, in_low, 
							0, sizex, 1, evenH, 
							0, 1,
							0, 1);
		  }

		  for(x =  work_x0, y = work_y0; x < work_x1; x++){
			out			= &data_float[y * total_sizeX + x];
			in_low		= out;
			in_high		= out + total_sizeX * Filter97_encoder::low_lenght(evenV, sizey);
			decoder->start(	out, in_high, in_low, 
							0, sizey, total_sizeX, evenV, 
							0, total_sizeX,
							0, total_sizeX);
		  }		  //int x, y;


	  }	

	  void Data::set_even(int h, int v)
	  {
		  if(h % 2 == 0){
			evenH = true;
		  }else{
			evenH = false;
		  }

		  if(v % 2 == 0){
			evenV = true;
		  }else{
			evenV = false;
		  }
	  }
	  void Data::fill_RGBbuffer_Y(unsigned char* buffer)
	  {
		unsigned int x, y;
		unsigned int point, bufferpoint, pointy;
		float value, value_temp;

		for( y = work_y0; y < work_y1; y++){
			pointy = y * total_sizeX;
			for( x = work_x0; x < work_x1; x++){
				point = pointy + x;
				bufferpoint = point * 3;
				value = data_float[point];

				value_temp = (float)buffer[bufferpoint];
				value_temp += value;
				if(value_temp > 254.0f){
					value_temp = 254.0f;
				}
				if(value_temp < 0.0f){
					value_temp = 0.0f;
				}
				buffer[bufferpoint] = (unsigned char) value_temp;

				value_temp = (float)buffer[bufferpoint + 1];
				value_temp += value;
				if(value_temp > 254.0f){
					value_temp = 254.0f;
				}
				if(value_temp < 0.0f){
					value_temp = 0.0f;
				}
				buffer[bufferpoint + 1] = (unsigned char) value_temp;

				value_temp = (float)buffer[bufferpoint + 2];
				value_temp += value;
				if(value_temp > 254.0f){
					value_temp = 254.0f;
				}
				if(value_temp < 0.0f){
					value_temp = 0.0f;
				}
				buffer[bufferpoint + 2] = (unsigned char) value_temp;
			}
		}
	  }

	  void Data::fill_RGBbuffer(Data *dataY, Data *dataCb, Data *dataCr, unsigned char* buffer)
	  {
		unsigned int x, y, work_y0, work_y1, work_x0, work_x1, total_sizeX;
		unsigned int point, bufferpoint, pointy;
		float valueY, valueCb, valueCr, value_temp;

		if(	dataY->work_x0 == dataCb->work_x0 && dataCr->work_x0 == dataCb->work_x0 &&
			dataY->work_x1 == dataCb->work_x1 && dataCr->work_x1 == dataCb->work_x1 &&
			dataY->work_y0 == dataCb->work_y0 && dataCr->work_y0 == dataCb->work_y0 &&
			dataY->work_y1 == dataCb->work_y1 && dataCr->work_y1 == dataCb->work_y1){
				
			work_x0		= dataY->work_x0;
			work_x1		= dataY->work_x1;
			work_y0		= dataY->work_y0;
			work_y1		= dataY->work_y1;
			total_sizeX	= dataY->total_sizeX; 

			for( y = work_y0; y < work_y1; y++){
				pointy = y * total_sizeX;
				for( x = work_x0; x < work_x1; x++){
					point = pointy + x;
					bufferpoint = point * 3;
					valueY	= dataY->data_float[point];
					valueCb	= dataCb->data_float[point];
					valueCr	= dataCr->data_float[point];

					value_temp = valueY + 1.402f * valueCr + 128.0f;
					if(value_temp < 0){
						value_temp = 0;
					}
					if(value_temp > 255){
						value_temp = 255;
					}
					buffer[bufferpoint] = (unsigned char)value_temp;

					value_temp = valueY - 0.34413f * valueCb - 0.71414f * valueCr + 128.0f;
					if(value_temp < 0){
						value_temp = 0;
					}
					if(value_temp > 255){
						value_temp = 255;
					}
					buffer[bufferpoint + 1] = (unsigned char)value_temp;

					value_temp = valueY + 1.772f * valueCb + 128.0f;
					if(value_temp < 0){
						value_temp = 0;
					}
					if(value_temp > 255){
						value_temp = 255;
					}
					buffer[bufferpoint + 2] = (unsigned char)value_temp;
				}
			}
		}else{
			throw new Default_Exceptionhandler(__FILE__, __LINE__, "Tilesizes is different");
		}
	  }

	  void Data::fill_RGBbuffer_Cr(unsigned char* buffer)
	  {
		unsigned int x, y;
		unsigned int point, bufferpoint, pointy;
		float value, value_temp;

		for( y = work_y0; y < work_y1; y++){
			pointy = y * total_sizeX;
			for( x = work_x0; x < work_x1; x++){
				point = pointy + x;
				bufferpoint = point * 3;
				value = data_float[point];

				value_temp = (float)buffer[bufferpoint];
				value_temp += value * 1.402f;
				if(value_temp > 254.0f){
					value_temp = 254.0f;
				}
				if(value_temp < 0.0f){
					value_temp = 0.0f;
				}
				buffer[bufferpoint] = (unsigned char) value_temp;

				value_temp = (float)buffer[bufferpoint + 1];
				value_temp += value * -0.71414f;
				if(value_temp > 254.0f){
					value_temp = 254.0f;
				}
				if(value_temp < 0.0f){
					value_temp = 0.0f;
				}
				buffer[bufferpoint + 1] = (unsigned char) value_temp;
			}
		}
	  }

	  void Data::fill_RGBbuffer_Cb(unsigned char* buffer)
	  {
		unsigned int x, y;
		unsigned int point, bufferpoint, pointy;
		float value, value_temp;

		for( y = work_y0; y < work_y1; y++){
			pointy = y * total_sizeX;
			for( x = work_x0; x < work_x1; x++){
				point = pointy + x;
				bufferpoint = point * 3;
				value = data_float[point];

				value_temp = (float)buffer[bufferpoint + 1];
				value_temp += value * -0.34413f;
				if(value_temp > 254.0f){
					value_temp = 254.0f;
				}
				if(value_temp < 0.0f){
					value_temp = 0.0f;
				}
				buffer[bufferpoint + 1] = (unsigned char) value_temp;

				value_temp = (float)buffer[bufferpoint + 2];
				value_temp += value * 1.772f;
				if(value_temp > 254.0f){
					value_temp = 254.0f;
				}
				if(value_temp < 0.0f){
					value_temp = 0.0f;
				}
				buffer[bufferpoint + 2] = (unsigned char) value_temp;
			}
		}
	  }
}