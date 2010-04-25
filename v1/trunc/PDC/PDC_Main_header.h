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

#ifndef __PDC_MAIN_HEADER_H__
#define __PDC_MAIN_HEADER_H__

#include <stdlib.h>
#include "PDC_Parameter.h"

START_C

	struct str_PDC_Main_header;
	typedef struct str_PDC_Main_header PDC_Main_header;


	struct str_PDC_Main_header{
		PDC_bool		SOC_read;
		PDC_bool		SIZ_read;
		PDC_bool		COD_read;
		PDC_bool		COC_read;
		PDC_bool		QCD_read;
		PDC_bool		QCC_read;
		PDC_bool		RGN_read;
		PDC_bool		POC_read;
		PDC_bool		PPM_read;
		PDC_bool		TLM_read;
		PDC_bool		PLM_read;
		PDC_bool		CRG_read;
		PDC_bool		COM_read;
	};

	

STOP_C
#endif
