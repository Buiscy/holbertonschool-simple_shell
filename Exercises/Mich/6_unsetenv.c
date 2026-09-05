#include "main.h"

/* Access the global environment array */
extern char **environ;

/**
 * _unsetenv - Deletes a variable from the environment
 * @name: The name of the variable to remove
 *
 * Return: 0 on success, -1 on error
 */
int _unsetenv(const char *name)
{
    int i = 0;
    int j;
    size_t len;

    /* 1. Validation checks */
    if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
    {
        return (-1);
    }

    len = strlen(name);

    /* 2. Scan the environment array */
    while (environ[i] != NULL)
    {
        /* Check if the variable starts with 'name' followed by '=' */
        if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
        {
            j = i;

            /* 3. Shift all subsequent pointers left to overwrite the match */
            while (environ[j] != NULL)
            {
                environ[j] = environ[j + 1];
                j++;
            }

            /* Re-check current index since a new element shifted into it */
            continue;
        }

        i++;
    }

    return (0);
}
