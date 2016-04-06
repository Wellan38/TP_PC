#include <stdio.h>

#include "primes.h"

void print_prime_factors(uint64_t n);
void parsePrimeFile(char* filename);

int main(void)
{
    // your code goes  here: open the text file (e.g.  with fopen() ),
    // then read each line (e.g. with fgets() ), turn it into a number
    // (e.g. with atoll() ) and then pass it to print_prime_factors.
	//premier(150);
	
	parsePrimeFile("numbers.txt");

    return 0;
}

void parsePrimeFile(char* filename)
{
	FILE* file = fopen(filename, "r");
	uint64_t number;
	
	while(file)
	{
		
		fscanf(file, "%ld", &number);
		print_prime_factors(number); 
	}
}
