#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/un.h>

#define BUFSIZE 512
#define UNIX_PATH_MAX 108

void communication(int ns, char *message, char *buf, char *host){
	ssize_t nread, nwrite;
	for (;;) {
		nwrite = write(ns, message, strlen(message));
		if (nwrite < 0) {
			perror("write");
			close(ns);
			break;
		}
		nread = read(ns, buf, BUFSIZE);
		if (nread == 0) {
			printf("Fin avec client '%s'\n", host);
			close(ns);
			break;
		} else if (nread < 0) {
			perror("read");
			close(ns);
			break;
		}
		buf[nread] = '\0';
		printf("Message recu '%s'\n", buf);
	}
}

int main(int argc, char **argv) {
	int sfd, s, ns, r;
	char buf[BUFSIZE];
	socklen_t addresslen;
	char host[NI_MAXHOST];
	struct sockaddr_un address;

	char *message = "Message a envoyer: ";

	if (argc != 2) {
		printf("Usage: %s  port_serveur\n", argv[0]);
		exit(EXIT_FAILURE);
	}


	unlink("./demo.socket");

	memset(&address,0,sizeof(struct sockaddr_un));
	address.sun_family = PF_UNIX;
	snprintf(address.sun_path, UNIX_PATH_MAX, "./demo.socket");


	/* getaddrinfo() retourne une liste de structures d'adresses.
	   On essaie chaque adresse jusqu'a ce que bind(2) reussisse.
	   Si socket(2) (ou bind(2)) echoue, on (ferme la socket et on)
	   essaie l'adresse suivante. cf man getaddrinfo(3) */
	//for (rp = result; rp != NULL; rp = rp->ai_next) {

	/* Creation de la socket */
	sfd = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	if (sfd < 0)
		fprintf(stderr,"erreur creation socket");

	/* Association d'un port a la socket */
	r = bind(sfd, (struct sockaddr *) &address, sizeof(struct sockaddr_un));
	if (r != 0){
		fprintf(stderr, "bindinfo: %s\n", gai_strerror(r));
		close(sfd);
	}

	/* Positionnement de la machine a etats TCP sur listen */
	listen(sfd, 5);

	for (;;) {
		/* Acceptation de connexions */
		addresslen = sizeof(address);
		ns = accept(sfd, (struct sockaddr *) &address, &addresslen);
		if (ns == -1) {
			perror("accept");
			exit(EXIT_FAILURE);
		}

		int pid;
		pid = fork();
		switch(pid){
			case -1:
				perror("fork");
				exit(EXIT_FAILURE);
				break;
			case 0:   //Nous sommes dans le fils
				close(sfd);
				s = getnameinfo((struct sockaddr *) &address, addresslen,
						host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
				if (s == 0)
					printf("Debut avec client '%s'\n", host);
				else
					fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
				communication(ns, message, buf, host);
				break;
			default:  //Nous sommes dans le pere
				signal(SIGCLD, SIG_IGN);
				close(ns); 
				break;
		}
	}
}
