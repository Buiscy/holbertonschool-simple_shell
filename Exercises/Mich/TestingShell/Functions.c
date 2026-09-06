#include "main.h"
void printbanner(void)
{
    printf("███████╗██╗███╗   ███╗██████╗ ██╗     ███████╗    ███████╗██╗  ██╗███████╗██╗     ██╗     \n");
    printf("██╔════╝██║████╗ ████║██╔══██╗██║     ██╔════╝    ██╔════╝██║  ██║██╔════╝██║     ██║     \n");
    printf("███████╗██║██╔████╔██║██████╔╝██║     █████╗      ███████╗███████║█████╗  ██║     ██║     \n");
    printf("╚════██║██║██║╚██╔╝██║██╔═══╝ ██║     ██╔══╝      ╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
    printf("███████║██║██║ ╚═╝ ██║██║     ███████╗███████╗    ███████║██║  ██║███████╗███████╗███████╗\n");
    printf("╚══════╝╚═╝╚═╝     ╚═╝╚═╝     ╚══════╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
}

/*
int token(char *line, char *token)
{

    line = read_line();

    if (line != NULL)
    {
        token = strtok(line, " ");

        while (token != NULL)
        {
            printf("%s\n", token);
            token = strtok(NULL, " ");
        }

        free(line);
    }

    return (0);
}
*/

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
