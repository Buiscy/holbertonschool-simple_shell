#include "main.h"

int main(int ac, char **av)
{
	char *buffer = NULL;
	char *token;
	size_t size = 0;
	ssize_t prompt;
	char *cursor;
	(void)ac;
	while (*av != NULL)
	{
		printf("%s\n", *av);
		av++; 
	}
	printf("$");
	fflush(stdout);
	prompt = getline(&buffer, &size, stdin);

	if (prompt == -1)
	{
		printf("EOF\n");
		free (buffer);
		return (0);
	}
	else
	{
		printf("Inputed line: %s", buffer);
	}

	printf("Tokening;\n");
	token = strtok(buffer, "  \n");
	while(token != NULL)
	{
	printf("%s\n", token);
	token = strtok(NULL, " ");
	}
	
	printf("Inside buffer\n");
	cursor = buffer;
	while (cursor < buffer + prompt)
	{
		printf("%s, ", cursor);
		cursor += strlen(cursor) + 1;
	}
	printf("\n");
	free(buffer);

	return (0);
}