#include "main.h"

int main(int ac, char **av, char **env)
{
	char *buffer = NULL;

	size_t size = 0;
	ssize_t prompt;

	int b = 0; /*Flag var for debug printing commands mode*/
	int j = 0; /*Flag var for holding within shell */
	int i = 1; /*Flag var for skipping banner */
	char *args[32];
	int cursor;
	int argc;
	int status; 

	(void)ac;

	while (*av != NULL)
	{
		if (strcmp(*av, "-ss") == 0)
		{
			i--;
		}
		if (strcmp(*av, "-debug") == 0)
		{
			b++;
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
		if (b == 1)
		{
			printf("Inputed line: %s\n", buffer);
		}

		if (prompt == -1)
		{
			printf("EOF\n");
			free (buffer);
			return (0);
		}

		if (buffer[prompt - 1] =='\n')
			buffer[prompt - 1] = '\0';

		argc =	_tokens(buffer, args);
		if (argc != 0)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				j++;
				continue;
			}
			if (strcmp(args[0], "clear") == 0)
			{
				printf("\033[2J\033[H\n");
				fflush(stdout);
				continue;
			}
			if (strcmp(args[0], "cd") == 0)
			{
				_Chdir(args[1]);
				continue;
			}
			if (strcmp(args[0], "debug") == 0)
			{
				b = b * -1;
				continue;
			}
			status = _procall(args, env);
			if (b == 1)
			{
				printf("Status code of fork: %i\n", status);
			}
		}
		if (argc == 0)
		{
			continue;
		}

		if (b == 1)
		{
			printf("args used; %i\n", argc);
			cursor = 0;
			while (cursor < argc)
			{
				printf("%s\n", args[cursor]);
				cursor++;
			}
		}

	}
	free(buffer);
	printf("exiting shell\n");
	return(0);
}
