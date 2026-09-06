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

int _Chdir(char *path, char **env)
{
	int status = 0;
	char **env_ptr;
	char *home;


	home = NULL;

	if (path == NULL)
	{
		env_ptr = env;
		while (*env_ptr != NULL)
		{
			if (strncmp(*env_ptr, "HOME=", 5) == 0)
			{
				home = *env_ptr + 5;
				break;
			}
			env_ptr++;
		}
		if (home != NULL)
		{
			if (chdir(home) == -1)
			{
				printf("Change directory error\n");
				status = -1;
			}
			return (status);
		}
		else
		{
			printf("'HOME' Path not found\n");
			status = -1;
			return (status);
		}
		return (status);
	}
	if (chdir(path) == -1)
	{
		status = -1;
		printf("'%s' Path not found\n", path);
		return (status);
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
			return (WEXITSTATUS(status));
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
