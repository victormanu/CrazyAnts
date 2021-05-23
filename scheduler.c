#include "scheduler.h" 

void priority(_strAnts *list){

}

void setOrder(_strAnts *list, int algorithm, 
            int wValue){
    if (algorithm == RR) {                                                                 // Don't sort
        printf("Algoritmo: RR\n");         
    }
    else if (algorithm == PRIORITY) {
        printf("Algoritmo: Prioridad\n");
        priority(list);
    }
}


void sche(_strAnts *listLeft, _strAnts *listRight, 
    int algorithm, int wValue, int time){
    if(listLeft[0].thread == NULL){
        if(listRight[0].thread == NULL){
            printf("Vacías ambas\n");
        }else{
            printf("Vacía la de izquierda\n");
            setOrder(listRight, algorithm, wValue);
        }
    }else{
        printf("Vacía la de derecha\n");
        setOrder(listRight, algorithm, wValue);
    }
}