#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
  int descr[2]; 
  int buffer = 0;
  pipe(descr);
  pid_t pid;
  float moy = 0;
  int compteur = 0;
  pid = fork();
  
  if (pid == 0){ /* Processus fils */
    int i = 0;
    close(descr[0]);
    while( i != -1){
      printf("Entrer un entier \n");
      scanf("%d", &i);
      if(i == -1){
	close(descr[1]);	
      } else{
	write(descr[1], &i, sizeof(int));
      }
     
    }

  }
  
  if (pid != 0){ /* Processus père */
    close(descr[1]);
    int fin = 0;
    while( read(descr[0], &buffer, sizeof(int)) != 0){
      moy = moy+buffer;
      compteur++;      
    }
    close(descr[0]);
    moy = moy / compteur;
    printf("Moyenne : %f \n",moy);
    //    char * result[50];
    
    //sprintf(result,"%f", moy);
    //printf(result); 
  }
  
  return EXIT_SUCCESS; 
}
