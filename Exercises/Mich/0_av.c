#include "main.h"

int main(int argc, char *argv[])
{
	int count;

	count = 0;
	(void)argc;

	while (argv[count] != NULL)
	{
		printf("%s\n", argv[count]);
		count++;
	}

	return (0);
}