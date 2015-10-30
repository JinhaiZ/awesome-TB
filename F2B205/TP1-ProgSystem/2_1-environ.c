#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	extern char **environ;
	char *env_value;
	int i = 0;

	if (argc == 1){
		while (environ[i] != NULL){
			printf("%s\n", environ[i]);
			i++;
		}

		return EXIT_SUCCESS;
	}
	else if (argc == 2){

		env_value = getenv(argv[1]);

		if (env_value == NULL){
			printf("variable %s inexistante\n", argv[1]);
			return EXIT_FAILURE;
		}

		printf("%s\n", env_value);
		return EXIT_SUCCESS;
	}
	else{

		printf("Bad usage : %s [environment_value]\n", argv[0]);
		return EXIT_FAILURE;
	}
} 
