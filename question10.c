#include <stdio.h>
#include <pthread.h>

#include "primes.h"
#include "hash.h"

#define MAX_FACTORS 21

static pthread_mutex_t mutexFile;
static pthread_mutex_t mutexEcran;

int get_prime_factors(uint64_t n, uint64_t* dest)
{
	int cpt = 0;
	
	while( !(n%2) )
	{
		n/=2;
		dest[cpt++] = 2;
	}
	
    uint64_t i;
    for(i = 3; i<= n && cpt < MAX_FACTORS; i+=2)
    {
		if(isfactor(n, i) && isPrime(i))
		{
			double tamp = n/i;
			while( tamp == floor(tamp) )
			{
				dest[cpt++] = i;
				tamp/=i;
			}
		}
	}
	return cpt;
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
	
	hash_table* h = create_hash(11);
	
	uint32_t i;
	
	for (i = 1; i <= 10; i++)
	{
		if (i == 3)
		{
			insert_hash(h, i, "test3");
		}
		else
		{
			insert_hash(h, i, "test");
		}
	}
	
	printf("%s\n", get_hash(h, 5));
	
	delete_hash(h);
	
	return 0;
}


