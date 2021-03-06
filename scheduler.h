#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "threads/CEthread.h"
#include "ants.h"

#define AVAILABLE 0
#define BUSY  	  1

typedef struct {
	_strAnts ants[ANTS_NUMBER];
	int idCanal;
	int counterLeft;
	int counterRight;
	int sides;
	int state;
} _strCanal;

void sche( _strAnts *listLeft,  _strAnts *listRight, 
	int algorithm, _configCanal conf);

_strCanal canal;
_strCanal canal1;
_strCanal canal2;
_strCanal canal3;

#endif