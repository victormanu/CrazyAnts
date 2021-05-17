/*
*   Este código está basado en la implmentación realizada por Ning Wang, 9/8/15.
*   Obtenido de: https://github.com/LancelotGT/gtthread
*/

#include "CEthread.h"

static steque_t ready_queue;
static steque_t zombie_queue;

static cethread* current;
static struct itimerval timer;
sigset_t vtalrm;
static cethread_t maxtid;

void scheduler(int sig){
    /* block the signal */
    sigprocmask(SIG_BLOCK, &vtalrm, NULL);

    /* if no thread in the ready queue, resume execution */
    if (steque_isempty(&ready_queue))
        return;

    /* get the next runnable thread and use preemptive scheduling */
    cethread* next = (cethread*) steque_pop(&ready_queue);
    while (next->state == CANCEL)
    {
        steque_enqueue(&zombie_queue, next);
        next = (cethread*) steque_pop(&ready_queue); 
    }
    cethread* prev = current;
    steque_enqueue(&ready_queue, current);
    next->state = RUNNING; 
    current = next;

    /* unblock the signal */
    sigprocmask(SIG_UNBLOCK, &vtalrm, NULL); 
    swapcontext(prev->ucp, current->ucp);
}

void startRoutine(void* (*start_routine)(void*), void* args){
    sigprocmask(SIG_UNBLOCK, &vtalrm, NULL);
    current->retval = (*start_routine)(args);
    cethread_end(current->retval);
}

cethread* getThread(cethread_t tid){
    steque_node_t* current = ready_queue.front;
    while (current != NULL){
        cethread* t = (cethread*) current->item;
        if (t->tid == tid)
            return t;
        current = current->next;
    }

    current = zombie_queue.front;
    while (current != NULL){
        cethread* t = (cethread*) current->item;
        if (t->tid == tid)
            return t;
        current = current->next;
    }
    return NULL;
}

void cethread_init(long period){
    struct sigaction act;

    /* initializing data structures */
    maxtid = 1;
    steque_init(&ready_queue);
    steque_init(&zombie_queue);
    
    /* create main thread and add it to ready queue */  
    /* only main thread is defined on heap and can be freed */
    cethread* main_thread = (cethread*) malloc(sizeof(cethread));
    main_thread->tid = maxtid++;
    main_thread->ucp = (ucontext_t*) malloc(sizeof(ucontext_t)); 
    memset(main_thread->ucp, '\0', sizeof(ucontext_t));
    main_thread->arg = NULL;
    main_thread->state = RUNNING;
    main_thread->joining = 0;

    /* must be called before makecontext */
    if (getcontext(main_thread->ucp) == -1)
    {
      perror("getcontext");
      exit(EXIT_FAILURE);
    }

    current = main_thread;
    
    /* setting uo the signal mask */
    sigemptyset(&vtalrm);
    sigaddset(&vtalrm, SIGALRM);
    sigprocmask(SIG_UNBLOCK, &vtalrm, NULL); /* in case this is blocked previously */

    /* set alarm signal and signal handler */
    timer.it_interval.tv_usec = period;
    timer.it_interval.tv_sec = 0;
    timer.it_value.tv_usec = period;
    timer.it_value.tv_sec = 0; 
    
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) < 0)
    {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    /* install signal handler for SIGVTALRM */  
    memset(&act, '\0', sizeof(act));
    act.sa_handler = &scheduler;
    if (sigaction(SIGVTALRM, &act, NULL) < 0)
    {
      perror ("sigaction");
      exit(EXIT_FAILURE);
    }
}

int  cethread_create(cethread_t *thread, void *(*start_routine)(void *), void *arg){
    /* block SIGVTALRM signal */
    sigprocmask(SIG_BLOCK, &vtalrm, NULL);
    
    /* allocate heap for thread, it cannot be stored on stack */
    cethread* t = malloc(sizeof(cethread));
    *thread = t->tid = maxtid++; // need to block signal
    t->state = RUNNING;
    t->proc = start_routine;
    t->arg = arg;
    t->ucp = (ucontext_t*) malloc(sizeof(ucontext_t));
    t->joining = 0;
    memset(t->ucp, '\0', sizeof(ucontext_t));

    if (getcontext(t->ucp) == -1)
    {
      perror("getcontext");
      exit(EXIT_FAILURE);
    }
    
    /* allocate stack for the newly created context */
    /* here we allocate the stack size using the canonical */
    /* size for signal stack. */
    t->ucp->uc_stack.ss_sp = malloc(SIGSTKSZ);
    t->ucp->uc_stack.ss_size = SIGSTKSZ;
    t->ucp->uc_stack.ss_flags = 0;
    t->ucp->uc_link = NULL;

    makecontext(t->ucp, (void (*)(void)) startRoutine, 2, start_routine, arg);
    steque_enqueue(&ready_queue, t);

    /* unblock the signal */
    sigprocmask(SIG_UNBLOCK, &vtalrm, NULL);   
    return 0;
}

void cethread_end(void *retval){
    /* block alarm signal */
    sigprocmask(SIG_BLOCK, &vtalrm, NULL);

    if (steque_isempty(&ready_queue))
    { 
        sigprocmask(SIG_UNBLOCK, &vtalrm, NULL); 
        exit((long) retval);
    }

    /* if the main thread call gtthread_exit */
    if (current->tid == 1)
    {
        while (!steque_isempty(&ready_queue))
        {
            sigprocmask(SIG_UNBLOCK, &vtalrm, NULL);  
            scheduler(SIGVTALRM);
            sigprocmask(SIG_BLOCK, &vtalrm, NULL);
        }
        sigprocmask(SIG_UNBLOCK, &vtalrm, NULL);   
        exit((long) retval);
    }

    cethread* prev = current; 
    current = (cethread*) steque_pop(&ready_queue);
    current->state = RUNNING; 

    /* free up memory allocated for exit thread */
    free(prev->ucp->uc_stack.ss_sp); 
    free(prev->ucp);                
    prev->ucp = NULL;

    /* mark the exit thread as DONE and add to zombie_queue */ 
    prev->state = DONE; 
    prev->retval = retval;
    prev->joining = 0;
    steque_enqueue(&zombie_queue, prev);

    /* unblock alarm signal and setcontext for next thread */
    sigprocmask(SIG_UNBLOCK, &vtalrm, NULL); 
    setcontext(current->ucp);
}

int cethread_yield(void){
    /* block SIGVTALRM signal */
    sigprocmask(SIG_BLOCK, &vtalrm, NULL);
    
    /* if no thread to yield, simply return */
    if (steque_isempty(&ready_queue))
        return 0;

    cethread* next = (cethread*) steque_pop(&ready_queue);
    cethread* prev = current;
    steque_enqueue(&ready_queue, current);
    current = next;

    /* unblock the signal */
    sigprocmask(SIG_UNBLOCK, &vtalrm, NULL); 
    swapcontext(prev->ucp, current->ucp); 
    return 0; 
}

int cethread_join(cethread_t thread, void **status){
    /* if a thread tries to join itself */
    if (thread == current->tid)
        return -1;

    cethread* t;
    /* if a thread is not created */
    if ((t = getThread(thread)) == NULL)
        return -1;

    /* check if that thread is joining on me */
    if (t->joining == current->tid)
        return -1;

    current->joining = t->tid;
    /* wait on the thread to terminate */
    while (t->state == RUNNING)
    {
        sigprocmask(SIG_UNBLOCK, &vtalrm, NULL);
        scheduler(SIGVTALRM);
        sigprocmask(SIG_BLOCK, &vtalrm, NULL);
    }

    if (status == NULL)
        return 0;

    if (t->state == CANCEL)
        *status = (void*) CANCEL;
    else if (t->state == DONE)
        *status = t->retval;

    return 0;
}

/*int cethread_detach(cethread_t thread){
    sigprocmask(SIG_BLOCK, &vtalrm, NULL);
    cethread* t;
    if ((t = getThread(thread)) != NULL){
        t->joinable = 0;
        sigprocmask(SIG_BLOCK, &vtalrm, NULL);
        return 0;
    }
    sigprocmask(SIG_BLOCK, &vtalrm, NULL);
    return -1;
}*/

int cemutex_init(cethread_mutex_t *mutex){
    sigprocmask(SIG_BLOCK, &vtalrm, NULL); /* in case this is blocked previously */    
    steque_init(mutex);
    sigprocmask(SIG_UNBLOCK, &vtalrm, NULL);
    return 0;
}

int cemutex_destroy(cethread_mutex_t *mutex){
    sigprocmask(SIG_BLOCK, &vtalrm, NULL); /* in case this is blocked previously */    
    steque_destroy(mutex);
    sigprocmask(SIG_UNBLOCK, &vtalrm, NULL); 
    return 0;
}

int cemutex_unlock(cethread_mutex_t *mutex){
    sigprocmask(SIG_BLOCK, &vtalrm, NULL);
    if (steque_isempty(mutex))
    {
        sigprocmask(SIG_UNBLOCK, &vtalrm, NULL);
        return -1;
    }

    if ((cethread_t) steque_front(mutex) != cethread_self())
    {
       sigprocmask(SIG_UNBLOCK, &vtalrm, NULL);
       return -1;
    }

    steque_pop(mutex);
    sigprocmask(SIG_UNBLOCK, &vtalrm, NULL); 
    return 0;
}

int cemutex_trylock(cethread_mutex_t *mutex){
    sigprocmask(SIG_BLOCK, &vtalrm, NULL); 

    /* if queue lock is empty */
    if (steque_isempty(mutex))
    {
        steque_enqueue(mutex, (steque_item) cethread_self());  
        sigprocmask(SIG_UNBLOCK, &vtalrm, NULL);   
        return 0;
    }

    /* if a thread try to acquire lock */ 
    if (cethread_self() == (cethread_t) steque_front(mutex))
    {
        sigprocmask(SIG_UNBLOCK, &vtalrm, NULL);
        return 0;
    }

    steque_enqueue(mutex, (steque_item) cethread_self()); 
    while (cethread_self() != (cethread_t) steque_front(mutex)) 
    {
        sigprocmask(SIG_UNBLOCK, &vtalrm, NULL); 
        /* actively perform context switching */
        scheduler(SIGVTALRM);
        sigprocmask(SIG_BLOCK, &vtalrm, NULL);
    }
    sigprocmask(SIG_UNBLOCK, &vtalrm, NULL);  
    return 0;
}

cethread_t cethread_self(void)
{
    return current->tid;
}