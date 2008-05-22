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

#include "PDC_SIZ_Segment_Componente.h"

START_C


/*
 * 
 */
PDC_SIZ_Segment_Componente* new_PDC_SIZ_Segment_Componente_01()
{
	PDC_SIZ_Segment_Componente* siz_segment_com = NULL;
	siz_segment_com = malloc(sizeof(PDC_SIZ_Segment_Componente));
	if(siz_segment_com == NULL){
		return NULL;
	}
	siz_segment_com->exception = NULL;

	siz_segment_com->exception = malloc(sizeof(PDC_SIZ_Segment_Componente));
	if(siz_segment_com->exception == NULL){
		delete_PDC_SIZ_Segment_Componente(siz_segment_com);	
		return NULL;
	}
	
	siz_segment_com->Ssiz	= 0;
	siz_segment_com->XRsiz	= 0;
	siz_segment_com->YRsiz	= 0;

	return siz_segment_com;
}

/*
 * 
 */
PDC_SIZ_Segment_Componente* new_PDC_SIZ_Segment_Componente_02(PDC_Buffer* buffer)
{
	PDC_SIZ_Segment_Componente* siz_segment_com = NULL;
	siz_segment_com = new_PDC_SIZ_Segment_Componente_01();
	if(siz_segment_com == NULL){
		return NULL;
	}
	PDC_SIZ_Segment_Componente_read_buffer(siz_segment_com, buffer);

	return siz_segment_com;
}

/*
 *
 */
void delete_PDC_SIZ_Segment_Componente(PDC_SIZ_Segment_Componente* siz_segment_com)
{
	if(siz_segment_com != NULL){
		delete_PDC_Exception(siz_segment_com->exception);
		free(siz_segment_com);
	}
}

/*
 *
 */
PDC_SIZ_Segment_Componente* PDC_SIZ_Segment_Componente_read_buffer(	PDC_SIZ_Segment_Componente* siz_segment_com,
																	PDC_Buffer* buffer)
{
	if(buffer->read_byte_pos + 3 >= buffer->write_byte_pos){
		PDC_Exception_error(siz_segment_com->exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return siz_segment_com;
	}

	PDC_Buffer_read_uint8(buffer, &(siz_segment_com->Ssiz));
	PDC_Buffer_read_uint8(buffer, &(siz_segment_com->XRsiz));
	PDC_Buffer_read_uint8(buffer, &(siz_segment_com->YRsiz));

	return siz_segment_com;
}

STOP_C