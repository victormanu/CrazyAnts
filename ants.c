#include "ants.h"
#include "scheduler.h" 
#include "threads/CEthread.h"

_strAnts newAnt(int _id, int _horm, int _canal, int _type){
    _strAnts ant;
    ant.speed = 10;
    ant.canal = _canal;
    ant.horm = _horm;
    ant.id = _id;
    return ant;
}

void* parallel(void * arg){
    return NULL;
}

void* schedulerC1(void* arg){
    sche(readyLists.readyListC1L, readyLists.readyListC1R, FCFS, W_VALUE, 10);
    return NULL;
}

void hilos(int _horm, int _canal, _strAnts _ant){
    cethread_t thread;
    cethread_create(&thread, parallel, (void*) 1);
    cethread_join(thread, NULL);
    _ant.thread = thread;
    if(_horm == 1){
        if(_canal == 1){
            readyLists.readyListC1L[readyLists.counterC1L] = _ant;
            readyLists.counterC1L += 1;
            sche(readyLists.readyListC1L, readyLists.readyListC1R, FCFS, W_VALUE, 10);
        }else if(_canal == 2){
            readyLists.readyListC2L[readyLists.counterC2L] = _ant;
            readyLists.counterC2L += 1;
        }else{
            readyLists.readyListC3L[readyLists.counterC3L] = _ant;
            readyLists.counterC3L += 1;
        }
    }else{
        if(_canal == 1){
            readyLists.readyListC1R[readyLists.counterC1R] = _ant;
            readyLists.counterC1R += 1;
        }else if(_canal == 2){
            readyLists.readyListC2R[readyLists.counterC2R] = _ant;
            readyLists.counterC2R += 1;
        }else{
            readyLists.readyListC3R[readyLists.counterC3R] = _ant;
            readyLists.counterC3R += 1;
        }
    }
    printf("%d\n",readyLists.counterC1L);
    readyLists.counterC1L += 1;
}

int main(){
	// Inicializar contadores de listas
    readyLists.counterC1L = 0;
    readyLists.counterC1R = 0;
    readyLists.counterC2L = 0;
    readyLists.counterC2R = 0;
    readyLists.counterC3L = 0;
    readyLists.counterC3R = 0;

    _strAntsHill h1;
    _strAntsHill h2;

    int horm, canal, type;
    int i = 1;

    cethread_init(1);
    cethread_t schedule;
    cethread_create(&schedule, schedulerC1,  &i);
    cethread_join(schedule, NULL);
    
    while(i<10){
        printf("Tipo: ");
        scanf("%d", &type);
        printf("Hormiguero: ");
        scanf("%d", &horm);
        printf("Canal: ");
        scanf("%d", &canal);
        _strAnts ant = newAnt(i, horm, canal, type);
        h1.ants[i] = ant;
        //while (getchar() != ENTER_ASCII_CODE);
        hilos(horm, canal, ant);
        printf("Id hormiga: %d\n", h1.ants[i].id);
        i++;
    }

    return 0;
}

