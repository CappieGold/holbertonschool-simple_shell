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
char *duplicate_path(void);
char *build_full_path(const char *directory, const char *cmd);
int is_executable(const char *path);
extern char **environ;

#endif
