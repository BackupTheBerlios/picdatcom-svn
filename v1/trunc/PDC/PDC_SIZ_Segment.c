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

#include "PDC_SIZ_Segment.h"

START_C

/*
 *
 */
PDC_SIZ_Segment* new_PDC_SIZ_Segment_01()
{
	PDC_SIZ_Segment* siz_segment = NULL;
	
	siz_segment = malloc(sizeof(PDC_SIZ_Segment));
	if(siz_segment == NULL){
		return NULL;
	}
	siz_segment->exception			= NULL;
	siz_segment->componente_part	= NULL;

	siz_segment->Lsiz	= 0;
	siz_segment->Rsiz	= 0;
	siz_segment->Xsiz	= 0;
	siz_segment->Ysiz	= 0;
	siz_segment->XOsiz	= 0;
	siz_segment->YOsiz	= 0;
	siz_segment->XTsiz	= 0;
	siz_segment->YTsiz	= 0;
	siz_segment->XTOsiz	= 0;
	siz_segment->YTOsiz	= 0;
	siz_segment->Csiz	= 0;

	siz_segment->componente_part = new_PDC_Pointer_Buffer_01(DEFAULT_NUMBER_COMPONENTEN);
	if(siz_segment->componente_part == NULL){
		delete_PDC_SIZ_Segment_01(siz_segment);
		return NULL;
	}
	return siz_segment;
}

/*
 *
 */
PDC_SIZ_Segment* new_PDC_SIZ_Segment_02(PDC_Buffer* buffer)
{
	PDC_SIZ_Segment* siz_segment = NULL;

	return siz_segment;
}

/*
 *
 */
void delete_PDC_SIZ_Segment_01(PDC_SIZ_Segment* siz_segment)
{

}

/*
 *
 */
PDC_SIZ_Segment* PDC_SIZ_Segment_read_buffer(	PDC_SIZ_Segment* siz_segment, 
												PDC_Buffer* buffer)
{
	PDC_uint32 read_byte_pos;
	PDC_uint16 csiz_pos;
	PDC_SIZ_Segment_Componente* siz_segment_com;

	if(buffer->read_byte_pos + 38 < buffer->write_byte_pos){
		PDC_Exception_error(siz_segment->exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return siz_segment;
	}
	read_byte_pos = buffer->read_byte_pos;

	PDC_Buffer_read_uint16(buffer, &(siz_segment->Csiz));
	PDC_Buffer_read_uint16(buffer, &(siz_segment->Rsiz));
	PDC_Buffer_read_uint32(buffer, &(siz_segment->Xsiz));
	PDC_Buffer_read_uint32(buffer, &(siz_segment->Ysiz));
	PDC_Buffer_read_uint32(buffer, &(siz_segment->XOsiz));
	PDC_Buffer_read_uint32(buffer, &(siz_segment->YOsiz));
	PDC_Buffer_read_uint32(buffer, &(siz_segment->XTsiz));
	PDC_Buffer_read_uint32(buffer, &(siz_segment->YTsiz));
	PDC_Buffer_read_uint32(buffer, &(siz_segment->XTOsiz));
	PDC_Buffer_read_uint32(buffer, &(siz_segment->YTOsiz));
	PDC_Buffer_read_uint16(buffer, &(siz_segment->Csiz));

	if(siz_segment->Csiz * 3 > buffer->write_byte_pos - buffer->read_byte_pos){
		// Todo
		buffer->read_byte_pos = read_byte_po
	}


	for(csiz_pos = 0;csiz_pos < siz_segment->Csiz; csiz_pos += 1){
		siz_segment_com = 
	}

	return siz_segment;
}


STOP_C