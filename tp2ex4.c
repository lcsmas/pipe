#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void traitement (){
    printf("Oups, l'entier est négatif !\n");
}

int main(void) {
        pid_t pid;
        int descr1 [2];
        int descr2 [2];
        int entier;
        int sig=0;        
        char buffer [256];
        pipe(descr1);
        pipe(descr2);
        pid = fork();
        for(;;){
            if (pid) { /* Processus père */
            	close(descr1[0]);
                close(descr2[1]);
    			printf("Saisir un entier :\n");
                scanf("%d", &entier);
                write(descr1[1], &entier,sizeof(int));                
                read(descr2[0], &sig,sizeof(int));
                if(sig)
                    kill(pid, SIGUSR1);
                sleep(1);
            }
            else if(!pid){/* Processus fils */
                close(descr1[1]);
                close(descr2[0]);
    			read(descr1[0], &entier,sizeof(int));
                if(entier<0){
                    signal(SIGUSR1, traitement);
                    sig= SIGUSR1;
                }
                write(descr2[1], &sig,sizeof(int));           
            }
        }
        
        return EXIT_SUCCESS;
}