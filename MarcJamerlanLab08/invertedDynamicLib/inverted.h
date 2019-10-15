/**
* Name: Marc Julian Jamerlan
* Lab: Lab 8 Dynamic Library
* Date: 10/19/18
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <dlfcn.h>

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

extern void initInverted(PROC **, int memSize, int frameSize);
extern void translateProcesses(PROC *table, int numOfProcesses, int numOfPids, int numOfPages);
extern long translate(PROC *, int, int, int);
extern void delay(int seconds);
