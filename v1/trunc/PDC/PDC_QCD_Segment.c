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

#include "PDC_QCD_Segment.h"

/*
 *
 */
PDC_QCD_Segment* new_PDC_QCD_Segment_01(Exception* exception)
{
	PDC_QCD_Segment* qcd_segment = NULL;

	qcd_segment = malloc(sizeof(PDC_QCD_Segment));
	if(qcd_segment == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	qcd_segment->succesfull_read	= PDC_false;
	qcd_segment->read_buffer_pos	= 0;
	qcd_segment->Lqcd				= 0;
	qcd_segment->Sqcd				= 0;
	qcd_segment->SPqcd				= NULL;

	return qcd_segment;
}

/*
 *
 */
PDC_QCD_Segment* new_PDC_QCD_Segment_02(Exception* exception,
										PDC_Buffer* buffer,
										PDC_COD_Segment* cod_segment);

/*
 *
 */
PDC_QCD_Segment* delete_PDC_QCD_Segment(PDC_Exception* exception,
										PDC_QCD_Segment* qcd_segment)
{
	if(qcd_segment != NULL){
		if(qcd_segment->SPqcd != NULL){
			free(qcd_segment->SPqcd);
		}
		free(qcd_segment);
	}

	return NULL
}


/*
 *
 */
PDC_QCD_Segment* PDC_QCD_Segment_read_buffer(	Exception* exception,
												PDC_QCD_Segment* qcd_segment,
												PDC_Buffer* buffer,
												PDC_COD_Segment* cod_segment)
{


	return qcd_segment;
}
