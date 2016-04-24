#include <stdint.h>
#include <string.h>

#ifndef STR_LEN
#define STR_LEN 200
#endif

typedef struct hash_box
{
	short int status; // 0 = empty, 1 = full
	uint32_t number;
	char decomposition[STR_LEN];
} hash_box;

typedef struct hash_table
{
	uint32_t size;
	hash_box* decompositions;
	
} hash_table;

uint32_t hash(hash_table* h, uint32_t n);
hash_table* create_hash(uint32_t size);
void delete_hash(hash_table* h);
void insert_hash(hash_table* h, uint32_t nb, char* decomposition);
char* get_hash(hash_table* h, uint32_t nb);

