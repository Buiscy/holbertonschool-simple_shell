#include "main.h"

int main (void)
{
	int i;
	int status;
	pid_t my_pid;
	pid_t pid;
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	extern char **environ;

	printf("Begining check loop\n");

	my_pid = getpid();
	i = 0;
	while (i < 5)
	{
		printf("ID is: %i\n", my_pid);
		sleep(1);
		pid = fork();
		if (pid == -1)
		{
			printf("Error\n");
			return (1);
		}

		if (pid == 0)
		{
			my_pid = getpid();
			printf("Child ID is; %i\n", my_pid);
			if (execve(argv[0], argv, environ) == -1)
			{
				printf("Execve Error\n");
			}
			return (1);
		}
		else
		{
			wait(&status);
			printf("Child complete\n");
		}
		sleep(1);
		++i;
	}
	return (0);
}