#include "canal.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CONF_PATH  "./conf/canal.conf"

_configCanal conf;

_configCanal canalConfig(int _canal){
    if(_canal == 1){
        
    }else if(_canal == 2){

    }else{
        
    }
    FILE* file = fopen(CONF_PATH, "r");
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
            strcpy(prev, current);
            current = strtok (NULL, "=:");
        }
    }
    fclose(file);
    return conf;
}