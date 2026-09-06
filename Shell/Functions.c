#include "main.h"
void printbanner(unsigned int mode)
{
	if (mode == 1)
	{
		printf("███████╗██╗███╗   ███╗██████╗ ██╗     ███████╗    ███████╗██╗  ██╗███████╗██╗     ██╗     \n");
		printf("██╔════╝██║████╗ ████║██╔══██╗██║     ██╔════╝    ██╔════╝██║  ██║██╔════╝██║     ██║     \n");
		printf("███████╗██║██╔████╔██║██████╔╝██║     █████╗      ███████╗███████║█████╗  ██║     ██║     \n");
		printf("╚════██║██║██║╚██╔╝██║██╔═══╝ ██║     ██╔══╝      ╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
		printf("███████║██║██║ ╚═╝ ██║██║     ███████╗███████╗    ███████║██║  ██║███████╗███████╗███████╗\n");
		printf("╚══════╝╚═╝╚═╝     ╚═╝╚═╝     ╚══════╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	}
}

int _tokens(char *input, char **array)
{
	char *token;
	int i;

	i = 0;

	if (input == NULL)
	{
		printf("No input detected");
		return (0);
	}
	token = strtok(input, " \t");

	while (token != NULL)
	{
		array[i] = token;
		token = strtok(NULL, " \t");
		i++;
	}
	array[i] = NULL;

	return (i);
}

void printdirect(unsigned int mode)
{
	if (mode == 1)
	{
		char direct_buffer[1024];

		if (getcwd(direct_buffer, sizeof(direct_buffer)) != NULL)
		{
			printf("%s$> ", direct_buffer);
			fflush(stdout);
		}
	}
}

void _Chdir(char *path)
{
	if (path == NULL)
	{
		if (chdir("..") == -1)
		{
			printf("Change directory error\n");
		}
		return;
	}
	if (chdir(path) == -1)
	{
		printf("'%s' Path not found\n", path);
	}
}

int _procall(char *full_path, char **args, char **env)
{
	int status;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Error\n");
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(full_path, args, env) == -1)
		{
			printf("Execve Error\n");
			_exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
			return(WEXITSTATUS(status));
	}
	return (1);
}

char *get_path(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);

		i++;
	}

	return (NULL);
}


