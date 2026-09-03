#include "main.h"

int main(void)
{
    int i = 0;
    pid_t pid;
    int status;
    char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};

    while (i < 5)
    {
        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            return (1);
        }

        if (pid == 0)
        {
            execve(argv[0], argv, NULL);
            perror("execve");
            return (1);
        }

        wait(&status);
        i++;
    }

    return (0);
}
