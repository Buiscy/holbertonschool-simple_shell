#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void printbanner(void);
void printdirect(void);
int _tokens(char *input, char **array);
void _Chdir(char *path);
int _procall(char **args, char **env);

#endif