#ifndef _ANTS_H
#define _ANTS_H

#include "threads/CEthread.h"
#include "canal.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ENTER_ASCII_CODE 10

#define SIZE_OF_LIST 4

#define ANTS_NUMBER 4
#define LEFT  0
#define RIGHT 1

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

#define QUANTUM 5.7

#define STOP 	0
#define RUNNING 1

typedef struct {
    int speed;
    int type;
    int canal;
    int horm;
    int id;
    int state;
    cethread_t thread;
    float executionTime;
}_strAnts;

typedef struct {
	int counterC1L;
	int counterC1R;
	int counterC2L;
	int counterC2R;
	int counterC3L;
	int counterC3R;
	_strAnts readyListC1L[ANTS_NUMBER];
	_strAnts readyListC1R[ANTS_NUMBER];
	_strAnts readyListC2L[ANTS_NUMBER];
	_strAnts readyListC2R[ANTS_NUMBER];
	_strAnts readyListC3L[ANTS_NUMBER];
	_strAnts readyListC3R[ANTS_NUMBER];
} _readyLists; 

_readyLists readyLists;


int counterAnts;

typedef struct {
    _strAnts ants[20];
}_strAntsHill;

_strAntsHill h1;
_strAntsHill h2;

#endif
