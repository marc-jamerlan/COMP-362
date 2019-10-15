/**
* Name: Marc Julian Jamerlan
* Lab: Lab 8 No Library
* Date: 10/18/18
**/

#include "inverted.h"

//long translate(PROC *, int, int, int);
long lookUp(PROC *, int, int);
long findOldest(PROC *table);
//void delay(int seconds);

int tableSize = 0;
int pageSize = 0;

/*
 * initializes the table for the given sizes of the memory and frame
 */
void initInverted(PROC **table, int msize, int fsize)
{
    // TODO: implement - done
    *table = (PROC *) calloc(msize / fsize, sizeof(PROC));
	tableSize = msize / fsize;
	pageSize = fsize;
}

/*
 * translates a specified number of random processes
 */
void translateProcesses(PROC *table, int numOfProcesses, int numOfPids, int numOfPages)
{
    int pid, page, offset;

    srand((unsigned) time(NULL));

    for (int i = 0; i < numOfProcesses; i++)
    {
        pid = rand() / (RAND_MAX / (numOfPids + 1) + 1);
        page = rand() / (RAND_MAX / (numOfPages + 1) + 1);
        offset = rand() / (RAND_MAX / pageSize + 1);

        printf("translate(%d, %d, %d) = %ld\n", pid, page, offset, translate(table, pid, page, offset));
        //delay(1);
    }

    /* printf("translate(1, 20, 5) = %ld\n", translate(table, 1, 20, 5));
     printf("translate(1, 10, 0) = %ld\n", translate(table, 1, 10, 0));
     printf("translate(1, 20, 7) = %ld\n", translate(table, 1, 20, 7));
     printf("translate(1, 10, 12) = %ld\n", translate(table, 1, 10, 12));
     printf("translate(2, 5, 15) = %ld\n", translate(table, 2, 5, 15));
     delay(1); // for testing
     printf("translate(1, 10, 8) = %ld\n", translate(table, 1, 10, 8));
     printf("translate(1, 20, 1) = %ld\n", translate(table, 1, 20, 1));
     printf("translate(1, 8, 0) = %ld\n", translate(table, 1, 8, 0));*/
}

/*
 * translate a logical address <pid, page, offset> into a physical address
 * if there is no entry for the pid and the page number in the table, it has to be added
 * if there is no room in the table for the new entry, then the oldest entry has to be removed
 */
long translate(PROC *table, int pid, int page, int offset)
{
    // TODO: implement - done

    long foundPage = lookUp(table, pid, page);
    long oldest;

    // if it doesn't exist, add it
    if (foundPage < 0)
    {
        // if the table is full
        if (table[tableSize - 1].timeStamp != 0)
        {
            oldest = findOldest(table);
            for (int i = 0; i < tableSize; i++)
            {
                if (table[i].timeStamp == oldest)
                {
                    table[i].timeStamp = 0;
                    break;
                }
            }
        }

        // add to the table
        for (int i = 0; i < tableSize; i++)
        {
            if (table[i].timeStamp == 0)
            {
                table[i].pid = pid;
                table[i].base = page;
                time(&table[i].timeStamp);
                //printf("%d %d %d %ld\n", i, table[i].pid, table[i].base, table[i].timeStamp); //DEBUG
                foundPage = i;
                break;
            }
        }
    }

    // physical address = index * pageSize + offset
    return foundPage * pageSize + offset;
}

/*
 * find the entry in the table for a specific pid and page
 */
long lookUp(PROC *table, int pid, int page)
{
    long i = -1;

    // TODO: implement - done

    for (int j = 0; j < tableSize; j++)
    {
        if (table[j].pid == pid && table[j].base == page)
        {
            // if it was found, then it was referenced, update time accordingly
            time(&table[j].timeStamp);
            i = j;
            break;
        }
    }

    return i;
}

/*
 * find the oldest entry in the table
 */
long findOldest(PROC *table)
{
    long min = LONG_MAX;

    // TODO: implement - done
    for (int i = 0; i < tableSize; i++)
    {
        if (table[i].timeStamp < min)
        {
            min = table[i].timeStamp;
        }
    }

    return min;
}

/*
 * delays the execution of the program for a specified amount of seconds
 */
/*void delay(int seconds)
{
    clock_t startTime = clock();
    long microSeconds = seconds * CLOCKS_PER_SEC;

    while (clock() < startTime + microSeconds)
    { ;
    }
}*/


