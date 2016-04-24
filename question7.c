#include <stdio.h>
#include <pthread.h>
#include "primes.h"

/**
 * The new function that print prime factors of
 * an integer n, but before store them in an array.
 */
void print_prime_factors_memory(uint64_t n);

/**
 * Print all the prime factors of each numbers
 * in the file numbers.txt, using only one thread.
 */
int main(void)
{
	parsePrimeFile("numbers.txt", print_prime_factors_memory);
	return 0;
}

void print_prime_factors_memory(uint64_t n)
{
	uint64_t factors[MAX_FACTORS];
	int j,k;
	k = get_prime_factors(n, factors);
	printf("%ju: ",n);
	for(j=0; j<k; j++)
	{
		printf("%ju ",factors[j]);
	}
	printf("\n");
}
