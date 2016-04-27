#include <stdio.h>
#include "hash.h"

/**
 * A prime number used in the hash function.
 */
#define PRIME_HASH 21001

/**
 * Clean a tree used to handle collision
 * in a hash table.
 */
static void cleanTree(hash_box* tree);

/**
 * Return the hash value of a number we want to insert
 * into a specific table (yes, it's table dependant).
 */
inline uint64_t hash(hash_table* h, uint64_t n)
{
    return (n % PRIME_HASH) % h->size;
}

/**
 * Create a new usable hash table.
 */
hash_table* create_hash(unsigned int size)
{
	hash_table* h = malloc(sizeof(hash_table));
	h->size = size;
	h->decompositions = malloc(sizeof(hash_box) * size);
	return h;
}

/**
 * Insert a number and his prime factors in a table.
 */
int insert_hash(hash_table* h, uint64_t nb, uint64_t* decomposition, int numberOfFactors)
{
	uint64_t index = hash(h, nb);
	hash_box* node = &h->decompositions[index];
	if(! h->decompositions[index].status)
	{
		for(;;)
		{
			if(nb == node->number)
			{
				return index;
			}
			else if(nb < node->number)
			{
				node = node->leftNode;
			}
			else
			{
				node = node->rightNode;
			}
			if(! node)
			{
				node = (hash_box*)malloc(sizeof(hash_box*));
				break;
			}
		}
	}
	unsigned int i;
	node->status = 1;
	node->number = nb;
	node->numberOfFactors = numberOfFactors;
	for(i = 0; i< numberOfFactors; i++)
	{
		node->factors[i] = decomposition[i];
	}
	return index;
}

/**
 * Destroy an existing hash table.
 */
void delete_hash(hash_table* h)
{
	unsigned int i;
	for(i = 0; i<h->size; i++)
	{
		if(h->decompositions[i].leftNode)
		{
			cleanTree(h->decompositions[i].leftNode);
		}
		if(h->decompositions[i].rightNode)
		{
			cleanTree(h->decompositions[i].rightNode);
		}
	}
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
	hash_box* node = &h->decompositions[index];
	
	while (node->number != nb && node->number != 0)
	{
		fprintf(stdout, "collision !!!!\n");
		if(nb < node->number && node->leftNode)
		{
			node = node->leftNode;
		}
		if(nb > node->number && node->rightNode)
		{
			node = node->rightNode;
		}
	}
	dec = node->factors;
	return node->numberOfFactors;
}

void cleanTree(hash_box* tree)
{
	if(tree->leftNode)
	{
		cleanTree(tree->leftNode);
	}
	if(tree->rightNode)
	{
		cleanTree(tree->rightNode);
	}
	free(tree);
}
