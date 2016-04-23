#include <stdint.h>

#define STR_LEN 200

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
void returnPrimeFactors (uint64_t n, char* res);

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
 * Read the file filename and call the function f
 * for each number in this file.
 */
void parsePrimeFile2(char* filename, char* res, void (*f)(uint64_t number, char* res));









