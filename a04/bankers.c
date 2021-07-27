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

int safetyAlgorithm(int *available, int **max, int **allocation, int **need)
{
}

int request(int *available, int **max, int **allocation, int **need)
{
}

int release(int *available, int **max, int **allocation, int **need)
{
}

void status(int *available, int **max, int **allocation, int **need)
{
}