#include "main.h"

list_t *build_path_list(void)
{
    char *path;
    char *start;
    char *dir;
    list_t *head;
    list_t *tail;
    list_t *new_node;
    int i;
    int len;

    path = _getenv("PATH");

    if (path == NULL)
        return (NULL);

    head = NULL;
    tail = NULL;
    start = path;
    i = 0;

    while (path[i] != '\0')
    {
        if (path[i] == ':')
        {
            len = &path[i] - start;

            dir = malloc(sizeof(char) * (len + 1));
            if (dir == NULL)
                return (NULL);

            strncpy(dir, start, len);
            dir[len] = '\0';

            new_node = malloc(sizeof(list_t));
            if (new_node == NULL)
            {
                free(dir);
                return (NULL);
            }

            new_node->dir = dir;
            new_node->next = NULL;

            if (head == NULL)
            {
                head = new_node;
                tail = new_node;
            }
            else
            {
                tail->next = new_node;
                tail = new_node;
            }

            start = &path[i + 1];
        }

        i++;
    }

    len = &path[i] - start;

    dir = malloc(sizeof(char) * (len + 1));
    if (dir == NULL)
        return (NULL);

    strncpy(dir, start, len);
    dir[len] = '\0';

    new_node = malloc(sizeof(list_t));
    if (new_node == NULL)
    {
        free(dir);
        return (NULL);
    }

    new_node->dir = dir;
    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        tail->next = new_node;
    }

    tail = new_node;

    return (head);
}

#include "main.h"

int main(void)
{
    list_t *list;

    list = build_path_list();

    while (list != NULL)
    {
        printf("%s\n", list->dir);
        list = list->next;
    }

    return (0);
}
