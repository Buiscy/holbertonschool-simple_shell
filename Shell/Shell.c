#include "main.h"

int main(int ac, char **av, char **env)
{

	(void)ac;
	(void)env;

	int j = 0; //Flag var for holding within shell
	int i = 0; //Flag variable for skipping banner
	char direct_buffer[1024];

	while (*av != NULL)
	{
		if (strcmp(*av, "-ss") == 0)
		{
			i++;
		}
		av++;
	}
	printf("\n");
	printf("\033[2J\033[H");

	if (i == 0)
	{
		printbanner();
		sleep(1);
	}

	if (getcwd(direct_buffer, sizeof(direct_buffer)) != NULL)
	{
		printf("%s$> ", direct_buffer);
		fflush(stdout);
	}
	while (j == 0)
	{
		
	}
	

	printf("\n");
	return(0);
}