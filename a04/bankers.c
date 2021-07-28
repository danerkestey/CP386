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
#include<string.h>
/*  FUNCTION DECLARATIONS   */

//int exit(int *available, int **max, int **allocation, int **need);
typedef struct customer{
	int *allocation;
	int *max;
	int *need;
} customer;

int safetyAlgorithm(int *available, int **max, int **allocation, int **need);
int request(int *available, int **max, int **allocation, int **need);
int release(int *available, int **max, int **allocation, int **need);
void status(int *available, int **max, int **allocation, int **need);
int isdigit();
int *arraySplitter(char* line);
int *fileStats();
int lineLength(char* line);

struct customer *customers;
int customerCount = 0;
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
    int n = 0;           //  number of processes (number of lines in file)
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
//function to create a list of all the customers, each customer contains max, allocation, and need
int fileToCustomer(){
	//create file, as of right now it will only read from sample4_in.txt
	FILE *fp = fopen("sample4_in.txt", "r");
	if(fp == NULL){
		printf("File: sample4_in.txt does not exist");
		return 0;
	}
	//read the file once to figure out the amount of customers
	char line[128];
	while(fgets(line, sizeof(line), fp) != NULL){
		customerCount++;
	}
	//go back to the start of the file using fseek
	fseek(fp, 0, SEEK_SET);
	int index = 0;
	customers = malloc(sizeof(struct customer) * customerCount);
	//read the relevant info from the file, attach it to a customer, and finally append the customer to the customer list
	while(fgets(line, sizeof(line), fp) != NULL){
		struct customer customer;
		int *array = arraySplitter(line);
		customer.max = array;
		customer.allocation = malloc(sizeof(int) * 4);
		customer.need = array;
		customers[index] = customer;
		index++;
	}
	fclose(fp);
	//loop to test if the arrays were filled correctly 
	
	for(int i = 0; i < customerCount; i++){
		for(int k = 0; k < 4; k++){
			printf("%d", customers[i].max[k]);
		}
	}
	
	
}
//function to turn lines read from the file into an array
int *arraySplitter(char* line){
	//create a copy of the input line
	char *copy = strdup(line);
	char *token;
	//initialize an array to store the values
	int *values = malloc(sizeof(int) * 4);

	int index = 0;
	//for each item in line fill the values array with the correct value
	while(token = strsep(&copy, ",")){
		*(values + index) = atoi(token);
		index++;
	}
	return values;
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


    fileToCustomer();
}
