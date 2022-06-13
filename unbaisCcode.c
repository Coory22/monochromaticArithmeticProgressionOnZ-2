
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdint.h>
#define n  50

uint32_t numofMAP(uint8_t* coloring)
{
	uint32_t count = 0;
	#pragma omp parallel for
	for (int x1 = 0; x1 < n; x1++)
	{
		for (int x2 = 0; x2 < n; x2++)
		{
			if ((((x1 + x2) % 2)) == 0)
			{
				for (int y1 = 0; y1 < n; y1++)
				{
					for (int y2 = 0; y2 < n; y2++)
					{
						if ((((y1 + y2) % 2)) == 0)
						{
							if (coloring[(x1 * n + y1)] == coloring[(((x1 + x2) / 2) * n) + ((y1 + y2) / 2)] && coloring[(x2 * n + y2)] == coloring[(((((x1 + x2) / 2)) * n) + ((y1 + y2) / 2))])
							{
								count = count + 1;
							}
						}
					}
				}
			}
		}
	}
	return count;
}

void swapping(uint8_t* coloring, uint16_t perm[], bool* wasswaped)
{
	#pragma omp parallel for
	for (uint32_t x = 0; x < (uint32_t)n * n; x++)
	{
		uint32_t numofColoring = numofMAP(coloring);
		bool isone = false;
		if (coloring[perm[x]] == 0)
		{
			coloring[perm[x]] = 1;
		}

		else
		{
			coloring[perm[x]] = 0;
			isone = true;
		}
		uint32_t numOfNewColoring = numofMAP(coloring);
		if (numOfNewColoring < numofColoring)
		{
			*wasswaped = true;
			numofColoring = numOfNewColoring;
		}

		else if (isone)
		{
			coloring[perm[x]] = 1;
		}
		else
		{
			coloring[perm[x]] = 0;
		}
		if (x==n-1)
			printf("%d", numofColoring);
	}
}

void printArray(uint16_t arr1[])
{
	printf("[");
	for (uint16_t i = 0; i <(uint16_t) (n * n); i++) {
		printf("%d, ", arr1[i]);
	}
	printf("]\n");
}


void printArray2D(uint8_t* A)
{
	printf("[");
	for (uint8_t i = 0; i < n; i++) {
		printf("[");
		for (uint8_t j = 0; j < n; j++) {
			if (j == n-1) {
				printf("%d ", A[i * n + j]);
			}
			else {
				printf("%d, ", A[i * n + j]);
			}
		}
		if (i == n - 1) {
			printf("]");
		}
		else {
			printf("],");
		}
	}
	printf("]\n");
}


void changeValues(uint16_t* a, uint16_t* b)
{
	uint16_t temp = *a;
	*a = *b;
	*b = temp;
}

void shuffleRandon(uint16_t arr1[])
{
	srand(time(NULL));
	for (uint16_t i = n * n - 1; i > 0; i--)
	{
		uint16_t j = rand() % (i + 1);
		changeValues(&arr1[i], &arr1[j]);
	}
}


int main()
{
	omp_set_num_threads(4);
	time_t startTime, endtime;
	startTime = time(NULL);
	// create a random coloring
	uint8_t* coloring = (uint8_t*)malloc(sizeof(uint8_t) * n * n);

	for (uint8_t i = 0; i < (uint8_t)n; i++)
	{
		for (uint8_t j = 0; j <(uint8_t) n; j++)
		{
			coloring[(int)(i * n + j)] = (uint8_t)(rand() % 2);
		}
	}

	printArray2D(coloring);

	uint16_t* perm = (uint16_t*)malloc(sizeof(uint16_t) * n * n);
	for (uint16_t i = 0; i < (uint16_t)pow(n, 2); i++)
	{
		perm[i] = i;
	}
	shuffleRandon(perm);

	//int permcol[n];
	//for (int i = 0; i < n; i++)
	//{
	//    permcol[i] = i;
	//}
	//shuffleRandon(permcol);

	/*printArray(permcol);*/
	printArray(perm);

	bool wasswaped = true;
	while (wasswaped)
	{
		wasswaped = false;
		swapping(coloring, perm, &wasswaped);
	}


	endtime = time(NULL);
	printArray2D(coloring);
	printf("%f", difftime(endtime, startTime));
	printf("\n%d", numofMAP(coloring));

	return 0;
}
