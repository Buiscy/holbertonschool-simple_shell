#include "main.h"

int main(int ac, char **av, char **env)
{
	char *buffer = NULL;
	size_t size = 0;
	ssize_t prompt;

	unsigned int debug_mode = 0;
	unsigned int container = 0;
	unsigned int screen = 0;
	unsigned int mode = 0;

	char *args[64];
	int cursor;
	int argc;
	int status = 0;

	char *path;
	char *directory;
	char *path_copy;
	int env_index;
	char *full_path;
	char *command;
	int found;
	int path_allocated;

	(void)ac;

	if (isatty(0))
	{
		mode = 1;
		printf("\n");
	}

	while (*av != NULL)
	{
		if (strcmp(*av, "-ss") == 0)
		{
			screen++;
		}
		if (strcmp(*av, "-debug") == 0)
		{
			debug_mode = 1;
		}
		av++;
	}

	if (screen == 0)
	{
		printbanner(mode);
	}

	/* Find PATH */
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

	while (container == 0)
	{
		printdirect(mode);

		prompt = getline(&buffer, &size, stdin);

		if (prompt == -1)
		{
			if (mode == 1)
			{
				printf("EOF\n");
			}

			free(buffer);
			return (status);
		}

		if (buffer[prompt - 1] == '\n')
		{
			buffer[prompt - 1] = '\0';
		}

		if (debug_mode == 1)
		{
			printf("Inputed line: %s\n", buffer);
		}

		argc = _tokens(buffer, args);

		if (argc == 0)
		{
			continue;
		}

		/* Builtins */
		if (strcmp(args[0], "exit") == 0)
		{
			container++;
			continue;
		}

		if (strcmp(args[0], "clear") == 0)
		{
			printf("\033[2J\033[H\n");
			fflush(stdout);
			continue;
		}

		if (strcmp(args[0], "cd") == 0)
		{
			_Chdir(args[1], env);
			continue;
		}

		if (strcmp(args[0], "debug") == 0)
		{
			debug_mode = !debug_mode;
			continue;
		}

		/* PATH handling */
		command = args[0];
		found = 0;
		path_allocated = 0;
		full_path = NULL;

		/*
		 * If command contains '/',
		 * use the command directly.
		 */
		if (strchr(command, '/') != NULL)
		{
			if (access(command, X_OK) == 0)
			{
				printf("Found: %s\n", command);
				full_path = command;
				found = 1;
			}
		}
		/*
		 * Otherwise search through PATH.
		 */
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
					found = 1;
					path_allocated = 1;
					break;
				}

				free(full_path);
				full_path = NULL;

				directory = strtok(NULL, ":");
			}

			free(path_copy);
		}

		/*
		 * Only fork if the command was found.
		 */
		if (found == 1)
		{
			status = _procall(full_path, args, env);

			if (debug_mode == 1)
			{
				printf("Status code of fork: %i\n", status);
			}

			if (path_allocated == 1)
			{
				free(full_path);
			}
		}
		else
		{
			fprintf(stderr, "%s: command not found\n", command);
			status = 127;
		}

		/* Debug arguments */
		if (debug_mode == 1)
		{
			printf("args used; %i\n", argc);

			cursor = 0;

			while (cursor < argc)
			{
				printf("%s\n", args[cursor]);
				cursor++;
			}
		}
	}

	if (mode == 1)
	{
		printf("exiting shell\n");
	}

	free(buffer);
	return (status);
}
