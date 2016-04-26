#include <stdio.h>
#include <pthread.h>

#include "primes.h"
#include "hash.h"

static pthread_mutex_t mutexFile;
static pthread_mutex_t mutexEcran;

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

void print_prime_factors_2(char* filename)
{
	FILE* file = fopen(filename, "r");	
	
	pthread_t t1, t2;
	
	pthread_create(&t1, NULL, th, file);
	pthread_create(&t2, NULL, th, file);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	fclose(file);
}

int main(void)
{
	/*
	pthread_mutex_init(&mutexFile, NULL);
	pthread_mutex_init(&mutexEcran, NULL);
	
	char* filename = "numbers.txt";
	
	print_prime_factors_2(filename);
	
	pthread_mutex_destroy(&mutexFile);
	pthread_mutex_destroy(&mutexEcran);
	*/
	
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
	
	//free(dec);
	
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


