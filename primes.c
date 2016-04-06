#include <stdio.h>
#include "primes.h"


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
    
	//prime_pair p = fermatFactor(n);
    
	printf("\n");

}

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

int isfactor(uint64_t n, uint64_t factor)
{
	return ! (n%factor);
}

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
    
	//prime_pair p = fermatFactor(n);
}


// TODO(Ruben) mettre parse ici et lui passer une fonction en parametre
