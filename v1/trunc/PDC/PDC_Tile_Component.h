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

#ifndef __PDC_TILE_COMPONENT_H__
#define __PDC_TILE_COMPONENT_H__

#include <stdlib.h>
#include "PDC_Parameter.h"


START_C

	struct str_PDC_Tile_Component;
	typedef struct str_PDC_Tile_Component PDC_Tile_Component;

	#include "PDC_Tile.h"
	#include "PDC_SIZ_Segment.h"
	#include "PDC_Picture.h"
	#include "PDC_COD_Segment.h"
	#include "PDC_Resolution.h"
	#include "PDC_Transformation_97_decoder.h"
	#include "PDC_QCD_Segment.h"

	struct str_PDC_Tile_Component{
		PDC_uint32			tcx0;
		PDC_uint32			tcx1;
		PDC_uint32			tcy0;
		PDC_uint32			tcy1;
		PDC_Tile*			tile;
		PDC_float32*		image_memory;
		PDC_int				image_mx0;
		PDC_int				image_mx1;
		PDC_int				image_my0;
		PDC_int				image_my1;
		PDC_int				msizex;
		PDC_int				msizey;

		/*
		 * Pointer to the data with the data for the transformation.
		 */
		PDC_float32*		tile_memory1;
		/*
		 * Pointer to the image data without the extra data for
		 * the transformation.
		 */
		PDC_float32*		tile_memory2;
		PDC_float32*		tile_memory_delete;
		PDC_int				line_stride;			// in Byte,
		PDC_int				line_stride_float;

		PDC_int				tile_mx0;
		PDC_int				tile_mx1;
		PDC_int				tile_my0;
		PDC_int				tile_my1;


		PDC_COD_Segment*				cod_segment;
		PDC_QCD_Segment*				qcd_segment;
		PDC_Resolution*					resolution;
		PDC_SIZ_Segment_Componente		*siz_segment_component;
		PDC_Transformation_97_decoder	*transformer_97_decoder;
		PDC_Threadcall					**threadcalls;
	};

	/*
	 *
	 */
	PDC_Tile_Component* new_PDC_Tile_Component_01(PDC_Exception* exception, PDC_Tile* tile, PDC_uint32 pos);

	/*
	 *
	 */
	PDC_Tile_Component* delete_PDC_Tile_Component(PDC_Exception* exception, PDC_Tile_Component* tile_component);

	/*
	 *
	 */
	PDC_Tile_Component* PDC_Tile_Component_set_COD_Segment(	PDC_Exception* exception,
															PDC_Tile_Component* tile_component,
															PDC_COD_Segment* cod_segment);

	/*
	 *
	 */
	PDC_Tile_Component* PDC_Tile_Component_set_QCD_Segment(	PDC_Exception* exception,
															PDC_Tile_Component* tile_component,
															PDC_QCD_Segment* qcd_segment);

	/*
	 *
	 */
	PDC_Tile_Component* PDC_Tile_Component_set_Resolution(	PDC_Exception* exception,
															PDC_Tile_Component* tile_component);

	/*
	 *
	 */
	PDC_Resolution* PDC_Tile_Component_get_Resolution(	PDC_Exception* exception,
														PDC_Tile_Component* tile_component,
														PDC_uint resolution_pos);

	/*
	 *
	 */
	PDC_Tile_Component* PDC_Tile_Component_inverse_quantization(PDC_Exception* exception,
															PDC_Tile_Component* tile_component);


	/*
	 *
	 */
	PDC_Tile_Component* PDC_Tile_Component_inverse_transformation(	PDC_Exception* exception,
																	PDC_Tile_Component* tile_component);


	/*
	 *
	 */
	PDC_Tile_Component* PDC_Tile_Component_interpolation(	PDC_Exception* exception,
															PDC_Tile_Component* tile_component);
STOP_C

#endif
