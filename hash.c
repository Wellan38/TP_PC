#include <stdio.h>
#include "hash.h"

uint32_t hash(hash_table* h, uint32_t n)
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

hash_table* create_hash(uint32_t size)
{
	hash_table* h = malloc(sizeof(hash_table));
	
	hash_box* ar = malloc(sizeof(hash_box) * size);
	
	uint32_t i;
	
	for (i = 0; i < size; i++)
	{
		ar[i].status = 0;
		ar[i].number = 0;
		strcpy(ar[i].decomposition, "");
	}
	
	h->size = size;
	h->decompositions = ar;
	
	return h;
}

void insert_hash(hash_table* h, uint32_t nb, char* decomposition)
{
	uint32_t index = hash(h, nb);
	
	while (h->decompositions[index].status != 0)
    {
    	index = (index + 1) % h->size;
    }

	strcpy(h->decompositions[index].decomposition, decomposition);
	h->decompositions[index].status = 1;
	h->decompositions[index].number = nb;
}

void delete_hash(hash_table* h)
{
	free(h->decompositions);
	free(h);
}

char* get_hash(hash_table* h, uint32_t nb)
{
	uint32_t index = hash(h, nb);
	
	while (h->decompositions[index].number != nb && h->decompositions[index].number != 0)
	{
		index = (index  + 1) % h->size;
	}
	
	return h->decompositions[index].decomposition;
}
