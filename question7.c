#include <stdio.h>
#include <pthread.h>

#include "primes.h"

#define MAX_FACTORS 64

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

void print_prime_factors_2(uint64_t n)
{
	uint64_t factors[MAX_FACTORS];
	int j,k;
	k = get_prime_factors(n,factors);
	printf("%ju: ",n);
	for(j=0; j<k; j++)
	{
		printf("%ju ",factors[j]);
	}
	printf("\n");
}

void parsePrimeFile(char* filename)
{
	FILE* file = fopen(filename, "r");
	uint64_t number;
	int car;
	if(file)
	{
		while (1)
		{
			int even = 1;
			
			// Lecture du nombre à décomposer
			fscanf(file, "%ld", &number);
			print_prime_factors_2(number);
			
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

int main(void)
{
	parsePrimeFile("numbers.txt");
	return 0;
}
