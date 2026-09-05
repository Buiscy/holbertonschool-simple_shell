#include "main.h"

int main(void)
{
	char *line;
	char *token;

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
