/**
* Name: Marc Julian Jamerlan
* Lab: Lab 8 No Library
* Date: 10/18/18
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MEM_SIZE 1024*1024 // original: 1024*1024
#define PAGE_SIZE 4096 // original: 4096
#define NUM_OF_PROC 50 // number of random processes to generate
#define RAND_RANGE 20

typedef struct proc
	{
      int pid;
      int base;
      time_t timeStamp;
	} PROC;

void initInverted(PROC **, int memSize, int frameSize);
void translateProcesses(PROC *table, int numOfProcesses, int numOfPids, int numOfPages);
long translate(PROC *, int, int, int);
//void delay(int seconds);
