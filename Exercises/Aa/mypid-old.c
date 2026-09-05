#include "main.h"

int main (void)
{
	pid_t my_pid;
	pid_t parent_pid;

	my_pid = getpid();
	parent_pid = getppid();
	
	printf("Current program ID is: %u \n Parrent program ID is: %u \n", my_pid, parent_pid);
	return (0);
}