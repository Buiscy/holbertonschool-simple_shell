#include "main.h"

int main(int ac, char **av, char **env)
{
	char *buffer = NULL;

	size_t size = 0;
	ssize_t prompt;
	char *path;
	char *directory;
	char *path_copy;
	int env_index;
	char *full_path;
	char *command;
	int found;

	int j = 0;
	int i = 0;
	char direct_buffer[1024];

	(void)ac;
	(void)av;

	printf("\n");

	if (i == 0)
	{
		printbanner();
		sleep(1);
	}

	env_index = 0;

	while (env[env_index] != NULL)
	{
		if (strncmp(env[env_index], "PATH=", 5) == 0)
		{
			break;
		}
		env_index++;
	}

	if (env[env_index] == NULL)
	{
		printf("PATH not found\n");
		return (1);
	}

	path = env[env_index] + 5;

	while (j == 0)
	{
		if (getcwd(direct_buffer, sizeof(direct_buffer)) != NULL)
		{
			printf("%s$> ", direct_buffer);
			fflush(stdout);
		}

		prompt = getline(&buffer, &size, stdin);

		if (prompt == -1)
		{
			printf("EOF\n");
			free(buffer);
			return (0);
		}

		if (buffer[prompt - 1] == '\n')
			buffer[prompt - 1] = '\0';

		if (buffer[0] == '\0')
			continue;

		if (strcmp(buffer, "exit") == 0)
		{
			j++;
			continue;
		}

		if (strcmp(buffer, "clear") == 0)
		{
			printf("\033[2J\033[H\n");
			printf("%s$> ", direct_buffer);
			fflush(stdout);
		}

		printf("Inputed line: %s", buffer);
		fflush(stdout);
		printf("\n");

		command = buffer;

		found = 0;

		if (strchr(command, '/') != NULL)
		{
			if (access(command, X_OK) == 0)
			{
				printf("Found: %s\n", command);
				found = 1;
			}
		}
		else
		{
			path_copy = malloc(strlen(path) + 1);

			if (path_copy == NULL)

			{
				perror("malloc");
				free(buffer);
				return (1);
			}

			strcpy(path_copy, path);

			directory = strtok(path_copy, ":");

			while (directory != NULL)
			{
				full_path = malloc(strlen(directory) + strlen(command) + 2);

				if (full_path == NULL)
				{
					perror("malloc");
					free(path_copy);
					free(buffer);
					return (1);
				}

				sprintf(full_path, "%s/%s", directory, command);

				if (access(full_path, X_OK) == 0)
				{
					printf("found: %s\n", full_path);
					free(full_path);
					found = 1;
					break;
				}

				free(full_path);

				directory = strtok(NULL, ":");
			}

			if (found == 0)
			{
				printf("Command not found: %s\n", command);
			}

			free(path_copy);
		}
	}
	free(buffer);
	printf("exiting shell\n");
	return (0);
}
