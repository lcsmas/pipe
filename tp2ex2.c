#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
        pid_t pid;
        int descr1 [2];
        int descr2 [2];
        int ent;
        int entier[5];        
        char buffer [256];
        pipe(descr1);
        pipe(descr2);
        pid = fork();
        if (pid) { /* Processus père */
        	close(descr1[0]);
            close(descr2[1]);
			printf("Saisir 5 entiers :\n");
            for(int i=0;i<5;i++){
    			scanf("%d", &entier[i]);		                
            }
            write(descr1[1], &entier, 5*sizeof(int));
            for(int i=0; i<5; i++){
                read(descr2[0], &entier[i], 5*sizeof(int));
                printf("Entier : %d\n", entier[i]);
            }
        }
        else if(!pid){
            close(descr1[1]);
            close(descr2[0]);
			read(descr1[0], &entier, 5*sizeof(int));
            for(int i=0; i<5; i++) {
                entier[i]++;
            }
            write (descr2[1], &entier, 5*sizeof(int));            
        }
        
        return EXIT_SUCCESS;
}