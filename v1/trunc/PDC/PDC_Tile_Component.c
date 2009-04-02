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

	PDC_uint32 maxSize = 0;

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

	tile_component->tile					= tile;
	tile_component->resolution				= NULL;
	tile_component->qcd_segment				= NULL;
	tile_component->siz_segment_component	= siz_segment_component;
	tile_component->transformer_97_decoder	= NULL;

	tile_component->tcx0	= PDC_i_ceiling(tile->tx0, siz_segment_component->XRsiz);
	tile_component->tcx1	= PDC_i_ceiling(tile->tx1, siz_segment_component->XRsiz);
	tile_component->tcy0	= PDC_i_ceiling(tile->ty0, siz_segment_component->YRsiz);
	tile_component->tcy1	= PDC_i_ceiling(tile->ty1, siz_segment_component->YRsiz);
	
	tile_component->mx0		= tile->tx0 - siz_segment->XOsiz;
	tile_component->mx1		= tile->tx1 - siz_segment->XOsiz;
	tile_component->my0		= tile->ty0 - siz_segment->YOsiz;
	tile_component->my1		= tile->ty1 - siz_segment->YOsiz;
	tile_component->msizex	= tile->picture->sizeX;
	tile_component->msizey	= tile->picture->sizeY;

	maxSize = max_uint32(tile_component->mx1 - tile_component->mx0, tile_component->my1 - tile_component->my0);
	tile_component->transformer_97_decoder = new_PDC_Transformation_97_decoder(exception, maxSize);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return NULL;
	}
	
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

/*
 *
 */
PDC_Tile_Component* PDC_Tile_Component_set_COD_Segment(	PDC_Exception* exception, 
														PDC_Tile_Component* tile_component,
														PDC_COD_Segment* cod_segment)
{
	tile_component->cod_segment = cod_segment;
	return tile_component;
}

/*
 *
 */
PDC_Tile_Component* PDC_Tile_Component_set_QCD_Segment(	PDC_Exception* exception, 
														PDC_Tile_Component* tile_component,
														PDC_QCD_Segment* qcd_segment)
{
	tile_component->qcd_segment = qcd_segment;
	return tile_component;

}

/*
 *
 */
PDC_Tile_Component* PDC_Tile_Component_set_Resolution(	PDC_Exception* exception,
														PDC_Tile_Component* tile_component)
{
	if(tile_component->resolution == NULL){
		tile_component->resolution = new_PDC_Resolution_02(	exception, tile_component);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return NULL;
		}
	}else{
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
	}
	
	return tile_component;
}

/*
 *
 */
PDC_Resolution* PDC_Tile_Component_get_Resolution(	PDC_Exception* exception,
													PDC_Tile_Component* tile_component,
													PDC_uint resolution_pos)
{
	PDC_Resolution* resolution = NULL;
	if(tile_component->resolution == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	resolution = PDC_Resolution_get_resolution(exception, tile_component->resolution, resolution_pos);

	return resolution;
}

/*
 *
 */
PDC_Tile_Component* PDC_Tile_Component_inverse_quantization(PDC_Exception* exception,
															PDC_Tile_Component* tile_component)
{
	PDC_Resolution_inverse_quantization(exception,tile_component->resolution);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return tile_component;
	}
	return tile_component;
}


/*
 *
 */
PDC_Tile_Component* PDC_Tile_Component_inverse_transformation(	PDC_Exception* exception,
																PDC_Tile_Component* tile_component)
{
	if((tile_component->cod_segment->multiple_component_transformation & MULTIPLE_TRANSFORMATION) != 0){
		if((tile_component->cod_segment->transformation & TRANSFORMATION_REVERSIBLE) != 0){
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			return tile_component;
		}else{
			PDC_Resolution_inverse_transformation_97(exception, tile_component->resolution);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return tile_component;
			}
		}
	}
	return tile_component;
}
																		
/*
 *
 */
PDC_Tile_Component* PDC_Tile_Component_interpolation(	PDC_Exception* exception,
														PDC_Tile_Component* tile_component)
{
	
	if(	tile_component->siz_segment_component->XRsiz == 1 &&
		tile_component->siz_segment_component->YRsiz == 1){
		return tile_component;
	}else{
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
		return tile_component;
	}
			
	return tile_component;
}

STOP_C
