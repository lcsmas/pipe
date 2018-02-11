#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
  int descr1[2];
  int descr2[2];
  int buffer[5];
  pipe(descr1);
  pipe(descr2);
  pid_t pid;
  pid = fork();
  

  if (pid){ /* Processus père */
    close(descr1[1]);
    close(descr2[0]);
    int i[5] = {1,2,3,4,5};
    write(descr2[1], &i, 5*sizeof(int));  
    read(descr1[0], &buffer, 5*sizeof(int));
    for(int j =0;j<5;j++){
      printf("Chiffre incrémenté : %d \n", buffer[j]);
    }    
  } else { /* Processus fils */
    close(descr1[0]);
    close(descr2[1]);
    read(descr2[0], &buffer, 5*sizeof(int));
    for(int i =0; i<5;i++ ){
      buffer[i] = buffer[i]+ 1;
    }
    write(descr1[1], &buffer, 5*sizeof(int));
  }
  
  return EXIT_SUCCESS; 
}
