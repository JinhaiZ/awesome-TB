#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int status;
int fils;

void fin_fils(int n) {
  printf("signal recu %d\n", n);
  fils = wait(&status);
  printf("Fils numero: %d\n", fils);

  if (WIFEXITED(status))
    printf("termine sur exit(%d)\n", WEXITSTATUS(status));

  if (WIFSIGNALED(status))
    printf("termine sur signal : %d\n", WTERMSIG(status));

  exit(EXIT_SUCCESS);			/* pour terminer le pere */
}


void travail() {
  /* Je travaille tres intensement !    */
  /* Ne cherchez pas a comprendre ;-) */
  /* Il n'y a rien a modifier ici     */
  const int width = 70;
  int i, x=0;
  char msg[] = "/\\";
  int incr = +1;

  for (;;) {
    write(STDOUT_FILENO, "\r", 1);
    usleep(50000);
    for (i=0; i<x; i++) write(STDOUT_FILENO, "_", 1);
    write(STDOUT_FILENO, msg, strlen(msg));
    for (i=0; i<width-x; i++) write(STDOUT_FILENO, "_", 1);
    x += incr; 
    if (x == width) incr = -1;
    if (x == 0) incr = +1;
  }
}
void travail() __attribute__((noreturn));
/* Petit raffinement pour le compilateur: cette fonction ne termine pas */


int main(int argc, char **argv) {
  int pid, x;

  if (argc == 2) 
    x = atoi(argv[1]);
      
  else {
    printf("Usage:  %s nombre\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  if ( x < 0 ) {
	  printf("Error: number '%d' need to be positive or null\n", x);
	  exit(EXIT_FAILURE);
  }
  else if ( x > 255) {
	  printf("Error: number '%d' need to be under 255\n", x);
	  exit(EXIT_FAILURE);
  }

  pid = fork();

  if (pid != 0) {	/* Processus Pere */
    signal(SIGCLD, fin_fils);
    travail();
  } else {		/* Processus Fils */
    sleep(10);
    exit(x);
  }
}
