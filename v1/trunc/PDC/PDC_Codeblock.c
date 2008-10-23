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
 * H0 H1 V0 V1 D0 D1 D2 D3
 * 87654321
 */

	PDC_uint8 BDK_context_states[3][256] = {{	  2,  3,  3,  4,  3,  4,  4,  4,  3,  4,  4,  4,  4,  4,  4,  4,
												  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
												  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
												  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
												  7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												  7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10	},
									{	
												  2,  3,  3,  4,  3,  4,  4,  4,  3,  4,  4,  4,  4,  4,  4,  4,
												  7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
												  7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
												  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
												  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
												  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10	},
									{	
												  2,  3,  3,  4,  3,  4,  4,  4,  3,  4,  4,  4,  4,  4,  4,  4,
												  7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
												  7,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
												  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
												  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
												  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,
												 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10	}};

												
	PDC_uint8 XORbit[256] = {	 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
								 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
								 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
								 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	};

								
	PDC_uint8 PDC_context_signstates[256] = {	 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
												 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
												 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
												 12, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11, 12, 12, 11, 11, 12,
												 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
												 15, 15, 13, 13, 15, 15, 13, 13, 13, 13, 15, 15, 13, 13, 15, 15,
												 15, 13, 15, 13, 15, 13, 15, 13, 13, 15, 13, 15, 13, 15, 13, 15,
												 15, 14, 14, 13, 15, 14, 14, 13, 13, 14, 14, 15, 13, 14, 14, 15,
												 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
												 15, 15, 13, 13, 13, 13, 15, 15, 15, 15, 13, 13, 13, 13, 15, 15,
												 15, 13, 15, 13, 13, 15, 13, 15, 15, 13, 15, 13, 13, 15, 13, 15,
												 15, 14, 14, 13, 13, 14, 14, 15, 15, 14, 14, 13, 13, 14, 14, 15,
												 14, 14, 14, 14, 11, 11, 11, 11, 11, 11, 11, 11, 14, 14, 14, 14,
												 15, 15, 13, 13, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 15, 15,
												 15, 13, 15, 13, 12, 12, 12, 12, 12, 12, 12, 12, 13, 15, 13, 15,
												 15, 14, 14, 13, 12, 11, 11, 12, 12, 11, 11, 12, 13, 14, 14, 15	};
	
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
	codeblock->coding_passes_per_layer		= NULL;
	codeblock->BDK_context_states			= NULL;
	codeblock->pass_state					= CLEANUP_PASS;
	codeblock->pos_x						= 0;
	codeblock->init_decoder					= PDC_false;


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
	PDC_Codeblock*	codeblock;
	PDC_uint		work;

	PDC_Resolution* resolution	= subband->resolution;
	PDC_uint		size_x		= 1 << resolution->xcb;
	PDC_uint		size_y		= 1 << resolution->ycb;
	PDC_uint		num_layer	= subband->resolution->tile_component->cod_segment->number_of_layer;

	codeblock = new_PDC_Codeblock_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Codeblock(exception, codeblock);
		return NULL;
	}

	codeblock->coding_passes_per_layer = (PDC_uint*) malloc(sizeof(PDC_uint) * num_layer);
	if(codeblock->coding_passes_per_layer == NULL){
		delete_PDC_Codeblock(exception, codeblock);
		return NULL;
	}

	for(work = 0; work < num_layer; work += 1){
		codeblock->coding_passes_per_layer[work] = 0;
	}

	codeblock->cx0	= max_uint32(size_x * pos_x, subband->tbx0);
	codeblock->cx1	= min_uint32(size_x *(pos_x + 1), subband->tbx1);
	codeblock->cy0	= max_uint32(size_y * pos_y, subband->tby0);
	codeblock->cy1	= min_uint32(size_y *(pos_y + 1), subband->tby1);

	if(codeblock->cx0 > codeblock->cx1){
		codeblock->cx0 = codeblock->cx1;
	}

	if(codeblock->cy0 > codeblock->cy1){
		codeblock->cy0 = codeblock->cy1;
	}

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
	PDC_uint32 size_x, size_y, size_x_bit, size1, size_pos, size2;

	size_x		= codeblock->cx1 - codeblock->cx0;
	size_y		= codeblock->cy1 - codeblock->cy0;

	size_x_bit				= PDC_ui_ceiling(size_x, 8);
	codeblock->street		= 0;
	codeblock->num_street	= PDC_ui_ceiling(size_y, 4);
	codeblock->state_bit	= STATE_BIT_8;
	codeblock->bit_plane	= 0;

	size1 = size_x_bit * codeblock->num_street;

	size2 = size_x * size_y;
	codeblock->value8		= malloc(size2);
	if(codeblock->value8 == NULL){
		delete_PDC_Codeblock(exception, codeblock);
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	};
	for(size_pos = 0; size_pos < size2; size_pos += 1){
		codeblock->value8[size_pos] = 0;
	}
	codeblock->value_size = STATE_BIT_8;

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
	for(size_pos = 0; size_pos < size1; size_pos += 1){
		codeblock->is_coded[size_pos]		= 0;
		codeblock->sign[size_pos]			= 0;
		codeblock->significant[size_pos]	= 0;
	}

	codeblock->significante_context_size_x = size_x + 2;
	codeblock->significante_context_size_y = size_y + 4;
	size1 = codeblock->significante_context_size_x * codeblock->significante_context_size_y;
	codeblock->significante_context_delete = malloc(sizeof(PDC_uint8) * size1);
	if(codeblock->significante_context_delete == NULL){
		delete_PDC_Codeblock(exception, codeblock);
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	};
	for(size_pos = 0; size_pos < size1; size_pos += 1){
		codeblock->significante_context_delete[size_pos] = 0;
	}
	codeblock->significante_context = codeblock->significante_context_delete + codeblock->significante_context_size_y + 1;

	codeblock->sign_context_size_x = size_x + 2;
	codeblock->sign_context_size_y = PDC_ui_ceiling(size_y, 2) + 4;
	size1 = codeblock->significante_context_size_y * codeblock->sign_context_size_x;
	codeblock->sign_context_delete = malloc(sizeof(PDC_uint8) * size1);
	if(codeblock->sign_context_delete == NULL){
		delete_PDC_Codeblock(exception, codeblock);
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	for(size_pos = 0; size_pos < size1; size_pos += 1){
		codeblock->sign_context_delete[size_pos] = 0;
	}
	codeblock->sign_context = codeblock->sign_context_delete + codeblock->sign_context_size_y + 1;

	codeblock->decoder = new_PDC_Arithmetic_entropy_decoder(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Codeblock(exception, codeblock);
		return NULL;
	}
	PDC_Aed_set_I_MPS_01(exception, codeblock->decoder, PDC_A_Encoder__mps, PDC_A_Encoder__index);
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
PDC_uint PDC_Codeblock_set_number_of_coding_passes(	PDC_Exception* exception, PDC_Codeblock* codeblock, PDC_uint number_of_coding_passes, PDC_uint layer_pos)
{
	PDC_COD_Segment* cod_segment = NULL;

	cod_segment = codeblock->subband->resolution->tile_component->cod_segment;

	if(layer_pos >= codeblock->subband->resolution->tile_component->cod_segment->number_of_layer){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
		return 0;
	}
	codeblock->coding_passes_per_layer[layer_pos] = number_of_coding_passes;

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
PDC_Codeblock *PDC_Codeblock_coefficient_bit_moddeling_decode( PDC_Exception *exception, PDC_Codeblock *codeblock, PDC_uint layer_pos){

	PDC_Codeword_List *codeword_list;
	PDC_uint number_of_codingpasses , done_codingpasses;

	codeword_list			= codeblock->write_codeword;
	number_of_codingpasses	= codeblock->coding_passes_per_layer[layer_pos];

	for(done_codingpasses = 0; done_codingpasses < number_of_codingpasses; done_codingpasses += 1){
		while(codeword_list->coding_pass_next >= codeword_list->coding_pass_to){
			codeword_list = codeword_list->next_codedword;
		}
		if(codeblock->init_decoder == PDC_false){
			codeblock->init_decoder = PDC_true;
			codeblock->decoder = PDC_Aed_initdec_01(	exception,
														codeblock->decoder,
														codeword_list->codeword);
		}
	
		switch(codeblock->pass_state){
			case CLEANUP_PASS:
				codeblock = PDC_Codeblock_cleanup_decoding_pass(exception, codeblock, codeword_list->codeword);
				codeblock->pass_state	= SIGNIFICANCE_PASS;
				break;
			case SIGNIFICANCE_PASS:
				codeblock->pass_state	= MAGNITUDE_PASS;
				break;
			case MAGNITUDE_PASS:
				// codeblock->pass_state	= CLEANUP_PASS;
				break;
		}
	}
	return codeblock;
}


/*
 *
 */
PDC_bool PDC_Codeblock_significance_decoding_pass(PDC_Exception* exception, PDC_Codeblock* codeblock, PDC_Buffer* codeword)
{
	PDC_bool		back = PDC_true;
	PDC_uint32		pos_street, max_street, size_x, pos_x,pos_x_end, pos_x_base, pos_value, pos_y_base, extrastreet_size;
	PDC_uint32		significant, significant_base_pos, sign_context1, sign_context2, sign_context3;
	PDC_int			nibble_pos, significant_pos, significant_size, significant_rest, significant_rest_pos, size_x_bit;
	PDC_uint8*		significante_context, *significante_context_use, *sign_context_base_address, *sign_context_base_address1;
	PDC_uint32		significante_context_size_y, context, *significant_address, *sign_address, bit_plane;
	PDC_Arithmetic_entropy_decoder *decoder;
	PDC_STATE_BIT	value_size;
	PDC_uint8*		value8;
	PDC_uint16*		value16;
	PDC_uint32*		value32;
	PDC_uint8*		sign_context;
	PDC_uint32		sign_context_size_y, sign_context_use, sign, is_coded, *is_coded_address;
	PDC_uint32		*context1_address, *context2_address, *context3_address;
	PDC_uint32		significant_temp, is_coded_temp, sign_temp, shift, significant_pos_x;
	PDC_uint8		*PDK_context_states;


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
	sign_address				= codeblock->sign;
	is_coded_address			= codeblock->is_coded;
	PDK_context_states			= codeblock->BDK_context_states;


	extrastreet_size = (codeblock->cy1 - codeblock->cy0) % 4;
	if(extrastreet_size != 0){
		max_street -= 1;
	}

	if(value_size == STATE_BIT_8){
		bit_plane = 7 - bit_plane;
	}else if(value_size == STATE_BIT_16){
		bit_plane = 15 - bit_plane;
	}else if(value_size == STATE_BIT_32){
		bit_plane = 31 - bit_plane;
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
			sign		= sign_address[significant_base_pos + significant_pos];
			is_coded	= is_coded_address[significant_base_pos + significant_pos];

			pos_x_base = 8 * significant_pos;
			if(significant != 0xFFFFFFFF){
				if((significant & 0xFFFF) != 0xFFFF){
					if((significant & 0xFF) != 0xFF){
						if((significant & 0xF) != 0xF){
							pos_x						= pos_x_base;
							significante_context_use	= &significante_context[pos_y_base + pos_x * significante_context_size_y]; 
							
							sign_context_base_address1 = sign_context_base_address + pos_x * sign_context_size_y; 
							sign_context1	= *((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y));
							sign_context2	= *((PDC_uint32*)(sign_context_base_address1));
							sign_context3	= *((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y));

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos A */
							if((significant & 0x1) == 0 && (context & 0xFF) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[context & 0xFF], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use - 1));
									context3_address = ((PDC_uint32*)(significante_context_use - 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * pos_y_base) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 <<  bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x01;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 8) & 0xF) | ( context & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use] , codeword); 
									if(decoder->D != 0){
										sign |= 0x1;
										sign_context1 |= SET_SIGN_CONTEXT_A1;
										sign_context2 |= SET_SIGN_CONTEXT_A2;
										sign_context3 |= SET_SIGN_CONTEXT_A3;
									}
								}
								is_coded |= 0x01;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos B */
							if((significant & 0x2) == 0 && (context & 0xFF00) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF00) >> 8], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use));
									context3_address = ((PDC_uint32*)(significante_context_use + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 1)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x02;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 12) & 0xF) | ( (context >> 8) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use] , codeword); 
									if(decoder->D != 0){
										sign |= 0x2;
										sign_context1 |= SET_SIGN_CONTEXT_B1;
										sign_context2 |= SET_SIGN_CONTEXT_B2;
										sign_context3 |= SET_SIGN_CONTEXT_B3;
									}
								}
								is_coded |= 0x02;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos C */
							if((significant & 0x4) == 0 && (context & 0xFF0000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF0000) >> 16], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 1 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 2)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x04;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 16) & 0xF) | ((context >> 16) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x4;
										sign_context1 |= SET_SIGN_CONTEXT_C1;
										sign_context2 |= SET_SIGN_CONTEXT_C2;
										sign_context3 |= SET_SIGN_CONTEXT_C3;
									}
								}
								is_coded |= 0x04;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos D */
							if((significant & 0x8) == 0 && (context & 0xFF000000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF000000) >> 24], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 2 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 2 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 2 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 3)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x08;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 20) & 0xF) | ((context >> 24) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x8;
										sign_context1 |= SET_SIGN_CONTEXT_D1;
										sign_context2 |= SET_SIGN_CONTEXT_D2;
										sign_context3 |= SET_SIGN_CONTEXT_D3;
									}
								}
								is_coded |= 0x08;
							}
							*((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y))	= sign_context1;
							*((PDC_uint32*)(sign_context_base_address1))						= sign_context2;
							*((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y))	= sign_context3;
						}

						if((significant & 0xF0) != 0xF0){
							pos_x						= pos_x_base + 1;
							significante_context_use	= &significante_context[pos_y_base + pos_x * significante_context_size_y]; 
							

							sign_context_base_address1 = sign_context_base_address + pos_x * sign_context_size_y; 
							sign_context1	= *((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y));
							sign_context2	= *((PDC_uint32*)(sign_context_base_address1));
							sign_context3	= *((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y));

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos A */
							if((significant & 0x10) == 0 && (context & 0xFF) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[context & 0xFF], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use - 1));
									context3_address = ((PDC_uint32*)(significante_context_use - 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * pos_y_base) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x10;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 8) & 0xF) | ( context & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x10;
										sign_context1 |= SET_SIGN_CONTEXT_A1;
										sign_context2 |= SET_SIGN_CONTEXT_A2;
										sign_context3 |= SET_SIGN_CONTEXT_A3;
									}
								}
								is_coded |= 0x10;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos B */
							if((significant & 0x20) == 0 && (context & 0xFF00) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF00) >> 8], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use));
									context3_address = ((PDC_uint32*)(significante_context_use + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 1)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x02;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 12) & 0xF) | ( (context >> 8) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x20;
										sign_context1 |= SET_SIGN_CONTEXT_B1;
										sign_context2 |= SET_SIGN_CONTEXT_B2;
										sign_context3 |= SET_SIGN_CONTEXT_B3;
									}
								}
								is_coded |= 0x20;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos C */
							if((significant & 0x40) == 0 && (context & 0xFF0000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF0000) >> 16], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 1 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 2)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x40;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 16) & 0xF) | ((context >> 16) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x40;
										sign_context1 |= SET_SIGN_CONTEXT_C1;
										sign_context2 |= SET_SIGN_CONTEXT_C2;
										sign_context3 |= SET_SIGN_CONTEXT_C3;
									}
								}
								is_coded |= 0x40;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos D */
							if((significant & 0x80) == 0 && (context & 0xFF000000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF000000) >> 24], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 2 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 2 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 2 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 3)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x80;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 20) & 0xF) | ((context >> 24) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x80;
										sign_context1 |= SET_SIGN_CONTEXT_D1;
										sign_context2 |= SET_SIGN_CONTEXT_D2;
										sign_context3 |= SET_SIGN_CONTEXT_D3;
									}
								}
								is_coded |= 0x80;
							}
							*((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y))	= sign_context1;
							*((PDC_uint32*)(sign_context_base_address1))						= sign_context2;
							*((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y))	= sign_context3;
						}
					}

					if((significant & 0xFF00) != 0xFF00){
						if((significant & 0x0F00) != 0x0F00){
							
							pos_x						= pos_x_base + 2;
							significante_context_use	= &significante_context[pos_y_base + pos_x * significante_context_size_y]; 
							
							sign_context_base_address1 = sign_context_base_address + pos_x * sign_context_size_y; 
							sign_context1	= *((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y));
							sign_context2	= *((PDC_uint32*)(sign_context_base_address1));
							sign_context3	= *((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y));

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos A */
							if((significant & 0x100) == 0 && (context & 0xFF) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[context & 0xFF], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use - 1));
									context3_address = ((PDC_uint32*)(significante_context_use - 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * pos_y_base) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x0100;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 8) & 0xF) | ( context & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x100;
										sign_context1 |= SET_SIGN_CONTEXT_A1;
										sign_context2 |= SET_SIGN_CONTEXT_A2;
										sign_context3 |= SET_SIGN_CONTEXT_A3;
									}
								}
								is_coded |= 0x0100;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos B */
							if((significant & 0x200) == 0 && (context & 0xFF00) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF00) >> 8], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use));
									context3_address = ((PDC_uint32*)(significante_context_use + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 1)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x0200;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 12) & 0xF) | ( (context >> 8) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x0200;
										sign_context1 |= SET_SIGN_CONTEXT_B1;
										sign_context2 |= SET_SIGN_CONTEXT_B2;
										sign_context3 |= SET_SIGN_CONTEXT_B3;
									}
								}
								is_coded |= 0x0200;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos C */
							if((significant & 0x400) == 0 && (context & 0xFF0000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF0000) >> 16], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 1 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 2)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x0400;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 16) & 0xF) | ((context >> 16) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x400;
										sign_context1 |= SET_SIGN_CONTEXT_C1;
										sign_context2 |= SET_SIGN_CONTEXT_C2;
										sign_context3 |= SET_SIGN_CONTEXT_C3;
									}
								}
								is_coded |= 0x0400;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos D */
							if((significant & 0x0800) == 0 && (context & 0xFF000000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF000000) >> 24], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 2 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 2 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 2 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 3)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x0800;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 20) & 0xF) | ((context >> 24) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x800;
										sign_context1 |= SET_SIGN_CONTEXT_D1;
										sign_context2 |= SET_SIGN_CONTEXT_D2;
										sign_context3 |= SET_SIGN_CONTEXT_D3;
									}
								}
								is_coded |= 0x0800;
							}
							*((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y))	= sign_context1;
							*((PDC_uint32*)(sign_context_base_address1))						= sign_context2;
							*((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y))	= sign_context3;
						}

						if((significant & 0xF000) != 0xF000){
							pos_x						= pos_x_base + 3;
							significante_context_use	= &significante_context[pos_y_base + pos_x * significante_context_size_y]; 
							
							sign_context_base_address1 = sign_context_base_address + pos_x * sign_context_size_y; 
							sign_context1	= *((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y));
							sign_context2	= *((PDC_uint32*)(sign_context_base_address1));
							sign_context3	= *((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y));

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos A */
							if((significant & 0x1000) == 0 && (context & 0xFF) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[context & 0xFF], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use - 1));
									context3_address = ((PDC_uint32*)(significante_context_use - 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * pos_y_base) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x1000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 8) & 0xF) | ( context & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x1000;
										sign_context1 |= SET_SIGN_CONTEXT_A1;
										sign_context2 |= SET_SIGN_CONTEXT_A2;
										sign_context3 |= SET_SIGN_CONTEXT_A3;
									}
								}
								is_coded |= 0x1000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos B */
							if((significant & 0x2000) == 0 && (context & 0xFF00) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF00) >> 8], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use));
									context3_address = ((PDC_uint32*)(significante_context_use + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 1)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x2000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 12) & 0xF) | ( (context >> 8) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x2000;
										sign_context1 |= SET_SIGN_CONTEXT_B1;
										sign_context2 |= SET_SIGN_CONTEXT_B2;
										sign_context3 |= SET_SIGN_CONTEXT_B3;
									}
								}
								is_coded |= 0x2000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos C */
							if((significant & 0x4000) == 0 && (context & 0xFF0000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF0000) >> 16], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 1 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 2)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x4000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 16) & 0xF) | ((context >> 16) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x4000;
										sign_context1 |= SET_SIGN_CONTEXT_C1;
										sign_context2 |= SET_SIGN_CONTEXT_C2;
										sign_context3 |= SET_SIGN_CONTEXT_C3;
									}
								}
								is_coded |= 0x4000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos D */
							if((significant & 0x8000) == 0 && (context & 0xFF000000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF000000) >> 24], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 2 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 2 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 2 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 3)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x8000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 20) & 0xF) | ((context >> 24) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x8000;
										sign_context1 |= SET_SIGN_CONTEXT_D1;
										sign_context2 |= SET_SIGN_CONTEXT_D2;
										sign_context3 |= SET_SIGN_CONTEXT_D3;
									}
								}
								is_coded |= 0x8000;
							}
							*((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y))	= sign_context1;
							*((PDC_uint32*)(sign_context_base_address1))						= sign_context2;
							*((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y))	= sign_context3;
						}
					}
				}

				if((significant & 0xFFFF0000) != 0xFFFF0000){
					if((significant & 0xFF0000) != 0xFF0000){
						if((significant & 0x0F0000) != 0x0F0000){
							pos_x						= pos_x_base + 4;
							significante_context_use	= &significante_context[pos_y_base + pos_x * significante_context_size_y]; 
							
							sign_context_base_address1 = sign_context_base_address + pos_x * sign_context_size_y; 
							sign_context1	= *((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y));
							sign_context2	= *((PDC_uint32*)(sign_context_base_address1));
							sign_context3	= *((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y));

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos A */
							if((significant & 0x10000) == 0 && (context & 0xFF) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[context & 0xFF], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use - 1));
									context3_address = ((PDC_uint32*)(significante_context_use - 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * pos_y_base) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x10000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 8) & 0xF) | ( context & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x10000;
										sign_context1 |= SET_SIGN_CONTEXT_A1;
										sign_context2 |= SET_SIGN_CONTEXT_A2;
										sign_context3 |= SET_SIGN_CONTEXT_A3;
									}
								}
								is_coded |= 0x10000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos B */
							if((significant & 0x20000) == 0 && (context & 0xFF00) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF00) >> 8], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use));
									context3_address = ((PDC_uint32*)(significante_context_use + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 1)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x20000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 12) & 0xF) | ( (context >> 8) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x20000;
										sign_context1 |= SET_SIGN_CONTEXT_B1;
										sign_context2 |= SET_SIGN_CONTEXT_B2;
										sign_context3 |= SET_SIGN_CONTEXT_B3;
									}
								}
								is_coded |= 0x20000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos C */
							if((significant & 0x40000) == 0 && (context & 0xFF0000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF0000) >> 16], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 1 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 2)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x40000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 16) & 0xF) | ((context >> 16) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x40000;
										sign_context1 |= SET_SIGN_CONTEXT_C1;
										sign_context2 |= SET_SIGN_CONTEXT_C2;
										sign_context3 |= SET_SIGN_CONTEXT_C3;
									}
								}
								is_coded |= 0x40000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos D */
							if((significant & 0x80000) == 0 && (context & 0xFF000000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF000000) >> 24], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 2 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 2 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 2 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 3)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x80000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 20) & 0xF) | ((context >> 24) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x80000;
										sign_context1 |= SET_SIGN_CONTEXT_D1;
										sign_context2 |= SET_SIGN_CONTEXT_D2;
										sign_context3 |= SET_SIGN_CONTEXT_D3;
									}
								}
								is_coded |= 0x80000;
							}
							*((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y))	= sign_context1;
							*((PDC_uint32*)(sign_context_base_address1))						= sign_context2;
							*((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y))	= sign_context3;
						}

						if((significant & 0xF00000) != 0xF00000){

							pos_x						= pos_x_base + 5;
							significante_context_use	= &significante_context[pos_y_base + pos_x * significante_context_size_y]; 
							
							sign_context_base_address1 = sign_context_base_address + pos_x * sign_context_size_y; 
							sign_context1	= *((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y));
							sign_context2	= *((PDC_uint32*)(sign_context_base_address1));
							sign_context3	= *((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y));

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos A */
							if((significant & 0x100000) == 0 && (context & 0xFF) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[context & 0xFF], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use - 1));
									context3_address = ((PDC_uint32*)(significante_context_use - 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * pos_y_base) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x100000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 8) & 0xF) | ( context & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x100000;
										sign_context1 |= SET_SIGN_CONTEXT_A1;
										sign_context2 |= SET_SIGN_CONTEXT_A2;
										sign_context3 |= SET_SIGN_CONTEXT_A3;
									}
								}
								is_coded |= 0x100000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos B */
							if((significant & 0x200000) == 0 && (context & 0xFF00) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF00) >> 8], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use));
									context3_address = ((PDC_uint32*)(significante_context_use + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 1)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x200000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 12) & 0xF) | ( (context >> 8) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x200000;
										sign_context1 |= SET_SIGN_CONTEXT_B1;
										sign_context2 |= SET_SIGN_CONTEXT_B2;
										sign_context3 |= SET_SIGN_CONTEXT_B3;
									}
								}
								is_coded |= 0x200000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos C */
							if((significant & 0x400000) == 0 && (context & 0xFF0000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF0000) >> 16], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 1 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 2)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x400000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 16) & 0xF) | ((context >> 16) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x400000;
										sign_context1 |= SET_SIGN_CONTEXT_C1;
										sign_context2 |= SET_SIGN_CONTEXT_C2;
										sign_context3 |= SET_SIGN_CONTEXT_C3;
									}
								}
								is_coded |= 0x400000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos D */
							if((significant & 0x800000) == 0 && (context & 0xFF000000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF000000) >> 24], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 2 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 2 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 2 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 3)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x800000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 20) & 0xF) | ((context >> 24) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x800000;
										sign_context1 |= SET_SIGN_CONTEXT_D1;
										sign_context2 |= SET_SIGN_CONTEXT_D2;
										sign_context3 |= SET_SIGN_CONTEXT_D3;
									}
								}
								is_coded |= 0x800000;
							}
							*((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y))	= sign_context1;
							*((PDC_uint32*)(sign_context_base_address1))						= sign_context2;
							*((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y))	= sign_context3;
						}
					}

					if((significant & 0xFF000000) != 0xFF000000){
						if((significant & 0x0F000000) != 0x0F000000){
							pos_x						= pos_x_base + 6;
							significante_context_use	= &significante_context[pos_y_base + pos_x * significante_context_size_y]; 
							
							sign_context_base_address1 = sign_context_base_address + pos_x * sign_context_size_y; 
							sign_context1	= *((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y));
							sign_context2	= *((PDC_uint32*)(sign_context_base_address1));
							sign_context3	= *((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y));

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos A */
							if((significant & 0x1000000) == 0 && (context & 0xFF) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[context & 0xFF], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use - 1));
									context3_address = ((PDC_uint32*)(significante_context_use - 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * pos_y_base) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x1000000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 8) & 0xF) | ( context & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x1000000;
										sign_context1 |= SET_SIGN_CONTEXT_A1;
										sign_context2 |= SET_SIGN_CONTEXT_A2;
										sign_context3 |= SET_SIGN_CONTEXT_A3;
									}
								}
								is_coded |= 0x1000000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos B */
							if((significant & 0x2000000) == 0 && (context & 0xFF00) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF00) >> 8], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use));
									context3_address = ((PDC_uint32*)(significante_context_use + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 1)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x2000000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 12) & 0xF) | ( (context >> 8) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x2000000;
										sign_context1 |= SET_SIGN_CONTEXT_B1;
										sign_context2 |= SET_SIGN_CONTEXT_B2;
										sign_context3 |= SET_SIGN_CONTEXT_B3;
									}
								}
								is_coded |= 0x2000000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos C */
							if((significant & 0x4000000) == 0 && (context & 0xFF0000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF0000) >> 16], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 1 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 2)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x4000000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 16) & 0xF) | ((context >> 16) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x4000000;
										sign_context1 |= SET_SIGN_CONTEXT_C1;
										sign_context2 |= SET_SIGN_CONTEXT_C2;
										sign_context3 |= SET_SIGN_CONTEXT_C3;
									}
								}
								is_coded |= 0x4000000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos D */
							if((significant & 0x8000000) == 0 && (context & 0xFF000000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF000000) >> 24], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 2 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 2 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 2 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 3)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x8000000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 20) & 0xF) | ((context >> 24) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x8000000;
										sign_context1 |= SET_SIGN_CONTEXT_D1;
										sign_context2 |= SET_SIGN_CONTEXT_D2;
										sign_context3 |= SET_SIGN_CONTEXT_D3;
									}
								}
								is_coded |= 0x8000000;
							}
							*((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y))	= sign_context1;
							*((PDC_uint32*)(sign_context_base_address1))						= sign_context2;
							*((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y))	= sign_context3;
						}
						if((significant & 0xF0000000) != 0xF0000000){
							
							pos_x						= pos_x_base + 7;
							significante_context_use	= &significante_context[pos_y_base + pos_x * significante_context_size_y]; 
							
							sign_context_base_address1 = sign_context_base_address + pos_x * sign_context_size_y; 
							sign_context1	= *((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y));
							sign_context2	= *((PDC_uint32*)(sign_context_base_address1));
							sign_context3	= *((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y));

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos A */
							if((significant & 0x10000000) == 0 && (context & 0xFF) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[context & 0xFF], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use - 1));
									context3_address = ((PDC_uint32*)(significante_context_use - 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * pos_y_base) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x10000000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 8) & 0xF) | ( context & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x10000000;
										sign_context1 |= SET_SIGN_CONTEXT_A1;
										sign_context2 |= SET_SIGN_CONTEXT_A2;
										sign_context3 |= SET_SIGN_CONTEXT_A3;
									}
								}
								is_coded |= 0x10000000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos B */
							if((significant & 0x20000000) == 0 && (context & 0xFF00) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF00) >> 8], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use));
									context3_address = ((PDC_uint32*)(significante_context_use + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 1)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x20000000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 12) & 0xF) | ( (context >> 8) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x20000000;
										sign_context1 |= SET_SIGN_CONTEXT_B1;
										sign_context2 |= SET_SIGN_CONTEXT_B2;
										sign_context3 |= SET_SIGN_CONTEXT_B3;
									}
								}
								is_coded |= 0x20000000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos C */
							if((significant & 0x40000000) == 0 && (context & 0xFF0000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF0000) >> 16], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 1 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 1 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 1 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 2)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x40000000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 16) & 0xF) | ((context >> 16) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x40000000;
										sign_context1 |= SET_SIGN_CONTEXT_C1;
										sign_context2 |= SET_SIGN_CONTEXT_C2;
										sign_context3 |= SET_SIGN_CONTEXT_C3;
									}
								}
								is_coded |= 0x40000000;
							}

							context = *((PDC_uint32*)significante_context_use);
							/* Decode Pos D */
							if((significant & 0x80000000) == 0 && (context & 0xFF000000) != 0){
								decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF000000) >> 24], codeword);
								if(decoder->D != 0){
									context1_address = ((PDC_uint32*)(significante_context_use + 2 - significante_context_size_y));
									context2_address = ((PDC_uint32*)(significante_context_use + 2 ));
									context3_address = ((PDC_uint32*)(significante_context_use + 2 + significante_context_size_y));

									*context1_address |= SET_CONTEXT_1;
									*context2_address |= SET_CONTEXT_2;
									*context3_address |= SET_CONTEXT_3;

									pos_value = (size_x * (pos_y_base + 3)) + pos_x;
									if(value_size == STATE_BIT_8){
										value8[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_16){
										value16[pos_value]	|= 1 << bit_plane;
									}else if(value_size == STATE_BIT_32){
										value32[pos_value]	|= 1 << bit_plane;
									}
									significant |= 0x80000000;
									/* Decode sign */
									sign_context_use = ((sign_context2 >> 20) & 0xF) | ((context >> 24) & 0xF0);
									decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
									if(decoder->D != 0){
										sign |= 0x80000000;
										sign_context1 |= SET_SIGN_CONTEXT_D1;
										sign_context2 |= SET_SIGN_CONTEXT_D2;
										sign_context3 |= SET_SIGN_CONTEXT_D3;
									}
								}
								is_coded |= 0x80000000;
							}
							*((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y))	= sign_context1;
							*((PDC_uint32*)(sign_context_base_address1))						= sign_context2;
							*((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y))	= sign_context3;
						}
					}
				}
				
				significant_address[significant_base_pos + significant_pos] = significant;
				sign_address[significant_base_pos + significant_pos]		= sign;
				is_coded_address[significant_base_pos + significant_pos]	= is_coded;
			}
			significant_pos += 1;
		}
		
		if(significant_rest != 0){
			pos_x					= significant_pos * 8;
			significant_rest_pos	= 0;
			pos_x_end				= pos_x + significant_rest;
			significant				= significant_address[significant_base_pos + significant_pos];
			sign					= sign_address[significant_base_pos + significant_pos];
			is_coded				= is_coded_address[significant_base_pos + significant_pos];

			while(pos_x < pos_x_end){
				shift				= significant * 4;
				significant_temp	= (significant >> shift) & 0xF;
				is_coded_temp		= (is_coded >> shift) & 0xF;
				sign_temp			= (sign >> shift) & 0xF;
				
			
				significante_context_use	= &significante_context[pos_y_base + pos_x * significante_context_size_y]; 
				
				sign_context_base_address1	= sign_context_base_address + pos_x * sign_context_size_y; 
				sign_context1				= *((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y));
				sign_context2				= *((PDC_uint32*)(sign_context_base_address1));
				sign_context3				= *((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y));

				context = *((PDC_uint32*)significante_context_use);
				/* Decode Pos A */
				if((significant_temp & 0x1) == 0 && (context & 0xFF) != 0){
					decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[context & 0xFF], codeword);
					if(decoder->D != 0){
						context1_address = ((PDC_uint32*)(significante_context_use - 1 - significante_context_size_y));
						context2_address = ((PDC_uint32*)(significante_context_use - 1));
						context3_address = ((PDC_uint32*)(significante_context_use - 1 + significante_context_size_y));

						*context1_address |= SET_CONTEXT_1;
						*context2_address |= SET_CONTEXT_2;
						*context3_address |= SET_CONTEXT_3;

						pos_value = (size_x * pos_y_base) + pos_x;
						if(value_size == STATE_BIT_8){
							value8[pos_value]	|= 1 << bit_plane;
						}else if(value_size == STATE_BIT_16){
							value16[pos_value]	|= 1 << bit_plane;
						}else if(value_size == STATE_BIT_32){
							value32[pos_value]	|= 1 << bit_plane;
						}
						significant_temp |= 0x01;
						/* Decode sign */
						sign_context_use = ((sign_context2 >> 8) & 0xF) | ( context & 0xF0);
						decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
						if(decoder->D != 0){
							sign_temp |= 0x1;
							sign_context1 |= SET_SIGN_CONTEXT_A1;
							sign_context2 |= SET_SIGN_CONTEXT_A2;
							sign_context3 |= SET_SIGN_CONTEXT_A3;
						}
					}
					is_coded_temp |= 0x01;
				}

				context = *((PDC_uint32*)significante_context_use);
				/* Decode Pos B */
				if((significant_temp & 0x2) == 0 && (context & 0xFF00) != 0){
					decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF00) >> 8], codeword);
					if(decoder->D != 0){
						context1_address = ((PDC_uint32*)(significante_context_use - significante_context_size_y));
						context2_address = ((PDC_uint32*)(significante_context_use));
						context3_address = ((PDC_uint32*)(significante_context_use + significante_context_size_y));

						*context1_address |= SET_CONTEXT_1;
						*context2_address |= SET_CONTEXT_2;
						*context3_address |= SET_CONTEXT_3;

						pos_value = (size_x * (pos_y_base + 1)) + pos_x;
						if(value_size == STATE_BIT_8){
							value8[pos_value]	|= 1 << bit_plane;
						}else if(value_size == STATE_BIT_16){
							value16[pos_value]	|= 1 << bit_plane;
						}else if(value_size == STATE_BIT_32){
							value32[pos_value]	|= 1 << bit_plane;
						}
						significant_temp |= 0x02;
						/* Decode sign */
						sign_context_use = ((sign_context2 >> 12) & 0xF) | ( (context >> 8) & 0xF0);
						decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
						if(decoder->D != 0){
							sign_temp |= 0x2;
							sign_context1 |= SET_SIGN_CONTEXT_B1;
							sign_context2 |= SET_SIGN_CONTEXT_B2;
							sign_context3 |= SET_SIGN_CONTEXT_B3;
						}
					}
					is_coded_temp |= 0x02;
				}

				context = *((PDC_uint32*)significante_context_use);
				/* Decode Pos C */
				if((significant_temp & 0x4) == 0 && (context & 0xFF0000) != 0){
					decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF0000) >> 16], codeword);
					if(decoder->D != 0){
						context1_address = ((PDC_uint32*)(significante_context_use + 1 - significante_context_size_y));
						context2_address = ((PDC_uint32*)(significante_context_use + 1 ));
						context3_address = ((PDC_uint32*)(significante_context_use + 1 + significante_context_size_y));

						*context1_address |= SET_CONTEXT_1;
						*context2_address |= SET_CONTEXT_2;
						*context3_address |= SET_CONTEXT_3;

						pos_value = (size_x * (pos_y_base + 2)) + pos_x;
						if(value_size == STATE_BIT_8){
							value8[pos_value]	|= 1 << bit_plane;
						}else if(value_size == STATE_BIT_16){
							value16[pos_value]	|= 1 << bit_plane;
						}else if(value_size == STATE_BIT_32){
							value32[pos_value]	|= 1 << bit_plane;
						}
						significant_temp |= 0x04;
						/* Decode sign */
						sign_context_use = ((sign_context2 >> 16) & 0xF) | ((context >> 16) & 0xF0);
						decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
						if(decoder->D != 0){
							sign_temp |= 0x4;
							sign_context1 |= SET_SIGN_CONTEXT_C1;
							sign_context2 |= SET_SIGN_CONTEXT_C2;
							sign_context3 |= SET_SIGN_CONTEXT_C3;
						}
					}
					is_coded_temp |= 0x04;
				}

				context = *((PDC_uint32*)significante_context_use);
				/* Decode Pos D */
				if((significant_temp & 0x8) == 0 && (context & 0xFF000000) != 0){
					decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF000000) >> 24], codeword);
					if(decoder->D != 0){
						context1_address = ((PDC_uint32*)(significante_context_use + 2 - significante_context_size_y));
						context2_address = ((PDC_uint32*)(significante_context_use + 2 ));
						context3_address = ((PDC_uint32*)(significante_context_use + 2 + significante_context_size_y));

						*context1_address |= SET_CONTEXT_1;
						*context2_address |= SET_CONTEXT_2;
						*context3_address |= SET_CONTEXT_3;

						pos_value = (size_x * (pos_y_base + 3)) + pos_x;
						if(value_size == STATE_BIT_8){
							value8[pos_value]	|= 1 << bit_plane;
						}else if(value_size == STATE_BIT_16){
							value16[pos_value]	|= 1 << bit_plane;
						}else if(value_size == STATE_BIT_32){
							value32[pos_value]	|= 1 << bit_plane;
						}
						significant_temp |= 0x08;
						/* Decode sign */
						sign_context_use = ((sign_context2 >> 20) & 0xF) | ((context >> 24) & 0xF0);
						decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
						if(decoder->D != 0){
							sign_temp |= 0x8;
							sign_context1 |= SET_SIGN_CONTEXT_D1;
							sign_context2 |= SET_SIGN_CONTEXT_D2;
							sign_context3 |= SET_SIGN_CONTEXT_D3;
						}
					}
					is_coded_temp |= 0x08;
				}
				*((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y))	= sign_context1;
				*((PDC_uint32*)(sign_context_base_address1))						= sign_context2;
				*((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y))	= sign_context3;

			
				significant		|= (significant_temp << shift);
				is_coded		|= (is_coded_temp << shift);
				sign			|= (sign_temp << shift);
			}
			significant_address[significant_base_pos + significant_pos] = significant;
			sign_address[significant_base_pos + significant_pos]		= sign;
			is_coded_address[significant_base_pos + significant_pos]	= is_coded;
		}
	}

	if(extrastreet_size != 0){
		max_street;
		pos_street					= max_street;
		significant_base_pos		= pos_street * size_x_bit;
		pos_y_base					= pos_street * 4;
		sign_context_base_address	= codeblock->sign_context + (2 * pos_street) - 1;
		significant_pos				= 0;
		pos_x						= 0;
		significant_pos_x			= 0;
		significant_base_pos		= pos_street * size_x_bit;
		pos_y_base					= pos_street * 4;
		sign_context_base_address	= codeblock->sign_context + (2 * pos_street) - 1;

		while(pos_x = 0 < size_x){
			if(significant_pos_x >= 8){
				significant_pos_x	= 0;
				significant_pos		+= 1;
				significant			= significant_address[significant_base_pos + significant_pos];
				sign				= sign_address[significant_base_pos + significant_pos];
				is_coded			= is_coded_address[significant_base_pos + significant_pos];
			}
			shift				= significant_pos_x * 4;
			significant_temp	= (significant >> shift) & 0xF;
			is_coded_temp		= (is_coded >> shift) & 0xF;
			sign_temp			= (sign >> shift) & 0xF;
			


			significante_context_use	= &significante_context[pos_y_base + pos_x * significante_context_size_y]; 
				
			sign_context_base_address1	= sign_context_base_address + pos_x * sign_context_size_y; 
			sign_context1				= *((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y));
			sign_context2				= *((PDC_uint32*)(sign_context_base_address1));
			sign_context3				= *((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y));

			context = *((PDC_uint32*)significante_context_use);
			/* Decode Pos A */
			if((significant_temp & 0x1) == 0 && (context & 0xFF) != 0){
				decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[context & 0xFF], codeword);
				if(decoder->D != 0){
					context1_address = ((PDC_uint32*)(significante_context_use - 1 - significante_context_size_y));
					context2_address = ((PDC_uint32*)(significante_context_use - 1));
					context3_address = ((PDC_uint32*)(significante_context_use - 1 + significante_context_size_y));

					*context1_address |= SET_CONTEXT_1;
					*context2_address |= SET_CONTEXT_2;
					*context3_address |= SET_CONTEXT_3;

					pos_value = (size_x * pos_y_base) + pos_x;
					if(value_size == STATE_BIT_8){
						value8[pos_value]	|= 1 << bit_plane;
					}else if(value_size == STATE_BIT_16){
						value16[pos_value]	|= 1 << bit_plane;
					}else if(value_size == STATE_BIT_32){
						value32[pos_value]	|= 1 << bit_plane;
					}
					significant_temp |= 0x01;
					/* Decode sign */
					sign_context_use = ((sign_context2 >> 8) & 0xF) | ( context & 0xF0);
					decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
					if(decoder->D != 0){
						sign_temp |= 0x1;
						sign_context1 |= SET_SIGN_CONTEXT_A1;
						sign_context2 |= SET_SIGN_CONTEXT_A2;
						sign_context3 |= SET_SIGN_CONTEXT_A3;
					}
				}
				is_coded_temp |= 0x01;
			}

			context = *((PDC_uint32*)significante_context_use);
			/* Decode Pos B */
			if((significant_temp & 0x2) == 0 && (context & 0xFF00) != 0){
				decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF00) >> 8], codeword);
				if(decoder->D != 0){
					context1_address = ((PDC_uint32*)(significante_context_use - significante_context_size_y));
					context2_address = ((PDC_uint32*)(significante_context_use));
					context3_address = ((PDC_uint32*)(significante_context_use + significante_context_size_y));

					*context1_address |= SET_CONTEXT_1;
					*context2_address |= SET_CONTEXT_2;
					*context3_address |= SET_CONTEXT_3;

					pos_value = (size_x * (pos_y_base + 1)) + pos_x;
					if(value_size == STATE_BIT_8){
						value8[pos_value]	|= 1 << bit_plane;
					}else if(value_size == STATE_BIT_16){
						value16[pos_value]	|= 1 << bit_plane;
					}else if(value_size == STATE_BIT_32){
						value32[pos_value]	|= 1 << bit_plane;
					}
					significant_temp |= 0x02;
					/* Decode sign */
					sign_context_use = ((sign_context2 >> 12) & 0xF) | ( (context >> 8) & 0xF0);
					decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
					if(decoder->D != 0){
						sign_temp |= 0x2;
						sign_context1 |= SET_SIGN_CONTEXT_B1;
						sign_context2 |= SET_SIGN_CONTEXT_B2;
						sign_context3 |= SET_SIGN_CONTEXT_B3;
					}
				}
				is_coded_temp |= 0x02;
			}

			context = *((PDC_uint32*)significante_context_use);
			/* Decode Pos C */
			if((significant_temp & 0x4) == 0 && (context & 0xFF0000) != 0){
				decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF0000) >> 16], codeword);
				if(decoder->D != 0){
					context1_address = ((PDC_uint32*)(significante_context_use + 1 - significante_context_size_y));
					context2_address = ((PDC_uint32*)(significante_context_use + 1 ));
					context3_address = ((PDC_uint32*)(significante_context_use + 1 + significante_context_size_y));

					*context1_address |= SET_CONTEXT_1;
					*context2_address |= SET_CONTEXT_2;
					*context3_address |= SET_CONTEXT_3;

					pos_value = (size_x * (pos_y_base + 2)) + pos_x;
					if(value_size == STATE_BIT_8){
						value8[pos_value]	|= 1 << bit_plane;
					}else if(value_size == STATE_BIT_16){
						value16[pos_value]	|= 1 << bit_plane;
					}else if(value_size == STATE_BIT_32){
						value32[pos_value]	|= 1 << bit_plane;
					}
					significant_temp |= 0x04;
					/* Decode sign */
					sign_context_use = ((sign_context2 >> 16) & 0xF) | ((context >> 16) & 0xF0);
					decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
					if(decoder->D != 0){
						sign_temp |= 0x4;
						sign_context1 |= SET_SIGN_CONTEXT_C1;
						sign_context2 |= SET_SIGN_CONTEXT_C2;
						sign_context3 |= SET_SIGN_CONTEXT_C3;
					}
				}
				is_coded_temp |= 0x04;
			}

			context = *((PDC_uint32*)significante_context_use);
			/* Decode Pos D */
			if((significant_temp & 0x8) == 0 && (context & 0xFF000000) != 0){
				decoder = PDC_Aed_decode_01(exception, decoder, PDK_context_states[(context & 0xFF000000) >> 24], codeword);
				if(decoder->D != 0){
					context1_address = ((PDC_uint32*)(significante_context_use + 2 - significante_context_size_y));
					context2_address = ((PDC_uint32*)(significante_context_use + 2 ));
					context3_address = ((PDC_uint32*)(significante_context_use + 2 + significante_context_size_y));

					*context1_address |= SET_CONTEXT_1;
					*context2_address |= SET_CONTEXT_2;
					*context3_address |= SET_CONTEXT_3;

					pos_value = (size_x * (pos_y_base + 3)) + pos_x;
					if(value_size == STATE_BIT_8){
						value8[pos_value]	|= 1 << bit_plane;
					}else if(value_size == STATE_BIT_16){
						value16[pos_value]	|= 1 << bit_plane;
					}else if(value_size == STATE_BIT_32){
						value32[pos_value]	|= 1 << bit_plane;
					}
					significant_temp |= 0x08;
					/* Decode sign */
					sign_context_use = ((sign_context2 >> 20) & 0xF) | ((context >> 24) & 0xF0);
					decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_use], codeword); 
					if(decoder->D != 0){
						sign_temp |= 0x8;
						sign_context1 |= SET_SIGN_CONTEXT_D1;
						sign_context2 |= SET_SIGN_CONTEXT_D2;
						sign_context3 |= SET_SIGN_CONTEXT_D3;
					}
				}
				is_coded_temp |= 0x08;
			}
			*((PDC_uint32*)(sign_context_base_address1 - sign_context_size_y))	= sign_context1;
			*((PDC_uint32*)(sign_context_base_address1))						= sign_context2;
			*((PDC_uint32*)(sign_context_base_address1 + sign_context_size_y))	= sign_context3;






			significant		|= (significant_temp << shift);
			is_coded		|= (is_coded_temp << shift);
			sign			|= (sign_temp << shift);
		
			significant_address[significant_base_pos + significant_pos] = significant;
			sign_address[significant_base_pos + significant_pos]		= sign;
			is_coded_address[significant_base_pos + significant_pos]	= is_coded;

			pos_x				+= 1;
			significant_pos_x	+= 1;

		}
	}
	return back;
}



/*
 *
 */
PDC_Codeblock* PDC_Codeblock_cleanup_decoding_pass(PDC_Exception* exception, PDC_Codeblock* codeblock, PDC_Buffer* codeword)
{
	PDC_uint32		max_street, max_street_rest, pos_street, pos_x, pos_x_end, pos_y_base, pos_y,
					significant_size, significant_pos, significant_pos_base, sign_context_size_x,
					significant_pos_x, siginficant_pos_shift, *sign, sign_value,
					sign_value_temp, *significant, significant_value, significant_value_temp,
					context_size_y, *context1, *context2, *context3, *is_coded, is_coded_value,
					is_coded_value_temp, runlengthpos, bit_plane, *value32, size_x, size_y, size_y_rest, sign_context1, sign_context2,
					sign_context3, context_value, *context_address, *context_address1, *context_address2, 
					*context_address3, sign_pos_base, sign_context_value1, sign_context_value2, 
					sign_context_value3, sign_context_size_y, significant_pos_shift, pos_value,
					sign_context_value;
	PDC_uint16		*value16;
	PDC_uint8		*value8, *context_base_address1, *context_base_address2, *context, *sign_context,
					*sign_context_address1, *sign_context_address2, *sign_context_address3, *BDK_context_states;
	PDC_STATE_BIT	value_size;

	PDC_Arithmetic_entropy_decoder *decoder;

	pos_x					= codeblock->pos_x;
	size_x					= codeblock->cx1 - codeblock->cx0;
	size_y					= codeblock->cy1 - codeblock->cy0;
	max_street				= codeblock->num_street;
	pos_street				= codeblock->street;
	pos_x_end				= size_x;
	significant_size		= PDC_i_ceiling(size_x, 8);
	sign_context_size_y		= codeblock->sign_context_size_y;
	sign_context_size_x		= codeblock->sign_context_size_x;
	sign					= codeblock->sign;
	significant				= codeblock->significant;
	context					= codeblock->significante_context;			
	context_size_y			= codeblock->significante_context_size_y;
	decoder					= codeblock->decoder;
	is_coded				= codeblock->is_coded;
	bit_plane				= codeblock->bit_plane;
	value8					= codeblock->value8;
	value16					= codeblock->value16;
	value32					= codeblock->value32;
	sign_context			= codeblock->sign_context;
	value_size				= codeblock->value_size;
	BDK_context_states		= codeblock->BDK_context_states;


	if(value_size == STATE_BIT_8){
		bit_plane = 7 - bit_plane;
	}else if(value_size == STATE_BIT_16){
		bit_plane = 15 - bit_plane;
	}else if(value_size == STATE_BIT_32){
		bit_plane = 31 - bit_plane;
	}

	max_street_rest = max_street;
	size_y_rest = size_y % 4;
	if(size_y_rest != 0){	
		max_street -= 1;
	}


	while(pos_street < max_street){
		pos_y_base				= 4 * pos_street;
		sign_pos_base			= 2 * pos_street - 1;
		significant_pos			= pos_street * significant_size;
		significant_pos_x		= 0;
		significant_pos_shift	= 0;

		sign_value				= sign[significant_pos + significant_pos_x];
		significant_value		= significant[significant_pos + significant_pos_x];
		is_coded_value			= is_coded[significant_pos + significant_pos_x];

		sign_context_address2	= sign_context + (pos_y_base + (pos_x - 1) * sign_context_size_y);
		sign_context_address3	= sign_context_address2 + sign_context_size_y;

		sign_context_value2		= *((PDC_uint32*)sign_context_address2);		
		sign_context_value3		= *((PDC_uint32*)sign_context_address3);

		context_base_address1	= codeblock->significante_context + pos_y_base;

		for(;pos_x < pos_x_end; pos_x += 1){
			significant_value_temp	= (significant_value >> significant_pos_shift)& 0x0F;
			sign_value_temp			= (sign_value >> significant_pos_shift) & 0x0F;
			is_coded_value_temp		= (is_coded_value >> significant_pos_shift) & 0x0F;
			context_address			= (PDC_uint32*)(context_base_address1 + pos_x * context_size_y);
			context_value			= *context_address;

			
			sign_context_address1	= sign_context_address2;
			sign_context_address2	= sign_context_address3;
			sign_context_address3	= sign_context_address2 + sign_context_size_y;

			sign_context_value1		= sign_context_value2;
			sign_context_value2		= sign_context_value3;
			sign_context_value3		= *((PDC_uint32*)sign_context_address3);


			/*
			 *	Run-length decoder
			 */
			if((context_value | is_coded_value_temp) == 0){
				decoder = PDC_Aed_decode_01(exception, decoder, RUNLENGTHCONTEXT, codeword);
				if(decoder->D != 0){
					runlengthpos = 0;
					decoder = PDC_Aed_decode_01(exception, decoder, UNIFORMCONTEXT, codeword);
					if(decoder->D != 0){
						runlengthpos = 2;
					}
					decoder = PDC_Aed_decode_01(exception, decoder, UNIFORMCONTEXT, codeword);
					if(decoder->D != 0){
						runlengthpos += 1;
					}

					switch(runlengthpos){
						case 0:
							pos_y = 1;
							pos_value = (size_x * (pos_y_base)) + pos_x;
							if(value_size == STATE_BIT_8){
								value8[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_16){
								value16[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_32){
								value32[pos_value]	|= 1 << bit_plane;
							}
							context_address2 = (PDC_uint32*)(context + (pos_x * context_size_y + pos_y_base - 1));
							context_address1 = (PDC_uint32*)((PDC_uint8*)context_address2 - context_size_y);
							context_address3 = (PDC_uint32*)((PDC_uint8*)context_address2 + context_size_y);

							*context_address1 |= SET_CONTEXT_1;
							*context_address2 |= SET_CONTEXT_2;
							*context_address3 |= SET_CONTEXT_3;
							/* decode sign */
							sign_context_value = (context_value & 0xF0) | ((sign_context_value2 >> 8) & 0x0F);
							decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_value], codeword);
							if(decoder->D != 0){
								sign_value_temp |= (0x01 ^ (0x1 & XORbit[sign_context_value]));
								sign_context1 |= SET_SIGN_CONTEXT_A1;
								sign_context2 |= SET_SIGN_CONTEXT_A2;
								sign_context3 |= SET_SIGN_CONTEXT_A3;
							}
							break;
						case 1:
							pos_y = 2;
							pos_value = (size_x * (pos_y_base + 1)) + pos_x;
							if(value_size == STATE_BIT_8){
								value8[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_16){
								value16[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_32){
								value32[pos_value]	|= 1 << bit_plane;
							}
							context_address2 = (PDC_uint32*)(context + (pos_x * context_size_y + pos_y_base));
							context_address1 = (PDC_uint32*)((PDC_uint8*)context_address2 - context_size_y);
							context_address3 = (PDC_uint32*)((PDC_uint8*)context_address2 + context_size_y);

							*context_address1 |= SET_CONTEXT_1;
							*context_address2 |= SET_CONTEXT_2;
							*context_address3 |= SET_CONTEXT_3;

							/* decode sign */
							sign_context_value = ((context_value >> 8) & 0xF0) | ((sign_context_value2 >> 12) & 0x0F);
							decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_value], codeword);
							if(decoder->D != 0){
								sign_value_temp |= (0x02 ^ (0x2 & XORbit[sign_context_value]));
								sign_context1 |= SET_SIGN_CONTEXT_B1;
								sign_context2 |= SET_SIGN_CONTEXT_B2;
								sign_context3 |= SET_SIGN_CONTEXT_B3;
							}
							break;
						case 2:
							pos_y = 3;
							pos_value = (size_x * (pos_y_base + 2)) + pos_x;
							if(value_size == STATE_BIT_8){
								value8[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_16){
								value16[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_32){
								value32[pos_value]	|= 1 << bit_plane;
							}
							context_address2 = (PDC_uint32*)(context + (pos_x * context_size_y + pos_y_base + 1));
							context_address1 = (PDC_uint32*)((PDC_uint8*)context_address2 - context_size_y);
							context_address3 = (PDC_uint32*)((PDC_uint8*)context_address2 + context_size_y);

							*context_address1 |= SET_CONTEXT_1;
							*context_address2 |= SET_CONTEXT_2;
							*context_address3 |= SET_CONTEXT_3;
							/* decode sign */
							sign_context_value = ((context_value >> 16) & 0xF0) | ((sign_context_value2 >> 16) & 0x0F);
							decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_value], codeword);
							if(decoder->D != 0){
								sign_value_temp |= (0x04 ^ (0x4 & XORbit[sign_context_value]));
								sign_context1 |= SET_SIGN_CONTEXT_C1;
								sign_context2 |= SET_SIGN_CONTEXT_C2;
								sign_context3 |= SET_SIGN_CONTEXT_C3;
							}
							break;
						case 3:
							pos_y = 4;
							pos_value = (size_x * (pos_y_base + 3)) + pos_x;
							if(value_size == STATE_BIT_8){
								value8[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_16){
								value16[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_32){
								value32[pos_value]	|= 1 << bit_plane;
							}
							context_address2 = (PDC_uint32*)(context + (pos_x * context_size_y + pos_y_base + 2));
							context_address1 = (PDC_uint32*)((PDC_uint8*)context_address2 - context_size_y);
							context_address3 = (PDC_uint32*)((PDC_uint8*)context_address2 + context_size_y);

							*context_address1 |= SET_CONTEXT_1;
							*context_address2 |= SET_CONTEXT_2;
							*context_address3 |= SET_CONTEXT_3;
							/* decode sign */
							sign_context_value = ((context_value >> 24) & 0xF0) | ((sign_context_value2 >> 20) & 0x0F);
							decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_value], codeword);
							if(decoder->D != 0){
								sign_value_temp |= (0x08 ^ (0x8 & XORbit[sign_context_value]));
								sign_context1 |= SET_SIGN_CONTEXT_D1;
								sign_context2 |= SET_SIGN_CONTEXT_D2;
								sign_context3 |= SET_SIGN_CONTEXT_D3;
							}
							break;
					}
				}else{
					pos_y = 4;
				}
			}else{
				pos_y = 0;
			}	

			for(;pos_y < 4; pos_y += 1){
				switch(pos_y){
					case 0:
						decoder = PDC_Aed_decode_01(exception, decoder, BDK_context_states[context_value & 0xFF], codeword);
						if(decoder->D != 0){
							pos_value = (size_x * (pos_y_base)) + pos_x;
							if(value_size == STATE_BIT_8){
								value8[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_16){
								value16[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_32){
								value32[pos_value]	|= 1 << bit_plane;
							}
							context_address2 = (PDC_uint32*)(context + (pos_x * context_size_y + pos_y_base - 1));
							context_address1 = (PDC_uint32*)((PDC_uint8*)context_address2 - context_size_y);
							context_address3 = (PDC_uint32*)((PDC_uint8*)context_address2 + context_size_y);

							*context_address1 |= SET_CONTEXT_1;
							*context_address2 |= SET_CONTEXT_2;
							*context_address3 |= SET_CONTEXT_3;
							/* decode sign */
							sign_context_value = ((context_value) & 0xF0) | ((sign_context_value2 >> 12) & 0x0F);
							decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_value], codeword);
							if(decoder->D != 0){
								sign_value_temp |= (0x08 ^ (0x8 & XORbit[sign_context_value]));
								sign_context1 |= SET_SIGN_CONTEXT_A1;
								sign_context2 |= SET_SIGN_CONTEXT_A2;
								sign_context3 |= SET_SIGN_CONTEXT_A3;
							}
						}
					case 1:
						context_value = *context_address;
						decoder = PDC_Aed_decode_01(exception, decoder, BDK_context_states[(context_value >> 8) & 0xFF], codeword);
						if(decoder->D != 0){
							pos_value = (size_x * (pos_y_base + 1)) + pos_x;
							if(value_size == STATE_BIT_8){
								value8[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_16){
								value16[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_32){
								value32[pos_value]	|= 1 << bit_plane;
							}
							context_address2 = (PDC_uint32*)(context + (pos_x * context_size_y + pos_y_base));
							context_address1 = (PDC_uint32*)((PDC_uint8*)context_address2 - context_size_y);
							context_address3 = (PDC_uint32*)((PDC_uint8*)context_address2 + context_size_y);

							*context_address1 |= SET_CONTEXT_1;
							*context_address2 |= SET_CONTEXT_2;
							*context_address3 |= SET_CONTEXT_3;
							/* decode sign */
							sign_context_value = ((context_value >> 8) & 0xF0) | ((sign_context_value2 >> 12) & 0x0F);
							decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_value], codeword);
							if(decoder->D != 0){
								sign_value_temp |= (0x08 ^ (0x8 & XORbit[sign_context_value]));
								sign_context1 |= SET_SIGN_CONTEXT_B1;
								sign_context2 |= SET_SIGN_CONTEXT_B2;
								sign_context3 |= SET_SIGN_CONTEXT_B3;
							}
						}

					case 2:
						context_value = *context_address;
						decoder = PDC_Aed_decode_01(exception, decoder, BDK_context_states[(context_value >> 16) & 0xFF], codeword);
						if(decoder->D != 0){
							pos_value = (size_x * (pos_y_base + 2)) + pos_x;
							if(value_size == STATE_BIT_8){
								value8[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_16){
								value16[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_32){
								value32[pos_value]	|= 1 << bit_plane;
							}
							context_address2 = (PDC_uint32*)(context + (pos_x * context_size_y + pos_y_base + 1));
							context_address1 = (PDC_uint32*)((PDC_uint8*)context_address2 - context_size_y);
							context_address3 = (PDC_uint32*)((PDC_uint8*)context_address2 + context_size_y);

							*context_address1 |= SET_CONTEXT_1;
							*context_address2 |= SET_CONTEXT_2;
							*context_address3 |= SET_CONTEXT_3;
							/* decode sign */
							sign_context_value = ((context_value >> 16) & 0xF0) | ((sign_context_value2 >> 16) & 0x0F);
							decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_value], codeword);
							if(decoder->D != 0){
								sign_value_temp |= (0x08 ^ (0x8 & XORbit[sign_context_value]));
								sign_context1 |= SET_SIGN_CONTEXT_C1;
								sign_context2 |= SET_SIGN_CONTEXT_C2;
								sign_context3 |= SET_SIGN_CONTEXT_C3;
							}
						}
					case 3:
						context_value = *context_address;
						pos_y = 4;
						decoder = PDC_Aed_decode_01(exception, decoder, BDK_context_states[(context_value >> 24) & 0xFF], codeword);
						if(decoder->D != 0){
							pos_value = (size_x * (pos_y_base + 3)) + pos_x;
							if(value_size == STATE_BIT_8){
								value8[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_16){
								value16[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_32){
								value32[pos_value]	|= 1 << bit_plane;
							}
							context_address2 = (PDC_uint32*)(context + (pos_x * context_size_y + pos_y_base + 2));
							context_address1 = (PDC_uint32*)((PDC_uint8*)context_address2 - context_size_y);
							context_address3 = (PDC_uint32*)((PDC_uint8*)context_address2 + context_size_y);

							*context_address1 |= SET_CONTEXT_1;
							*context_address2 |= SET_CONTEXT_2;
							*context_address3 |= SET_CONTEXT_3;
							/* decode sign */
							sign_context_value = ((context_value >> 24) & 0xF0) | ((sign_context_value2 >> 16) & 0x0F);
							decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_value], codeword);
							if(decoder->D != 0){
								sign_value_temp |= (0x08 ^ (0x8 & XORbit[sign_context_value]));
								sign_context1 |= SET_SIGN_CONTEXT_D1;
								sign_context2 |= SET_SIGN_CONTEXT_D2;
								sign_context3 |= SET_SIGN_CONTEXT_D3;
							}
						}
				}
			}

			significant_value	|= (significant_value_temp << significant_pos_shift);
			sign_value			|= (sign_value_temp << significant_pos_shift) ;
			is_coded_value		|= (is_coded_value_temp << significant_pos_shift);

			*((PDC_uint32*)sign_context_address1) = sign_context_value1;
			significant_pos_shift += 4;
			if(significant_pos_shift >= 32){
				sign[significant_pos + significant_pos_x]			= sign_value;
				significant[significant_pos + significant_pos_x]	= significant_value;
				is_coded[significant_pos + significant_pos_x]		= is_coded_value;

				significant_pos_x		+= 1;
				sign_value				= sign[significant_pos + significant_pos_x];
				significant_value		= significant[significant_pos + significant_pos_x];
				is_coded_value			= is_coded[significant_pos + significant_pos_x];
				significant_pos_shift	= 0;
			}
		}
		
		significant_value	|= (significant_value_temp << significant_pos_shift);
		sign_value			|= (sign_value_temp << significant_pos_shift) ;
		is_coded_value		|= (is_coded_value_temp << significant_pos_shift);

		sign[significant_pos + significant_pos_x]			= sign_value;
		significant[significant_pos + significant_pos_x]	= significant_value;
		is_coded[significant_pos + significant_pos_x]		= is_coded_value;
		
		pos_x		= 0;
		pos_street	+= 1;

	}

	while(pos_street < max_street_rest){
		pos_y_base				= 4 * pos_street;
		sign_pos_base			= 2 * pos_street - 1;
		significant_pos			= pos_street * significant_size;
		significant_pos_x		= 0;
		significant_pos_shift	= 0;

		sign_value				= sign[significant_pos + significant_pos_x];
		significant_value		= significant[significant_pos + significant_pos_x];
		is_coded_value			= is_coded[significant_pos + significant_pos_x];

		sign_context_address2	= sign_context + (pos_y_base + (pos_x - 1) * sign_context_size_y);
		sign_context_address3	= sign_context_address2 + sign_context_size_y;

		sign_context_value2		= *((PDC_uint32*)sign_context_address2);		
		sign_context_value3		= *((PDC_uint32*)sign_context_address3);

		context_base_address1	= codeblock->significante_context + pos_y_base;

		for(;pos_x < pos_x_end; pos_x += 1){
			significant_value_temp	= (significant_value >> significant_pos_shift)& 0x0F;
			sign_value_temp			= (sign_value >> significant_pos_shift) & 0x0F;
			is_coded_value_temp		= (is_coded_value >> significant_pos_shift) & 0x0F;
			context_address			= (PDC_uint32*)(context_base_address1 + pos_x * context_size_y);
			context_value			= *context_address;

			
			sign_context_address1	= sign_context_address2;
			sign_context_address2	= sign_context_address3;
			sign_context_address3	= sign_context_address2 + sign_context_size_y;

			sign_context_value1		= sign_context_value2;
			sign_context_value2		= sign_context_value3;
			sign_context_value3		= *((PDC_uint32*)sign_context_address3);

			pos_y = 0;
			for(;pos_y < size_y_rest; pos_y += 1){
				switch(pos_y){
					case 0:
						decoder = PDC_Aed_decode_01(exception, decoder, BDK_context_states[context_value & 0xFF], codeword);
						if(decoder->D != 0){
							pos_value = (size_x * (pos_y_base)) + pos_x;
							if(value_size == STATE_BIT_8){
								value8[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_16){
								value16[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_32){
								value32[pos_value]	|= 1 << bit_plane;
							}
							context_address2 = (PDC_uint32*)(context + (pos_x * context_size_y + pos_y_base - 1));
							context_address1 = (PDC_uint32*)((PDC_uint8*)context_address2 - context_size_y);
							context_address3 = (PDC_uint32*)((PDC_uint8*)context_address2 + context_size_y);

							*context_address1 |= SET_CONTEXT_1;
							*context_address2 |= SET_CONTEXT_2;
							*context_address3 |= SET_CONTEXT_3;
							/* decode sign */
							sign_context_value = ((context_value) & 0xF0) | ((sign_context_value2 >> 12) & 0x0F);
							decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_value], codeword);
							if(decoder->D != 0){
								sign_value_temp |= (0x08 ^ (0x8 & XORbit[sign_context_value]));
								sign_context1 |= SET_SIGN_CONTEXT_A1;
								sign_context2 |= SET_SIGN_CONTEXT_A2;
								sign_context3 |= SET_SIGN_CONTEXT_A3;
							}
						}
						pos_y += 1;
						break;
					case 1:
						context_value = *context_address;
						decoder = PDC_Aed_decode_01(exception, decoder, BDK_context_states[(context_value >> 8) & 0xFF], codeword);
						if(decoder->D != 0){
							pos_value = (size_x * (pos_y_base + 1)) + pos_x;
							if(value_size == STATE_BIT_8){
								value8[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_16){
								value16[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_32){
								value32[pos_value]	|= 1 << bit_plane;
							}
							context_address2 = (PDC_uint32*)(context + (pos_x * context_size_y + pos_y_base));
							context_address1 = (PDC_uint32*)((PDC_uint8*)context_address2 - context_size_y);
							context_address3 = (PDC_uint32*)((PDC_uint8*)context_address2 + context_size_y);

							*context_address1 |= SET_CONTEXT_1;
							*context_address2 |= SET_CONTEXT_2;
							*context_address3 |= SET_CONTEXT_3;
							/* decode sign */
							sign_context_value = ((context_value >> 8) & 0xF0) | ((sign_context_value2 >> 12) & 0x0F);
							decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_value], codeword);
							if(decoder->D != 0){
								sign_value_temp |= (0x08 ^ (0x8 & XORbit[sign_context_value]));
								sign_context1 |= SET_SIGN_CONTEXT_B1;
								sign_context2 |= SET_SIGN_CONTEXT_B2;
								sign_context3 |= SET_SIGN_CONTEXT_B3;
							}
						}
						pos_y += 1;
						break;
					case 2:
						context_value = *context_address;
						decoder = PDC_Aed_decode_01(exception, decoder, BDK_context_states[(context_value >> 16) & 0xFF], codeword);
						if(decoder->D != 0){
							pos_value = (size_x * (pos_y_base + 2)) + pos_x;
							if(value_size == STATE_BIT_8){
								value8[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_16){
								value16[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_32){
								value32[pos_value]	|= 1 << bit_plane;
							}
							context_address2 = (PDC_uint32*)(context + (pos_x * context_size_y + pos_y_base + 1));
							context_address1 = (PDC_uint32*)((PDC_uint8*)context_address2 - context_size_y);
							context_address3 = (PDC_uint32*)((PDC_uint8*)context_address2 + context_size_y);

							*context_address1 |= SET_CONTEXT_1;
							*context_address2 |= SET_CONTEXT_2;
							*context_address3 |= SET_CONTEXT_3;
							/* decode sign */
							sign_context_value = ((context_value >> 16) & 0xF0) | ((sign_context_value2 >> 16) & 0x0F);
							decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_value], codeword);
							if(decoder->D != 0){
								sign_value_temp |= (0x08 ^ (0x8 & XORbit[sign_context_value]));
								sign_context1 |= SET_SIGN_CONTEXT_C1;
								sign_context2 |= SET_SIGN_CONTEXT_C2;
								sign_context3 |= SET_SIGN_CONTEXT_C3;
							}
						}
						pos_y += 1;
						break;
					case 3:
						context_value = *context_address;
						pos_y = 4;
						decoder = PDC_Aed_decode_01(exception, decoder, BDK_context_states[(context_value >> 24) & 0xFF], codeword);
						if(decoder->D != 0){
							pos_value = (size_x * (pos_y_base + 3)) + pos_x;
							if(value_size == STATE_BIT_8){
								value8[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_16){
								value16[pos_value]	|= 1 << bit_plane;
							}else if(value_size == STATE_BIT_32){
								value32[pos_value]	|= 1 << bit_plane;
							}
							context_address2 = (PDC_uint32*)(context + (pos_x * context_size_y + pos_y_base + 2));
							context_address1 = (PDC_uint32*)((PDC_uint8*)context_address2 - context_size_y);
							context_address3 = (PDC_uint32*)((PDC_uint8*)context_address2 + context_size_y);

							*context_address1 |= SET_CONTEXT_1;
							*context_address2 |= SET_CONTEXT_2;
							*context_address3 |= SET_CONTEXT_3;
							/* decode sign */
							sign_context_value = ((context_value >> 24) & 0xF0) | ((sign_context_value2 >> 16) & 0x0F);
							decoder = PDC_Aed_decode_01(exception, decoder, PDC_context_signstates[sign_context_value], codeword);
							if(decoder->D != 0){
								sign_value_temp |= (0x08 ^ (0x8 & XORbit[sign_context_value]));
								sign_context1 |= SET_SIGN_CONTEXT_D1;
								sign_context2 |= SET_SIGN_CONTEXT_D2;
								sign_context3 |= SET_SIGN_CONTEXT_D3;
							}
						}
						pos_y += 1;
						break;
				}
			}

			significant_value	|= (significant_value_temp << significant_pos_shift);
			sign_value			|= (sign_value_temp << significant_pos_shift) ;
			is_coded_value		|= (is_coded_value_temp << significant_pos_shift);

			*((PDC_uint32*)sign_context_address1) = sign_context_value1;
			significant_pos_shift += 4;
			if(significant_pos_shift >= 32){
				sign[significant_pos + significant_pos_x]			= sign_value;
				significant[significant_pos + significant_pos_x]	= significant_value;
				is_coded[significant_pos + significant_pos_x]		= is_coded_value;

				significant_pos_x		+= 1;
				sign_value				= sign[significant_pos + significant_pos_x];
				significant_value		= significant[significant_pos + significant_pos_x];
				is_coded_value			= is_coded[significant_pos + significant_pos_x];
				significant_pos_shift	= 0;
			}
		}
		significant_value	|= (significant_value_temp << significant_pos_shift);
		sign_value			|= (sign_value_temp << significant_pos_shift) ;
		is_coded_value		|= (is_coded_value_temp << significant_pos_shift);

		pos_street += 1;
	}

	return codeblock;
}	



STOP_C

