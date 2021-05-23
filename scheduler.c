#include "scheduler.h" 

void sche(cethread_t *listLeft){
    printf("Hola\n");
    if(listLeft[0] == NULL){
        printf("Adios\n");
    }
    printf("Mundo\n");
}
/*
void scheduler( *pStackL[], struct Lpthreads *pStackR[], FlowControl flowControl,
enum Algorithms algorithm, stateBand SB, int value, float QUANTUM) {
    struct Lpthreads* tmp = pStackL[0];
    w = value;
    Side side = LEFT;
    int passedPacks = 0;
    while(1) {
        if(SB == RUNNINGBAND) {                            // State Band 1 == Running
            if (flowControl == CONTROLLED_ACCESS) {      // With controled access
                while(SB == RUNNINGBAND) {
                    // Make sure that if one stack is empty gets the other
                    if (tmp == NULL & side == LEFT) {
                        side = RIGHT;
                        tmp =  pStackR[0];
                        printf("Left Stack empty, changing to Right \n");
                        sleep(0.5);
                    }
                    else if (tmp == NULL & side == RIGHT) {
                        side = LEFT;
                        tmp =  pStackL[0];
                        printf("Right Stack empty, changing to Left \n");
                        sleep(0.5);
                    }
                    // Control Access Logic
                    if (tmp != NULL & passedPacks <= w & side == LEFT) {
                        int selectSch = selectScheduler(pStackL, algorithm, QUANTUM);       
                        tmp = pStackL[0]; 
                        if (passedPacks == w | tmp == NULL) {
                            side = RIGHT;
                            passedPacks = 0;
                            if (is_empty(pStackR) == 0) break;
                            tmp = pStackR[0];
                            break;
                        }                         
                    }
                    else if (tmp != NULL & passedPacks <= w & side == RIGHT) {
                        int selectSch = selectScheduler(pStackR, algorithm, QUANTUM); 
                        tmp = pStackL[0];                                           
                        if (passedPacks == w | tmp == NULL) {
                            side = LEFT;
                            passedPacks = 0;
                            if (is_empty(pStackL) == 0) break;
                            tmp = pStackL[0];
                            break;
                        }    
                    }
                    passedPacks++;                            
                }
            }
            else if (flowControl == SIGN) {
                float signTime = value;                             // Pass by value the sign time
                sign = LEFT;                                                
                time_t startSign, endSign;
                startSign = time(NULL);                         
                while (SB = RUNNINGBAND) {
                    endSign = time(NULL);
                    if (tmp != NULL & sign == LEFT) {                       
                        if (difftime(endSign, startSign) > signTime) {                 // If time out
                            sign = RIGHT;
                            startSign = time(NULL);
                            break;
                        }
                        int slectSch = selectScheduler(pStackL, algorithm, QUANTUM); 
                    }
                    else if (tmp != NULL & sign == LEFT) {
                        if (difftime(endSign, startSign) > signTime) {                 // If time out
                            sign = LEFT;
                            startSign = time(NULL);
                            break;
                        }
                        int slectSch = selectScheduler(pStackR, algorithm, QUANTUM); 
                    }                    
                }                          
            }
            else if (flowControl = RANDOM) {
                while(SB == RUNNINGBAND) {
                    int side = rand() % 2;
                    // Make sure that if one stack is empty gets the other
                     if (tmp == NULL & side == LEFT) {
                        side = RIGHT;
                        tmp =  pStackR[0];
                        printf("Left Stack empty, changing to Right \n");
                        sleep(0.5);
                    }
                    else if (tmp == NULL & side == RIGHT) {
                        side = LEFT;
                        tmp =  pStackL[0];
                        printf("Right Stack empty, changing to Left \n");
                        sleep(0.5);
                    }
                    if (side == 0) {
                        sign = LEFT;
                        int slectSch = selectScheduler(pStackL, algorithm, QUANTUM);

                    }
                    else if (side == 1) {
                        sign = RIGHT;
                        int slectSch = selectScheduler(pStackL, algorithm, QUANTUM); 
                    }
                }
            }  
        }
    }
}*/