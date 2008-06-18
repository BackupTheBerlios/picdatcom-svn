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

#include "PDC_SOT_Segment.h"

START_C

/*
 *
 */
PDC_SOT_Segment* new_PDC_SOT_Segment_01(PDC_Exception* exception)
{
	PDC_SOT_Segment* sot_segment = NULL;
	
	sot_segment = malloc(sizeof(PDC_SOT_Segment));
	if(sot_segment == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	
	sot_segment->Isot	= 0;
	sot_segment->Lsot	= 0;
	sot_segment->Psot	= 0;
	sot_segment->TNsot	= 0;
	sot_segment->TPsot	= 0;

	return sot_segment;
}

/*
 *
 */
PDC_SOT_Segment* new_PDC_SOT_Segment_02(PDC_Exception* exception, PDC_Buffer* buffer)
{
	PDC_SOT_Segment* sot_segment = NULL;

	sot_segment = new_PDC_SOT_Segment_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_SOT_Segment(exception, sot_segment);
		return NULL;
	}
	
	sot_segment = PDC_SOT_Segment_read_buffer(exception,  sot_segment, buffer);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_SOT_Segment(exception, sot_segment);
		return NULL;
	}

	return sot_segment;
}


/*
 *
 */
void delete_PDC_SOT_Segment(PDC_Exception* exception, PDC_SOT_Segment* sot_segment)
{
	if(sot_segment != NULL){
		
		free(sot_segment);
	}
}

/*
 *
 */
PDC_SOT_Segment* PDC_SOT_Segment_read_buffer(	PDC_Exception* exception,
												PDC_SOT_Segment* sot_segment,
												PDC_Buffer* buffer)
{
	
	if(buffer->read_byte_pos + 10 >= buffer->write_byte_pos){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return sot_segment;
	}
	
	PDC_Buffer_read_uint16(exception, buffer, &(sot_segment->Lsot));
	PDC_Buffer_read_uint16(exception, buffer, &(sot_segment->Isot));
	PDC_Buffer_read_uint32(exception, buffer, &(sot_segment->Psot));
	PDC_Buffer_read_uint8(exception, buffer, &(sot_segment->TPsot));
	PDC_Buffer_read_uint8(exception, buffer, &(sot_segment->TNsot));

	return sot_segment;
}

STOP_C