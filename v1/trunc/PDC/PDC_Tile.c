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
	tile->qcd_segment		= NULL;
	tile->tile_part_counter	= 0;

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
		tile->tile_component = PDC_Pointer_Buffer_add_pointer(	exception,
																tile->tile_component,
																tile_component);
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

/*
 *
 */
PDC_Tile* PDC_Tile_read_SOD_01(	PDC_Exception* exception,
								PDC_Tile* tile, 
								PDC_Buffer* buffer)
{
	PDC_Tile_Component* tile_component;
	PDC_uint	number, pos;
	if(tile->tile_part_counter == 0){
		number = tile->picture->siz_segment->Csiz;
		for(pos = 0; pos < number; pos += 1){
			tile_component = PDC_Pointer_Buffer_get_pointer(exception, tile->tile_component, pos);	
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return NULL;
			}
			
			PDC_Tile_Component_set_Resolution(	exception, tile_component);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return NULL;
			}
		}
	}
	tile->tile_part_counter += 1;
	PDC_Tile_read_Packageheader( exception, tile, tile->cod_segment, buffer);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return NULL;
	}
	PDC_Tile_decode_Package_01(exception, tile, tile->cod_segment);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return NULL;
	}
	
	PDC_Tile_dequantization_01(exception, tile);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return NULL;
	}
	return tile;
}

/*
 *
 */
PDC_Tile* PDC_Tile_set_COD_Segment(	PDC_Exception* exception,
									PDC_Tile* tile,
									PDC_COD_Segment* cod_segment)
{
	PDC_uint	number, pos;
	PDC_Tile_Component* tile_component;

	tile->cod_segment = cod_segment;

	number = tile->picture->siz_segment->Csiz;
	for(pos = 0; pos < number; pos += 1){
		tile_component = PDC_Pointer_Buffer_get_pointer(exception, tile->tile_component, pos);	
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Tile(exception, tile);
			return NULL;
		}

		PDC_Tile_Component_set_COD_Segment(	exception, tile_component, cod_segment);
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
PDC_Tile* PDC_Tile_set_QCD_Segment(	PDC_Exception* exception, 
									PDC_Tile* tile, 
									PDC_QCD_Segment* qcd_segment)
{
	PDC_uint	number, pos;
	PDC_Tile_Component* tile_component;

	tile->qcd_segment = qcd_segment;

	number = tile->picture->siz_segment->Csiz;
	for(pos = 0; pos < number; pos += 1){
		tile_component = PDC_Pointer_Buffer_get_pointer(exception, tile->tile_component, pos);	
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Tile(exception, tile);
			return NULL;
		}

		PDC_Tile_Component_set_QCD_Segment(	exception, tile_component, qcd_segment);
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
PDC_Tile* PDC_Tile_read_Packageheader(	PDC_Exception* exception,
										PDC_Tile* tile,
										PDC_COD_Segment* cod_segment,
										PDC_Buffer* buffer)
{
	PDC_uint r, Nmax, l, L, i, Csiz, k, numprecincts;

	Nmax			= cod_segment->number_of_decompostion_levels;
	L				= cod_segment->number_of_layer;
	Csiz			= tile->picture->siz_segment->Csiz;

	switch(cod_segment->progression_order){
		case LAYER_RESOLUTION_LEVEL_COMPONENT_POSITION:
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			break;
		case RESOLUTION_LEVEL_LAYER_COMPONENT_POSITION:
			for(r = 0; r <= Nmax; r += 1){
				for(l = 0; l < L; l += 1){
					for(i = 0; i < Csiz; i += 1){
						numprecincts = PDC_Tile_get_numprecinct(exception, tile, i, r);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							return 0;
						}
						for(k = 0; k < numprecincts; k += 1){
							PDC_Tile_read_package_header(	exception,
															tile,
															buffer,
															i,
															r,
															k,
															l);
							if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
								return 0;
							}
						}
					}
				}
			}
			break;
		case RESOLUTION_LEVEL_POSITION_COMPONENT_LAYER:
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			break;
		case POSITION_COMPONENT_RESOLUTION_LEVEL_LAYER:
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			break;
		case COMPONENT_POSITION_RESOLUTION_LEVEL_LAYER:
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			break;
		default:
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			break;
	}
	return tile;
}



PDC_Tile* PDC_Tile_decode_Package_01(	PDC_Exception* exception,
										PDC_Tile* tile,
										PDC_COD_Segment* cod_segment)
{
	PDC_uint r, Nmax, L, i, Csiz, k, numprecincts;

	Nmax			= cod_segment->number_of_decompostion_levels;
	L				= cod_segment->number_of_layer;
	Csiz			= tile->picture->siz_segment->Csiz;

	//Nmax	= 0;
	//L		= 1;
	//Csiz	= 1;

	switch(cod_segment->progression_order){
		case LAYER_RESOLUTION_LEVEL_COMPONENT_POSITION:
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			break;
		case RESOLUTION_LEVEL_LAYER_COMPONENT_POSITION:
			for(i = 0; i < Csiz; i += 1){
				//for(l = 0; l < L; l += 1){
					for(r = 0; r <= Nmax; r += 1){
						numprecincts = PDC_Tile_get_numprecinct(exception, tile, i, r);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							return 0;
						}
						for(k = 0; k < numprecincts; k += 1){
							PDC_Tile_decode_package_03(	exception,
														tile,
														i,
														r,
														k);
														//l);
							if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
								return 0;
							}
						}
					}
				//}
			}
			break;
		case RESOLUTION_LEVEL_POSITION_COMPONENT_LAYER:
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			break;
		case POSITION_COMPONENT_RESOLUTION_LEVEL_LAYER:
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			break;
		case COMPONENT_POSITION_RESOLUTION_LEVEL_LAYER:
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			break;
		default:
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			break;
	}
	return tile;
}


/*
 *
 */
PDC_uint PDC_Tile_get_numprecinct(	PDC_Exception* exception,
									PDC_Tile* tile,
									PDC_uint componente_pos,
									PDC_uint resolution_pos)
{
	PDC_uint back = 0;
	PDC_Resolution* resolution = NULL;

	resolution = PDC_Tile_get_resolution(exception, tile, componente_pos, resolution_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return 0;
	}
	back = PDC_Resolution_get_number_precinct(exception, resolution);
	return back;
}

/*
 *
 */
PDC_Resolution*	PDC_Tile_get_resolution(	PDC_Exception* exception,
											PDC_Tile* tile,
											PDC_uint componente_pos,
											PDC_uint resolution_pos)
{
	PDC_Resolution*	resolution = NULL;
	PDC_uint back = 0;
	PDC_Tile_Component* tile_component = NULL;

	tile_component = PDC_Pointer_Buffer_get_pointer(exception, tile->tile_component, componente_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return NULL;
	}
	resolution = PDC_Tile_Component_get_Resolution( exception, tile_component, resolution_pos);

	return resolution;
}

/*
 *
 */
void PDC_Tile_read_package_header(	PDC_Exception* exception,
									PDC_Tile* tile,
									PDC_Buffer* buffer,
									PDC_uint component_pos,
									PDC_uint resolution_pos,
									PDC_uint precinct_pos,
									PDC_uint layer_pos)
{
	PDC_Tile_Component*	component;
	PDC_Resolution*		resolution;
	PDC_Precinct*		precinct;
	component = (PDC_Tile_Component*)PDC_Pointer_Buffer_get_pointer(exception, 
																	tile->tile_component, 
																	component_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return;
	}
	resolution = PDC_Tile_Component_get_Resolution(	exception,
													component,
													resolution_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return;
	}

	precinct = PDC_Resolution_get_precinct(	exception,
											resolution,
											precinct_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return;
	}

	PDC_Precinct_read_package_header(	exception,
										precinct,
										buffer,
										layer_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return;
	}
}

/*
 *
 */
PDC_Tile* PDC_Tile_decode_package_02(	PDC_Exception* exception,
										PDC_Tile* tile,
										PDC_uint component_pos,
										PDC_uint resolution_pos,
										PDC_uint precinct_pos,
										PDC_uint layer_pos)
{
	PDC_Tile_Component*	component;
	PDC_Resolution*		resolution;
	PDC_Precinct*		precinct;
	component = (PDC_Tile_Component*)PDC_Pointer_Buffer_get_pointer(exception, 
																	tile->tile_component, 
																	component_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return tile;
	}
	resolution = PDC_Tile_Component_get_Resolution(	exception,
													component,
													resolution_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return tile;
	}

	precinct = PDC_Resolution_get_precinct(	exception,
											resolution,
											precinct_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return tile;
	}

	PDC_Precinct_decode_package_01(	exception,
									precinct,
									layer_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return tile;
	}

	return tile;
}

/*
 *
 */
PDC_Tile* PDC_Tile_decode_package_03(	PDC_Exception* exception,
										PDC_Tile* tile,
										PDC_uint component_pos,
										PDC_uint resolution_pos,
										PDC_uint precinct_pos)
{
	PDC_Tile_Component*	component;
	PDC_Resolution*		resolution;
	PDC_Precinct*		precinct;
	component = (PDC_Tile_Component*)PDC_Pointer_Buffer_get_pointer(exception, 
																	tile->tile_component, 
																	component_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return tile;
	}
	resolution = PDC_Tile_Component_get_Resolution(	exception,
													component,
													resolution_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return tile;
	}

	precinct = PDC_Resolution_get_precinct(	exception,
											resolution,
											precinct_pos);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return tile;
	}

	PDC_Precinct_set_End_of_Buffer(	exception,
									precinct);
	PDC_Precinct_decode_package_02(	exception,
									precinct);

	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return tile;
	}

	return tile;
}


/*
 *
 */
PDC_Tile* PDC_Tile_dequantization_01(	PDC_Exception* exception,
										PDC_Tile* tile)
{
	PDC_uint Csiz, Csiz_pos;
	PDC_Tile_Component* tile_component;
		
	Csiz = tile->picture->siz_segment->Csiz;
	for(Csiz_pos = 0; Csiz_pos < Csiz; Csiz_pos += 1){
		tile_component = PDC_Pointer_Buffer_get_pointer(exception, tile->tile_component, Csiz_pos);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return tile;
		}
		PDC_Tile_Component_inverse_quantization(exception, tile_component);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return tile;
		}
	}
	return tile;								
}

STOP_C