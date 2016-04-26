#include <stdio.h>
#include <pthread.h>

#include "primes.h"
#include "hash.h"

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
 * but with mutual exclusion for the screen,
 * and use the memoization optimization.
 */
int main(void)
{
	hash_table* h = create_hash(100);
	printf("table creee !\n");
	
	FILE* file = fopen("numbers.txt", "r");
	
	uint64_t number;
	uint64_t numberOfFactors;
	uint64_t* dec = (uint64_t*) malloc(sizeof(uint64_t)*MAX_FACTORS);
	
	if (file)
	{
		printf("Fichier ouvert !\n");
		while(!feof(file))
		{
			fscanf(file, "%ld", &number);
			printf("Le nombre lu vaut %ju\n", number);
			numberOfFactors = get_prime_factors(number, dec);
			printf("sa décomposition vaut: ");
			printf(dec);
			insert_hash(h, number, dec, numberOfFactors);
			printf("\nnombre insere dans la table\n");
		}
	}
	
	unsigned int i;
	unsigned int j;
	
	// TODO : only print numbers for which their is a decomposition
	for (i = 0; i < h->size; i++)
	{
		printf("%ld :", h->decompositions[i].number);
		
		for(j = 0; j<h->decompositions[i].numberOfFactors; j++)
		{
			printf(" %ju", h->decompositions[i].factors);
		}
		printf("\n");
	}
	
	delete_hash(h);
	free(dec);
	fclose(file);
	
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


