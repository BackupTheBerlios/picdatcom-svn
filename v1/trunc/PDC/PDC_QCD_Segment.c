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
PDC_QCD_Segment* new_PDC_QCD_Segment_01(PDC_Exception* exception)
{
	PDC_QCD_Segment* qcd_segment = NULL;

	qcd_segment = malloc(sizeof(PDC_QCD_Segment));
	if(qcd_segment == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	qcd_segment->succesfull_read	= PDC_false;
	qcd_segment->read_buffer_pos	= 0xFFFFFFFF;
	qcd_segment->Lqcd				= 0;
	qcd_segment->Sqcd				= 0;
	qcd_segment->SPqcd				= NULL;
	qcd_segment->read_pos_from		= PDC_READ_BUFFER_BYTE_POS;

	return qcd_segment;
}

/*
 *
 */
PDC_QCD_Segment* new_PDC_QCD_Segment_02(PDC_Exception* exception,
										PDC_Buffer* buffer,
										PDC_COD_Segment* cod_segment)
{
	PDC_QCD_Segment* qcd_segment = NULL;

	qcd_segment = new_PDC_QCD_Segment_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		return NULL;
	}

	qcd_segment = PDC_QCD_Segment_read_buffer(exception, qcd_segment, buffer, cod_segment);
	return NULL;
}

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

	return NULL;
}


/*
 *
 */
PDC_QCD_Segment* PDC_QCD_Segment_read_buffer(	PDC_Exception* exception,
												PDC_QCD_Segment* qcd_segment,
												PDC_Buffer* buffer,
												PDC_COD_Segment* cod_segment)
{
	PDC_uint32	read_byte_pos;
	PDC_uint8	quantization, temp;
	PDC_uint32	malloc_size, number_subbands, pos_subband;
	PDC_uint16	exponent, mantissa, temp_exponent, NL, nb;

	
	if(qcd_segment->succesfull_read == PDC_true){
		return qcd_segment;
	}
	read_byte_pos = buffer->read_byte_pos;

	if(qcd_segment->read_pos_from == PDC_READ_BUFFER_BYTE_POS){
		qcd_segment->read_buffer_pos = buffer->read_byte_pos;
	}else{
		buffer->read_byte_pos = qcd_segment->read_buffer_pos;
	}


	buffer = PDC_Buffer_read_uint16(exception, buffer, &(qcd_segment->Lqcd));
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		buffer->read_byte_pos = read_byte_pos;
		return qcd_segment;
	}
	if(buffer->read_byte_pos + qcd_segment->Lqcd - 2 > buffer->write_byte_pos){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_RANGE, __LINE__, __FILE__);
		buffer->read_byte_pos = read_byte_pos ;
		return qcd_segment;
	}
	if(cod_segment == NULL){
		if(qcd_segment->read_pos_from != PDC_READ_SEGMENT_BYTE_POS){
			qcd_segment->read_pos_from		= PDC_READ_SEGMENT_BYTE_POS;
			buffer->read_byte_pos			= read_byte_pos + qcd_segment->Lqcd;
			qcd_segment->read_buffer_pos	= read_byte_pos;
		}else{
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
		}
		return qcd_segment;
	}
	buffer = PDC_Buffer_read_uint8(exception, buffer, &(qcd_segment->Sqcd));
	quantization = qcd_segment->Sqcd & MASK_QUANTIZATION;

	number_subbands = (1 + 3 * cod_segment->number_of_decompostion_levels) ;
	malloc_size = number_subbands * 2;
	qcd_segment->SPqcd = malloc(malloc_size);
	if(qcd_segment == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		buffer->read_byte_pos = read_byte_pos;
		return qcd_segment;	
	}

	if(quantization == NO_QUANTIZATION){
		for(pos_subband = 0; pos_subband < number_subbands; pos_subband += 1){
			buffer = PDC_Buffer_read_uint8(exception, buffer, &(temp));
			qcd_segment->SPqcd[pos_subband] = temp;
		}
	}else if(quantization == SCALAR_DERIVED){
		pos_subband = 0;
		buffer = PDC_Buffer_read_uint16(exception, buffer, &(qcd_segment->SPqcd[pos_subband]));
		exponent = mantissa = qcd_segment->SPqcd[pos_subband];
		exponent = exponent >> SHIFT_EXPONENT;
		mantissa &= MASK_MANTISSA;
		NL	= cod_segment->number_of_decompostion_levels;
		nb	= NL;
		pos_subband += 1;
		for(;pos_subband < number_subbands;){
			
			temp_exponent = exponent - NL + nb;
			temp_exponent <<= SHIFT_EXPONENT;
			temp_exponent |= mantissa & MASK_MANTISSA;
			
			qcd_segment->SPqcd[pos_subband] = temp_exponent;
			pos_subband += 1;
			qcd_segment->SPqcd[pos_subband] = temp_exponent;
			pos_subband += 1;
			qcd_segment->SPqcd[pos_subband] = temp_exponent;
			pos_subband += 1;
			nb -= 1;
		}
	}else if(quantization == SCALAR_EXPOUNDED){
		for(pos_subband = 0; pos_subband < number_subbands; pos_subband += 1){
			buffer = PDC_Buffer_read_uint16(exception, buffer, &(qcd_segment->SPqcd[pos_subband]));
		}
	}else{
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_UNKNOW_CODE, __LINE__, __FILE__);
	}
	qcd_segment->succesfull_read = PDC_true;
	
	if(qcd_segment->read_pos_from == PDC_READ_SEGMENT_BYTE_POS){
		buffer->read_byte_pos = read_byte_pos;
	}
	
	return qcd_segment;
}
