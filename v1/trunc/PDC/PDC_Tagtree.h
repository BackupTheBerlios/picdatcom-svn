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

#ifndef __PDC_TAGTREE_H__
#define __PDC_TAGTREE_H__

#include <stdlib.h>
#include "PDC_Parameter.h"
#include "PDC_Exception.h"

START_C

	struct str_PDC_Tagtree;
	typedef struct str_PDC_Tagtree PDC_Tagtree;

	struct str_PDC_Tagtree_item;
	typedef struct str_PDC_Tagtree_item PDC_Tagtree_item;

	#include "PDC_Buffer.h"

	struct str_PDC_Tagtree
	{
		PDC_uint*	size_x;
		PDC_uint*	size_y;
		PDC_uint	level;

		PDC_Tagtree_item***  item;

	};

	struct str_PDC_Tagtree_item
	{
		PDC_Tagtree_item*	child1;
		PDC_Tagtree_item*	child2;
		PDC_Tagtree_item*	child3;
		PDC_Tagtree_item*	child4;
		PDC_Tagtree_item*	parent;
		PDC_int				value;
		PDC_int				value_noted;
		PDC_bool			decode;
		PDC_int				save_value;
		PDC_int				save_value_noted;
		PDC_bool			save_decode;
	};

	/*
	 *
	 */
	PDC_Tagtree* new_PDC_Tagtree_01(PDC_Exception* exception,
									PDC_uint size_x,
									PDC_uint size_y);

	/*
	 *
	 */
	PDC_Tagtree* delete_PDC_Tagtree_01(	PDC_Exception* exception,
											PDC_Tagtree* tagtree);


	/*
	 *
	 */
	PDC_Tagtree* PDC_Tagtree_set_value(	PDC_Exception* exception,
										PDC_Tagtree* tagtree,
										PDC_uint pos_x,
										PDC_uint pos_y,
										PDC_int	value);

	/*
	 *
	 */
	PDC_Tagtree* PDC_Tagtree_create_tree(	PDC_Exception* exception,
											PDC_Tagtree* tagtree);

	/*
	 *
	 */
	PDC_bool PDC_Tagtree_encode_pos(	PDC_Exception* exception,
										PDC_Tagtree* tagtree,
										PDC_Buffer*	buffer,
										PDC_uint pos_x,
										PDC_uint pos_y,
										PDC_int max_value);

	/*
	 *
	 */
	PDC_bool PDC_Tagtree_encode_item(	PDC_Exception* exception,
										PDC_Tagtree* tagtree,
										PDC_Buffer*	buffer,
										PDC_Tagtree_item* item,
										PDC_Tagtree_item* root_item,
										PDC_int max_value);

	/*
	 *
	 */
	PDC_bool PDC_Tagtree_decode_pos(	PDC_Exception* exception,
										PDC_Tagtree* tagtree,
										PDC_Buffer*	buffer,
										PDC_uint pos_x,
										PDC_uint pos_y,
										PDC_int max_value);

	/*
	 *
	 */
	PDC_bool PDC_Tagtree_decode_item(	PDC_Exception* exception,
										PDC_Tagtree* tagtree,
										PDC_Buffer*	buffer,
										PDC_Tagtree_item* item,
										PDC_int max_value);

	/*
	 *
	 */
	void PDC_Tagtree_push(	PDC_Exception* exception,
							PDC_Tagtree* tagtree);

	/*
	 *
	 */
	void PDC_Tagtree_pop(	PDC_Exception* exception,
							PDC_Tagtree* tagtree);

	/*
	 *
	 */
	PDC_int PDC_Tagtree_get_value(		PDC_Exception* exception,
										PDC_Tagtree* tagtree,
										PDC_uint pos_x,
										PDC_uint pos_y);

STOP_C
#endif
