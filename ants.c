#include "ants.h"
#include "scheduler.h" 
#include "threads/CEthread.h"

_strAnts newAnt(int _id, int _horm, int _canal, int _type, float _execTime){
    _strAnts ant;
    ant.speed = 10*_type;
    ant.canal = _canal;
    ant.horm = _horm;
    ant.id = _id;
    ant.type = _type;
    ant.executionTime = _execTime;
    return ant;
}

void setReadyList(_strAnts _ant){
    if(_ant.horm == 1){
        if(_ant.canal == 1){ // Falta verificar si la lista ya está llena en todos los casos
            readyLists.readyListC1L[readyLists.counterC1L] = _ant;
            readyLists.counterC1L += 1;
            setOrder(readyLists.readyListC1L, PRIORITY);
        }else if(_ant.canal == 2){
            readyLists.readyListC2L[readyLists.counterC2L] = _ant;
            readyLists.counterC2L += 1;
            setOrder(readyLists.readyListC2L, FCFS);
        }else{
            readyLists.readyListC3L[readyLists.counterC3L] = _ant;
            readyLists.counterC3L += 1;
            setOrder(readyLists.readyListC3L, FCFS);
        }
    }else{
        if(_ant.canal == 1){
            readyLists.readyListC1R[readyLists.counterC1R] = _ant;
            readyLists.counterC1R += 1;
            setOrder(readyLists.readyListC1R, PRIORITY);
        }else if(_ant.canal == 2){
            readyLists.readyListC2R[readyLists.counterC2R] = _ant;
            readyLists.counterC2R += 1;
            setOrder(readyLists.readyListC2R, FCFS);
        }else{
            readyLists.readyListC3R[readyLists.counterC3R] = _ant;
            readyLists.counterC3R += 1;
            setOrder(readyLists.readyListC3R, FCFS);
        }
    }
}


void* parallel(_strAnts* _ant){
    _strAnts ant = (*(_strAnts*)_ant);
    printf("Id: %d\n",ant.id);
    printf("Canal: %d\n",ant.canal);
    printf("Velocidad: %d\n",ant.speed);
    // Caminar del hormiguero a lista de listos 
    // Entrar a la lista de listos
    setReadyList(ant);
    // Se devuelve la posición del readyList para mover la hormiga visualmente
    // Se detiene la hormiga //Busy waiting GG
    // Se le indica que camine por el canal y salga hacia el siguiente hormiguero.
    while (ant.state != RUNNING);
    
    
    return NULL;
}

void canalWalk(_strAnts* ant){
    if(ant.canal == 1){
        _configCanal conf = canalConfig(1);
        sche(readyLists.readyListC1L, readyLists.readyListC1R, 
            PRIORITY, conf);
    }else if(ant.canal == 2){
        _configCanal conf = canalConfig(2);
        sche(readyLists.readyListC2L, readyLists.readyListC2R, 
            FCFS, conf);
    }else{
        _configCanal conf = canalConfig(3);
        sche(readyLists.readyListC3L, readyLists.readyListC3R, 
            SJF, conf);
    }
}

void hilos(_strAnts _ant){
    cethread_t thread;
    cethread_create(&thread, parallel, (_strAnts*) &_ant);
    cethread_join(thread, NULL);
    _ant.thread = thread;
}

int main(){
	// Inicializar contadores de listas
    readyLists.counterC1L = 0;
    readyLists.counterC1R = 0;
    readyLists.counterC2L = 0;
    readyLists.counterC2R = 0;
    readyLists.counterC3L = 0;
    readyLists.counterC3R = 0;
    canal1.sides = LEFT;

    int horm, canal, type;
    float exec;
    counterAnts = 0;
    cethread_init(1);
    //cethread_t schedule;
    //cethread_create(&schedule, schedulerC1,  &counterAnts);
    //cethread_join(schedule, NULL);
    
    while(counterAnts<10){
        printf("Tipo: ");
        scanf("%d", &type);
        printf("Hormiguero: ");
        scanf("%d", &horm);
        printf("Canal: ");
        scanf("%d", &canal);
        printf("Exec: ");
        scanf("%f", &exec);
        _strAnts ant = newAnt(counterAnts, horm, canal, type, exec);
        h1.ants[counterAnts] = ant;
        //while (getchar() != ENTER_ASCII_CODE);
        hilos(ant);
        counterAnts++;
    }

    return 0;
}

