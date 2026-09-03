#include "main.h"

extern char **environ;

int main(void)
{
	int count;

	count = 0;

	while (environ[count] != NULL)
	{
		printf("%s\n", environ[count]);
		count++;
	}
	return (0);
}
