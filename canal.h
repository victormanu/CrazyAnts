#ifndef _CANAL_H
#define _CANAL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct configCanal{
    int controlMethod;
    int canalLength;
    int orderedAnts;
    int signTime;
    int parameterW;
} _configCanal;

_configCanal canalConfig(int _canal);

#endif