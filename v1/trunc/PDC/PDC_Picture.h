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

#ifndef __PDC_PICTURE_H__
#define __PDC_PICTURE_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C
	struct str_PDC_Picture;
	typedef struct str_PDC_Picture PDC_Picture;
	typedef enum{PDC_USE_32_BIT, PDC_USE_64_BIT} PDC_use_bits;

	#include "PDC_SIZ_Segment.h"
	#include "PDC_COD_Segment.h"
	#include "PDC_QCD_Segment.h"
	#include "PDC_COM_Segment.h"
	#include "PDC_SOT_Segment.h"
	#include "PDC_Tile.h"

	struct str_PDC_Picture{
		PDC_SIZ_Segment*	siz_segment;
		PDC_COD_Segment*	cod_segment;
		PDC_QCD_Segment*	qcd_segment;
		PDC_COM_Segment*	com_segment;

		PDC_uint32			sizeX;
		PDC_uint32			sizeY;

		PDC_uint32			numXtiles;
		PDC_uint32			numYtiles;

		PDC_Pointer_Buffer*	tiles;
		PDC_Pointer_Buffer*	componentes;

		PDC_use_bits		use_bits;
	};

	/*
	 *
	 */
	PDC_Picture* new_PDC_Picture(PDC_Exception* exception);

	/*
	 * 
	 */
	void delete_PDC_Picture(PDC_Exception* exception,
							PDC_Picture* picture);
	


	/*
	 *
	 */
	PDC_Picture* PDC_Picture_set_SIZ_Segment(	PDC_Exception* exception,
												PDC_Picture* picture, 
												PDC_SIZ_Segment* siz_segment);

	/*
	 *
	 */
	PDC_Picture* PDC_Picture_set_COD_Segment(	PDC_Exception* exception,
												PDC_Picture* picture,
												PDC_COD_Segment* cod_segment);
												
	/*
	 *
	 */
	PDC_Picture* PDC_Picture_set_QCD_Segment(	PDC_Exception* exception,
												PDC_Picture* picture,
												PDC_QCD_Segment* qcd_segment);
												
									
	
STOP_C
#endif