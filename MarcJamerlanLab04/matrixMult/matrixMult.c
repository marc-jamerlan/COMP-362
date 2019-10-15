/**
* Name: Marc Julian Jamerlan
* Lab: Lab 4
* Date: 9/22/18
**/

#include "matrixMult.h"

void free_matrices(int **a, int **b, int **c, int m, int k)
{
	for(int i = 0; i < m; i++)
	{
		free(a[i]);
		free(c[i]);
	}

	for(int i = 0; i < k; i++)
	{
		free(b[i]);
	}

	free(a);
	free(b);
	free(c);
}

int main(int argc, char *argv[])
{
   if (freopen(argv[1], "r", stdin) == 0)
      oops("Cannot open the input file.\n", -1);

   int **a1, **b1, **c1, **a2, **b2, **c2; // matrices
   int m1, k1, n1, m2, k2, n2; // dimensions of the matices m x k and k x m

   allocateAndLoadMatrices(&a1, &b1, &c1, &m1, &k1, &n1);
   allocateAndLoadMatrices(&a2, &b2, &c2, &m2, &k2, &n2);

   // the real magic happens in there

   // TODO: implement the magic - done
	multiply(a1, b1, c1, m1, k1, n1);
	multiply(a2, b2, c2, m2, k2, n2);

   //Dispaly results of matrix multiplication

   printf("\nMATRIX A1\n");
   displayMatrix(a1, m1, k1);
   printf("\nMATRIX B1\n");
   displayMatrix(b1, k1, n1);
   printf("\nMATRIX A1 x B1\n");
   displayMatrix(c1, m1, n1);

   printf("\nMATRIX A2\n");
   displayMatrix(a2, m2, k2);
   printf("\nMATRIX B2\n");
   displayMatrix(b2, k2, n2);
   printf("\nMATRIX A2 x B2\n");
   displayMatrix(c2, m2, n2);

	//free the matrices afterwards
	free_matrices(a1, b1, c1, m1, k1);
	free_matrices(a2, b2, c2, m2, k2);

   return 0;
}

void *matrixThread(void *param)
{
   // map the parameter onto the structure
   struct matrixCell cell = *(struct matrixCell *)param;

   // TODO: implement the magic - done
	// innermost matrix multiplication loop
	for(int z = 0; z < cell.k; z++)
	{
		cell.c[cell.i][cell.j] += cell.a[cell.i][z] * cell.b[z][cell.j];
	}

   return NULL;
}

void allocateAndLoadMatrices(int ***a, int ***b, int ***c, int *m, int *k, int *n)
// takes pointers to two-dimensional matrices, so they can be allocated in here
// and used by the caller
{
   if (scanf("%d %d %d", m, k, n) == 0)
      oops("Cannot read matrix sizes.\n", -2);
	
   // TODO: implement the magic - done

   // allocate rows, A: m x k matrix, B: k x n, C: m x n 
	*a = (int **) malloc(*m * sizeof(int *));		   	
	*b = (int **) malloc(*k * sizeof(int *));
	*c = (int **) malloc(*m * sizeof(int *));

	// since A and C share row value, allocate columns in one loop
	for(int i = 0; i < *m; i++)
	{
		(*a)[i] = (int *) malloc(*k * sizeof(int));
		(*c)[i] = (int *) malloc(*n * sizeof(int));		   
	}		
	
	// allocate B columns
	for(int i = 0; i < *k; i++)
	{
		(*b)[i] = (int *) malloc(*n * sizeof(int));	
	}
	// load the values into the allocated matrices
	loadMatrix(a, *m, *k);
	loadMatrix(b, *k, *n);
}

void loadMatrix(int ***matrix, int m, int n)
{
   // TODO: implement the magic - done
	// take values from stdin
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			scanf("%d", &(*matrix)[i][j]);
		}
	}
}

pthread_t **multiply(int **a, int **b, int **c, int m, int k, int n)
{
   pthread_t **tids = alloc_tids(m, n);

   // TODO: implement the magic - done

	// initialize array of struct matrixCells
	struct matrixCell cell[m][n];
	// main matrix multiplication loop, one thread for each resultant cell
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			// initialize a particular struct matrixCell to pass on to a particular thread
			cell[i][j].i = i; // m
			cell[i][j].j = j; // n
			cell[i][j].k = k; // k, to be looped through in function
			cell[i][j].a = a; 
			cell[i][j].b = b; // a, b, and c are the matrices to be operated on	
			cell[i][j].c = c;
			// create the thread, uses matrixThread function with parameter cell
			pthread_create(&tids[i][j], NULL, matrixThread, &(cell[i][j])); 		
		}		
	}
	//after all threads are done computing, join the threads and free them	
	join(tids, m, n);
	free_tids(tids, m);

   return tids;
}

pthread_t **alloc_tids(int m, int n)
{
   pthread_t **tids;

   // TODO: implement the magic - done
	tids = (pthread_t **) malloc(m * sizeof(pthread_t *));
	
	for(int i = 0; i < m; i++)
	{
		tids[i] = (pthread_t *) malloc(n * sizeof(pthread_t));		
	}
	
   return tids;
}

void free_tids(pthread_t **tids, int m)
{
   // TODO: implement the magic - done
	for(int i = 0; i < m; i++)
	{
		free((void *) tids[i]);
	}

	free(tids);
}

void join(pthread_t **tids, int m, int n)
{
   // TODO: implement the magic - done
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			pthread_join(tids[i][j], NULL);		
		}		
	}
}

void displayMatrix(int **matrix, int m, int n)
{
   // TODO: implement the magic - done
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}	
}
