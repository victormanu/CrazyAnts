#include "scheduler.h" 

int size(_strAnts *list){
    int counter = 0;
    for(int i = 0; i < 100; i++){
        if(list[i].id == 0){
            break;
        }
        counter++;
    }
    return counter;
}

/* 
    Alogirtmo FCFS: Primero en Llegar, Primero en ser Servido
 */
_strAnts* first_Come_First_Served(_strAnts *list){
    //_strAnts reorderedList[SIZE_OF_LIST];
    _strAnts reorderedList;
    for(int i = 0; i < SIZE_OF_LIST; i++){
        if(list[i].id == 0){        
            break;
        }
        reorderedList = list[i];
        list[i] = reorderedList;
    }
    // Impresiones de prueba
    for(int i = 0; i < SIZE_OF_LIST; i++){
        if(list[i].id == 0){         
            break;
        }
        printf(" \n");
        printf("Speed: %d \n", list[i].speed);
        printf("Type: %d \n", list[i].type);
        printf("Canal: %d \n", list[i].canal);
        printf("Ant: %d \n", list[i].horm);
        printf("id: %d \n", list[i].id);    
        printf("Tiempo de ejecucion: %f \n", list[i].executionTime);
        printf(" \n");
        printf("Number of elements present in given array: %d \n", size(list));    
    }
    return list;
}
/*
  Algoritmo SJF: Primero el trabajo mas corto
*/
_strAnts* shortest_Job_First(_strAnts *list){
    _strAnts tmpi;
    _strAnts tmpj;
    for(int i = 0; i < SIZE_OF_LIST; i++){
        if(list[i].id == 0){         
            break;
        }
        tmpi = list[i];

        for(int j = i + 1; i < SIZE_OF_LIST; j++) {
            if(list[j].id == 0){
                break;
            }
            tmpj = list[j];            
            if(tmpi.executionTime > tmpj.executionTime){
                list[i] = tmpj;
                list[j] = tmpi;
                tmpi = list[i];
            }
        } 
    }
    // Print just for testing 
    for(int i = 0; i < SIZE_OF_LIST; i++){
        if(list[i].id == 0){         
            //printf("\nPRIORITY NULL\n"); 
            break;
        }
        printf(" \n");
        printf("Speed: %d \n", list[i].speed);
        printf("Type: %d \n", list[i].type);
        printf("Canal: %d \n", list[i].canal);
        printf("Ant: %d \n", list[i].horm);
        printf("id: %d \n", list[i].id);
        printf("Tiempo de ejecucion: %f \n", list[i].executionTime);
        printf(" \n");
        //int length = sizeof(list)/sizeof(list[0]);            
        printf("Number of elements present in given array: %d", size(list));    
        printf(" \n");
    }
    return list;
}

/*
    Algoritmo RR: Round Robin
    Quantum: cantidad de tiempo que se le va a permitir a cada proceso estar en el procesador
*/
void roundRobin(_strAnts *list, float Quantum){

}

// Calendarizador de prioridad
_strAnts* priority(_strAnts *list){
    _strAnts tmpi;
    _strAnts tmpj;
    printf("INSIDE PRIORITY\n"); 
    for(int i = 0; i < SIZE_OF_LIST; i++){
        if(list[i].id == 0){
            break;
        }
        tmpi = list[i];

        for(int j = i + 1; i < SIZE_OF_LIST; j++) {
            if(list[j].id == 0){
                break;
            }
            tmpj = list[j];
            if(tmpi.speed < tmpj.speed){
                list[i] = tmpj;
                list[j] = tmpi;
                tmpi = list[i];
            }
        } 
    }
    return list;
}

_strAnts* setOrder(_strAnts *list, int algorithm){
    if (algorithm == RR) {                            
        printf("Algoritmo: RR\n");
        roundRobin(list, QUANTUM);
        return list;         
    }
    else if (algorithm == PRIORITY) {
        printf("Algoritmo: Prioridad\n");
        list = priority(list);
        return list;
    }
    else if (algorithm == FCFS){
        printf("\nAlgoritmo: FCFS\n");
        list = first_Come_First_Served(list);
        printf("Es\n");
        return list;
    }
    else if (algorithm == SJF){
        printf("\nAlgoritmo: SJF\n");
        list = shortest_Job_First(list);
        return list;
    }
}

int getCounterCanal(_strCanal canal, int site){
    if(site == LEFT){
        return canal.counterLeft;
    }else{
        return canal.counterRight;
    }
}

void addCanalCounter(_strCanal _canal, int site){
    if(site == LEFT){
        _canal.counterLeft += 1;
    }else{
        _canal.counterRight += 1;
    }
}

_strCanal getCanal(int canal){
    _strCanal theCanal;
    switch(canal){
        case 1:
            theCanal = canal1;
        case 2:
            theCanal = canal2;
        default:
            theCanal = canal3;
    }
    return theCanal;
}

void equid(int _w, int algorithm, _strAnts *listLeft, _strAnts *listRight, int _canal){
    canal = getCanal(_canal);
    if(canal.sides == RIGHT){
        printf("Derecha\n");
        //listRight = setOrder(listRight, algorithm);
        if(size(listRight) >= _w){
            for(int i = 0; i < _w; i++){
                if(listRight[i].id == 0){
                    break;
                }
                canal.ants[i] = listRight[i];
            }
            canal.sides = LEFT;
        }else{
            for(int i = 0; i < size(listRight); i++){
                if(listRight[i].id == 0){
                    break;
                }
                canal.ants[i] = listRight[i];
                addCanalCounter(canal, RIGHT);
            }
        }
        int counter = getCounterCanal(canal, RIGHT);
        if(counter >= _w){
            canal.sides = LEFT;
        }
    }else{
        printf("Izquierda\n");
        //listLeft = setOrder(listLeft, algorithm);
         printf("Parte\n");
        if(size(listLeft) >= _w){
            for(int i = 0; i < _w; i++){
                if(listLeft[i].id == 0){
                    break;
                }
                canal.ants[i] = listLeft[i];
            }
            canal.sides = RIGHT;
        }else{
            for(int i = 0; i < size(listLeft); i++){
                if(listLeft[i].id == 0){
                    break;
                }
                canal.ants[i] = listLeft[i];
                addCanalCounter(canal, LEFT);
            }
        }
        int counter = getCounterCanal(canal, RIGHT);
        if(counter >= _w){
            canal.sides = RIGHT;
        }
    }
}

void sign(_strAnts *listLeft, _strAnts *listRight, int _sign, int algorithm, int _canal){
    canal = getCanal(_canal);
    if(_sign == LEFT){
        //listLeft = setOrder(listLeft, algorithm);
        for(int i = 0; i < size(listLeft); i++){
            if(listLeft[i].id == 0){
                break;
            }
            canal.ants[i] = listLeft[i];
        }
    }else{
        listRight = setOrder(listRight, algorithm);
        for(int i = 0; i < size(listRight); i++){
            if(listRight[i].id == 0){
                break;
            }
            canal.ants[i] = listRight[i];
        }
    }
}

void tico(_strAnts *listLeft, _strAnts *listRight, int algorithm, int _canal){
    canal = getCanal(_canal);
    if(listLeft[0].thread == 0){
        canal.state = BUSY;
        //listRight = setOrder(listRight, algorithm);
        for(int i = 0; i < size(listRight); i++){
            if(listRight[i].id == 0){
                break;
            }
            canal.ants[i] = listRight[i];
        }
    }else{
        canal.state = BUSY;
        //listLeft = setOrder(listLeft, algorithm);
        for(int i = 0; i < size(listLeft); i++){
            if(listLeft[i].id == 0){
                break;
            }
            canal.ants[i] = listLeft[i];
        }
    }
}

void sche(_strAnts *listLeft, _strAnts *listRight, 
    int algorithm, _configCanal conf){
    if(conf.controlMethod == EQUID){
        equid(conf.parameterW, algorithm, listLeft, listRight, conf.idCanal); // Quitar parámetros del algoritmo
    }else if(conf.controlMethod == SIGN){
        sign(listLeft, listRight, LEFT, algorithm, conf.idCanal);
    }else if(conf.controlMethod == TICO){
        tico(listLeft, listRight, algorithm, conf.idCanal);
    }
}