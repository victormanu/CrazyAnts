#ifndef _CANAL_H
#define _CANAL_H

#include "ants.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ANTS_NUMBER 4

typedef struct configCanal{
    int controlMethod;
    int canalLength;
    int orderedAnts;
    int signTime;
    int parameterW;
    int canalTime;
    int idCanal;
} _configCanal;


_configCanal canalConfig(int _canal);

#endif