#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
  int descr1[2];
  int descr2[2];
  int buffer[5];
  pipe(descr);
  pid_t pid;
  float moy = 0;
  int compteur = 0;
  pid = fork();
  

  if (pid){ /* Processus père */
    close(descr1[1]);
    close(descr2[0]);
    int i[5] = {1,2,3,4,5};
    int a = write(descr2[1], &i, sizeof(int)*5);  
    //printf ("%d \n", a);
    read(descr[0], &buffer, 5);
    for(int j =0; j++;j<5){
      printf("Chiffre incrémenté : %d", buffer[j]);
    }
     
    close(descr[0]);
    close(descr[1]);
    
  }


  else{ /* Processus fils */
    close(descr1[0]);
    close(descr2[1]);
    
    int a = read(descr[0], &buffer, 5);
    printf("%d \n", a);
    //printf("ntm \n");
    for(int i =0; i++; i<5){
      buffer[i] = buffer[i]+ 1;
    }
    write(descr[1], &buffer, sizeof(int));
    close(descr[1]);
    close(descr[0]);

  }
  
  return EXIT_SUCCESS; 
}
