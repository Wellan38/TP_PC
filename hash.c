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
	}
	h->size = size;
	h->decompositions = ar;
	return h;
}

/**
 * Insert a number and his prime factors in a table.
 */
int insert_hash(hash_table* h, uint64_t nb, uint64_t* decomposition, int numberOfFactors)
{
	uint64_t index = hash(h, nb);
	while (h->decompositions[index].status)
    {
    	index = (index + 1) % h->size;
    }
	h->decompositions[index].status = 1;
	h->decompositions[index].number = nb;
	h->decompositions[index].numberOfFactors = numberOfFactors;
	unsigned int i;
	for(i = 0; i<numberOfFactors; i++)
	{
		h->decompositions[index].factors[i] = decomposition[i];
	}
	return index;
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
unsigned int get_decomposition(hash_table* h, uint64_t nb, uint64_t* dec)
{
	uint64_t index = hash(h, nb);
	
	unsigned int cpt = 0;
	char trouve = 1;
	
	while (h->decompositions[index].number != nb && h->decompositions[index].number != 0)
	{
		index = (index  + 1) % h->size;
		cpt++;
		
		if (cpt == h->size)
		{
			trouve = 0;
			break;
		}
	}
	
	if (trouve)
	{
		for(cpt = 0; cpt<h->decompositions[index].numberOfFactors; cpt++)
		{
			dec[cpt] = h->decompositions[index].factors[cpt];
		}
		return h->decompositions[index].numberOfFactors;
	}
	
	else
	{
		dec = NULL;
		return 0;
	}
}

/**
 * Print all numbers in the hash table and their
 * decomposition in prime factors.
 * The shape is : "number: f1, ..., fn".
 */
uint64_t* print_hash(hash_table* h)
{
	unsigned int i;
	unsigned int j;
	for(i=0; i< h->size; i++) {
		if(!h->decompositions[i].status)
		{
			continue;
		}
		printf("%ju:", h->decompositions[i].number);
		for(j = 0; j<h->decompositions[i].numberOfFactors; j++)
		{
			printf(" %ju", h->decompositions[i].factors[j]);
		}
		printf("\n");
	}
}
