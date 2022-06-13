
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define n  40

int numofMAP(int coloring[n][n])
{
    int count = 0;
    #pragma parallel for
    for (int x1 = 0; x1 < n; x1++)
    {
        for (int x2 = 0; x2 < n; x2++)
        {
            if ((x1 + x2) % 2 == 0)
            {
                for (int y1 = 0; y1 < n; y1++)
                {
                    for (int y2 = 0; y2 < n; y2++)
                    {
                        if ((y1 + y2) % 2 == 0)
                        {
                            if (coloring[x1][y1] == coloring[(x1 + x2) / 2][(y1 + y2) / 2] && coloring[x2][y2] == coloring[(x1 + x2) / 2][(y1 + y2) / 2])
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

void swapping(int coloring[n][n], int permrow[n], int permcol[n], bool* wasswaped)
{
    for (int x = 0; x < n; x++)
    {
        int numofColoring = numofMAP(coloring);
        for (int y = 0; y < n; y++)
        {
            bool isone = false;
            if (coloring[permrow[x]][permcol[y]] == 0)
            {
                coloring[permrow[x]][permcol[y]] = 1;
            }

            else
            {
                coloring[permrow[x]][permcol[y]] = 0;
                isone = true;
            }
            int numOfNewColoring = numofMAP(coloring);
            if (numOfNewColoring < numofColoring)
            {
                *wasswaped = true;
                numofColoring = numOfNewColoring;
            }

            else if (isone)
            {
                coloring[permrow[x]][permcol[y]] = 1;
            }
            else
            {
                coloring[permrow[x]][permcol[y]] = 0;
            }
        }
        if (x == n - 1) {
            printf("%d", numofColoring);
        }
    }
    
}

void printArray(int arr1[])
{
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d, ", arr1[i]);
    }
    printf("]\n");
}


void printArray2D(int A[n][n])
{
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("[");
        for (int j = 0; j < n; j++) {
            printf("%d, ", A[i][j]);
        }
        printf("],");
    }
    printf("]\n");
}


void changeValues(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shuffleRandon(int arr1[])
{
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        changeValues(&arr1[i], &arr1[j]);
    }
}


int main()
{
    time_t startTime, endtime;
    startTime = time(NULL);
    // create a random coloring
    int coloring[n][n];
    omp_set_num_threads(4);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            coloring[i][j] = (rand() % 2);
        }
    }

    printArray2D(coloring);

    int permrow[n];
    for (int i = 0; i < n; i++)
    {
        permrow[i] = i;
    }
    shuffleRandon(permrow);

    int permcol[n];
    for (int i = 0; i < n; i++)
    {
        permcol[i] = i;
    }
    shuffleRandon(permcol);

    printArray(permcol);
    printArray(permrow);

    bool wasswaped = true;
    while (wasswaped)
    {
        wasswaped = false;
        swapping(coloring, permrow, permcol, &wasswaped);
    }


    endtime = time(NULL);
    printArray2D(coloring);
    printf("%f", difftime(endtime, startTime));
    printf("\n%d", numofMAP(coloring));

    return 0;
}
