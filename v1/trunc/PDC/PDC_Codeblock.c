/*
 * Copyright (C) 2008  Uwe Brünen
 * Contact Email: bruenen.u@web.de
 * 
 * This file is part of PicDatCom.
 * 
 * PicDatCom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * PicDatCom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with PicDatCom.  If not, see <http://www.gnu.org/licenses/>.
 * */

#include "PDC_Codeblock.h"

START_C

	
/*
 *
 */
PDC_Codeblock* new_PDC_Codeblock_01(PDC_Exception* exception)
{
	PDC_Codeblock* codeblock = NULL;
	codeblock = malloc(sizeof(PDC_Codeblock));
	if(codeblock == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	
	codeblock->read_codeword	= new_PDC_Codeword_List_01( exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Codeblock(exception, codeblock);
		return NULL;
	}
	codeblock->write_codeword	= codeblock->read_codeword;

	codeblock->cx0						= 0;
	codeblock->cx1						= 0;
	codeblock->cy0						= 0;
	codeblock->cy1						= 0;
	codeblock->subband					= NULL;
	codeblock->codeblock_inclusion		= PDC_false;
	codeblock->zero_bit_plane_inclusion	= PDC_false;
	codeblock->Lblock					= 3;

	return codeblock;
}

/*
 *
 */
PDC_Codeblock* new_PDC_Codeblock_02(PDC_Exception* exception, PDC_Subband* subband, PDC_uint pos_x, PDC_uint pos_y)
{
	PDC_Codeblock* codeblock;

	PDC_Resolution* resolution	= subband->resolution;
	PDC_uint		size_x		= 1 << resolution->xcb;
	PDC_uint		size_y		= 1 << resolution->ycb;

	codeblock = new_PDC_Codeblock_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Codeblock(exception, codeblock);
		return NULL;
	}

	codeblock->cx0	= max_uint32(size_x * pos_x, subband->tbx0);
	codeblock->cx1	= min_uint32(size_x *(pos_x + 1), subband->tbx1);
	codeblock->cy0	= max_uint32(size_y * pos_y, subband->tby0);
	codeblock->cy1	= min_uint32(size_y *(pos_y + 1), subband->tby1);

	codeblock->read_codeword	= NULL;
	codeblock->write_codeword	= new_PDC_Codeword_List_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Codeblock(exception, codeblock);
		return NULL;
	}
	codeblock->subband			= subband;

	return codeblock;
}


/*
 *
 */
PDC_Codeblock* delete_PDC_Codeblock(PDC_Exception* exception, PDC_Codeblock* codeblock)
{
	if(codeblock != NULL){
		free(codeblock);
	}
	return NULL;
}

/*
 *
 */
PDC_uint PDC_Codeblock_set_number_of_coding_passes(	PDC_Exception* exception, PDC_Codeblock* codeblock, PDC_uint number_of_coding_passes)
{
	PDC_COD_Segment* cod_segment = NULL;

	cod_segment = codeblock->subband->resolution->tile_component->cod_segment;

	if((cod_segment->code_block_style & TERMINATION_EACH_CODING) == 0){
		if((cod_segment->code_block_style & SELECTIVE_ARITHMETIC_CODING) == 0){
			codeblock->write_codeword->coding_pass_to			+= number_of_coding_passes;
			codeblock->write_codeword->number_of_coding_passes	= number_of_coding_passes;
			return 1;
		}else{
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			return 0;
		}
	}else{
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
		return 0;
	}


}

/*
 *
 */
PDC_Codeword_List* new_PDC_Codeword_List_01(PDC_Exception* exception)
{
	PDC_Codeword_List* codeword_list = NULL;
	codeword_list = malloc(sizeof(PDC_Codeword_List));
	if(codeword_list == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	codeword_list->codeword					= new_PDC_Buffer_1(exception, DEFAULT_RESIZE_CODEWORD);
	codeword_list->first_codedword			= NULL;
	codeword_list->last_codedword			= NULL;
	codeword_list->next_codedword			= NULL;
	codeword_list->coding_pass_from			= 0;
	codeword_list->coding_pass_to			= 0;
	codeword_list->coding_pass_next			= 0;
	codeword_list->number_of_coding_passes	= 0;
	codeword_list->number_of_byte			= 0;

	return codeword_list;
}

/*
 *
 */
PDC_Codeword_List* new_PDC_Codeword_List_02(PDC_Exception* exception, PDC_Codeword_List* last_codeword_list)
{
	PDC_Codeword_List* codeword_list = NULL;
	codeword_list = new_PDC_Codeword_List_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Codeword_List(exception, codeword_list);
		return NULL;
	}
	
	codeword_list->last_codedword		= last_codeword_list;
	last_codeword_list->next_codedword	= codeword_list;
	codeword_list->coding_pass_from		= last_codeword_list->coding_pass_to;
	
	return codeword_list;
}

/*
 *
 */
PDC_Codeword_List* delete_PDC_Codeword_List(PDC_Exception* exception, PDC_Codeword_List* codeword_list)
{

	if(codeword_list != NULL){
		delete_PDC_Codeword_List(exception, codeword_list->next_codedword);
		delete_PDC_Buffer(exception, codeword_list->codeword);

		free(codeword_list);

	}
	return NULL;
}

STOP_C

