#include <stdio.h>
#include <pthread.h>
#include "primes.h"

/**
 * The global mutex our functions will use to prevent
 * concurent access to the file we want to parse.
 */
static pthread_mutex_t mutexFile;

/**
 * The global mutex our functions will use to prevent
 * concurent access to the screen.
 */
static pthread_mutex_t mutexEcran;

/**
 * The function our threads will use.
 */
void* th(FILE* file);

/**
 * Print all the prime factors of each numbers
 * in the file numbers.txt, using two worker threads
 * but with mutual exclusion for the screen.
 */
int main(void)
{
	pthread_mutex_init(&mutexFile, NULL);
	pthread_mutex_init(&mutexEcran, NULL);
		
	parsePrimeFileThreaded("numbers.txt", 2, th);
	
	pthread_mutex_destroy(&mutexFile);
	pthread_mutex_destroy(&mutexEcran);
	
	return 0;
}

void* th(FILE* file)
{
	uint64_t number = 0;
	
	while(!feof(file))
    {
		pthread_mutex_lock(&mutexFile);
			fscanf(file, "%ld", &number);
		pthread_mutex_unlock(&mutexFile);
    	
    	uint64_t factors[MAX_FACTORS];
    	int k = get_prime_factors(number,factors);
    	int j;
    	pthread_mutex_lock(&mutexEcran);
			printf("%ju: ",number);
			for(j=0; j<k; j++)
			{
				printf("%ju ",factors[j]);
			}
			printf("\n");
    	pthread_mutex_unlock(&mutexEcran);
    }
	pthread_exit(0);
}


