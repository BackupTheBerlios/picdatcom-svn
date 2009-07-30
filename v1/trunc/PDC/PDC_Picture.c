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

#include "PDC_Picture.h"

START_C

/*
 *
 */
PDC_Picture* new_PDC_Picture(PDC_Exception* exception)
{
	PDC_Picture* picture = NULL;

	picture = malloc(sizeof(PDC_Picture));
	if(picture == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	picture->siz_segment	= NULL;
	picture->cod_segment	= NULL;
	picture->qcd_segment	= NULL;
	picture->com_segment	= NULL;

	picture->componentes	= NULL;
	picture->tiles			= NULL;

	picture->sizeX			= 0;
	picture->sizeY			= 0;

	picture->use_bits		= PDC_USE_32_BIT;

	return picture;
}

/*
 *
 */
void delete_PDC_Picture(PDC_Exception* exception, PDC_Picture* picture)
{
	int		numComponent, posComponent, numTile,  posTile;
	void*	pointer;
	PDC_Tile*	tempTile;

	if(picture != NULL){
		//delete_PDC_SIZ_Segment_01(exception, picture->siz_segment);
		//delete_PDC_COD_Segment(exception, picture->cod_segment);
		//delete_PDC_QCD_Segment(exception, picture->qcd_segment);
		//delete_PDC_COM_Segment(exception, picture->com_segment);

		if(picture->componentes != NULL){
			numComponent = picture->componentes->last_pointer + 1;
			for(posComponent = 0; posComponent < numComponent; posComponent += 1){
				pointer = PDC_Pointer_Buffer_get_pointer(exception, picture->componentes, posComponent);
				free(pointer);
			}
			delete_PDC_Pointer_Buffer_01(exception, picture->componentes);
		}

		if(picture->tiles != NULL){
			numTile = picture->tiles->last_pointer + 1;
			for(posTile = 0; posTile < numTile; posTile += 1){
				tempTile = (PDC_Tile*)PDC_Pointer_Buffer_get_pointer(exception, picture->tiles, posTile);
				delete_PDC_Tile(exception, tempTile);
			}
			delete_PDC_Pointer_Buffer_01(exception, picture->tiles);
		}

		free(picture);
	}
}

/*
 *
 */
PDC_Picture* PDC_Picture_set_SIZ_Segment(	PDC_Exception* exception,
												PDC_Picture* picture,
												PDC_SIZ_Segment* siz_segment)
{
	PDC_uint32	numPixel, numBytes, numComponentes, posComponent, numTile, posTile;
	void*		pointer;
	PDC_Tile*	tempTile;

	if(picture->siz_segment == NULL){
		if(siz_segment->XTOsiz > siz_segment->XOsiz || siz_segment->YTOsiz > siz_segment->YOsiz){
			PDC_Exception_error(exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
			return picture;
		}

		picture->siz_segment = siz_segment;

		picture->sizeX	= siz_segment->Xsiz - siz_segment->XOsiz;
		picture->sizeY	= siz_segment->Ysiz - siz_segment->YOsiz;
		numPixel		= picture->sizeX * picture->sizeY;
		numComponentes	= siz_segment->Csiz;

		if(picture->use_bits == PDC_USE_32_BIT){
			numBytes = numPixel * 4;
		}else{
			numBytes = numPixel * 8;
		}
		picture->componentes = new_PDC_Pointer_Buffer_01(exception, numComponentes);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return picture;
		}

		for(posComponent = 0; posComponent < numComponentes; posComponent += 1){
			pointer = malloc(numBytes);
			if(pointer == NULL){
				PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
				return picture;
			}
			PDC_Pointer_Buffer_add_pointer(exception, picture->componentes, pointer);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return picture;
			}
		}

		picture->numXtiles = PDC_i_ceiling(siz_segment->Xsiz - siz_segment->XTOsiz, siz_segment->XTsiz);
		picture->numYtiles = PDC_i_ceiling(siz_segment->Ysiz - siz_segment->YTOsiz, siz_segment->YTsiz);

		numTile = picture->numXtiles * picture->numYtiles;

		picture->tiles = new_PDC_Pointer_Buffer_01(exception, numTile);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return picture;
		}

		for(posTile = 0; posTile < numTile; posTile += 1){
			tempTile = new_PDC_Tile_01(exception, posTile, picture);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return picture;
			}

			PDC_Pointer_Buffer_add_pointer(exception, picture->tiles, tempTile);
			if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
				return picture;
			}
		}
	}else{
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_DAMAGED_CODE, __LINE__, __FILE__);
	}
	return picture;
}

/*
 *
 */
PDC_Picture* PDC_Picture_set_COD_Segment(	PDC_Exception* exception,
												PDC_Picture* picture,
												PDC_COD_Segment* cod_segment)
{
	PDC_uint32 num_tiles, pos;
	PDC_Tile* tile;
	num_tiles = picture->numXtiles * picture->numYtiles;

	for(pos = 0; pos < num_tiles; pos += 1){
		tile = PDC_Pointer_Buffer_get_pointer(exception, picture->tiles, pos);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Tile(exception, tile);
			return NULL;
		}

		PDC_Tile_set_COD_Segment(	exception, tile, cod_segment);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Tile(exception, tile);
			return NULL;
		}
	}
	return picture;
}

/*
 *
 */
PDC_Picture* PDC_Picture_set_QCD_Segment(	PDC_Exception* exception,
											PDC_Picture* picture,
											PDC_QCD_Segment* qcd_segment)
{
	PDC_uint32 num_tiles, pos;
	PDC_Tile* tile;
	num_tiles = picture->numXtiles * picture->numYtiles;

	for(pos = 0; pos < num_tiles; pos += 1){
		tile = PDC_Pointer_Buffer_get_pointer(exception, picture->tiles, pos);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Tile(exception, tile);
			return NULL;
		}

		PDC_Tile_set_QCD_Segment(	exception, tile, qcd_segment);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Tile(exception, tile);
			return NULL;
		}
	}
	return picture;

}


/*
 *
 */
PDC_uint32 PDC_Picture_get_width(	PDC_Exception *exception,
									PDC_Picture *picture)
{
	PDC_uint32 width				= 0;
	PDC_SIZ_Segment *siz_segment	= NULL;

	if(exception == NULL){
		return width;
	}

	if(picture == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_NULL_POINTER, __LINE__, __FILE__);
		return width;
	}

	if(picture->siz_segment == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_NULL_POINTER, __LINE__, __FILE__);
		return width;
	}
	siz_segment = picture->siz_segment;

	width = siz_segment->Xsiz - siz_segment->XOsiz;

	return width;
}

/*
 *
 */
PDC_uint32 PDC_Picture_get_height(	PDC_Exception *exception,
									PDC_Picture *picture)
{
	PDC_uint32 height				= 0;
	PDC_SIZ_Segment *siz_segment	= NULL;

	if(exception == NULL){
		return height;
	}

	if(picture == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_NULL_POINTER, __LINE__, __FILE__);
		return height;
	}

	if(picture->siz_segment == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_NULL_POINTER, __LINE__, __FILE__);
		return height;
	}
	siz_segment = picture->siz_segment;

	height = siz_segment->Ysiz - siz_segment->YOsiz;

	return height;
}


/*
 *
 */
PDC_Picture* PDC_Picture_get_RGB_float(	PDC_Exception *exception,
										PDC_Picture *picture,
										PDC_float32 *out_Vector,
										PDC_uint out_line_feed)
{
	PDC_uint32 numtiles, postile;
	PDC_Tile* tile;

	numtiles = picture->numXtiles * picture->numYtiles;
	for(postile = 0; postile < numtiles; postile += 1){
		tile = PDC_Pointer_Buffer_get_pointer(exception, picture->tiles, postile);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return picture;
		}

		PDC_Tile_get_RGB_float(	exception, tile, out_Vector, out_line_feed);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return picture;
		}
	}

	return picture;
}

/*
 *
 */
PDC_Picture* PDC_Picture_get_RGB_int(	PDC_Exception *exception,
										PDC_Picture *picture,
									PDC_uint32 *out_Vector,
										PDC_uint out_line_feed)
{
	PDC_uint32 numtiles, postile;
	PDC_Tile* tile;

	numtiles = picture->numXtiles * picture->numYtiles;
	for(postile = 0; postile < numtiles; postile += 1){
		tile = PDC_Pointer_Buffer_get_pointer(exception, picture->tiles, postile);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return picture;
		}

		PDC_Tile_get_RGB_int(	exception, tile, out_Vector, out_line_feed);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			return picture;
		}
	}

	return picture;
}


STOP_C
