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
	
	uint32_t number;
	char* dec = (char*) malloc(sizeof(char)*STR_LEN);
	
	if (file)
	{
		printf("Fichier ouvert !\n");
		while(!feof(file))
		{
			fscanf(file, "%ld", &number);
			printf("Le nombre lu vaut %ju\n", number);
			returnPrimeFactors(number, dec);
			printf("sa décomposition vaut: ");
			printf(dec);
			insert_hash(h, number, dec);
			printf("\nnombre insere dans la table\n");
		}
	}
	
	uint32_t i;
	
	for (i = 0; i < h->size; i++)
	{
		printf("%ld : %s\n", h->decompositions[i].number, h->decompositions[i].decomposition);
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


