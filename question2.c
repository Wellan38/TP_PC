#include <stdio.h>

#include "primes.h"

/**
 * Print all the prime factors of each numbers
 * in the file numbers.txt, using only one thread.
 */
int main(void)
{
	parsePrimeFile("numbers.txt", print_prime_factors);
    return 0;
}