#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/un.h>
#define BUFSIZE 512
#define UNIX_PATH_MAX 108

int main(int argc, char **argv) {
	int sfd, r;
	struct sockaddr_un address;
	socklen_t addresslen;
	char buf[BUFSIZE], *pt;
	ssize_t nread, nwrite;

	if (argc != 3) {
		printf("Usage: %s nom_machine_distante port_serveur\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/*
	 * Obtention de l'adresse IP du distant, a partir de son nom par
	 * consultation du fichier /etc/hosts ou de la base hosts des NIS
	 * ou du DNS (Domain Name Service)
	 * cf. man getaddrinfo(3)
	 */

	/* getaddrinfo() retourne une liste de structures d'adresses.
	   On essaie chaque adresse jusqu'a ce que connect(2) reussisse.
	   Si socket(2) (ou connect(2)) echoue, on (ferme la socket et on)
	   essaie l'adresse suivante. cf man getaddrinfo(3) */

	memset(&address, 0, sizeof(struct sockaddr_un));
	address.sun_family = PF_UNIX;
	snprintf(address.sun_path, UNIX_PATH_MAX, "./demo.socket");

	/* Ouverture de la socket */
	sfd = socket(AF_UNIX, SOCK_SEQPACKET, 0); 
	if (sfd < 0)
		printf("socket() failed\n");

	/* Connexion au distant */
	addresslen = sizeof(address);
	r = connect(sfd, (struct sockaddr *)&address, addresslen);
	if (r != 0){
		printf("connect() failed\n");
		close(sfd);
	}


	/* Dans ce qui suit, n'oubliez pas de tester le code de retour des
	 * fonctions utilisees et d'emettre un message d'erreur avec perror(),
	 * puis de sortir avec exit(). */

	/* Boucle de communication */
	for (;;) {
		/* Lecture socket */
		nread = read(sfd, buf, BUFSIZE);
		if (nread == 0) {
			printf("Connexion rompue\n");
			exit(EXIT_SUCCESS);
		} else if (nread < 0) {
			perror("read");
			exit(EXIT_FAILURE);
		}
		buf[nread] = '\0';
		/* Affichage ecran du message lu sur la socket */
		printf("Message recu '%s'", buf);

		/* Lecture clavier. Si on tape <Control-D>, gets() rend NULL
		 * <Control-D> symbolise la fin de fichier, ici la terminaison
		 * du client */
		pt = fgets(buf, BUFSIZE, stdin);
		if (pt == NULL) {
			printf("Sortie du client\n");
			exit(EXIT_SUCCESS);
		}
		nwrite = write(sfd, buf, strlen(buf));
		if (nwrite < 0) {
			perror("write");
			exit(EXIT_FAILURE);
		}
	}
}
