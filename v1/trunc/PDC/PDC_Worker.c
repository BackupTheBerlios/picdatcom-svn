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

#include "PDC_Worker.h"

START_C
/*
 *
 */
PDC_Worker* new_PDC_Worker_01(PDC_Exception *exception)
{
	PDC_Worker *worker = NULL;
	PDC_int pos_thread;
	PDC_int max_threads = PDC_max_thread();

	worker = malloc(sizeof(PDC_Worker));
	if(worker == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	worker->all_codeblock	= NULL;
	worker->open_work		= NULL;
	worker->worker_mutex	= NULL;
	worker->worker_wait		= NULL;
	worker->threads			= NULL;
	worker->state			= MORE_CODEBLOCKS_EXCPECTED;

	worker->worker_mutex = malloc(sizeof(pthread_mutex_t));
	if(worker->worker_mutex == NULL){
		delete_PDC_Worker(exception, worker);
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	pthread_mutex_init(worker->worker_mutex, NULL);

	worker->worker_wait = malloc(sizeof(pthread_cond_t));
	if(worker->worker_wait == NULL){
		delete_PDC_Worker(exception, worker);
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	pthread_cond_init(worker->worker_wait, NULL);

	/*
	 * Generate the threads here.
	 */
	worker->threads = (PDC_Worker_thread**)malloc(sizeof(PDC_Worker_thread*) * max_threads);
	if(worker->threads == NULL){
		delete_PDC_Worker(exception, worker);
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	for(pos_thread = 0; pos_thread < max_threads; pos_thread += 1){
		worker->threads[pos_thread] = NULL;
	}

	for(pos_thread = 0; pos_thread < max_threads; pos_thread += 1){
		worker->threads[pos_thread] = new_PDC_Worker_thread_01(exception, worker);
		if(worker->threads == NULL){
			delete_PDC_Worker(exception, worker);
			PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
			return NULL;
		}
	}

	return worker;
}


/*
 *
 */
void delete_PDC_Worker(PDC_Exception *exception, PDC_Worker* worker)
{
	PDC_int pos_thread;
	PDC_int max_threads = PDC_max_thread();

	if(worker != NULL){
		if(worker->worker_mutex != NULL){
			pthread_mutex_destroy(worker->worker_mutex);
			free(worker->worker_mutex);
			worker->worker_mutex = NULL;
		}

		if(worker->worker_wait != NULL){
			pthread_cond_destroy(worker->worker_wait);
			free(worker->worker_wait);
			worker->worker_wait = NULL;
		}

		if(worker->threads != NULL){
			for(pos_thread = 0; pos_thread < max_threads; pos_thread += 1){
				if(worker->threads[pos_thread] != NULL){
					delete_PDC_Worker_thread(exception, worker->threads[pos_thread]);
				}
			}
		}

		worker->all_codeblock	= NULL;
		worker->open_work		= NULL;

		free(worker);
	}
}

/*
 * Add PDC_Codeblock_list to all_codeblock
 */
void PDC_Worker_add_01(	PDC_Exception *exception,
						PDC_Worker *worker,
						PDC_Codeblock_list *codeblock_list)
{
	PDC_Codeblock_list *codeblock_list_work;
	pthread_mutex_lock(worker->worker_mutex);
	if(worker->all_codeblock == NULL){
		worker->all_codeblock = codeblock_list;
	}else{
		codeblock_list_work = worker->all_codeblock;
		while(codeblock_list_work->next != NULL){
			codeblock_list_work = codeblock_list_work->next;
		}

		codeblock_list_work->next	= codeblock_list;
		codeblock_list->last		= codeblock_list_work;
	}

	pthread_mutex_unlock(worker->worker_mutex);
}


/*
 * Remove a list element from the open_work list.
 * The function is not thread safe.
 */
PDC_Codeblock_list *PDC_Worker_remove_PDC_Codeblock_list(	PDC_Exception *exception,
															PDC_Worker *Worker,
															PDC_Codeblock_list *list)
{
	PDC_Codeblock_list *codeblock_list_work = list;

	if(codeblock_list_work->last != NULL){
		if(codeblock_list_work->next != NULL){
			codeblock_list_work->last->next = codeblock_list_work->next;
			codeblock_list_work->next->last = codeblock_list_work->last;
		}else{
			codeblock_list_work->last->next = NULL;
		}
	}else{
		if(codeblock_list_work->next != NULL){
			Worker->open_work 				= codeblock_list_work->next;
			codeblock_list_work->next->last	= NULL;
		}else{
			Worker->open_work = NULL;
		}
	}

	codeblock_list_work->last	= NULL;
	codeblock_list_work->next	= NULL;

	return codeblock_list_work;
}

/*
 *
 */
PDC_Codeblock *PDC_Worker_get_Codeblock_by_pointer(	PDC_Exception *exception,
													PDC_Worker *worker,
													PDC_Codeblock *codeblock)
{
	PDC_Codeblock_list *codeblock_list_work;
	PDC_Codeblock *return_codeblock = NULL;
	int status;

	while(return_codeblock == NULL){
		pthread_mutex_lock(worker->worker_mutex);
		if(worker->open_work != NULL){
			codeblock_list_work = worker->open_work;
			while(codeblock_list_work->this != codeblock && codeblock_list_work->next != NULL){

				codeblock_list_work = codeblock_list_work->next;
			}

			if(codeblock_list_work->this == codeblock){
				PDC_Worker_remove_PDC_Codeblock_list(	exception,
														worker,
														codeblock_list_work);
			}
		}


		if((status = pthread_mutex_trylock(codeblock->in_work)) != EBUSY){
			if(status != 0){
				PDC_Exception_error( exception, NULL, PDC_EXCEPTION_DECODER, __LINE__, __FILE__);
				pthread_mutex_unlock(codeblock->in_work);
				pthread_mutex_unlock(worker->worker_mutex);
				return NULL;
			}

			return_codeblock = codeblock;
			return_codeblock->current_thread = pthread_self();
			pthread_mutex_unlock(worker->worker_mutex);
		}else{

			pthread_mutex_unlock(worker->worker_mutex);
			pthread_mutex_lock(codeblock->in_work);
			pthread_mutex_unlock(codeblock->in_work);
		}
	}

	return return_codeblock;
}

/*
 * Return the next Codeblock from the open_work list.
 * If there is no Codeblock, the function blocks the caller thread until
 * there is a Codeblock.
 */
PDC_Codeblock *PDC_Worker_get_next_Codeblock(	PDC_Exception	*exception,
												PDC_Worker		*worker)
{
	PDC_Codeblock *codeblock = NULL;
	PDC_Codeblock_list *codeblock_list = NULL;

	pthread_mutex_lock(worker->worker_mutex);
	codeblock_list = worker->open_work;

	while(codeblock == NULL){

		if(codeblock_list != NULL){
			codeblock = codeblock_list->this;
			if(pthread_mutex_trylock(codeblock->in_work) == EBUSY){
				codeblock_list = codeblock_list->next;
				codeblock = NULL;
			}else{
				PDC_Worker_remove_PDC_Codeblock_list(	exception,
														worker,
														worker->open_work);
				pthread_mutex_unlock(worker->worker_mutex);
				codeblock->current_thread = pthread_self();
			}
		}else if(codeblock_list == NULL && worker->state == MORE_CODEBLOCKS_EXCPECTED){
			pthread_cond_wait(worker->worker_wait, worker->worker_mutex);
			codeblock_list = worker->open_work;
		}else{
			pthread_mutex_unlock(worker->worker_mutex);	
			break;
		}
	}

	return codeblock;
}


/*
 * Add codeblock to open_work list when new_job == PDC_true or
 * codeblock->has_job == PDC_true.
 */
void PDC_Worker_add_02(	PDC_Exception *exception,
						PDC_Worker *worker,
						PDC_Codeblock *codeblock,
						PDC_bool new_job)
{
	PDC_Codeblock_list *codeblock_list_work;
	PDC_bool codeblock_list_include = PDC_false;

	if(pthread_equal(pthread_self(), codeblock->current_thread)){
		if(new_job == PDC_true || codeblock->has_job == PDC_true){
			pthread_mutex_lock(worker->worker_mutex);
			if(worker->open_work == NULL){
				worker->open_work = codeblock->work_list;
			}else{
				codeblock_list_work = worker->open_work;
				while(codeblock_list_work != NULL){
					if(codeblock->work_list == codeblock_list_work){
						codeblock_list_include = PDC_true;
						break;
					}
					codeblock_list_work = codeblock_list_work->next;
				}

				if(codeblock_list_include == PDC_false){
					codeblock_list_work = worker->open_work;
					while(codeblock_list_work->next != NULL){
						codeblock_list_work = codeblock_list_work->next;
					}

					codeblock_list_work->next	= codeblock->work_list;
					codeblock->work_list->last	= codeblock_list_work;

					codeblock->has_job = PDC_true;
				}
			}
			pthread_mutex_unlock(codeblock->in_work);
			pthread_cond_signal(worker->worker_wait);
			pthread_mutex_unlock(worker->worker_mutex);
		}else{
			pthread_mutex_unlock(codeblock->in_work);
			pthread_cond_signal(worker->worker_wait);
		}
		//codeblock->current_thread = 0;
		
	}
}


/*
 *
 */
PDC_Codeblock_list *new_PDC_Codeblock_list_01(PDC_Exception *exception)
{
	PDC_Codeblock_list *codeblock_list = NULL;

	codeblock_list = malloc(sizeof(PDC_Codeblock_list));
	if(codeblock_list == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}

	codeblock_list->last	= NULL;
	codeblock_list->next	= NULL;
	codeblock_list->this	= NULL;

	return codeblock_list;
}


/*
 *
 */
PDC_Codeblock_list *new_PDC_Codeblock_list_02(PDC_Exception *exception, PDC_Codeblock *codeblock)
{
	PDC_Codeblock_list *codeblock_list;

	codeblock_list = new_PDC_Codeblock_list_01(exception);
	if(exception->code != PDC_EXCEPTION_NO_EXCEPTION){
		delete_PDC_Codeblock_list(exception, codeblock_list);
		return NULL;
	}

	codeblock_list->this	= codeblock;

	return codeblock_list;
}

/*
 *
 */
void delete_PDC_Codeblock_list(PDC_Exception *exception, PDC_Codeblock_list *codeblock_list)
{
	if(codeblock_list != NULL){
		codeblock_list->last	= NULL;
		codeblock_list->next	= NULL;
		codeblock_list->this	= NULL;
		free(codeblock_list);
	}
}


/*
 *
 */
void* start_worker_01(void *in_info){
	PDC_Worker_thread	*thread = (PDC_Worker_thread*)in_info;
	PDC_Worker			*worker = thread->worker;
	PDC_Codeblock		*codeblock;
	PDC_bool			run = PDC_true;

	while(run == PDC_true){
		codeblock = PDC_Worker_get_next_Codeblock(	thread->exception,
													worker);

		if(codeblock != NULL){
			codeblock = PDC_Codeblock_coefficient_bit_moddeling_decode_01(thread->exception, codeblock);
			PDC_Codeblock_set_false_has_job(thread->exception, codeblock);
			PDC_Codeblock_unlock(thread->exception, codeblock);
		}else{
			run = PDC_false;
		}
	}

	return in_info;
}

/*
 *
 */
PDC_Worker_thread *new_PDC_Worker_thread_01(	PDC_Exception *exception,
												PDC_Worker *worker)
{
	PDC_Worker_thread *worker_thread = NULL;

	worker_thread = malloc(sizeof(PDC_Worker_thread));
	if(worker_thread == NULL){
		PDC_Exception_error( exception, NULL, PDC_EXCEPTION_OUT_OF_MEMORY, __LINE__, __FILE__);
		return NULL;
	}
	worker_thread->end			= 0;
	worker_thread->exception	= exception;
	worker_thread->worker		= worker;

	pthread_create(&(worker_thread->thread_id), NULL, &start_worker_01, worker_thread);
	return worker_thread;
}

/*
 *
 */
void delete_PDC_Worker_thread(	PDC_Exception *exception,
								PDC_Worker_thread *worker_thread)
{
	if(worker_thread != NULL){
		free(worker_thread);
	}
}

/*
 *
 */
void set_PDC_Worker_state(PDC_Exception *exception, PDC_Worker *worker, PDC_Worker_state new_state)
{
	PDC_int pos_thread, max_thread;
	max_thread = PDC_max_thread();

	pthread_mutex_lock(worker->worker_mutex);
	worker->state = new_state;
	for(pos_thread = 0; pos_thread < max_thread; pos_thread += 1){
		pthread_cond_signal(worker->worker_wait);
	}
	pthread_mutex_unlock(worker->worker_mutex);
}

/*
 *
 */
void PDC_Worker_wait_to_finish(PDC_Exception *exception, PDC_Worker *worker)
{
	PDC_int pos_thread, max_thread;
	max_thread = PDC_max_thread();

	for(pos_thread = 0; pos_thread < max_thread; pos_thread += 1){
		pthread_join(worker->threads[pos_thread]->thread_id, NULL);
	}

}

STOP_C
