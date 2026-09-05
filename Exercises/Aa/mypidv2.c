#include "main.h"

int main (void)
{
	pid_t my_pid;
	pid_t parent_pid;
	pid_t child_pid;

	my_pid = getpid();
	parent_pid = getppid();

	printf("After forking\n");
	child_pid = fork();

	if (child_pid == -1)
		{
			printf("Error while forking\n");
			return(1);
		}
	if (child_pid == 0)
	{
		my_pid = getpid();
		parent_pid = getppid();
		printf("\nChild program:\n");
		printf("Current program ID is: %u \n Parrent program ID is: %u \n", my_pid, parent_pid);
		return (0);
	}
	else
	{
		printf("\nParrent program:\n");
		printf("Current program ID is: %u \n Parrent program ID is: %u \n", my_pid, parent_pid);
	}

	return (0);
}