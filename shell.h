#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *cmd);
char *find_command_in_path(const char *cmd);
void tokenize_command(char *cmd, char *argv[], int *argc);
void handle_builtin_commands(char *argv[]);
int execute_full_path_command(char *argv[]);
int execute_path_command(char *argv[]);
extern char **environ;

#endif
