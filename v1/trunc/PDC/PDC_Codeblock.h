/*
 * Copyright (C) 2008  Uwe Br�nen
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

#ifndef __PDC_CODEBLOCK_H__
#define __PDC_CODEBLOCK_H__

#include <stdlib.h>
#include "PDC_Parameter.h"
#include "PDC_Arithmetic_entropy_decoder.h"

START_C

	#define	SET_SIGN_CONTEXT_A1 0x0200
	#define	SET_SIGN_CONTEXT_A2 0x4080 
	#define	SET_SIGN_CONTEXT_A3 0x0100


	#define	SET_SIGN_CONTEXT_B1 0x02000
	#define	SET_SIGN_CONTEXT_B2 0x40800 
	#define	SET_SIGN_CONTEXT_B3 0x01000


	#define	SET_SIGN_CONTEXT_C1 0x020000
	#define	SET_SIGN_CONTEXT_C2 0x408000 
	#define	SET_SIGN_CONTEXT_C3 0x010000


	#define	SET_SIGN_CONTEXT_D1 0x0200000
	#define	SET_SIGN_CONTEXT_D2 0x4080000 
	#define	SET_SIGN_CONTEXT_D3 0x0100000


	#define SET_CONTEXT_1 0x028001
	#define	SET_CONTEXT_2 0x800040
	#define SET_CONTEXT_3 0x012004


	struct str_PDC_Codeblock;
	typedef struct str_PDC_Codeblock PDC_Codeblock;

	struct str_PDC_Codeword_List;
	typedef struct str_PDC_Codeword_List PDC_Codeword_List;

	typedef enum{ STATE_BIT_8, STATE_BIT_16, STATE_BIT_32}PDC_STATE_BIT;

	#define DEFAULT_RESIZE_CODEWORD 5

	#include "PDC_Subband.h"
	#include "PDC_Resolution.h"
	#include "PDC_Tile_Component.h"
	#include "PDC_COD_Segment.h"

	struct str_PDC_Codeblock{
		PDC_Subband*		subband;
		PDC_Codeword_List*	read_codeword;
		PDC_Codeword_List*	write_codeword;
		
		PDC_uint		Lblock;

		PDC_uint32		cx0;	
		PDC_uint32		cx1;
		PDC_uint32		cy0;
		PDC_uint32		cy1;

		PDC_bool		codeblock_inclusion;
		PDC_bool		zero_bit_plane_inclusion;

		/*
		 * Coefficient bit modeling variable
		 * Sign is FF | Y - 1 | Y |
		 */


	
		PDC_STATE_BIT	state_bit;
		PDC_uint32		street;
		PDC_uint32		num_street;
		PDC_uint32*		is_coded;
		PDC_uint32*		sign;
		PDC_uint32*		significant;
		PDC_uint8*		significante_context_delete;
		PDC_uint8*		significante_context;
		PDC_uint8*		sign_context_delete;
		PDC_uint8*		sign_context;
		PDC_uint32		significante_context_size_x;
		PDC_uint32		significante_context_size_y;
		PDC_uint32		sign_context_size_x;
		PDC_uint32		sign_context_size_y;
		PDC_uint8*		value8;
		PDC_uint16*		value16;
		PDC_uint32*		value32;
		PDC_uint32		bit_plane;
		PDC_uint8		*BDK_context_states;
		PDC_uint32		pos_x;
		PDC_STATE_BIT	value_size;
		PDC_Arithmetic_entropy_decoder *decoder;

	};
	
	struct str_PDC_Codeword_List{
		PDC_Codeword_List* first_codedword;
		PDC_Codeword_List* last_codedword;
		PDC_Codeword_List* next_codedword;
		
		PDC_Buffer* codeword;
		PDC_uint	coding_pass_from;
		PDC_uint	coding_pass_to;
		PDC_uint	coding_pass_next;
		PDC_uint	number_of_coding_passes;
		PDC_uint	number_of_byte;
	};


	/*
	 *
	 */
	PDC_Codeblock* new_PDC_Codeblock_01(PDC_Exception* exception);

	/*
	 *
	 */
	PDC_Codeblock* new_PDC_Codeblock_02(PDC_Exception* exception, PDC_Subband* subband, PDC_uint pos_x, PDC_uint pos_y);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_init_bit_modeling_variable(PDC_Exception* exception, PDC_Codeblock* codeblock);

	/*
	 *
	 
	PDC_Codeblock* new_PDC_Codeblock_02(PDC_Exception* exception, PDC_uint num_codingpasses);
	*/

	/*
	 *
	 */
	PDC_Codeblock* delete_PDC_Codeblock(PDC_Exception* exception, PDC_Codeblock* codeblock);

	/*
	 *
	 */
	PDC_uint PDC_Codeblock_set_number_of_coding_passes(	PDC_Exception* exception, 
														PDC_Codeblock* codeblock, 
														PDC_uint number_of_coding_passes);

	/*
	 *
	 */
	PDC_Codeword_List* new_PDC_Codeword_List_01(PDC_Exception* exception);

	/*
	 *
	 */
	PDC_Codeword_List* new_PDC_Codeword_List_02(PDC_Exception* exception, PDC_Codeword_List* last_codeword_list);

	/*
	 *
	 */
	PDC_Codeword_List* delete_PDC_Codeword_List(PDC_Exception* exception, PDC_Codeword_List* codeoword_list);

	/*
	 *
	 */
	PDC_bool PDC_Codeblock_significance_decoding_pass(PDC_Exception* exception, PDC_Codeblock* codeblock, PDC_Buffer* codeword);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_magnitude_decoding_pass(PDC_Exception* exception, PDC_Codeblock* codeblock, PDC_Buffer* buffer);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_cleanup_decoding_pass(PDC_Exception* exception, PDC_Codeblock* codeblock, PDC_Buffer* buffer);

STOP_C
#endif