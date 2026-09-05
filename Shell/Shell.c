#include "main.h"

int main(int ac, char **av, char **env)
{
	char *buffer = NULL;
	(void)ac;
	(void)env;

	size_t size = 0;
	ssize_t prompt;

	int j = 0; //Flag var for holding within shell
	int i = 0; //Flag variable for skipping banner
	char direct_buffer[1024];

	while (*av != NULL)
	{
		if (strcmp(*av, "-ss") == 0)
		{
			i++;
		}
		av++;
	}
	printf("\n");


	if (i == 0)
	{
		printbanner();
		sleep(1);
	}

	while (j == 0)
	{

		if (getcwd(direct_buffer, sizeof(direct_buffer)) != NULL)
		{
			printf("%s$> ", direct_buffer);
			fflush(stdout);
		}

		prompt = getline(&buffer, &size, stdin);

		if (prompt == -1)
		{
			printf("EOF\n");
			free (buffer);
			return (0);
		}

		if (buffer[prompt - 1] =='\n')
			buffer[prompt - 1] = '\0';

		if (strcmp(buffer, "exit") == 0)
		{
			j++;
		}
		if (strcmp(buffer, "clear") == 0)
		{
			printf("\033[2J\033[H\n");
			printf("%s$> ", direct_buffer);
			fflush(stdout);
		}

		printf("Inputed line: %s", buffer);
		fflush(stdout);
		printf("\n");

	}
	free(buffer);
	printf("exiting shell\n");
	return(0);
}
