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

#include "PDC_Tile.h"

START_C

/*
 * 
 */
PDC_Tile* new_PDC_Tile_01(PDC_Exception* exception, PDC_uint32 t, PDC_Picture* picture)
{
	PDC_uint32 numComponentes, posComponent;
	PDC_Tile* tile						= NULL;
	PDC_SIZ_Segment* siz_segment		= picture->siz_segment;
	PDC_Tile_Component* tile_component	= NULL;

	tile = malloc(sizeof(PDC_Tile));
	if(tile == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	tile->tile_component	= NULL;
	tile->cod_segment		= NULL;

	tile->p			= PDC_i_ceiling(t, picture->numYtiles);
	tile->q			= t % picture->numXtiles;

	tile->tx0		= max_uint32(siz_segment->XTOsiz + tile->p * siz_segment->XTsiz, siz_segment->XOsiz);
	tile->tx1		= min_uint32(siz_segment->XTOsiz + (tile->p + 1) * siz_segment->XTsiz, siz_segment->Xsiz);
	tile->ty0		= max_uint32(siz_segment->YTOsiz + tile->q * siz_segment->YTsiz, siz_segment->YOsiz);
	tile->ty1		= min_uint32(siz_segment->YTOsiz + (tile->q + 1) * siz_segment->YTsiz, siz_segment->Ysiz);
	tile->picture	= picture;

	numComponentes = picture->siz_segment->Csiz;
	
	tile->tile_component = new_PDC_Pointer_Buffer_01(exception, numComponentes);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Tile(exception, tile);
		return NULL;
	}
	
	for(posComponent = 0; posComponent < numComponentes; posComponent += 1){
		tile_component = new_PDC_Tile_Component_01(exception, tile, posComponent);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Tile(exception, tile);
			return NULL;
		}
	}

	return tile;
}


/*
 *
 */
PDC_Tile* delete_PDC_Tile(	PDC_Exception* exception,
							PDC_Tile* tile)
{	
	PDC_Tile_Component* tile_component;
	if(tile != NULL){
		PDC_Pointer_Buffer_set_start(exception, tile->tile_component);

		if((tile_component = PDC_Pointer_Buffer_get_next(exception, tile->tile_component)) != NULL){
			do{
				delete_PDC_Tile_Component(exception, tile_component);
			}while((tile_component = PDC_Pointer_Buffer_get_next(exception, tile->tile_component)) != NULL);

		}
		delete_PDC_Pointer_Buffer_01(exception, tile->tile_component);
		tile->picture = NULL;
		free(tile);

	}
	return NULL;
}

STOP_C