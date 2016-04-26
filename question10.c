#include <stdio.h>
#include <pthread.h>

#include "primes.h"
#include "hash.h"

/**
 * The size of the global hash map.
 */
#define HASH_SIZE 100

/**
 * The global mutex our functions will use to prevent
 * concurent access to the file we want to parse.
 */
static pthread_mutex_t mutexFile;

/**
 * The global mutex our functions will use to prevent
 * concurent access to the hashmap.
 */
static pthread_mutex_t mutexMap;

/**
 * The global hash table our functions will use.
 */
static hash_table* hashmap;

/**
 * The function which will initialize
 * the global hash table.
 */
static void initHashmap();

/**
 * The function which will destroy
 * the global hash table.
 */
static void destroyHashmap();

/**
 * The function our threads will use.
 */
void* th(FILE* file);

/**
 * Print all the prime factors of each numbers in the
 * file numbers.txt, using the memoization optimization
 * and four worker threads.
 */
int main(void)
{
	pthread_mutex_init(&mutexFile, NULL);
	pthread_mutex_init(&mutexMap, NULL);
	
	initHashmap();
	parsePrimeFileThreaded("numbers.txt", 4, th);
	
	pthread_mutex_destroy(&mutexFile);
	pthread_mutex_destroy(&mutexMap);
	
	destroyHashmap();
	return 0;
}

void* th(FILE* file)
{
	/*uint64_t number = 0;
	
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
    }*/
	pthread_exit(0);
}

void initHashmap() {
	hashmap = create_hash(HASH_SIZE);
}

void destroyHashmap()
{
	delete_hash(hashmap);
}

