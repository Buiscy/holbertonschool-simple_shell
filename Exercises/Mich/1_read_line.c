#include "main.h"

char *read_line(void)
{
	char *buf;
	size_t bufsize;

	buf = NULL;
	bufsize = 0;

	printf("$ ");

	if (getline(&buf, &bufsize, stdin) == -1)
	{
		buf = NULL;
		if (feof(stdin))
		{
			printf("[EOF]\n");
		}
		else
		{
			printf("Error reading line");
		}
	}
	return (buf);
}