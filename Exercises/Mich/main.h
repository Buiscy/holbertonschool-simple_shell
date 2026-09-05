#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

typedef struct list_s
{
    char *dir;
    struct list_s *next;
} list_t;

char *read_line(void);
char *_getenv(const char *name);
void print_dir(void);
list_t *build_path_list(void);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

#endif
