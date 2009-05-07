/*
 * Copyright (C) 2008  Uwe Br�nen
 *      Contact Email:
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

#ifndef __PDC_PARAMETER_H__
#define __PDC_PARAMETER_H__

#include <inttypes.h>


#ifdef __cplusplus
	#define START_C extern "C" {
	#define STOP_C }
#else
	#define START_C
	#define STOP_C
#endif

#if defined(PDC_IMPORT)
	#if defined(_MSC_VER)
		#include <windows.h>
		#define DLL extern "C" __declspec(dllimport)
	#else
		#define DLL
	#endif
#else
	#if defined(_MSC_VER)
		#include <windows.h>
		#define DLL __declspec(dllexport)
	#else
		#define DLL
	#endif
#endif


START_C

#define MAX_INT 0x7FFFFFFF

	typedef enum{PDC_true = 1, PDC_false = 0}PDC_bool;
	typedef unsigned char		PDC_uchar;
	typedef unsigned long		PDC_uint;
	typedef uint32_t			PDC_uint32;
	typedef uint8_t				PDC_decision;
	typedef uint8_t				PDC_context;
	typedef int				PDC_int;
	typedef uint16_t			PDC_uint16;
	typedef uint8_t				PDC_uint8;
	typedef float				PDC_float32;
	typedef uint8_t				PDC_bit;

	typedef unsigned long POINTER;


	PDC_int PDC_i_ceiling( PDC_int , PDC_int);
	PDC_int PDC_i_floor( PDC_int , PDC_int);

	PDC_uint PDC_ui_ceiling( PDC_uint , PDC_uint);
	PDC_uint PDC_ui_floor( PDC_uint , PDC_uint);

	PDC_int PDC_f_ceiling(PDC_float32);
	PDC_int	PDF_f_floor(PDC_float32);

	PDC_uint32 max_uint32(PDC_uint32 in1, PDC_uint32 in2);
	PDC_uint32 min_uint32(PDC_uint32 in1, PDC_uint32 in2);

	PDC_uint max_uint(PDC_uint in1, PDC_uint in2);
	PDC_uint min_uint(PDC_uint in1, PDC_uint in2);


	PDC_int min_int(PDC_int in1, PDC_int in2);

	PDC_uint PDC_floor_log2( PDC_uint in);

STOP_C

#endif
