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


#ifndef PDC_WORKER_H_
#define PDC_WORKER_H_

#include <stdlib.h>
#include <pthread.h>
#include "PDC_Parameter.h"

START_C

struct str_PDC_Worker;
typedef struct str_PDC_Worker PDC_Worker;

struct str_PDC_Codeblock_list;
typedef struct str_PDC_Codeblock_list PDC_Codeblock_list;

struct str_PDC_Worker_thread;
typedef struct str_PDC_Worker_thread PDC_Worker_thread;

#include "PDC_Codeblock.h"
#include "PDC_Exception.h"

struct str_PDC_Worker{
	pthread_mutex_t		*worker_mutex;
	pthread_cond_t		*worker_wait;
	PDC_Codeblock_list	*all_codeblock;
	PDC_Codeblock_list	*open_work;
};

struct str_PDC_Codeblock_list{
	PDC_Codeblock *this;
	PDC_Codeblock_list *next;
	PDC_Codeblock_list *last;
};

struct str_PDC_Worker_thread{
	PDC_Exception 	*exception;
	PDC_Worker		*worker;
	PDC_uint		end;
};

/*
 *
 */
PDC_Worker* new_PDC_Worker_01(PDC_Exception *exception);

/*
 *
 */
void delete_PDC_Worker(PDC_Exception *exception, PDC_Worker *worker);

/*
 * Add PDC_Codeblock_list to all_codeblock
 */
void PDC_Worker_add_01(PDC_Exception *exception, PDC_Worker *worker, PDC_Codeblock_list *codeblock_list);


/*
 * Add codeblock to open_work list when new_job == PDC_true or
 * codeblock->has_job == PDC_true.
 */
void PDC_Worker_add_02(	PDC_Exception *exception,
						PDC_Worker *worker,
						PDC_Codeblock *codeblock,
						PDC_bool new_job);

/*
 *
 */
PDC_Codeblock *PDC_Worker_get_Codeblock_by_pointer(	PDC_Exception *exception,
													PDC_Worker *worker,
													PDC_Codeblock *codeblock);

/*
 *
 */
PDC_Codeblock_list *new_PDC_Codeblock_list_01(PDC_Exception *exception);

/*
 *
 */
PDC_Codeblock_list *new_PDC_Codeblock_list_02(PDC_Exception *exception, PDC_Codeblock *codeblock);

/*
 *
 */
void delete_PDC_Codeblock_list(PDC_Exception *exception, PDC_Codeblock_list *codeblock_list);


/*
 *
 */
PDC_Worker_thread *new_PDC_Worker_thread_01(	PDC_Exception *exception,
												PDC_Worker *worker);

/*
 *
 */
void delete_PDC_Worker_thread(	PDC_Exception *exception,
								PDC_Worker_thread *worker_thread);
/*
 *
 */
void start_worker_01(void *in_info);

STOP_C
#endif /* PDC_WORKER_H_ */
