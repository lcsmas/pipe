#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void traitement(){
  printf("L'entier est négatif \n");
}

int main(void) {
  int descr[2];
  int buffer;
  pipe(descr);
  pid_t pid;
  pid = fork();

  if (pid){ /* Processus père */
    close(descr[0]);
    signal(SIGUSR1,traitement);
    int i = 0;
    while(1){
      printf("Veuillez saisir un entier \n");
      scanf("%d", &i);
      write(descr[1], &i, sizeof(int));
      sleep(1);
    }
  } else { /* Processus fils */
    close(descr[1]);
    while(1){
      read(descr[0], &buffer, sizeof(int));
      if(buffer<0){
	kill(getppid(),SIGUSR1);
      }
    }
  }
  return EXIT_SUCCESS; 
}
