#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TABSIZE 512

int main() {
	int pid, longueur;
	char tab[TABSIZE], *s;
	int r;

	printf("welcome !\n");
	for (;;) {
		fputs("petit_shell...> ", stdout);	/* Affichage d'un prompt */
		s = fgets(tab, TABSIZE, stdin);

		if (s == NULL) {
			fprintf(stderr, "Fin du Shell\n");
			exit(EXIT_SUCCESS);
		}

		longueur = strlen(s);
		tab[longueur - 1] = '\0';

		pid = fork();
		switch(pid) {
			case -1:	// Error
				fprintf(stderr, "Erreur du Shell\n");
				exit(EXIT_FAILURE);
			case 0:		// We are in the child
				r = execlp(tab, "", NULL);
				if (r == -1) {
					fprintf(stderr, "Erreur de l'execution de la commande\n");
					exit(EXIT_FAILURE);
				}
			default:	// We are still in the father
				wait(NULL);
		}
	}
}
