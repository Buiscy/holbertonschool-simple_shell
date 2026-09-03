#include "main.h"

extern char **environ;

char *_getenv(const char *name)
{
	int i;
	int j;

	if (name == NULL || *name == '\0')
	{
		return (NULL);
	}

	i = 0;
	while (environ[i] != NULL)
	{
		j = 0;

		while (name[j] != '\0' && name[j] == environ[i][j])
		{
			j++;
		}

		if (name[j] == '\0' && environ[i][j] == '=')
		{
			return (environ[i] + j + 1);
		}
		i++;
	}
	return (NULL);
}
