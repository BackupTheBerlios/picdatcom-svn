/*
 * Copyright (C) 2008  Uwe Brünen
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

	
	typedef enum{PDC_true = 1, PDC_false = 0}PDC_bool;
	typedef unsigned char	PDC_uchar;
	typedef unsigned int	PDC_uint;
	typedef unsigned int	PDC_uint32;
	typedef unsigned char	PDC_decision;
	typedef unsigned char	PDC_context;
	typedef int				PDC_int;
	typedef unsigned short	PDC_uint16;
	typedef unsigned char	PDC_uint8;
	typedef float			PDC_float32;

	PDC_int PDC_i_ceiling( PDC_int , PDC_int);
	PDC_int PDC_i_floor( PDC_int , PDC_int);

	PDC_int PDC_f_ceiling(PDC_float32);
	PDC_int	PDF_f_floor(PDC_float32);

	PDC_uint32 max_uint32(PDC_uint32 in1, PDC_uint32 in2);
	PDC_uint32 min_uint32(PDC_uint32 in1, PDC_uint32 in2);

	PDC_int min_int(PDC_int in1, PDC_int in2);

STOP_C

#endif