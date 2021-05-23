#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "threads/CEthread.h"
#include "ants.h"

void sche( _strAnts *listLeft,  _strAnts *listRight, 
	int algorithm, int wValue, int time);


#endif