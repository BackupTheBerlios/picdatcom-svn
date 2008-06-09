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

#include "PDC_COM_Segment.h"

START_C

/*
 *
 */
PDC_COM_Segment* new_PDC_COM_Segment_01(	PDC_Exception* exception)
{
	PDC_COM_Segment* com_segment = NULL;

	com_segment = malloc(sizeof(PDC_COM_Segment));
	if(com_segment == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	com_segment->Ccom	= NULL;
	com_segment->Lcom	= 0;
	com_segment->Rcom	= 0;

	return com_segment;
}

/*
 *
 */	
PDC_COM_Segment* new_PDC_COM_Segment_02(	PDC_Exception*	exception,
											PDC_Buffer*		buffer)
{
	PDC_COM_Segment*	com_segment = NULL;
	PDC_uint32			read_byte_pos;
	com_segment = new_PDC_COM_Segment_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return NULL;
	}

	read_byte_pos = buffer->read_byte_pos;
	com_segment = PDC_COM_Segment_read_buffer(exception, com_segment, buffer);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		buffer->read_byte_pos = read_byte_pos;
		delete_PDC_COM_Segment(exception, com_segment);
		return NULL;
	}

	return com_segment;
}
/*
 *
 */
PDC_COM_Segment* delete_PDC_COM_Segment(	PDC_Exception*		exception,
											PDC_COM_Segment*	com_segment)
{
	return NULL;
}

/*
 *
 */
PDC_COM_Segment* PDC_COM_Segment_read_buffer(	PDC_Exception*		exception,
												PDC_COM_Segment*	com_segment,
												PDC_Buffer*			buffer)
{
	PDC_uint32 read_byte_pos = buffer->read_byte_pos;
	PDC_uint32 number_bytes;

	buffer = PDC_Buffer_read_uint16(exception, buffer, &(com_segment->Lcom));
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		buffer->read_byte_pos = read_byte_pos;
		return com_segment;
	}

	if(buffer->read_byte_pos - 2 + com_segment->Lcom > buffer->write_byte_pos){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		buffer->read_byte_pos = read_byte_pos ;
		return com_segment;
	}
	buffer = PDC_Buffer_read_uint16(exception, buffer, &(com_segment->Rcom));

	number_bytes = com_segment->Lcom - 4;
	com_segment->Ccom = malloc(number_bytes);
	if(com_segment->Ccom == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		buffer->read_byte_pos = read_byte_pos ;
		return com_segment;
	}

	buffer = PDC_Buffer_read_uint8_02(exception, buffer, com_segment->Ccom, number_bytes);

	return com_segment;
}

STOP_C
