#include <stdio.h>
#include <pthread.h>

#include "primes.h"

void parsePrimeFile(char* filename);
void* th(uint64_t number);

int main(void)
{
    // your code goes  here: open the text file (e.g.  with fopen() ),
    // then read each line (e.g. with fgets() ), turn it into a number
    // (e.g. with atoll() ) and then pass it to print_prime_factors.
	//premier(150);
	
	parsePrimeFile("numbers.txt");

    return 0;
}

void parsePrimeFile(char* filename)
{
	FILE* file = fopen(filename, "r");
	uint64_t number1, number2;
	
	if(file)
	{
		while (!feof(file))
		{
			// Lecture du nombre à décomposer
			fscanf(file, "%ld", &number1);
			fscanf(file, "%ld", &number2);
		
			// Création des threads
			pthread_t thread1, thread2;
		
			pthread_create(&thread1, NULL, th(number1), NULL);
			pthread_create(&thread2, NULL, th(number2), NULL);
		
			// Attente de la fin des threads
			int *ret1, *ret2;
			pthread_join(thread1, (void**)&ret1);
			pthread_join(thread2, (void**)&ret2);
		}
	}
}

void* th(uint64_t number)
{
	print_prime_factors(number);
	
	int ret = 1;
	pthread_exit(&ret);
}
