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


PDC_uint8 BDK_context_states[3][256] = {{	 0, 1, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2,
												 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
												 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
												 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
												 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
												 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8	},
									{	
												 0, 1, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2,
												 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
												 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
												 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
												 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
												 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
												 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8	},
									{	
												 0, 1, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2,
												 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
												 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
												 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
												 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
												 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
												 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
												 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8	}};

												
	PDC_uint8 XORbit[256] = {	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
								 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
								 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
								 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
								 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
								 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
								 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
								 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
								 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
								 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
								 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
								 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
								 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
								 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
								 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0,
								 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0	};

								
	PDC_uint8 BDK_context_signstates[256] = {	  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
												 10,  9,  9, 10, 10,  9,  9, 10, 10,  9,  9, 10, 10,  9,  9, 10,
												 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
												 13, 13, 11, 11, 13, 13, 11, 11, 11, 11, 13, 13, 11, 11, 13, 13,
												 13, 11, 13, 11, 13, 11, 13, 11, 11, 13, 11, 13, 11, 13, 11, 13,
												 13, 12, 12, 11, 13, 12, 12, 11, 11, 12, 12, 13, 11, 12, 12, 13,
												 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
												 13, 13, 11, 11, 11, 11, 13, 13, 13, 13, 11, 11, 11, 11, 13, 13,
												 13, 11, 13, 11, 11, 13, 11, 13, 13, 11, 13, 11, 11, 13, 11, 13,
												 13, 12, 12, 11, 11, 12, 12, 13, 13, 12, 12, 11, 11, 12, 12, 13,
												 12, 12, 12, 12,  9,  9,  9,  9,  9,  9,  9,  9, 12, 12, 12, 12,
												 13, 13, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 13, 13,
												 13, 11, 13, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 13, 11, 13,
												 13, 12, 12, 11, 10,  9,  9, 10, 10,  9,  9, 10, 11, 12, 12, 13	};
	
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
	codeblock->cx0							= 0;
	codeblock->cx1							= 0;
	codeblock->cy0							= 0;
	codeblock->cy1							= 0;
	codeblock->subband						= NULL;
	codeblock->codeblock_inclusion			= PDC_false;
	codeblock->zero_bit_plane_inclusion		= PDC_false;
	codeblock->Lblock						= 3;
	codeblock->is_coded						= NULL;
	codeblock->sign							= NULL;
	codeblock->significant					= NULL;
	codeblock->significante_context			= NULL;
	codeblock->significante_context_delete	= NULL;
	codeblock->value8						= NULL;
	codeblock->value16						= NULL;
	codeblock->value32						= NULL;
	codeblock->sign_context					= NULL;
	codeblock->sign_context_delete			= NULL;
	codeblock->decoder						= NULL;


	codeblock->read_codeword	= new_PDC_Codeword_List_01( exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Codeblock(exception, codeblock);
		return NULL;
	}
	codeblock->write_codeword	= codeblock->read_codeword;



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

	codeblock = PDC_Codeblock_init_bit_modeling_variable(exception, codeblock);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Codeblock(exception, codeblock);
		return NULL;
	}
	return codeblock;
}


/*
 *
 */
PDC_Codeblock* PDC_Codeblock_init_bit_modeling_variable(PDC_Exception* exception, PDC_Codeblock* codeblock)
{
	PDC_uint32 size_x, size_y, size_x_bit, size1;

	size_x		= codeblock->cx1 - codeblock->cx0;
	size_y		= codeblock->cy1 - codeblock->cy0;

	size_x_bit				= PDC_ui_ceiling(size_x, 8);
	codeblock->street		= 0;
	codeblock->num_street	= PDC_ui_ceiling(size_y, 4);
	codeblock->state_bit	= STATE_BIT_8;
	codeblock->bit_plane	= 0;

	size1 = size_x_bit * codeblock->num_street;

	codeblock->value8		= malloc(size_x * size_y);
	if(codeblock->value8 == NULL){
		delete_PDC_Codeblock(exception, codeblock);
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	};

	codeblock->is_coded = malloc(sizeof(PDC_uint32) * size1);
	if(codeblock->is_coded == NULL){
		delete_PDC_Codeblock(exception, codeblock);
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	};
	codeblock->sign = malloc(sizeof(PDC_uint32) * size1);
	if(codeblock->sign  == NULL){
		delete_PDC_Codeblock(exception, codeblock);
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	};
	codeblock->significant = malloc(sizeof(PDC_uint32) * size1);
	if(codeblock->significant == NULL){
		delete_PDC_Codeblock(exception, codeblock);
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	};


	codeblock->significante_context_size_x = size_x + 2;
	codeblock->significante_context_size_y = size_y + 4;
	size1 = codeblock->significante_context_size_x * codeblock->significante_context_size_y;
	codeblock->significante_context_delete = malloc(sizeof(PDC_uint8) * size1);
	if(codeblock->is_coded == NULL){
		delete_PDC_Codeblock(exception, codeblock);
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	};
	codeblock->significante_context = codeblock->significante_context_delete + codeblock->significante_context_size_y + 1;

	codeblock->sign_context_size_x = size_x + 2;
	codeblock->sign_context_size_y = PDC_ui_ceiling(size_y, 2) + 4;


	size1 = size_x * size_y;
	codeblock->value8 = malloc(sizeof(PDC_uint8) * size1);
	if(codeblock->value8 == NULL){
		delete_PDC_Codeblock(exception, codeblock);
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	};

	codeblock->decoder = new_PDC_Arithmetic_entropy_decoder(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Codeblock(exception, codeblock);
		return NULL;
	}

	switch(codeblock->subband->type){
		case SUBBAND_LL:
			codeblock->BDK_context_states	= BDK_context_states[0];
			break;
		case SUBBAND_LH:
			codeblock->BDK_context_states	= BDK_context_states[0];
			break;
		case SUBBAND_HL:
			codeblock->BDK_context_states	= BDK_context_states[1];
			break;
		case SUBBAND_HH:
			codeblock->BDK_context_states	= BDK_context_states[2];
			break;

	}

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

/*
 *
 */
PDC_bool PDC_Codeblock_significance_decoding_pass(PDC_Exception* exception, PDC_Codeblock* codeblock, PDC_Buffer* codeword)
{
	PDC_bool	back = PDC_true;
	PDC_uint32	pos_street, max_street, size_x, pos_x, pos_x_base, pos_value, pos_y_base, extrastreet_size;
	PDC_uint32	significant, significant_base_pos, sign_context1, sign_context2, sign_context3;
	PDC_int		nibble_pos, significant_pos, significant_size, significant_rest, size_x_bit;
	PDC_uint8*	significante_context, *significante_context_use, *sign_context_base_address, *sign_context_base_address1;
	PDC_uint32	significante_context_size_y, context, *significant_address, bit_plane;
	PDC_Arithmetic_entropy_decoder *decoder;
	PDC_STATE_BIT	value_size;
	PDC_uint8*		value8;
	PDC_uint16*		value16;
	PDC_uint32*		value32;
	PDC_uint8*		sign_context;
	PDC_uint32		sign_context_size_y, sign_context_use;

	

	significante_context_size_y	= codeblock->significante_context_size_y;
	significante_context		= codeblock->significante_context; 
	max_street					= codeblock->num_street;
	pos_street					= codeblock->street;
	size_x						= codeblock->cx1 - codeblock->cx0;
	significant_address			= codeblock->significant;
	decoder						= codeblock->decoder;
	bit_plane					= codeblock->bit_plane;
	value_size					= codeblock->value_size;
	value8						= codeblock->value8;
	value16						= codeblock->value16;
	value32						= codeblock->value32;
	sign_context				= codeblock->sign_context;
	sign_context_size_y			= codeblock->sign_context_size_y;

	extrastreet_size = (codeblock->cy1 - codeblock->cy0) % 4;
	if(extrastreet_size != 0){
		max_street -= 1;
	}

	size_x_bit			= PDC_ui_ceiling(size_x, 8);
	pos_x				= codeblock->pos_x;
	nibble_pos			= pos_x % 8;
	significant_pos		= PDC_i_floor(pos_x, 8);
	significant_size	= PDC_i_floor(size_x, 8);
	significant_rest	= size_x % 8;

	while(pos_street < max_street){
		significant_base_pos		= pos_street * size_x_bit;
		pos_y_base					= pos_street * 4;
		sign_context_base_address	= codeblock->sign_context + (2 * pos_street) - 1;
		while(significant_pos < significant_size){
			significant = significant_address[significant_base_pos + significant_pos];
			pos_x_base = 8 * significant_pos;
			if(significant != 0xFFFFFFFF){
				if((significant & 0xFFFF) != 0xFFFF){
					if((significant & 0xFF) != 0xFF){
						if((significant & 0xF) != 0xF){
							pos_x					= pos_x_base;
							significante_context_use = &significante_context[pos_y_base + pos_x * significante_context_size_y]; 
							context = *((PDC_uint32*)significante_context_use);

							sign_context_base_address1 = sign_context_base_address + pos_x * sign_context_size_y; 
							sign_context1	= *((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y));
							sign_context2	= *((PDC_uint32*)(sign_context_base_address1));
							sign_context3	= *((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y));


							if((significant & 0x1) == 0 && (context & 0xFF) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, context & 0xFF, codeword);
								if(decoder->D != 0){
									pos_value = (size_x * pos_y_base) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x1;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 8) & 0xF) | ( context & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, sign_context_use & 0xFF, codeword); 
									if(decoder->D != 0){

									}
								}



							}
						}
					}
				}

			}
			significant_pos += 1;
		}
	}

	return back;
}

STOP_C

