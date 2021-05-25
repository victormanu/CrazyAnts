#include "canal.h"

_configCanal conf;

_configCanal canalConfig(int _canal){
    FILE* file;
    if(_canal == 1){
        file = fopen("./conf/canal1.conf", "r");
    }else if(_canal == 2){
        file = fopen("./conf/canal2.conf", "r");
    }else{
        file = fopen("./conf/canal3.conf", "r");
    }
    if(file==NULL){
        printf ("Path to config not avaliable. \n");
        exit(EXIT_FAILURE); 
    }
    char line[256];
    char prev[256];
    while (fgets(line, sizeof(line), file)) {
        char* current = strtok (line, "=:");
        while (current) {
            if(!strcmp(prev,"controlMethod")){
                conf.controlMethod = atoi(current);
            }
            else if(!strcmp(prev,"canalLength")){
                conf.canalLength = atoi(current);
            }
            else if(!strcmp(prev,"orderedAnts")){
                conf.orderedAnts = atof(current);
            }            
            else if(!strcmp(prev,"signTime")){
                conf.signTime = atoi(current);
            }
            else if(!strcmp(prev,"parameterW")){
                conf.parameterW = atoi(current);
            }
            else if(!strcmp(prev,"canalTime")){
                conf.canalTime = atoi(current);
            }
            else if(!strcmp(prev,"idCanal")){
                conf.idCanal = atoi(current);
            }
            strcpy(prev, current);
            current = strtok (NULL, "=:");
        }
    }
    fclose(file);
    return conf;
}