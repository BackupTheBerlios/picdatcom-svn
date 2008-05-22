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

#include "PDC_Picture.h"

START_C

/*
 *
 */
PDC_Picture* new_PDC_Picture()
{
	PDC_Picture* picture = NULL;
	picture = malloc(sizeof(PDC_Picture));
	if(picture == NULL){
		return NULL;
	}
	picture->siz_segment = NULL;
	return picture;
}

/*
 * 
 */
void delete_PDC_Picture(PDC_Picture* picture)
{
	if(picture != NULL){
		delete_PDC_SIZ_Segment_01(picture->siz_segment);
		free(picture);
	}
}

STOP_C
