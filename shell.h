#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
extern char *program_name;

int shell_loop(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
int builtin_exit(char **args);
int builtin_env(char **args);
void free_args(char **args);

#endif /* SHELL_H */
