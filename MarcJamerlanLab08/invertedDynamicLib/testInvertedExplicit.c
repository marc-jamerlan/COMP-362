/**
* Name: Marc Julian Jamerlan
* Lab: Lab 8 Dynamic Library (explicit)
* Date: 10/19/18
**/

#include "inverted.h"

PROC *table;

int main(int argc, char **argv)
{
	void *dylibHandle;
   	char *error;
   
   	dylibHandle = dlopen ("./libinverted.so", RTLD_LAZY);
   	if (!dylibHandle)
   	{
      	fprintf (stderr, "ERR: %s\n", dlerror());
      	exit(1);
   	}
   	// clear any existing errors
   	dlerror();
	
	void (*initInverted)(PROC **, int, int) = (void (*)(PROC **, int, int)) dlsym(dylibHandle, "initInverted");
	void (*translateProcesses)(PROC *, int, int, int) = (void (*)(PROC *, int, int, int)) dlsym(dylibHandle, "translateProcesses");
	long (*translate)(PROC *, int, int, int) = (long (*)(PROC *, int, int, int)) dlsym(dylibHandle, "translate");

	(*initInverted)(&table, MEM_SIZE, PAGE_SIZE);
	printf("translate(1, 20, 5) = %ld\n", (*translate)(table, 1, 20, 5));	
	(*translateProcesses)(table, NUM_OF_PROC, RAND_RANGE, RAND_RANGE);

 	if ((error = dlerror()) != NULL)
   	{
      	fprintf (stderr, "ERR: %s\n", error);
      	exit(1);
   	}

	dlclose(dylibHandle);
    return 0;
}

