// SPcoc.cpp
//
// This header file defines the implementation of the class SPcoc
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
#include "SPcoc.h"


BDK::SPcoc::SPcoc(const unsigned char* information, Coding_style_component_COC* coc)
{
	int iWork1, iWork2;
	byte code_block_style = 0;
	this->number_of_decomposition_level = information[0];
	if(this->number_of_decomposition_level > 32){
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "SPcoc number_of_decomposition_level > 32." );
	}
	this->codeblock_width_value_xcb = information[1];
	this->codeblock_width_value_ycb = information[2];
	if((this->codeblock_width_value_xcb + this->codeblock_width_value_ycb + 4) > 12){
		throw new Default_Exceptionhandler(__FILE__ , __LINE__ , "Codeblock to big!" );
	}

	this->codeblock_width_value_xcb += 2;
	this->codeblock_width_value_ycb += 2;

	code_block_style = information[3];
	if((code_block_style & SELECTIVE_ARITHMETIC_CODING_BYPASS) ==SELECTIVE_ARITHMETIC_CODING_BYPASS){
		this->use_selective_arithmetic_coding_bypass = true;
	}else{
		this->use_selective_arithmetic_coding_bypass = false;
	}

	if((code_block_style & RESET_CONTEXT_PROBALITIES) == RESET_CONTEXT_PROBALITIES){
		this->use_reset_of_context_probabilities_on_coding_pass = true;
	}else{
		this->use_reset_of_context_probabilities_on_coding_pass = false;
	}

	if((code_block_style & TERMINATION_ON_EACH_CODING_PASS) == TERMINATION_ON_EACH_CODING_PASS){
		this->use_termination_on_each_coding_pass = true;
	}else{
		this->use_termination_on_each_coding_pass = false;
	}

	if((code_block_style & VERTICALLY_CAUSAL_CONTEXT) == VERTICALLY_CAUSAL_CONTEXT){
		this->use_vertical_causal_context = true;
	}else{
		this->use_vertical_causal_context = false;
	}

	if((code_block_style & PREDICTABEL_TERMINATION) == PREDICTABEL_TERMINATION){
		this->use_predictiable_termination = true;
	}else{
		this->use_predictiable_termination = false;
	}

	if((code_block_style & SEGMENTION_SYMBOLS_USED) == SEGMENTION_SYMBOLS_USED){
		this->use_segmentation_symbols = true;
	}else{
		this->use_segmentation_symbols = false;
	}

	if(information[4] == NINESEVENFILTER){
		this->transformation = irreversible;
	}else{
		this->transformation = reversible;
	}

	if(coc->use_default_PPx_PPy){
		precinct_size.push_back(new Precinct_size(DEFAULT_PRECINCT_SIZE, DEFAULT_PRECINCT_SIZE));
		for(iWork1 = 0; iWork1 < this->number_of_decomposition_level; iWork1++){
			precinct_size.push_back(new Precinct_size(DEFAULT_PRECINCT_SIZE, DEFAULT_PRECINCT_SIZE));
		}
	}else{
		precinct_size.push_back(new Precinct_size(information[5]));
		for(iWork1 = 0, iWork2 = 6; iWork1 < this->number_of_decomposition_level; iWork1++){
			precinct_size.push_back(new Precinct_size(information[iWork2]));
			iWork2++;
		}

	}

}
BDK::SPcoc::~SPcoc()
{
}
