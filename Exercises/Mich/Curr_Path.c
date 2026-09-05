#include "main.h"

int main(int ac, char **av)
{
	char *path;
	char *dir;
	char full_path[1024];
	struct stat st;

	if (ac < 2)
	{
		printf("Usage: %s filename\n", av[0]);
		return (1);
	}

	path = getenv("PATH");

	dir = strtok(path, ":");

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, av[1]);

		if (stat(full_path, &st) == 0)
		{
			printf("%s\n", full_path);
			return (0);
		}

		dir = strtok(NULL, ":");
	}

	return (1);
}
