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

#ifndef __PDC_TILE_H__
#define __PDC_TILE_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C
	struct str_PDC_Tile;
	typedef struct str_PDC_Tile PDC_Tile;

	#include "PDC_Pointer_Buffer.h"
	#include "PDC_Buffer.h"
	#include "PDC_SIZ_Segment.h"
	#include "PDC_Picture.h"
	#include "PDC_Tile_Component.h"
	#include "PDC_COD_Segment.h"
	#include "PDC_Resolution.h"
	#include "PDC_Precinct.h"


	struct str_PDC_Tile{
		PDC_Picture*		picture;
		PDC_uint32			q;
		PDC_uint32			p;
		PDC_uint32			tx0;
		PDC_uint32			tx1;
		PDC_uint32			ty0;
		PDC_uint32			ty1;
		PDC_uint32			tile_part_counter;			

		PDC_Pointer_Buffer*	tile_component;
		PDC_COD_Segment*	cod_segment;
		PDC_QCD_Segment*	qcd_segment;
	};

	/*
	 * 
	 */
	PDC_Tile* new_PDC_Tile_01(PDC_Exception* exception, PDC_uint32 t, PDC_Picture* picture);
	
	/*
	 *
	 */
	PDC_Tile* delete_PDC_Tile(	PDC_Exception* exception,
								PDC_Tile* tile);



	/*
	 *
	 */
	PDC_Tile* PDC_Tile_set_COD_Segment(	PDC_Exception* exception,
										PDC_Tile* tile,
										PDC_COD_Segment* cod_segment);

	/*
	 *
	 */
	PDC_Tile* PDC_Tile_read_Packageheader(	PDC_Exception* exception,
											PDC_Tile* tile,
											PDC_COD_Segment* cod_segment,
											PDC_Buffer* buffer);


	/*
	 *
	 */
	PDC_Tile* PDC_Tile_decode_Package_01(	PDC_Exception* exception,
											PDC_Tile* tile,
											PDC_COD_Segment* cod_segment);

	/*
	 *
	 */
	PDC_Tile* PDC_Tile_decode_package_02(	PDC_Exception* exception,
											PDC_Tile* tile,
											PDC_uint component_pos,
											PDC_uint resolution_pos,
											PDC_uint precinct_pos,
											PDC_uint layer_pos);

	/*
	 *
	 */
	PDC_Tile* PDC_Tile_decode_package_03(	PDC_Exception* exception,
											PDC_Tile* tile,
											PDC_uint component_pos,
											PDC_uint resolution_pos,
											PDC_uint precinct_pos);

	/*
	 *
	 */
	PDC_Tile* PDC_Tile_read_SOD_01(	PDC_Exception* exception,
									PDC_Tile* tile,
									PDC_Buffer* buffer);

	/*
	 *
	 */
	PDC_uint PDC_Tile_get_numprecinct(	PDC_Exception* exception,
										PDC_Tile* tile,
										PDC_uint componente_pos,
										PDC_uint resolution_pos);

	/*
	 *
	 */
	PDC_Resolution* PDC_Tile_get_resolution(	PDC_Exception* exception,
												PDC_Tile* tile,
												PDC_uint componente_pos,
												PDC_uint resolution_pos);

	/*
	 *
	 */
	void PDC_Tile_read_package_header(	PDC_Exception* exception,
										PDC_Tile* tile,
										PDC_Buffer* buffer,
										PDC_uint component_pos,
										PDC_uint resolution_pos,
										PDC_uint precinct_pos,
										PDC_uint layer_pos);

	/*
	 *
	 */
	void PDC_Tile_dequantization_01(	PDC_Exception* exception,
										PDC_Tile* tile);

	/* 
	 *
	 
	PDC_Precinct* PDC_Tile_get_precinct(PDC_Exception* exception,
										PDC_Tile* tile,
										PDC_uint componente_pos,
										PDC_uint resolution_pos,
										PDC_uint precinct_pos);
	*/									
STOP_C
#endif
	
