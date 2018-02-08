#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
        pid_t pid;
        int descr [2];
        int entier;
        int somme = 0;
        int resaisie = 1;
        int count = 0;
        char buffer [256];
        pipe(descr);
        pid = fork();
        if (pid == 0) { /* Processus fils */
        	close(descr[0]);
			while(resaisie){
				count++;
				printf("Saisir un entier :\n");
				scanf("%d", &entier);
				somme+=entier;
            	printf("Effectuer une autre saisie ? (1 : true/ 0 : false) :\n");
            	scanf("%d", &resaisie);
			}
			write(descr[1], &count, sizeof(int));
			write(descr[1], &somme, sizeof(int));
            write(descr[1], &entier, sizeof(int));
        }
        else if(pid!=0){
			read(descr[0], &entier, sizeof(int));
			read(descr[0], &somme, sizeof(int));
			read(descr[0], &count, sizeof(int));
			float moyenne = (float)somme/(float)entier;
			printf("Somme : %d\n Dernier entier reçu : %d\n Nombre d'entiers reçus : %d\n Moyenne des entiers reçus %f\n",somme, count, entier, moyenne);
        }
        return EXIT_SUCCESS;
}
