#include <stdint.h>

#ifndef STR_LEN
#define STR_LEN 200
#endif

typedef struct prime_pair
{
	uint64_t p1;
	uint64_t p2;
} prime_pair;

void print_prime_factors(uint64_t n);
prime_pair fermatFactor(uint64_t n);
int isfactor(uint64_t n, uint64_t factor);
int isPrime(uint64_t n);
void returnPrimeFactors (uint64_t n, char* res);
void premier(uint64_t max);
