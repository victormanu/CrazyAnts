/*
*   Este código está basado en la implmentación realizada por Ning Wang, 9/8/15.
*   Obtenido de: https://github.com/LancelotGT/gtthread
*/

#ifndef _CETHREAD_H
#define _CETHREAD_H

#include <ucontext.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include "steque.h"

#define RUNNING 0 
#define CANCEL 1 
#define DONE 2 

typedef unsigned long int cethread_t;

typedef steque_t cethread_mutex_t; 

typedef struct CEThread_t
{
    cethread_t tid;
    cethread_t joining;
    int state;
    void* (*proc)(void*);
    void* arg;
    void* retval;
    ucontext_t* ucp; 
    int joinable;
} cethread; 

/* must be called before any of the below functions. failure to do so may
 * result in undefined behavior. 'period' is the scheduling quantum (interval)
 * in microseconds (i.e., 1/1000000 sec.). */
void cethread_init(long period);

/* see man pthread_create(3); the attr parameter is omitted, and this should
 * behave as if attr was null (i.e., default attributes) */
int  cethread_create(cethread_t *thread, void *(*start_routine)(void *), void *arg);

/* see man pthread_exit(3) */
void cethread_end(void *retval);

/* see man sched_yield(2) */
int cethread_yield(void);

/* see man pthread_join(3) */
int cethread_join(cethread_t thread, void **status);

int cethread_detach(cethread_t thread);


/* see man pthread_mutex(3); except init does not have the mutexattr parameter,
 * and should behave as if mutexattr is NULL (i.e., default attributes); also,
 * static initializers do not need to be implemented */
int cemutex_init(cethread_mutex_t *mutex);
int cemutex_destroy(cethread_mutex_t *mutex);
int cemutex_unlock(cethread_mutex_t *mutex);
int cemutex_trylock(cethread_mutex_t *mutex);

cethread_t cethread_self(void);

#endif