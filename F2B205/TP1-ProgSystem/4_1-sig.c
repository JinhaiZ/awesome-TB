#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int is_msg_one = 1;

static void pSigHandler_commutation(int n){
	printf("Signal recu : %d\n", n);
	printf("Commutation\n");
	is_msg_one *= -1;
}

static void pSigHandler(int n) {
	printf("Signal recu : %d\n", n);
	if (is_msg_one == 1)
		printf("Message 1\n");
	else
		printf("Message 2\n");
}

void travail() {
	/* Je travaille tres intensement !    */
	/* Ne cherchez pas a comprendre ;-) */
	/* Il n'y a rien a modifier ici     */
	const char msg[] = "-\\|/";
	const int sz = strlen(msg);
	int i = 0;

	for (;;) {
		write(STDOUT_FILENO, "\r", 1);
		usleep(100000);
		write(STDOUT_FILENO, " => ", 4);
		write(STDOUT_FILENO, &msg[i++], 1);
		if (i == sz) i = 0;
	}
}
void travail() __attribute__((noreturn));
/* Petit raffinement pour le compilateur: cette fonction ne termine pas */


int main() {
	printf("PID: %d\n", getpid());

	struct sigaction sa_int, sa_quit;

	memset(&sa_int, 0, sizeof(struct sigaction));
	memset(&sa_quit, 0, sizeof(struct sigaction));

	sa_int.sa_handler = pSigHandler;
	sa_quit.sa_handler = pSigHandler_commutation;

	if (sigaction(SIGINT, &sa_int, NULL) < 0) {
		fprintf(stderr, "sigaction SIGINT error");
		exit(EXIT_FAILURE);
	}

	if (sigaction(SIGQUIT, &sa_quit, NULL) < 0){
		fprintf(stderr, "sigaction SIGQUIT error");
		exit(EXIT_FAILURE);
	}

	travail();

}
