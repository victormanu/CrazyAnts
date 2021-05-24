#include "scheduler.h" 

void priority(_strAnts *list){
    _strAnts tmpi;
    _strAnts tmpj;
    printf("INSIDE PRIORITY\n"); 
    for(int i = 0; i < 10; i++){
        if(list[i].id == NULL){ 
            printf(" PRIORITY NULL\n"); 
            break;
        }else{
            printf(" \n ");
            printf("Speed: %d \n", list[i].speed);
            printf("Type: %d \n", list[i].type);
            printf("Canal: %d \n", list[i].canal);
            printf("Ant: %d \n", list[i].horm);
            printf("id: %d \n", list[i].id);
            printf(" \n ");
        }

        //tmpi.speed = list[i]->speed;

        /*
        for(size_t j = i + 1; i < 10; j++){
            if(list[j] == NULL) break;
            tmpj = *list[j];
            //if(tmpj.algorithm != PRIORITY) break;

            if(tmpi.priority > tmpj.priority){
                *list[i] = tmpj;
                *list[j] = tmpi;
                tmpi = pStack[i];
            }
        }*/
    }
    //printf("Stack ordenado: \n");
    //print_stack(pStack);
    //printf("Creando thread con pid: %d \n", pStack[0]->pid);
    //lpthread_create(pStack[0]);
    //waitpid(pStack[0]->pid, 0, 0);
    //lpthread_end(pStack[0]);
    //remove_by_index(pStack, 0);
    //return 0;
}

void setOrder(_strAnts *list, int algorithm, _configCanal conf){
    if (algorithm == RR) {                                                                 // Don't sort
        printf("Algoritmo: RR\n");         
    }
    else if (algorithm == PRIORITY) {
        printf("Algoritmo: Prioridad\n");
        priority(list);
    }
}

void sche(_strAnts *listLeft, _strAnts *listRight, 
    int algorithm, _configCanal conf){
    if(listLeft[0].thread == NULL){
        if(listRight[0].thread == NULL){
            printf("Vacías ambas\n");
        }else{
            printf("Vacía la de izquierda\n");
            setOrder(listRight, algorithm, conf);
        }
    }else{
        printf("Vacía la de derecha\n");
        setOrder(listLeft, algorithm, conf);

    }
}