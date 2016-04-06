#include <stdio.h>
#include <pthread.h>

#include "primes.h"

#define MAX_FACTORS 21

int get_prime_factors(uint64_t n, uint64_t* dest)
{
	int cpt = 0;
	
	while( !(n%2) )
	{
		n/=2;
		dest[cpt++] = 2;
	}
	
    uint64_t i;
    for(i = 3; i<= n; i+=2)
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

int main(void)
{
	print_prime_factors_2(876578);
	return 0;
}
