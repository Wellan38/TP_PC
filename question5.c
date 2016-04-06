#include <stdio.h>
#include <pthread.h>

#include "primes.h"

void parsePrimeFile(char* filename);
void* th(FILE* file);

static pthread_mutex_t mutex;

int main(void)
{
	pthread_mutex_init(&mutex, NULL);
	parsePrimeFile("numbers.txt");
	
	pthread_mutex_destroy(&mutex);

    return 0;
}

void parsePrimeFile(char* filename)
{
	FILE* file = fopen(filename, "r");
	uint64_t number;
			
	// Création des threads
	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, th, file);
	pthread_create(&thread2, NULL, th, file);

	// Attente de la fin des threads
	char *ret1;
	char *ret2;
	pthread_join(thread1, (void**)&ret1);
	pthread_join(thread2, (void**)&ret2);
	
	fclose(file);
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
