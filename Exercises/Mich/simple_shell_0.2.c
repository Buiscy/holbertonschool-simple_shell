#include "main.h"

int main(void)
{
	char *line;
	char *token;
	char *argv[64];
	int i;
	pid_t pid;
	int status;

	line = read_line();

	while (line != NULL)
	{
		/* Split the command into arguments */
		i = 0;
		token = strtok(line, " \n");

		while (token != NULL && i < 63)
		{
			argv[i] = token;
			i++;
			token = strtok(NULL, " \n");
		}

		argv[i] = NULL;

		/* Check if command is empty */
		if (argv[0] == NULL)
		{
			free(line);
			line = read_line();
			continue;
		}

		/* Create child process */
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			free(line);
			return (1);
		}

		if (pid == 0)
		{
			/* Execute command */
			execve(argv[0], argv, NULL);

			perror("execve");
			free(line);
			return (1);
		}

		/* Parent waits for child */
		wait(&status);

		free(line);
		line = read_line();
	}

	return (0);
}
