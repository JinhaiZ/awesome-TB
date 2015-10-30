#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sig_handler(int n) {
	printf("signal sigcld recu\n");
	int status;
	int pid = wait(&status);
	printf("processus %d killed by :\n", pid);
	
	if (WIFEXITED(status))
		printf("\texit\n");
	if (WIFSIGNALED(status))
		printf("\tsignal\n");
	if (WIFSTOPPED(status))
		printf("\tstop\n");
}

void travail() {
	/* Je travaille tres intensement !    */
	/* Ne cherchez pas a comprendre ;-) */
	/* Il n'y a rien a modifier ici     */
	for (;;) {
		printf("%s", random() > RAND_MAX>>1 ? "." : "\b \b");
		fflush(stdout);
		usleep(100000);
	}
}
void travail() __attribute__((noreturn));
/* Petit raffinement pour le compilateur: cette fonction ne termine pas */


int main() {
	int pid = fork();

	if (pid != 0) {	/* Processus Pere */
		
		// The father need to treat the death of the child
		// Either by an handler
		signal(SIGCLD, sig_handler);       
		// Either by a SIG_IGN
		//signal(SIGCLD, SIG_IGN);
		travail();

	} else {		/* Processus Fils */
		sleep(10);
		printf("Ahrg!!! je suis le fils et je meurs\n");
		exit(EXIT_SUCCESS);
	}
}
