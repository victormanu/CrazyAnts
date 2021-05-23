#ifndef _ANTS_H
#define _ANTS_H

#include "threads/CEthread.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	int counterC1L;
	int counterC1R;
	int counterC2L;
	int counterC2R;
	int counterC3L;
	int counterC3R;
	cethread_t readyListC1L[10];
	cethread_t readyListC1R[10];
	cethread_t readyListC2L[10];
	cethread_t readyListC2R[10];
	cethread_t readyListC3L[10];
	cethread_t readyListC3R[10];
} _readyLists; 

_readyLists readyLists;

typedef struct {
    int speed;
    int type;
    int canal;
    int horm;
    int id;
}_strAnts;

typedef struct {
    _strAnts ants[10];
}_strAntsHill;

#endif
