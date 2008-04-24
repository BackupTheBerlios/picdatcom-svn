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

#define SIGNMASK1 0x80000000
#define SIGNMASK2 0x7FFFFFFF

extern int sign_context[];
extern int significant_context_LL[];
extern int significant_context_HL[];
extern int significant_context_LH[];

Default_Exceptionhandler* Data::ptr_exception = new Default_Exceptionhandler(__FILE__,__LINE__, "No Memory");

Data::~Data()
{
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
	__int8* work_pointer;
	int size,i;

	total_sizeX = sizeX;
	total_sizeY = sizeY;

	free_pointer = malloc(sizeof(__int32) * total_sizeX * total_sizeY + 32);
	if(free_pointer == NULL){
		ptr_exception->line = __LINE__ - 2;
		throw ptr_exception;
	}
	state = (unsigned __int8*)malloc(sizeof(__int8) * total_sizeX * total_sizeY);
	if(state == NULL){
		ptr_exception->line = __LINE__ - 2;
		throw ptr_exception;
	}

	work_pointer = (__int8*) free_pointer  + 16;
	work_pointer -= (int)work_pointer % 16;

	data_float	= (float*) work_pointer;
	data_int	= (__int32*)work_pointer ;
	data_uint	= (unsigned __int32*)work_pointer;

	size = total_sizeX * total_sizeY;
	for(i = 0; i < size; i++){
		data_int[i] = 0;
		state[i]	= 0;
	}

	work_x0 = 0;
	work_x1 = total_sizeX;
	work_y0 = 0;
	work_y1	= total_sizeY;
	free_void = true;

	significant_context = significant_context_LL;
}

//  Operation: Data
//
//  Description:
//   
//  Parameters:
//      Data*
//


Data::Data(Data* in)
{
	__int8* work_pointer;
	
	unsigned int length, i;

	total_sizeX = in->total_sizeX;
	total_sizeY = in->total_sizeY;

	length = total_sizeX * total_sizeY;

	free_pointer = malloc(sizeof(__int32) * total_sizeX * total_sizeY + 32);
	if(free_pointer == NULL){
		ptr_exception->line = __LINE__ - 2;
		throw ptr_exception;
	}
	state = (unsigned __int8*)malloc(sizeof(__int8) * total_sizeX * total_sizeY);
	if(state == NULL){
		ptr_exception->line = __LINE__ - 2;
		throw ptr_exception;
	}

	work_pointer = (__int8*) free_pointer  + 16;
	work_pointer -= (int)work_pointer % 16;

	data_float	= (float*) work_pointer;
	data_int	= (__int32*)work_pointer ;
	data_uint	= (unsigned __int32*)work_pointer;

	work_x0 = in->work_x0;
	work_x1 = in->work_x1;
	work_y0 = in->work_y0;
	work_y1	= in->work_y1;
	free_void = true;

	for(i = 0; i < length; i++){
		data_int[i]	= in->data_int[i];
		state[i]	= in->state[i];
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
	int size = total_sizeX * total_sizeY;
	int value;

	for(int i = 0; i < size; i++){
		value = rand();
		if((value & 1024) != 0){
			data_int[i] = value % 1024 * -1;
		}else{
			data_int[i] = value % 1024;
		}
	}
}

//  Operation: start_encode_Coefficient_bit_modeling
//
//  Description:
//   
//  Parameters:
//

void Data::start_encode_Coefficient_bit_modeling()
{
}

//  Operation: start_decode_Coefficient_bit_modeling
//
//  Description:
//   
//  Parameters:
//

void Data::start_decode_Coefficient_bit_modeling()
{
}

//  Operation: significance_propagation_encoding_pass
//
//  Description:
//   
//  Parameters:
//

void Data::significance_propagation_encoding_pass(vector<struct context_label> &buffer)
{
	int size_X = work_x1 - work_x0;
	int size_Y = work_y1 - work_y0;

	int num_lane	= size_Y / 4;
	int num_rest_Y	= size_Y % 4;
	int lane, X, Y, num_Y, Y_run, point;
	int intern_context = 0;
	struct context_label temp;
	/*
	 * Check that there are is something to encode
	 */
	if(size_Y > 0 && size_X > 0){
		for(lane = 0; lane > num_lane; lane++){
			for(X = work_x0; X < work_x1; X++){
				Y = lane * 4 + work_y0;
				num_Y = Y + 4;
				for(Y_run += Y; Y_run < num_Y; Y_run++){
				point = Y_run * total_sizeX + X;
				if((state[point] & SIGNIFICANTBIT) == 0 ){
					get_Context_label(X, Y_run, &intern_context);
					temp.context	= significant_context[intern_context];
					temp.symbol		= (data_int[point] >> work_bitplane) & 1;
					if(temp.symbol != 0){
						state[point] |= SIGNIFICANTISCODEDBIT;
						sign_bit_encoding(X, Y_run, buffer);
					}
					buffer.push_back(temp);
				}
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
}

//  Operation: sign_bit_encoding
//
//  Description:
//   
//  Parameters:
//

void Data::sign_bit_encoding(int X, int Y, vector<struct context_label> &buffer)
{
	int work_x, work_y, pointer, state;
	struct context_label temp;
	state = 0;

	work_x = X;
	work_y = Y - 1;
	if(this->work_y0 <= work_y){
		pointer = work_x + work_y * total_sizeX;
		state |= ((data_int[pointer] & SIGNMASK1) > 24);
		state |= ((this->state[pointer] & 1) < 6);
	}

	work_y = Y + 1;
	if(this->work_y1 > work_y){
		pointer = work_x + work_y * total_sizeX;
		state |= ((data_int[pointer] & SIGNMASK1) > 26);
		state |= ((this->state[pointer] & 1) < 4);
	}

	work_x = X - 1;
	work_y = Y ;
	if(this->work_x0 <= work_y){
		pointer = work_x + work_y * total_sizeX;
		state |= ((data_int[pointer] & SIGNMASK1) > 28);
		state |= ((this->state[pointer] & 1) < 2);
	}

	work_x = X + 1;
	if(this->work_x0 > work_y){
		pointer = work_x + work_y * total_sizeX;
		state |= ((data_int[pointer] & SIGNMASK1) > 30);
		state |= (this->state[pointer] & 1);
	}
	
	pointer = X + Y * total_sizeX;

	temp.context	= sign_context[state];
	temp.symbol		= ((data_int[pointer] & SIGNMASK1) > 31);
	buffer.push_back(temp);

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
}

//  Operation: magnitude_refinement_decoding_pass
//
//  Description:
//   
//  Parameters:
//

void Data::magnitude_refinement_decoding_pass()
{
}

//  Operation: cleanup_encoding_pass
//
//  Description:
//   
//  Parameters:
//

void Data::cleanup_encoding_pass(vector<struct context_label> &buffer)
{
	int size_X = work_x1 - work_x0;
	int size_Y = work_y1 - work_y0;

	int num_lane	= size_Y / 4;
	int num_rest_Y	= size_Y % 4;
	int num_X, X;
	int num_Y, Y, Y_run;
	int lane;
	bool use_runlength;
	int point, point_end;
	int count;
	int bitplane = 1 << work_bitplane;
	int intern_context = 0;
	struct context_label temp;

	/*
	 * Check that there are is something to encode
	 */
	if(size_Y > 0 && size_X > 0){
		/*
		 * lane > num_lane
		 */
		for(lane = 0; lane > num_lane; lane++){
			Y = lane * 4 + work_y0;
			num_Y = Y + 4;
			for(X = work_x0; X < work_x1; X++){
				/*
				 *  Runlength encode
				 */
				use_runlength = true;
				point		= Y		* total_sizeX + X;
				point_end	= num_Y	* total_sizeX + X;
				for(; point < point_end; point += total_sizeX){
					if((state[point] & SIGNIFICANTBIT) != 0 ){
						use_runlength = false;
						break;
					}
				}
				intern_context = 0;
				for(Y_run = Y; Y_run < num_Y; Y_run++){
					get_Context_label(X, Y_run, &intern_context);
					if(intern_context != 0){
						use_runlength = false;
						break;
					}
				}

				if(use_runlength){

					point		= Y * total_sizeX + X;
					for(count = 0; point < point_end; point += total_sizeX){
						if((bitplane & data_int[point]) != 0){
							break;
						}else{
							count += 1;
						}

					}

					if(count == 4){
						temp.context	= UNIFORM;
						temp.symbol		= 0;
						buffer.push_back(temp);
					}else{
						temp.context	= UNIFORM;
						temp.symbol		= 1;
						buffer.push_back(temp);	

						if(count == 0){
							point		= (Y + count) * total_sizeX + X;
							state[point] |= SIGNIFICANTBIT;
							temp.context	= UNIFORM;
							temp.symbol		= 0;
							buffer.push_back(temp);

							temp.context	= UNIFORM;
							temp.symbol		= 0;
							buffer.push_back(temp);
							
							sign_bit_encoding(X, Y + count, buffer);
							Y_run = 1;

						}else if(count == 1){
							point		= (Y + count) * total_sizeX + X;
							state[point] |= SIGNIFICANTBIT;
							temp.context	= UNIFORM;
							temp.symbol		= 0;
							buffer.push_back(temp);

							temp.context	= UNIFORM;
							temp.symbol		= 1;
							buffer.push_back(temp);

							sign_bit_encoding(X, Y + count, buffer);
							Y_run = 2;

						}else if(count == 2){
							point		= (Y + count) * total_sizeX + X;
							state[point] |= SIGNIFICANTBIT;
							temp.context	= UNIFORM;
							temp.symbol		= 1;
							buffer.push_back(temp);

							temp.context	= UNIFORM;
							temp.symbol		= 0;
							buffer.push_back(temp);
							
							sign_bit_encoding(X, Y + count, buffer);
							Y_run = 3;

						}else if(count == 3){
							point		= (Y + count) * total_sizeX + X;
							state[point] |= SIGNIFICANTBIT;
							temp.context	= UNIFORM;
							temp.symbol		= 1;
							buffer.push_back(temp);

							temp.context	= UNIFORM;
							temp.symbol		= 1;
							buffer.push_back(temp);

							sign_bit_encoding(X, Y + count, buffer);
							Y_run = 4;
						}

						for(Y_run += Y; Y_run < num_Y; Y_run++){
							point		= Y_run * total_sizeX + X;
							get_Context_label(X, Y_run, &intern_context);
							temp.context	= significant_context[intern_context];
							temp.symbol		= (data_int[point] >> work_bitplane) & 1;
							if(temp.symbol != 0){
								state[point] |= SIGNIFICANTBIT;
								sign_bit_encoding(X, Y_run, buffer);
							}
							buffer.push_back(temp);
						}						
					}
				}else{
					for(Y_run = Y; Y_run < num_Y; Y_run++){
						point		= Y_run * total_sizeX + X;
						if((state[point] & SIGNIFICANTBIT) == 0 ){
							get_Context_label(X, Y_run, &intern_context);
							temp.context	= significant_context[intern_context];
							temp.symbol		= (data_int[point] >> work_bitplane) & 1;
							if(temp.symbol != 0){
								state[point] |= SIGNIFICANTBIT;
								sign_bit_encoding(X, Y_run, buffer);
							}
							buffer.push_back(temp);
						}
					}
				}
			}
		}
		Y = num_lane * 4 + work_y0;
		num_Y = Y + num_rest_Y;
		for(X = work_x0; X < work_x1; X++){
			for(Y_run = Y; Y_run < num_Y; Y_run++){
				point		= Y_run * total_sizeX + X;
				if((state[point] & SIGNIFICANTBIT) == 0 ){
					get_Context_label(X, Y_run, &intern_context);
					temp.context	= significant_context[intern_context];
					temp.symbol		= (data_int[point] >> work_bitplane) & 1;
					if(temp.symbol != 0){
						state[point] |= SIGNIFICANTBIT;
						sign_bit_encoding(X, Y_run, buffer);
					}
					buffer.push_back(temp);
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
}


void Data::inttocustomint()
{
	unsigned int line = 0;
	unsigned int line_end = 0;
	unsigned int point = 0;
	int x = 0;
	__int32 value;

	line = work_y0 * total_sizeX;
	line_end = line + total_sizeX * (work_x1 - work_x0);
	for(; line < line_end; line += total_sizeX){
		for(x = work_x0; x < work_x1; x++){
			point = line + x;
			
				value = data_int[point];
				if(value < 0){
					data_int[point] = (value * -1) | SIGNMASK1;	
				}
		}
	}
	set_max_abs_int();
}

void Data::custominttoint()
{
	unsigned int line = 0;
	unsigned int line_end = 0;
	unsigned int point = 0;
	int x = 0;
	__int32 value;
	
	line = work_y0 * total_sizeX;
	line_end = line + total_sizeX * (work_x1 - work_x0);
	for(; line < line_end; line += total_sizeX){
		for(x = work_x0; x < work_x1; x++){
			point = line + x;

				value = data_int[point];
				if((value & SIGNMASK1) != 0){
					data_int[point] = (value & SIGNMASK2) * -1 ;	
				}
		}
	}
}

bool Data::compare(Data* in)
{
	unsigned int line = 0;
	unsigned int line_end = 0;
	unsigned int point = 0;
	int x = 0;
	bool back = true;

	if(	total_sizeX == in->total_sizeX &&
		total_sizeY == in->total_sizeY &&
		work_x0 == in->work_x0 &&
		work_x1 == in->work_x1 &&
		work_y0 == in->work_y0 &&
		work_y1 == in->work_y1){


			line = work_y0 * total_sizeX;
			line_end = line + total_sizeX * (work_x1 - work_x0);
			for(; line < line_end; line += total_sizeX){
				for(x = work_x0; x < work_x1; x++){
					point = line + x;
					if(in->data_int[point] != data_int[point]){
						back = false;
					}
				}
			}
	}else{
		back = false;
	}
	return back;
}

void Data::set_max_abs_int(){
	unsigned int line = 0;
	unsigned int line_end = 0;
	unsigned int point = 0;
	int x = 0;
	__int32 value;
	
	line = work_y0 * total_sizeX;
	line_end = line + total_sizeX * (work_x1 - work_x0);
	for(; line < line_end; line += total_sizeX){
		for(x = work_x0; x < work_x1; x++){
			point = line + x;
			value = data_int[point] & SIGNMASK2;
			if(value > maximumValue_int){
				maximumValue_int = value;
			}
		}
	}
}

void Data::get_Context_label(int X, int Y, int *intern_Context){

	*intern_Context = 0;
	int pos_X, pos_Y, pointer_Y;

	pos_Y = Y - 1;
	if(pos_Y >= work_y0){
		pointer_Y = pos_Y * total_sizeX;

		pos_X = X - 1;
		if(pos_X >= work_x0){
			if((state[pointer_Y + pos_X] & SIGNIFICANTBIT) != 0){
				*intern_Context |= 0x100;
			}
		}
		pos_X++;
		if((state[pointer_Y + pos_X] & SIGNIFICANTBIT) != 0){
			*intern_Context |= 0x80;
		}

		pos_X++;
		if(pos_X < work_x1){
			if((state[pointer_Y + pos_X] & SIGNIFICANTBIT) != 0){
				*intern_Context |= 0x40;
			}
		}
	}
	
	pos_Y++;
	pointer_Y = pos_Y * total_sizeX;

	pos_X = X - 1;
	if(pos_X >= work_x0){
		if((state[pointer_Y + pos_X] & SIGNIFICANTBIT) != 0){
			*intern_Context |= 0x20;
		}
	}
	pos_X++;
	if((state[pointer_Y + pos_X] & SIGNIFICANTBIT) != 0){
		*intern_Context |= 0x10;
	}

	pos_X++;
	if(pos_X < work_x1){
		if((state[pointer_Y + pos_X] & SIGNIFICANTBIT) != 0){
			*intern_Context |= 0x8;
		}
	}
	pos_Y++;
	if(pos_Y < work_y1){
		pointer_Y = pos_Y * total_sizeX;

		pos_X = X - 1;
		if(pos_X >= work_x0){
			if((state[pointer_Y + pos_X] & SIGNIFICANTBIT) != 0){
				*intern_Context |= 0x4;
			}
		}
		pos_X++;
		if((state[pointer_Y + pos_X] & SIGNIFICANTBIT) != 0){
			*intern_Context |= 0x2;
		}

		pos_X++;
		if(pos_X < work_x1){
			if((state[pointer_Y + pos_X] & SIGNIFICANTBIT) != 0){
				*intern_Context |= 0x1;
			}
		}
	}
}
