#include "main.h"
void printbanner(void)
{
	printf("███████╗██╗███╗   ███╗██████╗ ██╗     ███████╗    ███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf(	"██╔════╝██║████╗ ████║██╔══██╗██║     ██╔════╝    ██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf(	"███████╗██║██╔████╔██║██████╔╝██║     █████╗      ███████╗███████║█████╗  ██║     ██║     \n");
	printf(	"╚════██║██║██║╚██╔╝██║██╔═══╝ ██║     ██╔══╝      ╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf(	"███████║██║██║ ╚═╝ ██║██║     ███████╗███████╗    ███████║██║  ██║███████╗███████╗███████╗\n");
	printf(	"╚══════╝╚═╝╚═╝     ╚═╝╚═╝     ╚══════╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
}

/*
int token(char *line, char *token)
{

	line = read_line();

	if (line != NULL)
	{
		token = strtok(line, " ");

		while (token != NULL)
		{
			printf("%s\n", token);
			token = strtok(NULL, " ");
		}

		free(line);
	}

	return (0);
}

int token(char *input, char *token)
{
	char *buffer

	if (input == NULL)
	{
		printf("No input detected");
		continue;
	}
	else
	{
		buffer = strtok(input, token)
	}

	return (0);
}
*/
void printdirect(void)
{
	char direct_buffer[1024];

	if (getcwd(direct_buffer, sizeof(direct_buffer)) != NULL)
	{
		printf("%s$> ", direct_buffer);
		fflush(stdout);
	}
}
