/*
--------------------------------------------------
Project: CP386-assignment 4
File:    bankers.c
Author:  Daner Yasin     | 190773490
         Jacob Goldman   | 190509690
Version: 2021-07-26
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int exit(int *available, int **max, int **allocation, int **need);
int safetyAlgorithm(int *available, int **max, int **allocation, int **need);
int request(int *available, int **max, int **allocation, int **need);
int release(int *available, int **max, int **allocation, int **need);
void status(int *available, int **max, int **allocation, int **need);

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

int main(int argc, char *argv[])
{
    int available[argc - 1];
    for (int i = 0; i < argc; i++)
    {
        char *c;
        int num = strtol(argv[i + 1], &c, 10);
        available[i] = num;
    }
}

int exit(int *available, int **max, int **allocation, int **need)
{
}

//  grant a request, if itdoes leave the system in a safe state, otherwisewill deny it.
int safetyAlgorithm(int *available, int **max, int **allocation, int **need)
{
}

//  return 0 if successful, 01 if unsuccessful
int request(int *available, int **max, int **allocation, int **need)
{
}

int release(int *available, int **max, int **allocation, int **need)
{
}

void status(int *available, int **max, int **allocation, int **need)
{
}