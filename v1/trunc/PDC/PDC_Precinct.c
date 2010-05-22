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

#include "PDC_Precinct.h"

START_C

//extern FILE* DEBUG_FILE;

/*
 *
 */
PDC_Precinct* new_PDC_Precinct_01(PDC_Exception* exception)
{
	PDC_Precinct* precinct;
	precinct = malloc(sizeof(PDC_Precinct));
	if(precinct == NULL){
		PDC_Exception_error(exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	precinct->codeblock_x0				= 0;
	precinct->codeblock_x1				= 0;
	precinct->codeblock_y0				= 0;
	precinct->codeblock_y1				= 0;
	precinct->resolution				= NULL;
	precinct->codeblock_inclusion[0]	= NULL;
	precinct->codeblock_inclusion[1]	= NULL;
	precinct->codeblock_inclusion[2]	= NULL;
	precinct->zero_bitplane[0]			= NULL;
	precinct->zero_bitplane[1]			= NULL;
	precinct->zero_bitplane[2]			= NULL;

	return precinct;
}

/*
 *
 */
PDC_Precinct* new_PDC_Precinct_02(PDC_Exception* exception,
								  PDC_Resolution* resolution,
								  PDC_uint pos_x,
								  PDC_uint pos_y)
{
	PDC_uint		codeblocks_x;
	PDC_uint		codeblocks_y;
	PDC_Precinct*	precinct = NULL;
	PDC_uint		x0, x1, y0, y1, size_x, size_y;

	precinct = new_PDC_Precinct_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Precinct(exception, precinct);
		return NULL;
	}

	precinct->resolution = resolution;

	codeblocks_x = 1 << (resolution->PPx - resolution->xcb);
	codeblocks_y = 1 << (resolution->PPy - resolution->ycb);

	x0 = codeblocks_x * pos_x;
	x1 = x0 + codeblocks_x;
	y0 = codeblocks_y * pos_y;
	y1 = y0 + codeblocks_y;

	precinct->codeblock_x0 = max_uint(x0, resolution->codeblock_x0);
	precinct->codeblock_x1 = min_uint(x1, resolution->codeblock_x1);
	precinct->codeblock_y0 = max_uint(y0, resolution->codeblock_y0);
	precinct->codeblock_y1 = min_uint(y1, resolution->codeblock_y1);

	size_x = precinct->codeblock_x1 - precinct->codeblock_x0;
	size_y = precinct->codeblock_y1 - precinct->codeblock_y0;

	precinct->codeblock_inclusion[0] = new_PDC_Tagtree_01(exception, size_x, size_y);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Precinct(exception, precinct);
		return NULL;
	}

	precinct->zero_bitplane[0]	= new_PDC_Tagtree_01(exception, size_x, size_y);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Precinct(exception, precinct);
		return NULL;
	}

	if(resolution->r != 0){
		precinct->codeblock_inclusion[1] = new_PDC_Tagtree_01(exception, size_x, size_y);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Precinct(exception, precinct);
			return NULL;
		}

		precinct->codeblock_inclusion[2] = new_PDC_Tagtree_01(exception, size_x, size_y);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Precinct(exception, precinct);
			return NULL;
		}

		precinct->zero_bitplane[1]	= new_PDC_Tagtree_01(exception, size_x, size_y);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Precinct(exception, precinct);
			return NULL;
		}

		precinct->zero_bitplane[2]	= new_PDC_Tagtree_01(exception, size_x, size_y);
		if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
			delete_PDC_Precinct(exception, precinct);
			return NULL;
		}
	}

	return precinct;
}


/*
 *
 */
PDC_Precinct* delete_PDC_Precinct(	PDC_Exception* exception,
										PDC_Precinct* precinct)
{
	if(precinct != NULL){

		delete_PDC_Tagtree_01(exception, precinct->codeblock_inclusion[0]);
		delete_PDC_Tagtree_01(exception, precinct->codeblock_inclusion[1]);
		delete_PDC_Tagtree_01(exception, precinct->codeblock_inclusion[2]);
		delete_PDC_Tagtree_01(exception, precinct->zero_bitplane[0]);
		delete_PDC_Tagtree_01(exception, precinct->zero_bitplane[1]);
		delete_PDC_Tagtree_01(exception, precinct->zero_bitplane[2]);

		precinct->codeblock_inclusion[0]	= NULL;
		precinct->codeblock_inclusion[1]	= NULL;
		precinct->codeblock_inclusion[2]	= NULL;
		precinct->zero_bitplane[0]			= NULL;
		precinct->zero_bitplane[1]			= NULL;
		precinct->zero_bitplane[2]			= NULL;


		free(precinct);
	}
	return NULL;
}



/*
 *
 */
PDC_Precinct* PDC_Precinct_read_package_header(	PDC_Exception* exception,
												PDC_Precinct* precinct,
												PDC_Buffer*	buffer,
												PDC_uint layer_pos)
{
	PDC_bit				bit;
	PDC_uint			pos_subband, size_subband, pos_codeblock, pos_codeblock_x, pos_codeblock_y, size_codeblock_x, size_codeblock_y;
	PDC_uint			pos_x, pos_y, size_x;
	PDC_Subband*		subband;
	PDC_Codeblock*		codeblock;
	PDC_uint			number_of_codingpasses, number_of_codeword_segment, codeword_segment_pos;
	PDC_Codeword_List*	codeword_list;
	PDC_uint			num_bits, codewordlength;
	PDC_bool			layer_inclusion;

	PDC_Buffer_push_state(exception, buffer);
	PDC_Tagtree_push(exception, precinct->codeblock_inclusion[0]);
	PDC_Tagtree_push(exception, precinct->codeblock_inclusion[1]);
	PDC_Tagtree_push(exception, precinct->codeblock_inclusion[2]);
	PDC_Tagtree_push(exception, precinct->zero_bitplane[0]);
	PDC_Tagtree_push(exception, precinct->zero_bitplane[1]);
	PDC_Tagtree_push(exception, precinct->zero_bitplane[2]);



	if(precinct->resolution->r == 0){
		size_subband = 1;
	}else{
		size_subband = 3;
	}


	bit = PDC_Buffer_get_next_bit(exception, buffer);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		PDC_Buffer_pop_state(exception, buffer);
		PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
		PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
		PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
		PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
		PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
		PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);
		return precinct;
	}
	if(bit == 1){
		for(pos_subband = 0; pos_subband < size_subband; pos_subband += 1){
			subband = precinct->resolution->subband[pos_subband];
			pos_codeblock = 0;
			size_codeblock_x = precinct->codeblock_x1;
			size_codeblock_y = precinct->codeblock_y1;
			for(pos_codeblock_y = precinct->codeblock_y0; pos_codeblock_y < size_codeblock_y; pos_codeblock_y += 1){
				for(pos_codeblock_x = precinct->codeblock_x0; pos_codeblock_x < size_codeblock_x; pos_codeblock_x += 1){
					pos_x	= pos_codeblock_x - precinct->codeblock_x0;
					pos_y	= pos_codeblock_y - precinct->codeblock_y0;
					size_x	= precinct->codeblock_x1 - precinct->codeblock_x0;
					pos_codeblock = PDC_Resolution_get_codeblock_position(exception, precinct->resolution, pos_codeblock_x, pos_codeblock_y);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						PDC_Buffer_pop_state(exception, buffer);
						PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
						PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
						PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
						PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
						PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
						PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);
						return precinct;
					}
					codeblock = subband->codeblocks[pos_codeblock];
					layer_inclusion = PDC_false;


					if(codeblock->codeblock_inclusion == PDC_false){
						codeblock->codeblock_inclusion = PDC_Tagtree_decode_pos(exception,
																				precinct->codeblock_inclusion[pos_subband],
																				buffer,
																				pos_x,
																				pos_y,
																				layer_pos + 1);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							PDC_Buffer_pop_state(exception, buffer);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);
								return precinct;
						}
						if(codeblock->codeblock_inclusion == PDC_true){
							layer_inclusion = PDC_true;
						}

					}else{
						bit = PDC_Buffer_get_next_bit(exception, buffer);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							PDC_Buffer_pop_state(exception, buffer);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);
							return precinct;
						}

						if(bit != 0){
							layer_inclusion = PDC_true;
						}

					}

					if(layer_inclusion == PDC_true){
						if(codeblock->zero_bit_plane_inclusion	!= PDC_true){
							codeblock->zero_bit_plane_inclusion = PDC_Tagtree_decode_pos(	exception,
																							precinct->zero_bitplane[pos_subband],
																							buffer,
																							pos_x,
																							pos_y,
																							MAX_INT);
							if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
								PDC_Buffer_pop_state(exception, buffer);
								PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
								PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
								PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
								PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
								PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
								PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);
								return precinct;
							}
							codeblock->zero_bit_plane_inclusion	= PDC_true;
							codeblock->zero_bitplanes			= PDC_Tagtree_get_value(	exception,
																							precinct->zero_bitplane[pos_subband],
																							pos_x,
																							pos_y);
							if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
								PDC_Buffer_pop_state(exception, buffer);
								PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
								PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
								PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
								PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
								PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
								PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);
								return precinct;
							}
						}
						number_of_codingpasses = PDC_Buffer_get_number_of_codingpasses(exception, buffer);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							PDC_Buffer_pop_state(exception, buffer);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);
							return precinct;
						}

						number_of_codeword_segment = PDC_Codeblock_set_number_of_coding_passes(	exception,
																								codeblock,
																								number_of_codingpasses,
																								layer_pos);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							PDC_Buffer_pop_state(exception, buffer);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);
							return precinct;
						}

						codeblock->Lblock += PDC_Buffer_get_Lblock_increase(	exception,
																				buffer);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							PDC_Buffer_pop_state(exception, buffer);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
							PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
							PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);
							return precinct;
						}
						for(codeword_segment_pos = 0; codeword_segment_pos < number_of_codeword_segment; codeword_segment_pos++){
							codeword_list = codeblock->write_codeword;
							number_of_codingpasses = codeword_list->number_of_coding_passes;
							num_bits = PDC_floor_log2( number_of_codingpasses);

							num_bits += codeblock->Lblock;
							codewordlength = PDC_Buffer_read_bits(	exception,
																	buffer,
																	num_bits);
							if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
								PDC_Buffer_pop_state(exception, buffer);
								PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
								PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
								PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
								PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
								PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
								PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);
								return precinct;
							}

							codeword_list->number_of_byte = codewordlength;
							if(codeword_list->next_codedword != NULL){
								codeword_list = codeword_list->next_codedword;
							}
						}
					}
				}
			}
		}

		PDC_Buffer_padding_read(exception, buffer);
		/* Start reading codewordsegments. */

		for(pos_subband = 0; pos_subband < size_subband; pos_subband += 1){
			subband = precinct->resolution->subband[pos_subband];
			for(pos_codeblock_y = precinct->codeblock_y0; pos_codeblock_y < size_codeblock_y; pos_codeblock_y += 1){
				for(pos_codeblock_x = precinct->codeblock_x0; pos_codeblock_x < size_codeblock_x; pos_codeblock_x += 1){
					pos_x	= pos_codeblock_x - precinct->codeblock_x0;
					pos_y	= pos_codeblock_y - precinct->codeblock_y0;
					size_x	= precinct->codeblock_x1 - precinct->codeblock_x0;
					pos_codeblock = PDC_Resolution_get_codeblock_position(exception, precinct->resolution, pos_codeblock_x, pos_codeblock_y);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						PDC_Buffer_pop_state(exception, buffer);
						PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
						PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
						PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
						PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
						PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
						PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);
						return precinct;
					}
					codeblock = subband->codeblocks[pos_codeblock];
					if(codeblock->codeblock_inclusion == PDC_true){
						codeword_list = codeblock->write_codeword;

						while(codeword_list != NULL){
							if(codeword_list->number_of_byte != 0){
								PDC_Buffer_copy_bytes_01(	exception,
															buffer,
															codeword_list->codeword,
															codeword_list->number_of_byte);
								codeword_list->number_of_byte = 0;
								if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
									PDC_Buffer_pop_state(exception, buffer);
									PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
									PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
									PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
									PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
									PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
									PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);
									return precinct;
								}
							}
							codeword_list = codeword_list->next_codedword;
						}
					}
				}
			}
		}
	}

	return precinct;
}

void PDC_Precinct_print(PDC_Exception* exception, FILE *file, PDC_Precinct* precinct, PDC_uint layer_pos)
{
	PDC_uint			pos_subband, size_subband, pos_codeblock, pos_codeblock_x, pos_codeblock_y, size_codeblock_x, size_codeblock_y;
	PDC_uint			pos_x, pos_y, size_x;
	PDC_Subband*		subband;

	PDC_Codeblock*		codeblock;

	if(precinct->resolution->r == 0){
		size_subband = 1;
	}else{
		size_subband = 3;
	}

	if(precinct->bit1 == 1){
		fprintf(file,"Precinct inclusion at resolution r = %lu and layer = %lu \n", precinct->resolution->r , layer_pos);
		for(pos_subband = 0; pos_subband < size_subband; pos_subband += 1){
			fprintf(file,"Subband %lu\n", pos_subband);
			subband = precinct->resolution->subband[pos_subband];
			subband = precinct->resolution->subband[pos_subband];
			pos_codeblock = 0;
			size_codeblock_x = precinct->codeblock_x1;
			size_codeblock_y = precinct->codeblock_y1;
			for(pos_codeblock_y = precinct->codeblock_y0; pos_codeblock_y < size_codeblock_y; pos_codeblock_y += 1){
				for(pos_codeblock_x = precinct->codeblock_x0; pos_codeblock_x < size_codeblock_x; pos_codeblock_x += 1){
					pos_x	= pos_codeblock_x - precinct->codeblock_x0;
					pos_y	= pos_codeblock_y - precinct->codeblock_y0;
					size_x	= precinct->codeblock_x1 - precinct->codeblock_x0;
					pos_codeblock = PDC_Resolution_get_codeblock_position(exception, precinct->resolution, pos_codeblock_x, pos_codeblock_y);
					codeblock = subband->codeblocks[pos_codeblock];
					if(codeblock->codeblock_inclusion == PDC_false){
						fprintf(file,"Codeblock not inclusion pos_x = %5lu pos_y = %5lu \n", pos_x, pos_y );
					}else{
						fprintf(file,"Codeblock inclusion  pos_x = %5lu pos_y = %5lu \n", pos_x, pos_y );
					}

					codeblock = subband->codeblocks[pos_codeblock];
					if(codeblock->layer_inclusion == PDC_true){
						fprintf(file,"	Layer inclusion\n");
						fprintf(file,"	codeblock->zero_bitplanes 				= %5u \n",codeblock->zero_bitplanes);
						fprintf(file,"	codeblock->number_of_codingpasses 		= %5lu \n", codeblock->number_of_codingpasses);
						fprintf(file,"	codeblock->number_of_codeword_segment 	= %5lu \n", codeblock->number_of_codeword_segment);
						fprintf(file,"	codeblock->Lblock 						= %5lu \n", codeblock->Lblock);
						fprintf(file,"	codeblock->codewordlength				= %5lu \n", codeblock->codewordlength);
					}else{
						fprintf(file,"	Layer not inclusion\n");
					}

				}
			}
		}



	}else{
		fprintf(file,"Precinct not inclusion \n" );
	}

	fprintf(file,"\n\n" );
}


/*
 *
 */
PDC_Precinct* PDC_Precinct_read_package_header_02(	PDC_Exception* exception,
													PDC_Precinct* precinct,
													PDC_Buffer*	buffer,
													PDC_uint layer_pos,
													PDC_uint layer_max,
													PDC_Decoder* decoder)
{
	PDC_bit				bit;
	PDC_uint			pos_subband, size_subband, pos_codeblock, pos_codeblock_x, pos_codeblock_y, size_codeblock_x, size_codeblock_y;
	PDC_uint			pos_x, pos_y, size_x;
	PDC_Subband*		subband;
	PDC_Codeblock*		codeblock;
	PDC_uint			number_of_codingpasses, number_of_codeword_segment, codeword_segment_pos;
	PDC_Codeword_List*	codeword_list;
	PDC_uint			num_bits, codewordlength, codewordslength_total;
	PDC_bool			layer_inclusion;
	PDC_bool			new_job;
	PDC_Worker			*worker;

	codewordslength_total = 0;
	worker	= precinct->resolution->tile_component->tile->worker;

	PDC_Buffer_push_state(exception, buffer);
	PDC_Precinct_push(exception, precinct);


	if(precinct->resolution->r == 0){
		size_subband = 1;
	}else{
		size_subband = 3;
	}


	bit = PDC_Buffer_get_next_bit(exception, buffer);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		PDC_Buffer_pop_state(exception, buffer);
		PDC_Precinct_pop(exception, precinct);

		if(buffer->end_state == END_OF_BUFFER){
			PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
			decoder->data_situation = PDC_WAIT_FOR_DATA;
			return precinct;
		}else{
			PDC_Exception_unset_exception(exception);
			decoder->data_situation = PDC_WAIT_FOR_DATA;
			return precinct;
		}
		return precinct;
	}
	precinct->bit1 = bit;
	if(bit == 1){
		for(pos_subband = 0; pos_subband < size_subband; pos_subband += 1){
			subband = precinct->resolution->subband[pos_subband];
			pos_codeblock = 0;
			size_codeblock_x = precinct->codeblock_x1;
			size_codeblock_y = precinct->codeblock_y1;
			for(pos_codeblock_y = precinct->codeblock_y0; pos_codeblock_y < size_codeblock_y; pos_codeblock_y += 1){
				for(pos_codeblock_x = precinct->codeblock_x0; pos_codeblock_x < size_codeblock_x; pos_codeblock_x += 1){
					pos_x	= pos_codeblock_x - precinct->codeblock_x0;
					pos_y	= pos_codeblock_y - precinct->codeblock_y0;
					size_x	= precinct->codeblock_x1 - precinct->codeblock_x0;
					pos_codeblock = PDC_Resolution_get_codeblock_position(exception, precinct->resolution, pos_codeblock_x, pos_codeblock_y);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						PDC_Buffer_pop_state(exception, buffer);
						PDC_Precinct_pop(exception, precinct);
						if(buffer->end_state == END_OF_BUFFER){
							PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
							decoder->data_situation = PDC_WAIT_FOR_DATA;
							return precinct;
						}else{
							PDC_Exception_unset_exception(exception);
							decoder->data_situation = PDC_WAIT_FOR_DATA;
							return precinct;
						}
						return precinct;
					}
					codeblock = subband->codeblocks[pos_codeblock];
					codeblock = PDC_Worker_get_Codeblock_by_pointer(exception,
																	worker,
																	codeblock);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						PDC_Buffer_pop_state(exception, buffer);
						PDC_Precinct_pop(exception, precinct);
						PDC_Codeblock_unlock(exception, codeblock);
						return precinct;
					}

					layer_inclusion = PDC_false;
					if(codeblock->codeblock_inclusion == PDC_false){
						codeblock->codeblock_inclusion = PDC_Tagtree_decode_pos(exception,
																				precinct->codeblock_inclusion[pos_subband],
																				buffer,
																				pos_x,
																				pos_y,
																				layer_pos + 1);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							PDC_Buffer_pop_state(exception, buffer);
							PDC_Precinct_pop_unlock(exception, precinct);
							if(buffer->end_state == END_OF_BUFFER){
								PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
								decoder->data_situation = PDC_WAIT_FOR_DATA;
								PDC_Codeblock_unlock(exception, codeblock);
								return precinct;
							}else{
								PDC_Exception_unset_exception(exception);
								decoder->data_situation = PDC_WAIT_FOR_DATA;
								PDC_Codeblock_unlock(exception, codeblock);
								return precinct;
							}
						}
						if(codeblock->codeblock_inclusion == PDC_true){
							layer_inclusion = PDC_true;
						}

					}else{
						bit = PDC_Buffer_get_next_bit(exception, buffer);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							PDC_Buffer_pop_state(exception, buffer);
							PDC_Precinct_pop_unlock(exception, precinct);
							if(buffer->end_state == END_OF_BUFFER){
								PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
								decoder->data_situation = PDC_WAIT_FOR_DATA;
								PDC_Codeblock_unlock(exception, codeblock);
								return precinct;
							}else{
								PDC_Exception_unset_exception(exception);
								decoder->data_situation = PDC_WAIT_FOR_DATA;
								PDC_Codeblock_unlock(exception, codeblock);
								return precinct;
							}
						}

						if(bit != 0){
							layer_inclusion = PDC_true;
						}

					}

					codeblock->layer_inclusion = layer_inclusion;

					if(layer_inclusion == PDC_true){
						if(codeblock->zero_bit_plane_inclusion	!= PDC_true){
							codeblock->zero_bit_plane_inclusion = PDC_Tagtree_decode_pos(	exception,
																							precinct->zero_bitplane[pos_subband],
																							buffer,
																							pos_x,
																							pos_y,
																							MAX_INT);
							if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
								PDC_Buffer_pop_state(exception, buffer);
								PDC_Precinct_pop_unlock(exception, precinct);
								if(buffer->end_state == END_OF_BUFFER){
									PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
									decoder->data_situation = PDC_WAIT_FOR_DATA;
									PDC_Codeblock_unlock(exception, codeblock);
									return precinct;
								}else{
									PDC_Exception_unset_exception(exception);
									decoder->data_situation = PDC_WAIT_FOR_DATA;
									PDC_Codeblock_unlock(exception, codeblock);
									return precinct;
								}
								return precinct;
							}
							codeblock->zero_bit_plane_inclusion	= PDC_true;
							codeblock->zero_bitplanes			= PDC_Tagtree_get_value(	exception,
																							precinct->zero_bitplane[pos_subband],
																							pos_x,
																							pos_y);
							if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
								PDC_Buffer_pop_state(exception, buffer);
								PDC_Precinct_pop_unlock(exception, precinct);
								if(buffer->end_state == END_OF_BUFFER){
									PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
									decoder->data_situation = PDC_WAIT_FOR_DATA;
									PDC_Codeblock_unlock(exception, codeblock);
									return precinct;
								}else{
									PDC_Exception_unset_exception(exception);
									decoder->data_situation = PDC_WAIT_FOR_DATA;
									PDC_Codeblock_unlock(exception, codeblock);
									return precinct;
								}
							}
						}
						number_of_codingpasses = PDC_Buffer_get_number_of_codingpasses(exception, buffer);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							PDC_Buffer_pop_state(exception, buffer);
							PDC_Precinct_pop_unlock(exception, precinct);
							if(buffer->end_state == END_OF_BUFFER){
								PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
								decoder->data_situation = PDC_WAIT_FOR_DATA;
								PDC_Codeblock_unlock(exception, codeblock);
								return precinct;
							}else{
								PDC_Exception_unset_exception(exception);
								decoder->data_situation = PDC_WAIT_FOR_DATA;
								PDC_Codeblock_unlock(exception, codeblock);
								return precinct;
							}
						}

						number_of_codeword_segment = PDC_Codeblock_set_number_of_coding_passes(	exception,
																								codeblock,
																								number_of_codingpasses,
																								layer_pos);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							PDC_Buffer_pop_state(exception, buffer);
							PDC_Precinct_pop_unlock(exception, precinct);
							if(buffer->end_state == END_OF_BUFFER){
								PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
								decoder->data_situation = PDC_WAIT_FOR_DATA;
								PDC_Codeblock_unlock(exception, codeblock);
								return precinct;
							}else{
								PDC_Exception_unset_exception(exception);
								decoder->data_situation = PDC_WAIT_FOR_DATA;
								PDC_Codeblock_unlock(exception, codeblock);
								return precinct;
							}
							
						}
						codeblock->number_of_codingpasses		= number_of_codingpasses;
						codeblock->number_of_codeword_segment	= number_of_codeword_segment;


						codeblock->Lblock += PDC_Buffer_get_Lblock_increase(	exception,
																				buffer);
						if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
							PDC_Buffer_pop_state(exception, buffer);
							PDC_Precinct_pop_unlock(exception, precinct);
							if(buffer->end_state == END_OF_BUFFER){
								PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
								decoder->data_situation = PDC_WAIT_FOR_DATA;
								PDC_Codeblock_unlock(exception, codeblock);
								return precinct;
							}else{
								PDC_Exception_unset_exception(exception);
								decoder->data_situation = PDC_WAIT_FOR_DATA;
								PDC_Codeblock_unlock(exception, codeblock);
								return precinct;
							}
						}
						for(codeword_segment_pos = 0; codeword_segment_pos < number_of_codeword_segment; codeword_segment_pos++){
							codeword_list = codeblock->write_codeword;
							number_of_codingpasses = codeword_list->number_of_coding_passes;
							num_bits = PDC_floor_log2( number_of_codingpasses);

							num_bits += codeblock->Lblock;
							codewordlength = PDC_Buffer_read_bits(	exception,
																	buffer,
																	num_bits);
							if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
								PDC_Buffer_pop_state(exception, buffer);
								PDC_Precinct_pop_unlock(exception, precinct);
								if(buffer->end_state == END_OF_BUFFER){
									PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
									decoder->data_situation = PDC_WAIT_FOR_DATA;
									PDC_Codeblock_unlock(exception, codeblock);
									return precinct;
								}else{
									PDC_Exception_unset_exception(exception);
									decoder->data_situation = PDC_WAIT_FOR_DATA;
									PDC_Codeblock_unlock(exception, codeblock);
									return precinct;
								}
							}

							codewordslength_total += codewordlength;
							codeblock->codewordlength = codewordlength;
							codeword_list->number_of_byte = codewordlength;
							if(codeword_list->next_codedword != NULL){
								codeword_list = codeword_list->next_codedword;
							}
						}
					}
				}
			}
		}

		PDC_Buffer_padding_read(exception, buffer);
		/* Start reading codewordsegments. */

		if(buffer->read_byte_pos + codewordslength_total > buffer->write_byte_pos){
			PDC_Buffer_pop_state(exception, buffer);
			PDC_Precinct_pop_unlock(exception, precinct);
			decoder->data_situation = PDC_WAIT_FOR_DATA;
			PDC_Codeblock_unlock(exception, codeblock);
			return precinct;
		}

		for(pos_subband = 0; pos_subband < size_subband; pos_subband += 1){
			subband = precinct->resolution->subband[pos_subband];
			for(pos_codeblock_y = precinct->codeblock_y0; pos_codeblock_y < size_codeblock_y; pos_codeblock_y += 1){
				for(pos_codeblock_x = precinct->codeblock_x0; pos_codeblock_x < size_codeblock_x; pos_codeblock_x += 1){
					pos_x	= pos_codeblock_x - precinct->codeblock_x0;
					pos_y	= pos_codeblock_y - precinct->codeblock_y0;
					size_x	= precinct->codeblock_x1 - precinct->codeblock_x0;
					pos_codeblock = PDC_Resolution_get_codeblock_position(exception, precinct->resolution, pos_codeblock_x, pos_codeblock_y);
					if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
						PDC_Buffer_pop_state(exception, buffer);
						PDC_Precinct_pop_unlock(exception, precinct);
						if(buffer->end_state == END_OF_BUFFER){
							PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
							decoder->data_situation = PDC_WAIT_FOR_DATA;
							PDC_Codeblock_unlock(exception, codeblock);
							return precinct;
						}else{
							PDC_Exception_unset_exception(exception);
							decoder->data_situation = PDC_WAIT_FOR_DATA;
							PDC_Codeblock_unlock(exception, codeblock);
							return precinct;
						}
					}
					codeblock = subband->codeblocks[pos_codeblock];
					new_job = PDC_false;
					if(codeblock->layer_inclusion == PDC_true){
						codeword_list = codeblock->write_codeword;
						new_job = PDC_true;

						while(codeword_list != NULL){
							if(codeword_list->number_of_byte != 0){
								PDC_Buffer_copy_bytes_01(	exception,
															buffer,
															codeword_list->codeword,
															codeword_list->number_of_byte);
								codeword_list->number_of_byte = 0;
								if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
									PDC_Buffer_pop_state(exception, buffer);
									PDC_Precinct_pop_unlock(exception, precinct);
									if(buffer->end_state == END_OF_BUFFER){
										PDC_Exception_error(exception, exception, PDC_EXCEPTION_NO_CODE_FOUND, __LINE__, __FILE__);
										decoder->data_situation = PDC_WAIT_FOR_DATA;
										PDC_Codeblock_unlock(exception, codeblock);
										return precinct;
									}else{
										PDC_Exception_unset_exception(exception);
										decoder->data_situation = PDC_WAIT_FOR_DATA;
										PDC_Codeblock_unlock(exception, codeblock);
										return precinct;
									}
									if(layer_pos == layer_max){
										codeword_list->codeword->end_state = END_OF_BUFFER;
									}
									return precinct;
								}
							}
							codeword_list = codeword_list->next_codedword;
						}
						PDC_Worker_add_02(	exception,
											worker,
											codeblock,
											new_job);
					}else{
						if(layer_pos == layer_max){
							codeword_list = codeblock->write_codeword;
							
							while(codeword_list != NULL){
								codeword_list->codeword->end_state = END_OF_BUFFER;
								codeword_list = codeword_list->next_codedword;
							}

							PDC_Worker_add_02(	exception,
												worker,
												codeblock,
												new_job);
						}
						PDC_Codeblock_unlock(exception, codeblock);
					}
				}
			}
		}
	}
	//PDC_Precinct_print(exception, DEBUG_FILE, precinct, layer_pos);

	return precinct;
}

/*
 *
 */
PDC_Precinct* PDC_Precinct_decode_package_01(	PDC_Exception *exception,
												PDC_Precinct *precinct,
												PDC_uint layer_pos)
{
	PDC_uint		pos_subband, size_subband, pos_codeblock, pos_codeblock_x, pos_codeblock_y, size_codeblock_x, size_codeblock_y;
	PDC_uint		pos_x, pos_y, size_x;
	PDC_Subband*	subband;
	PDC_Codeblock*	codeblock;

	if(precinct->resolution->r == 0){
		size_subband = 1;
	}else{
		size_subband = 3;
	}

	for(pos_subband = 0; pos_subband < size_subband; pos_subband += 1){
		subband = precinct->resolution->subband[pos_subband];
		pos_codeblock = 0;
		size_codeblock_x = precinct->codeblock_x1;
		size_codeblock_y = precinct->codeblock_y1;
		for(pos_codeblock_y = precinct->codeblock_y0; pos_codeblock_y < size_codeblock_y; pos_codeblock_y += 1){
			for(pos_codeblock_x = precinct->codeblock_x0; pos_codeblock_x < size_codeblock_x; pos_codeblock_x += 1){
				pos_x	= pos_codeblock_x - precinct->codeblock_x0;
				pos_y	= pos_codeblock_y - precinct->codeblock_y0;
				size_x	= precinct->codeblock_x1 - precinct->codeblock_x0;
				pos_codeblock = PDC_Resolution_get_codeblock_position(exception, precinct->resolution, pos_codeblock_x, pos_codeblock_y);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return precinct;
				}
				codeblock = subband->codeblocks[pos_codeblock];

				codeblock = PDC_Codeblock_coefficient_bit_moddeling_decode(	exception,
																			codeblock,
																			layer_pos);

				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return precinct;
				}
			}
		}
	}
	return precinct;
}

/*
 *
 */
PDC_Precinct* PDC_Precinct_decode_package_02(	PDC_Exception *exception,
												PDC_Precinct *precinct)
{
	PDC_uint		pos_subband, size_subband, pos_codeblock, pos_codeblock_x, pos_codeblock_y, size_codeblock_x, size_codeblock_y;
	PDC_uint		pos_x, pos_y, size_x;
	PDC_Subband*	subband;
	PDC_Codeblock*	codeblock;

	PDC_size_t		write_byte_pos; // write_byte_pos1;

	if(precinct->resolution->r == 0){
		size_subband = 1;
	}else{
		size_subband = 3;
	}

	for(pos_subband = 0; pos_subband < size_subband; pos_subband += 1){
		subband = precinct->resolution->subband[pos_subband];
		pos_codeblock = 0;
		size_codeblock_x = precinct->codeblock_x1;
		size_codeblock_y = precinct->codeblock_y1;
		for(pos_codeblock_y = precinct->codeblock_y0; pos_codeblock_y < size_codeblock_y; pos_codeblock_y += 1){
			for(pos_codeblock_x = precinct->codeblock_x0; pos_codeblock_x < size_codeblock_x; pos_codeblock_x += 1){
				pos_x	= pos_codeblock_x - precinct->codeblock_x0;
				pos_y	= pos_codeblock_y - precinct->codeblock_y0;
				size_x	= precinct->codeblock_x1 - precinct->codeblock_x0;
				pos_codeblock = PDC_Resolution_get_codeblock_position(exception, precinct->resolution, pos_codeblock_x, pos_codeblock_y);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return precinct;
				}
				codeblock = subband->codeblocks[pos_codeblock];

				write_byte_pos = codeblock->write_codeword->codeword->write_byte_pos;

				codeblock = PDC_Codeblock_coefficient_bit_moddeling_decode_01(	exception,
																				codeblock);
				/*
				for(write_byte_pos1 = 0; write_byte_pos1 <= write_byte_pos; write_byte_pos1 += 1){


					codeblock->write_codeword->codeword->write_byte_pos	= write_byte_pos1;
					codeblock->write_codeword->codeword->end_state		= MORE_DATA_EXPECTED;
					if(write_byte_pos1 == write_byte_pos){
						codeblock->write_codeword->codeword->end_state = END_OF_BUFFER;
					}

					codeblock = PDC_Codeblock_coefficient_bit_moddeling_decode_01(	exception,
																					codeblock);

				}
				*/

				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return precinct;
				}
			}
		}
	}
	return precinct;
}


/*
 *
 */
PDC_Precinct* PDC_Precinct_set_End_of_Buffer(	PDC_Exception *exception,
												PDC_Precinct *precinct)
{
	PDC_uint		pos_subband, size_subband, pos_codeblock, pos_codeblock_x, pos_codeblock_y, size_codeblock_x, size_codeblock_y;
	PDC_uint		pos_x, pos_y, size_x;
	PDC_Subband*	subband;
	PDC_Codeblock*	codeblock;

	if(precinct->resolution->r == 0){
		size_subband = 1;
	}else{
		size_subband = 3;
	}

	for(pos_subband = 0; pos_subband < size_subband; pos_subband += 1){
		subband = precinct->resolution->subband[pos_subband];
		pos_codeblock = 0;
		size_codeblock_x = precinct->codeblock_x1;
		size_codeblock_y = precinct->codeblock_y1;
		for(pos_codeblock_y = precinct->codeblock_y0; pos_codeblock_y < size_codeblock_y; pos_codeblock_y += 1){
			for(pos_codeblock_x = precinct->codeblock_x0; pos_codeblock_x < size_codeblock_x; pos_codeblock_x += 1){
				pos_x	= pos_codeblock_x - precinct->codeblock_x0;
				pos_y	= pos_codeblock_y - precinct->codeblock_y0;
				size_x	= precinct->codeblock_x1 - precinct->codeblock_x0;
				pos_codeblock = PDC_Resolution_get_codeblock_position(exception, precinct->resolution, pos_codeblock_x, pos_codeblock_y);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return precinct;
				}
				codeblock = subband->codeblocks[pos_codeblock];

				codeblock = PDC_Codeblock_set_End_of_Buffer(	exception, codeblock);
				if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
					return precinct;
				}
			}
		}
	}
	return precinct;
}

/*
 *
 */
PDC_Precinct* PDC_Precinct_push(PDC_Exception* exception,
								PDC_Precinct* precinct)
{
	PDC_uint			pos_subband, size_subband, pos_codeblock, pos_codeblock_x, pos_codeblock_y, size_codeblock_x, size_codeblock_y;
//	PDC_uint			pos_x, pos_y, size_x;
	PDC_Subband*		subband;

	PDC_Codeblock*		codeblock;

	if(precinct->resolution->r == 0){
		size_subband = 1;
	}else{
		size_subband = 3;
	}

	for(pos_subband = 0; pos_subband < size_subband; pos_subband += 1){
		subband = precinct->resolution->subband[pos_subband];
		pos_codeblock = 0;
		size_codeblock_x = precinct->codeblock_x1;
		size_codeblock_y = precinct->codeblock_y1;
		for(pos_codeblock_y = precinct->codeblock_y0; pos_codeblock_y < size_codeblock_y; pos_codeblock_y += 1){
			for(pos_codeblock_x = precinct->codeblock_x0; pos_codeblock_x < size_codeblock_x; pos_codeblock_x += 1){
				// pos_x	= pos_codeblock_x - precinct->codeblock_x0;
				// pos_y	= pos_codeblock_y - precinct->codeblock_y0;
				// size_x	= precinct->codeblock_x1 - precinct->codeblock_x0;
				pos_codeblock = PDC_Resolution_get_codeblock_position(exception, precinct->resolution, pos_codeblock_x, pos_codeblock_y);
				codeblock = subband->codeblocks[pos_codeblock];
				PDC_Codeblock_push(exception, codeblock);
			}
		}
	}

	PDC_Tagtree_push(exception, precinct->codeblock_inclusion[0]);
	PDC_Tagtree_push(exception, precinct->codeblock_inclusion[1]);
	PDC_Tagtree_push(exception, precinct->codeblock_inclusion[2]);
	PDC_Tagtree_push(exception, precinct->zero_bitplane[0]);
	PDC_Tagtree_push(exception, precinct->zero_bitplane[1]);
	PDC_Tagtree_push(exception, precinct->zero_bitplane[2]);


	return precinct;
}

/*
 *
 */
PDC_Precinct* PDC_Precinct_pop(PDC_Exception* exception,
								PDC_Precinct* precinct)
{
	PDC_uint			pos_subband, size_subband, pos_codeblock, pos_codeblock_x, pos_codeblock_y, size_codeblock_x, size_codeblock_y;
//	PDC_uint			pos_x, pos_y, size_x;
	PDC_Subband*		subband;

	PDC_Codeblock*		codeblock;

	if(precinct->resolution->r == 0){
		size_subband = 1;
	}else{
		size_subband = 3;
	}

	for(pos_subband = 0; pos_subband < size_subband; pos_subband += 1){
		subband = precinct->resolution->subband[pos_subband];
		pos_codeblock = 0;
		size_codeblock_x = precinct->codeblock_x1;
		size_codeblock_y = precinct->codeblock_y1;
		for(pos_codeblock_y = precinct->codeblock_y0; pos_codeblock_y < size_codeblock_y; pos_codeblock_y += 1){
			for(pos_codeblock_x = precinct->codeblock_x0; pos_codeblock_x < size_codeblock_x; pos_codeblock_x += 1){
				// pos_x	= pos_codeblock_x - precinct->codeblock_x0;
				// pos_y	= pos_codeblock_y - precinct->codeblock_y0;
				// size_x	= precinct->codeblock_x1 - precinct->codeblock_x0;
				pos_codeblock = PDC_Resolution_get_codeblock_position(exception, precinct->resolution, pos_codeblock_x, pos_codeblock_y);
				codeblock = subband->codeblocks[pos_codeblock];
				PDC_Codeblock_pop(exception, codeblock);
			}
		}
	}


	PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
	PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
	PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
	PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
	PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
	PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);

	return precinct;
}

/*
 *
 */
PDC_Precinct* PDC_Precinct_pop_unlock(	PDC_Exception* exception,
										PDC_Precinct* precinct)
{
	PDC_uint			pos_subband, size_subband, pos_codeblock, pos_codeblock_x, pos_codeblock_y, size_codeblock_x, size_codeblock_y;
//	PDC_uint			pos_x, pos_y, size_x;
	PDC_Subband			*subband;

	PDC_Codeblock		*codeblock;
	PDC_Worker			*worker = precinct->resolution->tile_component->tile->worker;
	if(precinct->resolution->r == 0){
		size_subband = 1;
	}else{
		size_subband = 3;
	}

	for(pos_subband = 0; pos_subband < size_subband; pos_subband += 1){
		subband = precinct->resolution->subband[pos_subband];
		pos_codeblock = 0;
		size_codeblock_x = precinct->codeblock_x1;
		size_codeblock_y = precinct->codeblock_y1;
		for(pos_codeblock_y = precinct->codeblock_y0; pos_codeblock_y < size_codeblock_y; pos_codeblock_y += 1){
			for(pos_codeblock_x = precinct->codeblock_x0; pos_codeblock_x < size_codeblock_x; pos_codeblock_x += 1){
				// pos_x	= pos_codeblock_x - precinct->codeblock_x0;
				// pos_y	= pos_codeblock_y - precinct->codeblock_y0;
				// size_x	= precinct->codeblock_x1 - precinct->codeblock_x0;
				pos_codeblock = PDC_Resolution_get_codeblock_position(exception, precinct->resolution, pos_codeblock_x, pos_codeblock_y);
				codeblock = subband->codeblocks[pos_codeblock];
				PDC_Codeblock_pop(exception, codeblock);
				PDC_Worker_add_02(	exception,
									worker,
									codeblock,
									PDC_false);
			}
		}
	}


	PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[0]);
	PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[1]);
	PDC_Tagtree_pop(exception, precinct->codeblock_inclusion[2]);
	PDC_Tagtree_pop(exception, precinct->zero_bitplane[0]);
	PDC_Tagtree_pop(exception, precinct->zero_bitplane[1]);
	PDC_Tagtree_pop(exception, precinct->zero_bitplane[2]);

	return precinct;
}

void PDC_Precinct_print_codeblock_01(PDC_Exception* exception, PDC_Precinct* precinct, FILE *file, int component, int resolution, int n, int m)
{
	PDC_uint			pos_subband, size_subband, pos_codeblock, pos_codeblock_x, pos_codeblock_y, size_codeblock_x, size_codeblock_y;
//	PDC_uint			pos_x, pos_y, size_x;
	PDC_Subband			*subband;

	PDC_Codeblock		*codeblock;
	if(precinct->resolution->r == 0){
		size_subband = 1;
	}else{
		size_subband = 3;
	}

	for(pos_subband = 0; pos_subband < size_subband; pos_subband += 1){
		subband = precinct->resolution->subband[pos_subband];
		pos_codeblock = 0;
		size_codeblock_x = precinct->codeblock_x1;
		size_codeblock_y = precinct->codeblock_y1;
		for(pos_codeblock_y = precinct->codeblock_y0; pos_codeblock_y < size_codeblock_y; pos_codeblock_y += 1){
			for(pos_codeblock_x = precinct->codeblock_x0; pos_codeblock_x < size_codeblock_x; pos_codeblock_x += 1){
				// pos_x	= pos_codeblock_x - precinct->codeblock_x0;
				// pos_y	= pos_codeblock_y - precinct->codeblock_y0;
				// size_x	= precinct->codeblock_x1 - precinct->codeblock_x0;
				pos_codeblock = PDC_Resolution_get_codeblock_position(exception, precinct->resolution, pos_codeblock_x, pos_codeblock_y);
				codeblock = subband->codeblocks[pos_codeblock];
				print_codeblock_02(codeblock,file, component, resolution, n, m);
			}
		}
	}

}
STOP_C

