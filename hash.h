#include <stdint.h>
#include <string.h>

#include "primes.h"

/**
 * A box in which our map will store a number
 * and his known prime factors.
 */
typedef struct hash_box
{
	int status;							// Wheter the box is empty (0) or not (1)
	uint64_t number;						// The number we have decomposed into prime factors
	uint64_t* factors;			// The decomposition in prime factors
	unsigned int numberOfFactors;					// The number of prime factors
} hash_box;

/**
 * The structure of an hash table.
 */
typedef struct hash_table
{
	unsigned int size;
	hash_box* decompositions;
	
} hash_table;

/**
 * Return the hash value of a number we want to insert
 * into a specific table (yes, it's table dependant).
 */
uint64_t hash(hash_table* h, uint64_t n);

/**
 * Create a new usable hash table.
 */
hash_table* create_hash(unsigned int size);

/**
 * Destroy an existing hash table.
 */
void delete_hash(hash_table* h);

/**
 * Insert a number and his prime factors in a table.
 */
int insert_hash(hash_table* h, uint64_t nb, uint64_t* decomposition, int numberOfFactors);

/**
 * Return the decomposition in prime factors of
 * the given number.
 */
unsigned int get_decomposition(hash_table* h, uint64_t nb, uint64_t* dec);

