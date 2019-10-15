/**
* Name: Marc Julian Jamerlan
* Lab: Lab 9
* Date: 10/23/18
**/

#include "replace.h"

int main(int argc, char **argv)
{
    PAGE *top = NULL;
    int currentPage = 0;
    int faultCount = 0;

    //freopen(argv[1], "r", stdin); // FOR CLION USE

    scanf("%d", &tableSize);
    //printf("\nTable size: %d\n", tableSize); //debug

    // initial read is always a page fault
    scanf("%d", &currentPage);
    top = addPage(top, currentPage);
    printf("*");
    displayTable(top);
    faultCount++;

    while (scanf("%d", &currentPage) == 1 && !feof(stdin))
    {
        if (tableCount < tableSize)
        {
            // fault
            if (lookUp(top, currentPage) < 0)
            {
                addPage(top, currentPage);
                printf("*");
                displayTable(top);
                faultCount++;
            }

            // hit
            else
            {
                top = moveToTop(top, currentPage);
                printf(">");
                displayTable(top);
            }
        }

        // if table is full
        else
        {
            // fault
            if (lookUp(top, currentPage) < 0)
            {
                top = removePage(top);
                if (top == NULL)
                {
                    top = addPage(top, currentPage);
                }
                else
                {
                    addPage(top, currentPage);
                }
                printf("*");
                displayTable(top);
                faultCount++;
            }

            // hit
            else
            {
                top = moveToTop(top, currentPage);
                printf(">");
                displayTable(top);
            }
        }
    }

    printf("Number of faults: %d\n", faultCount);

    freeTable(top);
    return 0;
}

/*
 *  adds a page to the linked list
 *
 */
PAGE *addPage(PAGE *top, int pageNum)
{
    PAGE *page;

    // if top is empty, initialize
    if(top == NULL)
    {
        page = (PAGE *) malloc(sizeof(PAGE));
        page->pageNum = pageNum;
        tableCount++;
    }

    // look for an empty space
    else if (top->next == NULL)
    {
        page = (PAGE *) malloc(sizeof(PAGE));
        top->next = page;

        page->prev = top;
        page->next = NULL;
        page->pageNum = pageNum;
        tableCount++;

        return page;
    }

    else
    {
        page = addPage(top->next, pageNum);
    }

    return page;
}

/*
 *  deletes the top of the linked list (which is the bottom of the stack)
 *
 */
PAGE *removePage(PAGE *top)
{
    PAGE *temp = top;

    top = top->next;
    if (top != NULL)
    {
        top->prev = NULL;
    }
    free(temp);
    tableCount--;

    return top;
}

/*
 *  moves a page to the bottom of the list (which is the top of the stack)
 *
 */
PAGE *moveToTop(PAGE *top, int pageNum)
{
    PAGE *curr;
    PAGE *temp;

    curr = top;

    //traverse to the bottom of the list
    while (top->next != NULL)
    {
        top = top->next;
    }

    // get to the page being referenced
    while (curr->pageNum != pageNum)
    {
        curr = curr->next;
    }

    // if the referenced page is already at the top of the stack, no moving needed
    if (top->pageNum != curr->pageNum)
    {
        // top of the stack is now referenced page
        temp = top;
        top = curr;

        // fill in the gap left by current
        if (curr->prev != NULL)
        {
            curr->prev->next = curr->next;
        }

        if (curr->next != NULL)
        {
            curr->next->prev = curr->prev;
        }

        // put old top of stack below new top of stack
        top->prev = temp;
        top->prev->next = top;
        top->next = NULL;
    }

    // traverse back to the top of the list
    while (top->prev != NULL)
    {
        top = top->prev;
    }

    return top;
}

/*
 *  look for the specified page number in the page table
 *
 */
int lookUp(PAGE *top, int pageNum)
{
    int found = -1;

    while (top != NULL)
    {
        if (top->pageNum == pageNum)
        {
            found = top->pageNum;
            break;
        }

        top = top->next;
    }

    return found;
}

/*
 *  displays the page table bottom-up
 *
 */
void displayTable(PAGE *top)
{
    while (top->next != NULL)
    {
        top = top->next;
    }

    while (top != NULL)
    {
        printf("%d ", top->pageNum);
        top = top->prev;
    }

    printf("\n");
}

/*
 *  free all nodes in the table
 *
 */
void freeTable(PAGE *top)
{
    PAGE *temp;

    while (top != NULL)
    {
        temp = top;
        top = top->next;
        free(temp);
    }
}
