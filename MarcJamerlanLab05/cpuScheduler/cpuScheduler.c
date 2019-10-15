/**
* Name: Marc Julian Jamerlan
* Lab: Lab 5
* Date: 9/30/18
**/

#include "cpuScheduler.h"

int main()
{
    int time = 0; // simulated time

    ALGORITHM_PARAMS parameters = {NULL, "", NULL, 0, 0, NULL}; // simulation parameters

    // read the algorithm type and time quantum if necessary
    scanf("%s", parameters.algorithm);

    //check which algorithm was passed, set values accordingly
    if (strcmp(parameters.algorithm, "RR") == 0)
    {
        scanf("%d", &parameters.quantum);
        parameters.step = &rrStep;
    }
    else if (strcmp(parameters.algorithm, "FCFS") == 0)
        parameters.step = &fcfsStep;
    else if (strcmp(parameters.algorithm, "SJF") == 0)
        parameters.step = &sjfStep;
    else if (strcmp(parameters.algorithm, "SRTF") == 0)
        parameters.step = &srtfStep;
    else
    {
        printf("The job type input is not a valid input!");
        exit(EXIT_FAILURE);
    }

    // skip over the enf of line marker
    scanf("\n");

    printf("\nALGORITHM: %s", parameters.algorithm);
    if (strcmp(parameters.algorithm, "RR") == 0)
        printf("%3d", parameters.quantum);
    printf("\n\n");

    createProcessTable(PROCESS_TABLE_CAPACITY); //create process table
    createReadyQueue(READY_QUEUE_CAPACITY);//create queue with size == number of processes

    readProcessTable(); //populate process table

    displayProcessTable();

    if ((parameters.newProcess = arrivingProcess(time)) != NULL)
        addProcessToReadyQueue(parameters.newProcess);

    while (processesLeftToExecute())
    {
        parameters.time = time;

        doStep(parameters.step, &parameters);

        displayTimeTick(time, parameters.cpu);

        if (parameters.cpu != NULL)
            parameters.cpu->burstTime--;

        time++;

        if ((parameters.newProcess = arrivingProcess(time)) != NULL)
            addProcessToReadyQueue(parameters.newProcess);
    }

    printAverageWaitTime();

    cleanUp();

    return EXIT_SUCCESS;
}

// step executor
void doStep(void (*func)(void *), void *param)
{
    func(param);
}

// function implementing a step of FCFS
void fcfsStep(void *param)
{
    ALGORITHM_PARAMS *p = (ALGORITHM_PARAMS *) param;
	
	// TODO: implement - done

	// always fetch job from head of the queue 
	if(p->cpu == NULL) // check first if cpu is idle
	{
		if(getReadyQueueSize() > 0) // check if queue has processes first
		{	
			p->cpu = fetchProcessFromReadyQueue(0);
			// if cpu was idle, wait time is always 0
		}
	}

	else // if a process is in cpu
	{
		if((*p->cpu).burstTime == 0) // burst time decremented outside step()
		{
			p->cpu = NULL; // execution done, set to NULL and await another process
			
			// check immediately if there is a new process in the queue
			if(getReadyQueueSize() > 0) 
			{
				p->cpu = fetchProcessFromReadyQueue(0); 
				// wait time is current time minus entry time
				(*p->cpu).waitTime = (p->time - (*p->cpu).entryTime);
			}
		}
	}
}

// function implementing a step of SJF
void sjfStep(void *param)
{
    ALGORITHM_PARAMS *p = (ALGORITHM_PARAMS *) param;

    // TODO: implement - done

	// find the shortest job in the queue and fetch it; cannot interrupt job
	if(p->cpu == NULL) // check first if cpu is idle
	{
		if(getReadyQueueSize() > 0) // check if queue has processes first
		{	
			p->cpu = fetchProcessFromReadyQueue(findShortestJob());
			// if cpu was idle, wait time is always 0
		}
	}

	else // if a process is in cpu
	{
		if((*p->cpu).burstTime == 0) // burst time decremented outside step()
		{
			p->cpu = NULL; // execution done, set to NULL and await another process
			
			// check immediately if there is a new process in the queue
			if(getReadyQueueSize() > 0) 
			{
				p->cpu = fetchProcessFromReadyQueue(findShortestJob()); 
				// wait time is current time minus entry time
				(*p->cpu).waitTime = (p->time - (*p->cpu).entryTime);
			}
		}
	}
}

// function implementing a step of SRTF
void srtfStep(void *param)
{
    ALGORITHM_PARAMS *p = (ALGORITHM_PARAMS *) param;

    // TODO: implement - done

	// like SJF, but allows interrupting a job if a shorter job arrives
	if(p->cpu == NULL) // check first if cpu is idle
	{
		if(getReadyQueueSize() > 0) // check if queue has processes first
		{
			p->cpu = fetchProcessFromReadyQueue(findShortestJob());
			// if cpu was idle, wait time is always 0
		}
	}
	
	else // if a process is in cpu
	{
		if(getReadyQueueSize() > 0) // check first if queue is empty
		{
			// if a shorter job exists, interrupt current job and execute the shorter job
			if((*p->cpu).burstTime > getProcessFromReadyQueue(findShortestJob())->burstTime)
			{
				(*p->cpu).offTime = p->time - 1; // set off time before interrupt
				addProcessToReadyQueue(p->cpu); // put current process back into queue
				p->cpu = fetchProcessFromReadyQueue(findShortestJob());  
				// account for off time if the process was interrupted
				(*p->cpu).waitTime += p->time - (*p->cpu).entryTime - (*p->cpu).offTime;
			}
		}
		
		if((*p->cpu).burstTime == 0) // burst time decremented outside step()
		{
			p->cpu = NULL; // execution done, set to NULL and await another process		
			
			// check immediately if there is a new process in the queue
			if(getReadyQueueSize() > 0)
			{	
				p->cpu = fetchProcessFromReadyQueue(findShortestJob());
				// account for off time if the process was interrupted
				(*p->cpu).waitTime += p->time - (*p->cpu).entryTime - (*p->cpu).offTime;
			}
		}
	}
}

// function implementing a step of RR
void rrStep(void *param)
{
    ALGORITHM_PARAMS *p = (ALGORITHM_PARAMS *) param;

    static int rrCounter; // counter to keep track of how many more ticks the process in cpu has left (count down from quantum)

	// TODO: implement - implement wait time calculation

	// each process can only execute for a set amount of time; interrupted if not finished
	if(p->cpu == NULL) // check first if cpu is idle
	{
		if(getReadyQueueSize() > 0) // check if queue has processes first
		{
			p->cpu = fetchProcessFromReadyQueue(0);
			rrCounter = p->quantum; // initialize counter to quantum
			// if cpu was idle, wait time is always 0
			rrCounter--; 
		}
	}
	
	else // if a process is in cpu
	{
		if((*p->cpu).burstTime == 0) // burst time decremented outside step()
		{
			p->cpu = NULL; // execution done, set to NULL and await another process
			
			// check immediately if there is a new process in the queue
			if(getReadyQueueSize() > 0)
			{
				p->cpu = fetchProcessFromReadyQueue(0);
				rrCounter = p->quantum; // reset counter
				(*p->cpu).waitTime += p->time - (*p->cpu).offTime;
			}	
		}	
		
		// if the time limit is over, reset counter and fetch a new job
		if(rrCounter == 0)
		{
			(*p->cpu).offTime = p->time;
			addProcessToReadyQueue(p->cpu); // put current process back into queue
			p->cpu = fetchProcessFromReadyQueue(0);
			rrCounter = p->quantum; // reset counter
			(*p->cpu).waitTime += p->time - (*p->cpu).offTime;
		}

		rrCounter--; 
	}
}

//fills the processTable with processes from input
int readProcessTable()
{
    PROCESS tempProcess = {"", 0, 0, 0, 0};

    char *line = NULL;
    char *currPos;
    size_t len = 0;

    int counter = 0;
    int offset = 0;

    while (getline(&line, &len, stdin) != -1)
    {
        currPos = line;
        sscanf(currPos, "%s%n", tempProcess.name, &offset);
        currPos += offset;
        sscanf(currPos, "%d%n", &tempProcess.entryTime, &offset);
        currPos += offset;
        sscanf(currPos, "%d", &tempProcess.burstTime);

        addProcessToTable(tempProcess);

        free(line);
        line = NULL;

        counter++;
    }

    free(line);

    return counter;
}

void displayTimeTick(int time, PROCESS *cpu)
{
    printf("T%d:\nCPU: ", time);
    if (cpu == NULL)
        printf("<idle>\n");
    else
        printf("%s(%d)\n", cpu->name, cpu->burstTime);

    displayQueue();
    printf("\n\n");
}






