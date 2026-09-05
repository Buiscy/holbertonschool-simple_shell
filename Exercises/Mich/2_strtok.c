int main(void)
{
	char *line = NULL;
	char *token;
	size_t size = 0;
	ssize_t nread;

	nread = getline(&line, &size, stdin);

	if (nread != -1)
	{
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		token = strtok(line, " \t");

		while (token != NULL)
		{
			printf("%s\n", token);
			token = strtok(NULL, " \t");
		}
	}

	free(line);

	return (0);
}
