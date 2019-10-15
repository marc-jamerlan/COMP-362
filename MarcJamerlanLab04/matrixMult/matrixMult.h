/**
* Name: Marc Julian Jamerlan
* Lab: Lab 4
* Date: 9/22/18
**/

#ifndef __MATRIX_MULT_H_
#define __MATRIX_MULT_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define oops(errmsg, err) { perror(errmsg); exit(err); }

// struct for passing indices to the threads
struct matrixCell
{
   int i; // resultant row
   int j; // resultant column 
   int k; // common
   int **a; //2D arrays 
   int **b;
   int **c;
};

void *matrixThread(void *);
void allocateAndLoadMatrices(int ** *, int ** *, int ** *, int *, int *, int *);
void loadMatrix(int ** *, int, int);
pthread_t **alloc_tids(int, int);
void free_tids(pthread_t **, int);
pthread_t **multiply(int **, int **, int **, int, int, int);
void join(pthread_t **, int, int);
void displayMatrix(int **, int, int);

#endif
