#ifndef PRIMES_H
#define PRIMES_H

#include <stdint.h>
#include <stdio.h>

/**
 * The maximum length of the string that
 * our functions use.
 */
#ifndef STR_LEN
	#define STR_LEN 200
#endif

/**
 * The maximum number of prime factors that an integer
 * coded on 64 bits can have.
 */
#ifndef MAX_FACTORS
	#define MAX_FACTORS 64
#endif

/**
 * This structure define a couple of prime numbers.
 */
typedef struct prime_pair
{
	uint64_t p1;
	uint64_t p2;
} prime_pair;

/**
 * Print all prime factors of the integer n.
 */
void print_prime_factors(uint64_t n);

/**
 * ?
 */
// prime_pair fermatFactor(uint64_t n);

/**
 * Return true only if the given interger n is
 * divisible by the integer factor.
 */
int isfactor(uint64_t n, uint64_t factor);

/**
 * Return true only if the given integer n is
 * a prime number.
 */
int isPrime(uint64_t n);

/**
 * Return all the primes factors of n in the string res.
 */
void returnPrimeFactors(uint64_t n, char* res);

/**
 * Return all the primes factors of n in the array dest.
 */
int get_prime_factors(uint64_t n, uint64_t* dest);

/**
 * Print all prime numbers lower than max.
 */
void premier(uint64_t max);

/**
 * Read the file filename and call the function f
 * for each number in this file.
 */
void parsePrimeFile(char* filename, void (*f)(uint64_t number));

/**
 * Read the file filename use numberOfThreads threads
 * which call the function threadFunction.
 */
void parsePrimeFileThreaded(char* filename, int numberOfThreads, void (*threadFunction)(FILE* file));

#endif







