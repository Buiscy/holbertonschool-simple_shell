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
char *get_path(char **env);
int _tokens(char *input, char **array);
void printdirect(unsigned int mode);
void _Chdir(char *directory);
int _procall(char *full_path, char **args, char **env);

#endif