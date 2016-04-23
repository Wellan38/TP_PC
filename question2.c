#include <stdio.h>

#include "primes.h"

int main(void)
{
    // your code goes  here: open the text file (e.g.  with fopen() ),
    // then read each line (e.g. with fgets() ), turn it into a number
    // (e.g. with atoll() ) and then pass it to print_prime_factors.
	//premier(150);
	
	parsePrimeFile("numbers.txt", print_prime_factors);

    return 0;
}