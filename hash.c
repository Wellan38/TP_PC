#include <stdio.h>
#include "hash.h"

/**
 * Return the hash value of a number we want to insert
 * into a specific table (yes, it's table dependant).
 */
uint64_t hash(hash_table* h, uint64_t n)
{
	n += ~(n << 15);
    n ^= (n >> 10);
    n += (n << 3);
    n ^=  (n >> 6);
    n += ~(n << 11);
    n ^=  (n >> 16);
    
    n %= h->size;
    
    return n;
}

/**
 * Create a new usable hash table.
 */
hash_table* create_hash(unsigned int size)
{
	hash_table* h = malloc(sizeof(hash_table));
	hash_box* ar = malloc(sizeof(hash_box) * size);
	
	uint64_t i;
	
	// TODO : by default, it's 0. We may not wanna lost this time
	for (i = 0; i < size; i++)
	{
		ar[i].status = 0;
		ar[i].number = 0;
		//ar[i].factors = {0};
	}
	h->size = size;
	h->decompositions = ar;
	return h;
}

/**
 * Insert a number and his prime factors in a table.
 */
void insert_hash(hash_table* h, uint64_t nb, uint64_t* decomposition, int numberOfFactors)
{
	uint64_t index = hash(h, nb);
	while (h->decompositions[index].status != 0)
    {
    	index = (index + 1) % h->size;
    }
	int i;
	for(i = 0; i<numberOfFactors; i++) {
		h->decompositions[index].factors[i] = decomposition[i];
	}
	h->decompositions[index].status = 1;
	h->decompositions[index].number = nb;
	h->decompositions[index].numberOfFactors = numberOfFactors;
}

/**
 * Destroy an existing hash table.
 */
void delete_hash(hash_table* h)
{
	free(h->decompositions);
	free(h);
}

/**
 * Return the decomposition in prime factors of
 * the given number.
 */
uint64_t* get_decomposition(hash_table* h, uint64_t nb)
{
	uint64_t index = hash(h, nb);
	
	while (h->decompositions[index].number != nb && h->decompositions[index].number != 0)
	{
		index = (index  + 1) % h->size;
	}
	
	return h->decompositions[index].factors;
}
