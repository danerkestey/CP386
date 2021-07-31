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
#include <string.h>
/*  FUNCTION DECLARATIONS   */

//int exit(int *available, int **max, int **allocation, int **need);
typedef struct customer
{
    int *allocation;
    int *max;
    int *need;
    int isFinished;
} customer;

int safety(int *available, int n, int m);
int request(int *available, int **max, int **allocation, int **need);
int release(int *available, int **max, int **allocation, int **need);
void status(int *available, int **max, int **allocation, int **need);
int isdigit();
int *arraySplitter(char *line);
int *fileStats();
int lineLength(char *line);

int n; //   number of processes
int m; //   number of resources
struct customer *customers;
int customerCount = 0;
/*
    COMMANDS:
        RQ  -   for requesting resources (remember threads cannot request more than maximum number of resource for that thread)
                the command would fill the allocation array. the customer would  use  ‘RQ’  to  request  for  the  resources  for  all  the customers/thread
                ex: RQ 0 3 1 2 1
        RL  -   for releasing resources -> ex: RL 4 1 2 3 1
        Status   -   would  output  the current  stateof the available, maximum, allocation, and need arrays
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
//function to create a list of all the customers, each customer contains max, allocation, and need
int fileToCustomer()
{
    //create file, as of right now it will only read from sample4_in.txt
    FILE *fp = fopen("sample4_in.txt", "r");
    if (fp == NULL)
    {
        printf("File: sample4_in.txt does not exist");
        return 0;
    }
    //read the file once to figure out the amount of customers
    char line[128];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        customerCount++;
    }
    //go back to the start of the file using fseek
    fseek(fp, 0, SEEK_SET);
    int index = 0;
    customers = malloc(sizeof(struct customer) * customerCount);
    //read the relevant info from the file, attach it to a customer, and finally append the customer to the customer list
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        struct customer customer;
        int *array = arraySplitter(line);
        customer.max = array;
        customer.allocation = malloc(sizeof(int) * 4);
        customer.need = array;
	customer.isFinished = 0;
        customers[index] = customer;
        index++;
    }
    fclose(fp);
    //loop to test if the arrays were filled correctly
/*
    for (int i = 0; i < customerCount; i++)
    {
        for (int k = 0; k < 4; k++)
        {
            printf("%d", customers[i].max[k]);
        }
    }
    */
}
//function to turn lines read from the file into an array
int *arraySplitter(char *line)
{
    //create a copy of the input line
    char *copy = strdup(line);
    char *token;
    //initialize an array to store the values
    int *values = malloc(sizeof(int) * 4);

    int index = 0;
    //for each item in line fill the values array with the correct value
    while (token = strsep(&copy, ","))
    {
        *(values + index) = atoi(token);
        index++;
    }
    return values;
}

/*
    helper method to sum the values in an int array
    ex:
        [1,2,3] -> returns 6
*/
int sumArrayItems(int *array)
{
    int sum = 0;

    if (array == NULL)
    {
        printf("PASSED ARRAY IS NULL");
        return -1;
    }

    for (int i = 0; i < (sizeof(array) / sizeof(int)); i++)
    {
        sum += array[i];
    }

    return sum;
}

/*
    sums the values of two arrays and returns the summed array
    ex:
        [1,1,1] <- array 1
      + [2,2,2] <- array 2
      ---------
      = [3,3,3] <- the return array 
*/
int *sumTwoArrays(int *array1, int *array2)
{
    int arrayLength = (sizeof(array1) / sizeof(int));
    int *sumArray = malloc(sizeof(int) * arrayLength);
    for (int i = 0; i < arrayLength; i++)
    {
        sumArray[i] = array1[i] + array2[i];
    }

    return sumArray;
}

int safety(int *available, int n, int m)
{
    //  (step 1) -> init and set work = available
    int isSafe = 0;                      //  true or false for if the system is safe or not
    int *work;
    work = (int*)malloc(sizeof(int) * m); //  work array to be set to available array
    int isFound = 0;                     //  true or false for if found tmp

    for (int i = 0; i < m; i++) //  loop to init work array to = available
    {

        *(work + i) = available[i];
    }
    for (int i = 0; i < n; i++) //  init finish[i] to false
    {   
        customers[i].isFinished = 0;
       // printf("customers[%d].isFinished = %d", i, customers[i].isFinished);
    }


    for (int i = 0; i < n; i++) //  (step 2) -> find processes to set to true for finish[i]
    {
        struct customer c_process = customers[i];

        //  sum of need[i] array and work array to be used for if statement
        int needSum = sumArrayItems(c_process.need);
        int workSum = sumArrayItems(work);

        if (c_process.isFinished == 0 && (needSum <= workSum)) //  (step 3) if the customer process in the customer array is false and need[i] <= work
        {
            //  work = work + allocation[i] -> finish[i] = true (1)
            work = sumTwoArrays(work, c_process.allocation);
            c_process.isFinished = 1; //  customer process set to true
            customers[i] = c_process;
        }
    }

    int x = 0;

    while (x < n) //  (step 4) finalize and verify all finsih[i] == true and set isSafe to either safe state or not safe
    {
        if (customers[x].isFinished == 1) //  if customer struct in the customer resource array == true -> j++
        {
            x++;
        }

        if (x == n - 1)
        {
            isSafe = 1; //  the system is in a safe state
        }
    }
    return isSafe; //  return final 0 or 1 depending on safe state
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

    int processes[4] = {10, 5, 7,8};

    //  gets number of processes (n) and number of resources (m) from sample4_in.txt
    int *stats;
    stats = fileStats();
    int n = stats[0];
    int m = stats[1];

    printf("Rows = %d\nCols = %d\n", n, m);
    fileToCustomer();
    
    int isSafe = safety(processes, n, m);
    printf("System safe: %d\n", isSafe);
}
