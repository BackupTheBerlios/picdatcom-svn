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

#ifndef __PDC_CODEBLOCK_H__
#define __PDC_CODEBLOCK_H__

#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include "PDC_Parameter.h"
#include "PDC_Arithmetic_entropy_decoder.h"


START_C

	#define	SET_SIGN_CONTEXT_A1 0x0800
	#define	SET_SIGN_CONTEXT_A2 0x1020
	#define	SET_SIGN_CONTEXT_A3 0x0400


	#define	SET_SIGN_CONTEXT_B1 0x08000
	#define	SET_SIGN_CONTEXT_B2 0x10200
	#define	SET_SIGN_CONTEXT_B3 0x04000


	#define	SET_SIGN_CONTEXT_C1 0x080000
	#define	SET_SIGN_CONTEXT_C2 0x102000
	#define	SET_SIGN_CONTEXT_C3 0x040000


	#define	SET_SIGN_CONTEXT_D1 0x0800000
	#define	SET_SIGN_CONTEXT_D2 0x1020000
	#define	SET_SIGN_CONTEXT_D3 0x0400000

/*
	#define SET_CONTEXT_1 0x028001
	#define	SET_CONTEXT_2 0x800040
	#define SET_CONTEXT_3 0x012004
*/
	#define SET_CONTEXT_1 0x044001
	#define	SET_CONTEXT_2 0x200010
	#define SET_CONTEXT_3 0x088002


	struct str_PDC_Codeblock;
	typedef struct str_PDC_Codeblock PDC_Codeblock;

	struct str_PDC_Codeword_List;
	typedef struct str_PDC_Codeword_List PDC_Codeword_List;

	typedef enum{ STATE_BIT_8, STATE_BIT_16, STATE_BIT_32}PDC_STATE_BIT;
	typedef enum{ CLEANUP_PASS, SIGNIFICANCE_PASS,MAGNITUDE_PASS, NO_PASS = 76} PDC_PASS_STATE;
	typedef enum{
		MARK_00, MARK_01, MARK_02, MARK_03, MARK_04, MARK_05, MARK_06, MARK_07,
		MARK_08, MARK_09, MARK_10, MARK_11, MARK_12, MARK_13, MARK_14, MARK_15,
		MARK_16, MARK_17, MARK_18, MARK_19, MARK_20, MARK_21, MARK_22, MARK_23,
		MARK_24, MARK_25, MARK_26, MARK_27, MARK_28, MARK_29, MARK_30, MARK_31,
		MARK_32, MARK_33, MARK_34, MARK_35, MARK_36, MARK_37, MARK_38, MARK_39,
		MARK_40, MARK_41, MARK_42, MARK_43, MARK_44, MARK_45, MARK_46, MARK_47,
		MARK_48, MARK_49, MARK_50, MARK_51, MARK_52, MARK_53, MARK_54, MARK_55,
		MARK_56, MARK_57, MARK_58, MARK_59, MARK_60, MARK_61, MARK_62, MARK_63,
		MARK_64, MARK_65, MARK_66, MARK_67, MARK_68, MARK_69, MARK_70, MARK_71, MARK_72,
		MARK_73, MARK_74, MARK_75, MARK_76, MARK_77, MARK_78, MARK_79, MARK_80,
		MARK_81, MARK_82, MARK_83, MARK_84, MARK_85, MARK_86, MARK_87, MARK_88,
		MARK_89, MARK_90, MARK_91, MARK_92, MARK_93, MARK_94, MARK_95, MARK_96,
		MARK_97, MARK_98, MARK_99, MARK_100, MARK_101, MARK_102, MARK_103, MARK_104,
		MARK_105, MARK_106, MARK_107, MARK_108, MARK_109, MARK_110, MARK_111, MARK_112} PDC_MARK;

	#define DEFAULT_RESIZE_CODEWORD 5

	#include "PDC_Subband.h"
	#include "PDC_Resolution.h"
	#include "PDC_Tile_Component.h"
	#include "PDC_COD_Segment.h"
	#include "PDC_Worker.h"

	struct str_PDC_Codeblock{
		PDC_Subband*		subband;
		PDC_Codeword_List*	read_codeword;
		PDC_Codeword_List*	write_codeword;
		PDC_uint*			coding_passes_per_layer;

		PDC_uint		Lblock;
		PDC_uint		save_Lblock;

		PDC_uint32		cx0;
		PDC_uint32		cx1;
		PDC_uint32		cy0;
		PDC_uint32		cy1;
		PDC_int			mx0;
		PDC_int			mx1;
		PDC_int			my0;
		PDC_int			my1;

		PDC_bool		codeblock_inclusion;
		PDC_bool		zero_bit_plane_inclusion;

		PDC_bool		save_codeblock_inclusion;
		PDC_bool		save_zero_bit_plane_inclusion;

		PDC_uint32		zero_bitplanes;

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
		PDC_uint32*		first_refinement;
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
		PDC_bool		init_decoder;
		PDC_PASS_STATE	pass_state;

		PDC_MARK		mark;
		PDC_uint		runlengthpos;
		PDC_uint		pos_y;
		PDC_uint		significant_pos_x;
		PDC_uint		significant_pos_x1;
		PDC_uint		significant_pos_shift;


		PDC_uint8		*significante_context_use;
		PDC_uint8		*sign_context_base_address1;
		PDC_uint8		*significant_context_base_address;
		PDC_uint32		significant_context_value;
		PDC_uint32		sign_context1;
		PDC_uint32		sign_context2;
		PDC_uint32		sign_context3;
		PDC_uint32		context;
		PDC_uint32		sign_context_use;
		PDC_uint32		pos_x_end;
		PDC_uint32		is_coded_temp;
		PDC_uint32		sign_temp;
		PDC_uint32		significant_temp;
		PDC_uint32		current_bit;
		PDC_uint32		shift_temp;

		/*
		 * For thread scheduling
		 */
		PDC_Codeblock_list	*all_list;
		PDC_Codeblock_list	*work_list;
		pthread_mutex_t		*in_work;
		PDC_bool			has_job;
		pthread_t			current_thread;
		pthread_t			root_thread;

		// Only for testing;
		PDC_bool		layer_inclusion;
		PDC_uint		number_of_codingpasses, number_of_codeword_segment, codewordlength;
		PDC_uint		*extra1, *extra2;
		int		n, m;
	};

	struct str_PDC_Codeword_List{
		PDC_Codeword_List*	first_codedword;
		PDC_Codeword_List*	last_codedword;
		PDC_Codeword_List*  next_codedword;
		//PDC_uint*			coding_passes_per_layer;

		PDC_Buffer* codeword;
		PDC_uint	coding_pass_from;
		PDC_uint	coding_pass_to;
		PDC_uint	coding_pass_next;
		PDC_uint	number_of_coding_passes;
		PDC_uint	number_of_byte;
		PDC_bool	empty;

		PDC_uint	save_coding_pass_to;
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
														PDC_uint number_of_coding_passes,
														PDC_uint layer_pos);

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
	PDC_Codeblock *PDC_Codeblock_coefficient_bit_moddeling_decode( PDC_Exception *exception, PDC_Codeblock *codeblock, PDC_uint layer_pos);

	/*
	 *
	 */
	PDC_Codeblock *PDC_Codeblock_coefficient_bit_moddeling_decode_01( PDC_Exception *exception, PDC_Codeblock *codeblock);

	/*
	 *
	 */
	PDC_bool PDC_Codeblock_significance_decoding_pass(PDC_Exception* exception, PDC_Codeblock* codeblock, PDC_Buffer* codeword);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_magnitude_decoding_pass(PDC_Exception* exception, PDC_Codeblock* codeblock, PDC_Buffer* codeword);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_cleanup_decoding_pass(PDC_Exception* exception, PDC_Codeblock* codeblock, PDC_Buffer* codeword);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_reset_is_coded(PDC_Exception* exception, PDC_Codeblock *codeblock);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_change_value_size_up(PDC_Exception* exception, PDC_Codeblock *codeblock);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_set_End_of_Buffer(PDC_Exception* exception, PDC_Codeblock *codeblock);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_inverse_quantization(PDC_Exception* exception, PDC_Codeblock *codeblock);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_push(PDC_Exception* exception, PDC_Codeblock* codeblock);


	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_pop(PDC_Exception* exception, PDC_Codeblock* codeblock);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_lock(PDC_Exception* exception, PDC_Codeblock* codeblock);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_trylock(PDC_Exception* exception, PDC_Codeblock* codeblock);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_unlock(PDC_Exception* exception, PDC_Codeblock* codeblock);

	/*
	 *
	 */
	PDC_Codeblock* PDC_Codeblock_set_false_has_job(PDC_Exception* exception, PDC_Codeblock* codeblock);

	void print_codeblock_02(PDC_Codeblock *codeblock,FILE *file, int component, int resolution, int n, int m);
	void set_extra(PDC_Codeblock *codeblock, int pos, int layer,int codingpasstype, int extra, PDC_Arithmetic_entropy_decoder *decoder);
STOP_C
#endif
