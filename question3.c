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
	int car;
	if(file)
	{
		while (1)
		{
			int even = 1;
			
			// Lecture du nombre à décomposer
			fscanf(file, "%ld", &number1);
			if (feof(file))
			{
				even = 0;
				printf("impair");
			}
			if (even)
			{
				fscanf(file, "%ld", &number2);
			}
					
			// Création des threads
			pthread_t thread1, thread2;
		
			pthread_create(&thread1, NULL, th, number1);
			
			if (even)
			{
				pthread_create(&thread2, NULL, th, number2);
			}

			// Attente de la fin des threads
			char *ret1;
			char *ret2;
			pthread_join(thread1, (void**)&ret1);
			
			if (even)
			{
				pthread_join(thread2, (void**)&ret2);
			}
			
			
			// Affichage du résultat
			printf("%ld:", number1);
			printf(ret1);
			free(ret1);
			
			if (even)
			{
				printf("\n%ld:", number2);
				printf(ret2);
				free(ret2);
			}
			
			printf("\n");
			
			car = getc(file);
			if(car == EOF)
			{
				printf("fin");
				break;
			}
			else ungetc(car, file);
			
		}
	}
}

void* th(uint64_t number)
{
	char* ret = (char*) malloc(sizeof(char)*STR_LEN);
	returnPrimeFactors(number, ret);
	pthread_exit(ret);
}
