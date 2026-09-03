#include "main.h"

void print_dir(void)
{
    char *path;
    int i;

    path = _getenv("PATH");

    if (path == NULL)
    {
        return;
    }

    i = 0;

    while (path[i] != '\0')
    {
        if (path[i] == ':')
        {
            printf("\n");
        }
        else
        {
            printf("%c", path[i]);
        }
        i++;
    }

    printf("\n");
}
