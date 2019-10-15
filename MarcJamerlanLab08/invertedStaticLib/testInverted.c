/**
* Name: Marc Julian Jamerlan
* Lab: Lab 8 Static Library
* Date: 10/19/18
**/

#include "inverted.h"

PROC *table;

int main(int argc, char **argv)
{
    initInverted(&table, MEM_SIZE, PAGE_SIZE);
	printf("translate(1, 20, 5) = %ld\n", translate(table, 1, 20, 5));
    translateProcesses(table, NUM_OF_PROC, RAND_RANGE, RAND_RANGE);
    return 0;
}
