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

#ifndef __PDC_ARITHMETIC_ENTROPY_ENCODER_H__
#define __PDC_ARITHMETIC_ENTROPY_ENCODER_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C

	struct str_PDC_Arithmetic_entropy_encoder;
	typedef struct str_PDC_Arithmetic_entropy_encoder PDC_Arithmetic_entropy_encoder;

	#include "PDC_Parameter.h"
	#include "PDC_Exception.h"

	struct str_PDC_Arithmetic_entropy_encoder{
		PDC_uint_32	c_register;
		PDC_uint_32	a_register;

	};

STOP_C

#endif