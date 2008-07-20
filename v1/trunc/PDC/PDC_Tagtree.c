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

#include "PDC_Tagtree.h"

START_C

/* 
 *
 */
PDC_Tagtree* new_PDC_Tagtree_01(PDC_Exception* exception,
								PDC_uint size_x,
								PDC_uint size_y)
{
	PDC_Tagtree*	tagtree;
	PDC_uint		max, value, pos, pos1, pos_y, pos_x, pos_x1, pos_y1;

	tagtree = malloc(sizeof(PDC_Tagtree));
	if(tagtree == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	tagtree->level	= 0;
	max				= max_uint(size_x, size_y);

	value = 1;
	while(value < max){
		tagtree->level += 1;
		value	= 1 << tagtree->level;
	}
	tagtree->level += 1;

	tagtree->size_x = malloc(sizeof(PDC_uint) * tagtree->level);
	if(tagtree->size_x == NULL){
		delete_PDC_Tagtree_01(exception, tagtree);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	tagtree->size_y	= malloc(sizeof(PDC_uint) * tagtree->level);
	if(tagtree->size_y == NULL){
		delete_PDC_Tagtree_01(exception, tagtree);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	tagtree->size_x[0]	= size_x;
	tagtree->size_y[0]	= size_y;
	for(pos = 1, pos1 = 0; pos < tagtree->level; pos += 1, pos1 += 1){
		tagtree->size_x[pos] = PDC_ui_ceiling(tagtree->size_x[pos1], 2);
		tagtree->size_y [pos] = PDC_ui_ceiling(tagtree->size_y[pos1], 2);
	}
	
	tagtree->item = malloc(sizeof(PDC_Tagtree_item**) * tagtree->level) ;
	if(tagtree->size_y == NULL){
		delete_PDC_Tagtree_01(exception, tagtree);
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	for(pos = 0; pos < tagtree->level; pos += 1){
		tagtree->item[pos] = NULL;
	}

	for(pos = 0; pos < tagtree->level; pos += 1){
		tagtree->item[pos] = malloc(sizeof(PDC_Tagtree_item*) * tagtree->size_x[pos]);
		if(tagtree->item[pos] == NULL){
			delete_PDC_Tagtree_01(exception, tagtree);
			PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
			return NULL;
		}
		for(pos_x = 0; pos_x < tagtree->size_x[pos]; pos_x += 1){
			tagtree->item[pos][pos_x] = NULL;
		}
		
		for(pos_x = 0; pos_x < tagtree->size_x[pos]; pos_x += 1){
			tagtree->item[pos][pos_x] = malloc(sizeof(PDC_Tagtree_item) * tagtree->size_y[pos]);
			if(tagtree->item[pos][pos_x] == NULL){
				delete_PDC_Tagtree_01(exception, tagtree);
				PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
				return NULL;
			}
			if(pos > 0){
				for(pos_y = 0; pos_y < tagtree->size_y[pos]; pos_y += 1){
					pos_x1	= pos_x * 2;
					pos_y1	= pos_y * 2;
					pos1	= pos - 1;
					tagtree->item[pos][pos_x][pos_y].child1 = &(tagtree->item[pos1][pos_x1][pos_y1]);
					if(pos_x1 + 1 < tagtree->size_x[pos1]){
						tagtree->item[pos][pos_x][pos_y].child2 = &(tagtree->item[pos1][pos_x1 + 1][pos_y1]);
						if(pos_y1 + 1 < tagtree->size_y[pos1]){
							tagtree->item[pos][pos_x][pos_y].child3 = &(tagtree->item[pos1][pos_x1][pos_y1 + 1]);
							tagtree->item[pos][pos_x][pos_y].child4 = &(tagtree->item[pos1][pos_x1 + 1][pos_y1 + 1]);
						}else{
							tagtree->item[pos][pos_x][pos_y].child3 = NULL;
							tagtree->item[pos][pos_x][pos_y].child4 = NULL;
						}
					}else{
						if(pos_y1 + 1 < tagtree->size_y[pos1]){
							tagtree->item[pos][pos_x][pos_y].child3 = &(tagtree->item[pos1][pos_x1][pos_y1 + 1]);
						}else{
							tagtree->item[pos][pos_x][pos_y].child3 = NULL;
						}
						tagtree->item[pos][pos_x][pos_y].child2 = NULL;
						tagtree->item[pos][pos_x][pos_y].child4	= NULL;

					}
				}
			}else{
				for(pos_y = 0; pos_y < tagtree->size_y[pos]; pos_y += 1){
					tagtree->item[pos][pos_x][pos_y].child1 = NULL;
					tagtree->item[pos][pos_x][pos_y].child2 = NULL;
					tagtree->item[pos][pos_x][pos_y].child3 = NULL;
					tagtree->item[pos][pos_x][pos_y].child4 = NULL;
				}	
			}
			for(pos_y = 0; pos_y < tagtree->size_y[pos]; pos_y += 1){
				tagtree->item[pos][pos_x][pos_y].value	= 0;
				tagtree->item[pos][pos_x][pos_y].decode	= PDC_false;
				tagtree->item[pos][pos_x][pos_y].parent	= NULL;
			}	
		}
	}

	for(pos = 0; pos < tagtree->level - 1; pos += 1){
		for(pos_x = 0; pos_x < tagtree->size_x[pos]; pos_x += 1){
			for(pos_y = 0; pos_y < tagtree->size_y[pos]; pos_y += 1){
				pos_x1 = PDC_ui_floor(pos_x, 2);
				pos_y1 = PDC_ui_floor(pos_y, 2);
				tagtree->item[pos][pos_x][pos_y].parent = &(tagtree->item[pos + 1][pos_x1][pos_y1]);
			}
		}
	}

	return tagtree;
}

/*
 *
 */
PDC_Tagtree* delete_PDC_Tagtree_01(	PDC_Exception* exception,
									PDC_Tagtree* tagtree)
{
	
	return NULL;
}

/*
 *
 */
PDC_Tagtree* PDC_Tagtree_set_value(	PDC_Exception* exception,
									PDC_Tagtree* tagtree, 
									PDC_uint pos_x,
									PDC_uint pos_y,
									PDC_int	value)
{
	if(pos_x < tagtree->size_x[0] && pos_y < tagtree->size_y[0]){
		tagtree->item[0][pos_x][pos_y].value = value;
	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
	}
	return tagtree;
}

/*
 *
 */
PDC_Tagtree* PDC_Tagtree_create_tree(	PDC_Exception* exception,
										PDC_Tagtree* tagtree)
{
	PDC_uint pos, pos_x, pos_y;
	PDC_Tagtree_item* item;

	for(pos = 1; pos < tagtree->level; pos += 1){
		for(pos_x = 0; pos_x < tagtree->size_x[pos]; pos_x += 1){
			for(pos_y = 0; pos_y <tagtree->size_y[pos]; pos_y += 1){
				item = &(tagtree->item[pos][pos_x][pos_y]);
				item->value = MAX_INT;
				if(item->child1 != NULL){
					if(item->value > item->child1->value){
						item->value = item->child1->value;
					}
				}
				if(item->child2 != NULL){
					if(item->value > item->child2->value){
						item->value = item->child2->value;
					}	
				}
				if(item->child3 != NULL)
				{
					if(item->value > item->child3->value){
						item->value = item->child3->value;
					}
				}
				if(item->child4 != NULL)
				{
					if(item->value > item->child4->value){
						item->value = item->child4->value;
					}
				}
			}
		}
	}

	return tagtree;
}
	
/*
 *
 */
PDC_bool PDC_Tagtree_encode_pos(	PDC_Exception* exception,
									PDC_Tagtree* tagtree,
									PDC_Buffer*	buffer,
									PDC_uint pos_x,
									PDC_uint pos_y,
									PDC_int max_value)
{
	PDC_bool encode = PDC_false;

	return encode;
}


/*
 *
 */
PDC_bool PDC_Tagtree_encode_item(	PDC_Exception* exception,
									PDC_Tagtree* tagtree,
									PDC_Buffer*	buffer,
									PDC_Tagtree_item* item,
									PDC_int max_value)
{
	PDC_bool encode = PDC_false;
	
	if(item->decode == PDC_true){
		return PDC_true;
	}
	if(item->parent != NULL ){
		if(item->parent->decode == PDC_false){
			encode = PDC_bool PDC_Tagtree_encode_item(exception, tagtree, buffer,item->parent, max_value)
		}
	}
	

	return encode;
}

STOP_C
