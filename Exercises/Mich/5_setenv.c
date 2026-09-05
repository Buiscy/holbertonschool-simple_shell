#include "main.h"

char *create_env_string(const char *name, const char *value)
{
    char *new_value;
    int i;
    int j;
    int len;

    len = strlen(name) + strlen(value) + 2;

    new_value = malloc(sizeof(char) * len);
    if (new_value == NULL)
        return (NULL);

    i = 0;
    while (name[i] != '\0')
    {
        new_value[i] = name[i];
        i++;
    }

    new_value[i] = '=';
    i++;

    j = 0;
    while (value[j] != '\0')
    {
        new_value[i] = value[j];
        i++;
        j++;
    }

    new_value[i] = '\0';

    return (new_value);
}
