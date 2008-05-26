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

#include "PDC_COD_Segment.h"

START_C

/*
 *
 */
 PDC_COD_Segment* new_PDC_COD_Segment_01(PDC_Exception *exception)
{
	PDC_COD_Segment* cod_segment = NULL;
	cod_segment = malloc(sizeof(PDC_COD_Segment));
	if(cod_segment == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	cod_segment->lcot								= 0;
	cod_segment->scot								= 0;
	cod_segment->progression_order					= 0;
	cod_segment->number_of_layer					= 0;
	cod_segment->multiple_component_transformation	= 0;
	cod_segment->number_of_decompostion_levels		= 0;
	cod_segment->code_block_width					= 0;
	cod_segment->code_block_height					= 0;
	cod_segment->code_block_style					= 0;
	cod_segment->transformation						= 0;
	cod_segment->precinct_size						= NULL;

	return cod_segment;
}

/*
 *
 */
PDC_COD_Segment* new_PDC_COD_Segment_02(	PDC_Exception *exception,
											PDC_Buffer* buffer)
{
	PDC_COD_Segment* cod_segment;
	cod_segment = new_PDC_COD_Segment_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return NULL;
	}

	cod_segment = PDC_COD_Segment_read_buffer(	exception,
												cod_segment,
												buffer);

	return cod_segment;
}

/*
 *
 */
PDC_COD_Segment* delete_PDC_COD_Segment(	PDC_Exception* exception,
											PDC_COD_Segment* cod_segment)
{
	if(cod_segment != NULL){
		delete_PDC_Buffer(exception, cod_segment->precinct_size);
		free(cod_segment);
	
	}
	return NULL;
}

/*
 *
 */
PDC_COD_Segment* PDC_COD_Segment_read_buffer(	PDC_Exception* exception,
												PDC_COD_Segment* cod_segment,
												PDC_Buffer* buffer)
{
	PDC_uint32	level_pos;
	PDC_uint8	precinct_size;

	if(buffer->read_byte_pos + 12 >= buffer->write_byte_pos){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		return cod_segment;
	}

	PDC_Buffer_read_uint16(exception, buffer, &(cod_segment->lcot));
	PDC_Buffer_read_uint8(exception, buffer, &(cod_segment->scot));
	PDC_Buffer_read_uint8(exception, buffer, &(cod_segment->progression_order));
	PDC_Buffer_read_uint16(exception, buffer, &(cod_segment->number_of_layer));
	PDC_Buffer_read_uint8(exception, buffer, &(cod_segment->multiple_component_transformation));
	PDC_Buffer_read_uint8(exception, buffer, &(cod_segment->number_of_decompostion_levels));
	PDC_Buffer_read_uint8(exception, buffer, &(cod_segment->code_block_width));
	PDC_Buffer_read_uint8(exception, buffer, &(cod_segment->code_block_height));
	PDC_Buffer_read_uint8(exception, buffer, &(cod_segment->code_block_style));
	PDC_Buffer_read_uint8(exception, buffer, &(cod_segment->transformation));



	if(cod_segment->number_of_decompostion_levels != 0){
		cod_segment->precinct_size = new_PDC_Buffer_1(exception, cod_segment->number_of_decompostion_levels + 1);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
			return cod_segment;		
		}

		if((cod_segment->scot & DEFAULT_PRECINCT_SIZE) == DEFAULT_PRECINCT_SIZE){
			for(level_pos = 0; level_pos <= cod_segment->number_of_decompostion_levels; level_pos += 1){
				PDC_Buffer_read_uint8(exception, buffer, &precinct_size);
				PDC_Buffer_add_byte_1(exception, cod_segment->precinct_size, precinct_size);
			}
		}else{
			precinct_size = 0xFF;
			for(level_pos = 0; level_pos <= cod_segment->number_of_decompostion_levels; level_pos += 1){
				PDC_Buffer_add_byte_1(exception, cod_segment->precinct_size, precinct_size);
			}
		}
	}
	return cod_segment;
}

STOP_C

