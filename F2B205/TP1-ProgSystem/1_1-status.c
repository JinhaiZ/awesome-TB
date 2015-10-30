#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

/* Petite fonction qui se charge d'envoyer les messages d'erreur
   et qui ensuite "suicide" le processus. */

void erreur_grave(char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

/* Fonction principale (fournie avec erreur(s?)) */

int main(int argc, char **argv) {
	struct stat *buffer = malloc(sizeof(struct stat));
	int r;

	//printf("argc=%d\n", argc);
	if (argc != 2){
		fprintf(stderr, "Bad usage : %s <file_path>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	r = stat(argv[1], buffer);
	if (r < 0)
		erreur_grave("Stat");

	struct passwd *pw = getpwuid(buffer->st_uid);
	if (pw == NULL)
		erreur_grave("getpwuid failure");

	printf("Fichier %s:  mode: %X  Taille: %ld  Proprietaire: %s\n",
			argv[1], buffer->st_mode, buffer->st_size, pw->pw_name);

	exit(EXIT_SUCCESS); 
}
