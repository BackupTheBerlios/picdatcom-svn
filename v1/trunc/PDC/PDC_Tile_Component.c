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

#include "PDC_Tile_Component.h"

START_C

/*
 *
 */
PDC_Tile_Component* new_PDC_Tile_Component_01(PDC_Exception* exception, PDC_Tile* tile, PDC_uint32 pos)
{
	PDC_Tile_Component*			tile_component;
	PDC_Picture*				picture;
	PDC_SIZ_Segment*			siz_segment;
	PDC_SIZ_Segment_Componente*	siz_segment_component;


	tile_component			= NULL;
	picture					= tile->picture;
	siz_segment				= picture->siz_segment;
	siz_segment_component	= PDC_Pointer_Buffer_get_pointer(exception, siz_segment->componente_part, pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return NULL;
	}

	tile_component = malloc(sizeof(PDC_Tile_Component));
	if(tile_component == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	tile_component->memory = (PDC_float32*)PDC_Pointer_Buffer_get_pointer(exception, picture->componentes, pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return NULL;
	}

	tile_component->tile	= tile;
		
	tile_component->tcx0	= PDC_i_ceiling(tile->tx0, siz_segment_component->XRsiz);
	tile_component->tcx1	= PDC_i_ceiling(tile->tx1, siz_segment_component->XRsiz);
	tile_component->tcy0	= PDC_i_ceiling(tile->ty0, siz_segment_component->YRsiz);
	tile_component->tcy1	= PDC_i_ceiling(tile->ty1, siz_segment_component->YRsiz);

	return tile_component;
}

/*
 *
 */
PDC_Tile_Component* delete_PDC_Tile_Component(PDC_Exception* exception, PDC_Tile_Component* tile_component)
{
	if(tile_component != NULL){
		free(tile_component);
	}

	return NULL;
}

STOP_C
