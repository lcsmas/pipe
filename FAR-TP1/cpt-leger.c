#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 
#define NB_THREADS 10000
int somme=0;
void * Fils(void *t) {
	int i= (long)t;	
	int tmp = somme;
	int a = getpid();
	tmp ++;
	somme = tmp;
	
	printf("Fils %d : somme = %d : pid  = %d \n ", i, somme, a); 
	pthread_exit(0);
}

int main() {
	long i;
	pthread_t thread[NB_THREADS]; 
	for (i=0;i<NB_THREADS;i++)
		pthread_create(&thread[i], NULL, Fils, (void *)i); 
	for (i=0;i<NB_THREADS;i++) 
		pthread_join(thread[i], NULL);
	int a = getpid();
	printf("Pere : somme = %d : pid = %d \n ", somme, a); return 0;
}
