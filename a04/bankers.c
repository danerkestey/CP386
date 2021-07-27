/*
--------------------------------------------------
Project: CP386-assignment 4
File:    bankers.c
Author:  Daner Yasin     | 190773490
         Jacob Goldman   | 190509690
Version: 2021-07-26
--------------------------------------------------
*/

/*  IMPORTS  */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

/*  FUNCTION DECLARATIONS   */

//int exit(int *available, int **max, int **allocation, int **need);
int safetyAlgorithm(int *available, int **max, int **allocation, int **need);
int request(int *available, int **max, int **allocation, int **need);
int release(int *available, int **max, int **allocation, int **need);
void status(int *available, int **max, int **allocation, int **need);
int isdigit();

int *fileStats();

/*
    COMMANDS:
        RQ  -   for requesting resources (remember threads cannot request more than maximum number of resource for that thread)
                the command would fill the allocation array. the customer would  use  ‘RQ’  to  request  for  the  resources  for  all  the customers/thread
                ex: RQ 0 3 1 2 1

        RL  -   for releasing resources -> ex: RL 4 1 2 3 1

        *   -   would  output  the current  stateof the available, maximum, allocation, and need arrays

        Run -   find the safe sequence and run each thread
                The command would execute the safe sequence based on the current state and all the threads would be run same function code and prints
*/

/*
   used for finding number of processes and resources in the sample file
   Returns [n, m] || [processes, resources] 
*/
int *fileStats()
{
    static int stats[2]; //  returns n and m from sample file in list type-> [n, m] || [rows, columns] || [processes, resources]
    int n = 1;           //  number of processes (number of lines in file)
    int m = 0;           //  number of resources (number of columns in file)
    char c;              //  for storing each char read from file

    FILE *fp;

    fp = fopen("sample4_in.txt", "r");

    if (fp == NULL)
    {
        printf("File: sample4_in.txt does not exist");
        return 0;
    }

    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '\n') //  if current char in file is a new line -> n++ (row++)
            n++;

        if (n == 1 && isdigit(c)) //  if first line and char is a digit (not ,) and not new line char -> m++ (column++)
            m++;
    }

    fclose(fp);

    stats[0] = n;
    stats[1] = m;

    return stats;
}

/*
int exit(int *available, int **max, int **allocation, int **need)
{
    return 0;
}
*/

//  grant a request, if it does leave the system in a safe state, otherwisewill deny it.
int safetyAlgorithm(int *available, int **max, int **allocation, int **need)
{
    return 0;
}

//  return 0 if successful, 01 if unsuccessful
int request(int *available, int **max, int **allocation, int **need)
{
    return 0;
}

int release(int *available, int **max, int **allocation, int **need)
{
    return 0;
}

void status(int *available, int **max, int **allocation, int **need)
{
    return;
}

int main(int argc, char *argv[])
{
    /*
    int available[argc - 1];
    for (int i = 0; i < argc; i++)
    {
        char *c;
        int num = strtol(argv[i + 1], &c, 10);
        available[i] = num;
    }
    */

    //  gets number of processes (n) and number of resources (m) from sample4_in.txt
    int *stats;
    stats = fileStats();
    int n = stats[0];
    int m = stats[1];

    //printf("\nRows = %d\nCols = %d", n, m);

    //  init arrays
    int *available[m];
    int *max[n * m];
    int *allocation[n * m];
    int *need[n * m];
}