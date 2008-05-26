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

	#include "PDC_SIZ_Segment.h"

	struct str_PDC_Picture{
		PDC_SIZ_Segment* siz_segment;
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
	
STOP_C
#endif