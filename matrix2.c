#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// compile like:  gcc -Wall -O2 -DNROWS=1000 matrix1.c -o matrix1

#define NCOLS 100

void get_walltime(double *wct) {
	struct timeval tp;
	gettimeofday(&tp,NULL);
	*wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}


int main()
{
	int i, j;	//counters
	double *table;
	double ts,te;
	int error = 0;	//0=FALSE, 1=TRUE
	double elapsed_time;	//used to calculate the time elapsed while accessing the matrix
	
	FILE *table_fptr;	//Pointer to the .csv file "TableValues.csv" where the values of matrix "table" are saved
	table_fptr = fopen("TableValues.csv", "w");
	
	FILE *time_fptr;	//Pointer to the .csv file "ElapsedTime.csv" where the time elapsed while accessing the matrix is saved
	time_fptr = fopen("ElapsedTime.csv", "w");
	
	table = (double *)malloc(NROWS*NCOLS*sizeof(double)); 
	if (table==NULL) {
		printf("alloc error!\n");
		exit(1);
	}



	// warmup - Matrix Initialization

	for(i=0; i<NROWS*NCOLS; i++)
	{
		table[i] = 2;
		
	}
	

//____________________________________________________________________________

  	// get starting time (double, seconds) 
  	get_walltime(&ts);
  
  	// workload

	for(i=0; i<NCOLS; i++)
	{
		for(j=0; j<NROWS; j++)
		{
			table[i+NCOLS*j] = table[i+NCOLS*j] + 3;	// prospelash ANA STHLH
			fprintf(table_fptr, "%lf\n", table[i+NCOLS*j]);	//print in .csv
		}
	}
	
	// get ending time
	get_walltime(&te);
//____________________________________________________________________________
	
	// check results

	for(i=0; i<NROWS*NCOLS; i++)	//Each table cell must have the value 5.	
	{
		
		if(table[i] != 5)	// If not, something must have gone wrong while accessing the table
		{
			error = 1;
		}
	}
	if(error != 0)
	{
		printf("Something went wrong while accessing the table");
	}
	
	
	// print time elapsed and/or Maccesses/sec
	
	elapsed_time = te-ts;	//elapsed_time = ending_time - starting_time
	fprintf(time_fptr, "%lf", elapsed_time);
	printf("\n\nTimeElapsed: %lf\n", elapsed_time);
	
	free(table);
	fclose(table_fptr);
	fclose(time_fptr);

	return 0;
}
