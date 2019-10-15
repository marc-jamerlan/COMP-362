/**
* Name: Marc Julian Jamerlan
* Lab: Lab 8 No Library
* Date: 10/18/18
**/

#include "inverted.h"

PROC *table;

int main(int argc, char **argv)
{
    initInverted(&table, MEM_SIZE, PAGE_SIZE);
    translateProcesses(table, NUM_OF_PROC, RAND_RANGE, RAND_RANGE);
    return 0;
}
