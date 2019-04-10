// C program to illustrate Banker's Algorithm 
/*
Written By:

Shirisha Vadlamudi
Peter Kemper

*/


#include <stdbool.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4



// Function to find the need of each process 
void calculateNeed(int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES], int maxm[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES],
	int allot[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES])
{
	// Calculating Need of each P 
	int i,j;
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
		for (j = 0; j < NUMBER_OF_RESOURCES; j++)

			// Need of instance = maxm instance - 
			//				 allocated instance 
			need[i][j] = maxm[i][j] - allot[i][j];
}

// Function to find the system is in safe state or not 
bool isSafe(int processes[], int avail[], int maxm[][NUMBER_OF_RESOURCES],
	int allot[][NUMBER_OF_RESOURCES])
{
	int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

	// Function to calculate need matrix 
	calculateNeed(need, maxm, allot);

	// Mark all processes as infinish 
	bool finish[NUMBER_OF_CUSTOMERS] = { 0 };

	// To store safe sequence 
	int safeSeq[NUMBER_OF_CUSTOMERS];

	// Make a copy of available resources 
	int work[NUMBER_OF_RESOURCES];
	int i;
	for (i = 0; i < NUMBER_OF_RESOURCES; i++)
		work[i] = avail[i];

	// While all processes are not finished 
	// or system is not in safe state. 
	int count = 0;
	while (count < NUMBER_OF_CUSTOMERS)
	{
		// Find a process which is not finish and 
		// whose needs can be satisfied with current 
		// work[] resources. 
		bool found = false;
		int p;
		for (p = 0; p < NUMBER_OF_CUSTOMERS; p++)
		{
			// First check if a process is finished, 
			// if no, go for next condition 
			if (finish[p] == 0)
			{
				// Check if for all resources of 
				// current P need is less 
				// than work 
				int j;
				for (j = 0; j < NUMBER_OF_RESOURCES; j++)
					if (need[p][j] > work[j])
						break;

				// If all needs of p were satisfied. 
				if (j == NUMBER_OF_RESOURCES)
				{
					// Add the allocated resources of 
					// current P to the available/work 
					// resources i.e.free the resources 
					int k;
					for (k = 0; k < NUMBER_OF_RESOURCES; k++)
						work[k] += allot[p][k];

					// Add this process to safe sequence. 
					safeSeq[count++] = p;

					// Mark this p as finished 
					finish[p] = 1;

					found = true;
				}
			}
		}

		// If we could not find a next process in safe 
		// sequence. 
		if (found == false)
		{
			printf("System is not in safe state");
			return false;
		}
	}

	// If system is in safe state then 
	// safe sequence will be as below 
	printf("System is in safe state.\nSafe"
		" sequence is: ");
	for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
		printf(safeSeq[i]);
		printf(" ");
	return true;
}

// Driver code 
int main()
{
	int processes[] = { 0, 1, 2, 3, 4 };

	// Available instances of resources 
	int avail[] = { 3, 3, 2 };

	// Maximum R that can be allocated 
	// to processes 
	int maxm[][NUMBER_OF_RESOURCES] = { {7, 5, 3},
					{3, 2, 2},
					{9, 0, 2},
					{2, 2, 2},
					{4, 3, 3} };

	// Resources allocated to processes 
	int allot[][NUMBER_OF_RESOURCES] = { {0, 1, 0},
					{2, 0, 0},
					{3, 0, 2},
					{2, 1, 1},
					{0, 0, 2} };

	// Check system is in safe state or not 
	isSafe(processes, avail, maxm, allot);

	return 0;
}
