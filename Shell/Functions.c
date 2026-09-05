#include "main.h"
void printbanner(void)
{
	printf("███████╗██╗███╗   ███╗██████╗ ██╗     ███████╗    ███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf(	"██╔════╝██║████╗ ████║██╔══██╗██║     ██╔════╝    ██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf(	"███████╗██║██╔████╔██║██████╔╝██║     █████╗      ███████╗███████║█████╗  ██║     ██║     \n");
	printf(	"╚════██║██║██║╚██╔╝██║██╔═══╝ ██║     ██╔══╝      ╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf(	"███████║██║██║ ╚═╝ ██║██║     ███████╗███████╗    ███████║██║  ██║███████╗███████╗███████╗\n");
	printf(	"╚══════╝╚═╝╚═╝     ╚═╝╚═╝     ╚══════╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
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

void printdirect(void)
{
	char direct_buffer[1024];

	if (getcwd(direct_buffer, sizeof(direct_buffer)) != NULL)
	{
		printf("%s$> ", direct_buffer);
		fflush(stdout);
	}
}

void _Chdir(char *path)
{
	if (path == NULL)
	{
		if (chdir("..") == -1)
		{
			printf("CD Error\n");
		}
		return;
	}
	if (chdir(path) == -1)
	{
		printf("CD Error\n");
	}
}

int _procall(char **args, char **env)
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
		if (execve(args[0], args, env) == -1)
		{
			printf("Execve Error\n");
			_exit(1);
		}
	}
	else
	{
		wait(&status);
	}
	return (status);
}