#ifndef _ANTS_H
#define _ANTS_H

#include "threads/CEthread.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ENTER_ASCII_CODE 10

// Calendarizadores
#define PRIORITY  1
#define RR        2
#define FCFS      3
#define SJF       4
#define REAL_TIME 5

// Algortimos de ingreso al canal
#define EQUID 1
#define SIGN  2
#define TICO  3

typedef struct {
    int speed;
    int type;
    int canal;
    int horm;
    int id;
    cethread_t thread;
}_strAnts;

typedef struct {
	int counterC1L;
	int counterC1R;
	int counterC2L;
	int counterC2R;
	int counterC3L;
	int counterC3R;
	_strAnts readyListC1L[10];
	_strAnts readyListC1R[10];
	_strAnts readyListC2L[10];
	_strAnts readyListC2R[10];
	_strAnts readyListC3L[10];
	_strAnts readyListC3R[10];
} _readyLists; 

_readyLists readyLists;

typedef struct {
    _strAnts ants[10];
}_strAntsHill;

#endif
