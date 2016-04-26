#include <stdio.h>
#include <pthread.h>
#include "primes.h"

/**
 * Print all prime factors of the integer n.
 */
 
void print_prime_factors(uint64_t n)
{
	printf("%ld:", n);
	while( !(n%2) )
	{
		n/=2;
		printf(" 2");
	}
    uint64_t i;
    for(i = 3; i<= n; i++)
    {
		if(isfactor(n, i) && isPrime(i))
		{
			double tamp = n/i;
			while( tamp == floor(tamp) )
			{
				printf(" %ld", i);
				tamp/=i;
			}
		} 
	}    
	printf("\n");
}

/**
 * Return true only if the given integer n is
 * a prime number.
 */
int isPrime(uint64_t n)
{
	uint64_t i;
	if( n <= 3 && n )
	{
		return 1;
	}
	if( !(n%2) || !(n%3) )
	{
		return 0;
	}
	for(i=5; i<= sqrt(n); i+=2)
	{
		if(isfactor(n, i))
		{
			return 0;
		}
	}
	return 1;
}

/**
 * Return true only if the given interger n is
 * divisible by the integer factor.
 */
int isfactor(uint64_t n, uint64_t factor)
{
	return ! (n%factor);
}

/**
 * ?
 */
prime_pair fermatFactor(uint64_t n)
{
	uint64_t a = ceil(sqrt(n));
	uint64_t b2 = a*a - n;
	
	double b = sqrt(b2);
	while( (uint64_t)b - b )
	{
		a++;
		b2 = a*a - n;
		b = sqrt(b2);
	} 
	
	prime_pair pp;
	pp.p1 = a - (uint64_t)b;
	pp.p2 = a + (uint64_t)b;
	
	return pp;
}

/**
 * Print all prime numbers lower than max.
 */
void premier(uint64_t max)
{
	uint64_t* m = (uint64_t*)malloc(sizeof(uint64_t)*(max/3));
	uint64_t* p = (uint64_t*)malloc(sizeof(uint64_t)*(max/3));
	uint64_t sommet = 1;
	uint64_t essai;
	
	m[0] = 25;
	p[0] = 5;
	
	uint64_t pasi = 4;
	uint64_t i, j;
	for(i=7; i< max; i+= pasi, pasi =6- pasi)
	{
		for(essai = p[j=0]; (i != m[j]) && (essai*essai < i); essai = p[j++])
		{
			if(i>m[j])
			{
				m[j] += 2*essai;
			}
		}
		if(i != m[j])
		{
			printf("%ld\n", i);
			p[sommet] = i;
			m[sommet++] = i*i;
		}
	}
	
	free(p);
	free(m);
}

/**
 * Return all the primes factors of n in the string res.
 */
void returnPrimeFactors (uint64_t n, char* res)
{
	char nb [STR_LEN];
	
	sprintf(nb, "");
	sprintf(res, "");
	
	while( !(n%2) )
	{
		n/=2;
		sprintf(nb, " 2");
		strcat(res, nb);
	}
    uint64_t i;
    for(i = 3; i<= n; i++)
    {
		if(isfactor(n, i) && isPrime(i))
		{
			double tamp = n/i;
			while( tamp == floor(tamp) )
			{
				sprintf(nb, " %ld", i);
				strcat(res, nb);
				tamp/=i;
			}
		}
	}
 }
 
 /**
 * Read the file filename and call the function f
 * for each number in this file.
 */
void parsePrimeFile(char* filename, void (*f)(uint64_t number))
{
	FILE* file = fopen(filename, "r");
	uint64_t number;
	char car;
	if(file)
	{
		while (!feof(file))
		{
			fscanf(file, "%ld", &number);
			(*f)(number);
			
			if((car = getc(file)) == EOF)
			{
				break;	//  Avoid some problems
			}
			else ungetc(car, file);
		}
	}
	fclose(file);
}

/**
 * Read the file filename use numberOfThreads threads
 * which call the function threadFunction.
 */
void parsePrimeFileThreaded(char* filename, int numberOfThreads, void (*threadFunction)(FILE* file))
{
	FILE* file = fopen(filename, "r");
			
	// Création des threads
	pthread_t* threads = (pthread_t*)malloc(numberOfThreads*sizeof(pthread_t));
	char** ret = (char**)malloc(numberOfThreads*sizeof(char*));
	int i;
	
	for(i = 0; i< numberOfThreads; i++) {
		pthread_create(threads + i, NULL, threadFunction, file);
	}
	
	// Attente de la fin des threads
	for(i = 0; i< numberOfThreads; i++) {
		pthread_join(*(threads+i), (void**)(ret+i));
	}
		
	fclose(file);
	free(threads);
	free(ret);
}

/**
 * Return all the primes factors of n in the array dest.
 */
int get_prime_factors(uint64_t n, uint64_t* dest)
{
	int cpt = 0;
	
	while( !(n%2) )
	{
		n/=2;
		dest[cpt++] = 2;
	}
	
    uint64_t i;
    for(i = 3; i<= n && cpt < MAX_FACTORS; i+=2)
    {
		if(isfactor(n, i) && isPrime(i))
		{
			double tamp = n/i;
			while( tamp == floor(tamp) )
			{
				dest[cpt++] = i;
				tamp/=i;
			}
		}
	}
	return cpt;
}
