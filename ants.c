#include "ants.h"
#include "scheduler.h" 
#include "threads/CEthread.h"
#define ENTER_ASCII_CODE 10
#define SHORTEST_FIRST 1

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
    sche(readyLists.readyListC1L, readyLists.readyListC1L, 1);//readyLists.readyListC1L
    return NULL;
}

void hilos(int _horm, int _canal){
    cethread_t thread;
    cethread_create(&thread, parallel, (void*) 1);
    cethread_join(thread, NULL);
    if(_horm == 1){
        if(_canal == 1){
            readyLists.readyListC1L[readyLists.counterC1L] = thread;
            readyLists.counterC1L += 1;
            sche(readyLists.readyListC1L, readyLists.readyListC1L, 1);//readyLists.readyListC1L
        }else if(_canal == 2){
            readyLists.readyListC2L[readyLists.counterC2L] = thread;
            readyLists.counterC2L += 1;
        }else{
            readyLists.readyListC3L[readyLists.counterC3L] = thread;
            readyLists.counterC3L += 1;
        }
    }else{
        if(_canal == 1){
            readyLists.readyListC1R[readyLists.counterC1R] = thread;
            readyLists.counterC1R += 1;
        }else if(_canal == 2){
            readyLists.readyListC2R[readyLists.counterC2R] = thread;
            readyLists.counterC2R += 1;
        }else{
            readyLists.readyListC3R[readyLists.counterC3R] = thread;
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
    
    cethread_init(1);
    cethread_t schedule;
    cethread_create(&schedule, schedulerC1, (void*) 1);
    cethread_join(schedule, NULL);
    int i = 1;
    while(i<10){
        printf("Tipo: ");
        scanf("%d", &type);
        printf("Hormiguero: ");
        scanf("%d", &horm);
        printf("Canal: ");
        scanf("%d", &canal);
        h1.ants[i] = newAnt(i, horm, canal, type);
        //while (getchar() != ENTER_ASCII_CODE);
        hilos(horm, canal);
        printf("Id hormiga: %d\n", h1.ants[i].id);
        i++;
    }

    return 0;
}

