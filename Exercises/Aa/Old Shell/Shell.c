#include "main.h"

int main(int ac, char **av, char **env)
{
	char *buffer = NULL;

	size_t size = 0;
	ssize_t prompt;

	unsigned int debug_mode = 0; /*Flag var for debug printing commands mode*/
	unsigned int container = 0; /*Flag var for holding within shell */
	unsigned int screen = 0; /*Flag var for skipping banner */
	unsigned int mode = 0; /*Flag for interactive mode checking - 1 is interactive mode*/
	char *args[64];
	int cursor;
	int argc;
	int status = 0; 

	(void)ac;

	if (isatty(0))
	{
		mode = 1;
		printf("\n");
	}

	while (*av != NULL)
	{
		if (strcmp(*av, "-ss") == 0)
		{
			screen++;
		}
		if (strcmp(*av, "-debug") == 0)
		{
			debug_mode = 1;
		}
		av++;
	}
	

	if (screen == 0)
	{
		printbanner(mode);
	}

	while (container == 0)
	{

		printdirect(mode);

		prompt = getline(&buffer, &size, stdin);

		
		if (prompt == -1)
		{
			if (mode == 1)
			{
				printf("EOF\n");
			}
			free (buffer);
			return (status);
		}


		if (buffer[prompt - 1] =='\n')
			buffer[prompt - 1] = '\0';

		if (debug_mode == 1)
		{
			printf("Inputed line: %s\n", buffer);
		}

		argc =	_tokens(buffer, args);
		if (argc != 0)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				container++;
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
				debug_mode = !debug_mode;
				continue;
			}
			status = _procall(args, env);
			if (debug_mode == 1)
			{
				printf("Status code of fork: %i\n", status);
			}
		}
		if (argc == 0)
		{
			continue;
		}

		if (debug_mode == 1)
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

	if (mode == 1)
	{
		printf("exiting shell\n");
	}

	free(buffer);
	return(status);
}

