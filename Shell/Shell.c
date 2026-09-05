#include "main.h"

int main(int ac, char **av, char **env)
{
	char *buffer = NULL;

	size_t size = 0;
	ssize_t prompt;

	//char *token;
	int j = 0; /*Flag var for holding within shell */
	int i = 0; /*Flag variable for skipping banner */

	(void)ac;
	(void)env;

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

		printdirect();

		prompt = getline(&buffer, &size, stdin);

		if (prompt == -1)
		{
			printf("EOF\n");
			free (buffer);
			return (0);
		}

		printf("Inputed line: %s", buffer);
		fflush(stdout);

		if (buffer[prompt - 1] =='\n')
			buffer[prompt - 1] = '\0';



		if (strcmp(buffer, "exit") == 0)
		{
			j++;
		}
		if (strcmp(buffer, "clear") == 0)
		{
			printf("\033[2J\033[H\n");
			printdirect();
			fflush(stdout);
		}

	}
	free(buffer);
	printf("exiting shell\n");
	return(0);
}
