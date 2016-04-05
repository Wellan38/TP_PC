#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

using namespace std;

void* th1( void* );
void* th2( void* );


int main(int argc, char** argv)
{
	srand(time(NULL));
	cout << "Hello world !" << endl;
	
	// Création des threads
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, th1, NULL);
	pthread_create(&thread2, NULL, th2, NULL);
		
	
	// Attente de la fin des threads créés
	int *ret1, *ret2;
	pthread_join(thread1, (void**)&ret1);
	cout << "Le thread 1 a ete arrete avec le code " << *ret1 << endl;
	pthread_join(thread2, (void**)&ret2);
	cout << "Le thread 2 a ete arrete avec le code " << *ret2 << endl;
	
	return 0;
}

void* th1( void* )
{
	sleep(rand()%5);
	cout << "Je suis le thread 1 !" << endl;
	int ret = 1;
	pthread_exit(&ret);
}

void* th2( void* )
{
	sleep(rand()%5);
	cout << "Je suis le thread 2 !" << endl;
	int ret = 2;
	pthread_exit(&ret);
}

