/**
* Name: Marc Julian Jamerlan
* Lab: Lab 5
* Date: 9/30/18
**/

#include "processQueue.h"

PROCESS *processTable; // an array of all processes
int processTableSize = 0;
//int processTableCapacity = PROCESS_TABLE_CAPACITY;

PROCESS **readyQueue; // an array of pointers to the processes in the processTable
int readyQueueSize = 0;
//int readyQueueCapacity = READY_QUEUE_CAPACITY;

int capacities[2] = {PROCESS_TABLE_CAPACITY, READY_QUEUE_CAPACITY}; // holds capacities of table and queue

// constructor of the process table
void createProcessTable(int capacity)
{
    processTable = (PROCESS *) malloc(capacity * sizeof(PROCESS));
	capacities[0] = capacity;
}

// constructor of the ready queue
void createReadyQueue(int capacity)
{
    readyQueue = (PROCESS **) malloc(capacity * sizeof(PROCESS *));
	capacities[1] = capacity;
}

// adds a process and expands the table if necessary
void addProcessToTable(PROCESS process)
{
    // TODO: complete - done
	// check if table exists
	if(processTable == NULL)
	{
		createProcessTable(capacities[0]);
	}

	// if table is full, reallocate to double the size and initialize new capacity
	if(processTableSize >= capacities[0])
	{
		capacities[0] *= 2;
		processTable = (PROCESS *) realloc(processTable, 
									(capacities[0]) * sizeof(PROCESS));		
	}

	// add process to table and increment size counter
	processTable[processTableSize] = process;
	processTableSize++;
	
	
}

void displayProcessTable()
{
    printf("PROCESSES:\nName    \tEntry\tBurst\n");

    // TODO: complete - done
	for(int i = 0; i < processTableSize; i++)
	{
		printf("%s    \t\t%d    \t%d\n", processTable[i].name, 
									processTable[i].entryTime, 
									processTable[i].burstTime);
	}
    printf("\n");
}

// finds the shortest job in the ready queue and returns its location in the queue
int findShortestJob()
{
    int shortest = INT_MAX;

    // TODO: complete - done
	int index = 0;
	for(int i = 0; i < readyQueueSize; i++)
	{
		if(readyQueue[i]->burstTime < shortest)
		{
			shortest = readyQueue[i]->burstTime;
			index = i;
		}
	}

    return index;
}


// adds any processes that arrive at the current time to the readyQueue
PROCESS * arrivingProcess(int time)
{
    // TODO: complete - done
	PROCESS *arrival = NULL;
	
	for (int i = 0; i < processTableSize; i++)
	{
		if(processTable[i].entryTime == time)
		{
			arrival = &(processTable[i]);
		}
	}
		
    return arrival;
}

// determines if any processes in the process queue have more to execute
bool processesLeftToExecute()
{
    // TODO: complete - done
	for(int i = 0; i < processTableSize; i++)
	{
		if(processTable[i].burstTime > 0) // check processTable burst values
		{
			return true; // returns 1 if there are processes left 
		}
	}

    return false; //return 0 if all processes are complete
}


// adds a pointer and expands the ready queue if necessary
void addProcessToReadyQueue(PROCESS *pointer)
{
    // TODO: complete - done	
	// check if queue exists
	if(readyQueue == NULL)
	{
		createReadyQueue(capacities[1]);
	}

	// if the ready queue is full, reallocate to double the size
	if(readyQueueSize >= capacities[1])
	{
		capacities[1] *= 2;
		readyQueue = (PROCESS **) realloc(readyQueue, 
									(capacities[1]) * sizeof(PROCESS *));
	}
	
	// add process to ready queue and increment size counter
	readyQueue[readyQueueSize] = pointer;
	readyQueueSize++;
}

// exposes a specific process in the ready queue (it stays in the queue)
PROCESS *getProcessFromReadyQueue(int index)
{
    return readyQueue[index];
}

// gets a specific process from the ready queue (it gets removed from the queue)
PROCESS *fetchProcessFromReadyQueue(int index)
{
    PROCESS *proc = readyQueue[index];

    removeProcessFromReadyQueue(index);

    return proc;
}

// removes the process at index from the ready queue and returns a pointer to it
PROCESS *removeProcessFromReadyQueue(int index)
{
    PROCESS *removed = readyQueue[index];

    // TODO: complete - done
	for(int i = index; i < readyQueueSize; i++)
	{
		readyQueue[i] = readyQueue[i + 1]; // move the queue up by 1
	}	

	readyQueueSize--; // decrement the queue size

    return removed;
}

// get size of the ready queue
int getReadyQueueSize()
{
    return readyQueueSize;
}

// displays the contents of the ready queue
void displayQueue()
{
    // TODO: complete - done
	printf("QUEUE: ");
	
	if(readyQueueSize == 0)
	{
		printf("<empty>");
	}
	else
	{
		for(int i = 0; i < readyQueueSize; i++)
		{			
			printf("%s(%d) ", readyQueue[i]->name, readyQueue[i]->burstTime);
		}
	}
}

//calculates the average wait time using information in the proc_queue
//and prints the value.
void printAverageWaitTime()
{
    // TODO: complete - done
	double avg = 0;
	for(int i = 0; i < processTableSize; i++)
	{
		avg += processTable[i].waitTime; // add all wait times from queue
	}

	avg /= processTableSize;

	printf("Average Wait Time: %.2lf time units\n", avg);
}

// clean-up the table and the queue
void cleanUp()
{
    free(processTable);
    free(readyQueue);
}

