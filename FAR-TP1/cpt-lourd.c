#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 
#define NB_PROCESSUS 500 

int pid, i, somme ;
int main()
{ 
	somme = 0 ;
	for (i=0 ; i<NB_PROCESSUS ; i++) { 
		pid=fork();
		if (pid == 0) { 
		  somme++ ;
		  int a = getpid();
		  printf("processus fils %d : somme = %d : pid = %d \n", i, somme, a) ;
		  exit(0) ; 
		}
	}

	while ( wait(0) != -1) { } ;
	int a = getpid();
	printf("processus père : somme = %d : pid = %d \n", somme, a) ; return 0 ;
}
