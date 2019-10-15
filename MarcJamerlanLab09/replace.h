/**
* Name: Marc Julian Jamerlan
* Lab: Lab 9
* Date: 10/23/18
**/

#include <stdio.h>
#include <stdlib.h>

typedef struct page
{
    struct page *prev;
    struct page *next;
    int pageNum;
} PAGE;

int tableSize = 0; // maximum table size
int tableCount = 0; // count of pages in table; cannot exceed tableSize

PAGE *addPage(PAGE *top, int pageNum);
PAGE *removePage(PAGE *top);
PAGE *moveToTop(PAGE *top, int pageNum);
int lookUp(PAGE *top, int pageNum);
void displayTable(PAGE *top);
void freeTable(PAGE *top);
