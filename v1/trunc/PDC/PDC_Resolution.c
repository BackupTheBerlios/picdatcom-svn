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

#include "PDC_Resolution.h"

START_C

/*
 *
 */
PDC_Resolution* new_PDC_Resolution_01(PDC_Exception* exception)
{
	PDC_Resolution* resolution = NULL;
	resolution = malloc(sizeof(PDC_Resolution));
	if(resolution == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	resolution->n					= 0;
	resolution->r					= 0;
	resolution->resolution_big		= NULL;
	resolution->resolution_small	= NULL;
	resolution->tile_component		= NULL;
	resolution->trx0				= 0;
	resolution->trx1				= 0;
	resolution->try0				= 0;
	resolution->try1				= 0;

	return resolution;
}

/*
 *
 */
PDC_Resolution* new_PDC_Resolution_02(	PDC_Exception* exception,
										PDC_Tile_Component* tile_component)
{
	PDC_Resolution* resolution = NULL;
	resolution = new_PDC_Resolution_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Resolution(exception, resolution);
		return NULL;
	}
	
	resolution->r		= tile_component->cod_segment->number_of_decompostion_levels;

	return resolution;
}

/*
 *
 */
PDC_Resolution* new_PDC_Resolution_03(	PDC_Exception* exception,
										PDC_Resolution* resolution)
{
	return NULL;
}

/*
 *
 */
PDC_Resolution* delete_PDC_Resolution(	PDC_Exception* exception,
										PDC_Resolution* resolution)
{
	return NULL;
}

STOP_C

