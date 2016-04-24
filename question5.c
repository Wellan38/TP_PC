#include <stdio.h>
#include <pthread.h>

#include "primes.h"

/**
 * The function that our threads will call.
 */
void* th(FILE* file);

/**
 * The global mutex our functions will use to prevent
 * concurent access to the file we want to parse.
 */
static pthread_mutex_t mutex;

/**
 * Print all the prime factors of each numbers
 * in the file numbers.txt, using two worker threads.
 */
int main(void)
{
	pthread_mutex_init(&mutex, NULL);
	parsePrimeFileThreaded("numbers.txt", 2, th);
	pthread_mutex_destroy(&mutex);

    return 0;
}

void* th(FILE* file)
{
	uint64_t number = 0;
	char* ret = (char*) malloc(sizeof(char)*STR_LEN);
	while(!feof(file))
    {
		pthread_mutex_lock(&mutex);
			fscanf(file, "%ld", &number);
		pthread_mutex_unlock(&mutex);
    
    	returnPrimeFactors(number, ret);
    	printf("\n%ld:", number);
		printf(ret);    	
    }
	free(ret);
	pthread_exit(0);
}
