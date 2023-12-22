#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int shell_loop(char *program_name);
char *read_line(void);
char **split_line(char *line);
int execute(char **args, char *program_name, char *line);
void builtin_exit(char **args, char *line);
int builtin_env(char **args);
void free_args(char **args);
int shell_loop(char *program_name);
char *find_command_in_path(char *cmd);
char *my_strcpy(char *dest, const char *src, size_t n);
int is_absolute_or_relative_path(char *path);
void prompt(void);
void clean_up(char *line, char **args);
void signal_handler(int signal);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **resize_tokens(char **tokens, size_t *bufsize);
char *my_strdup(const char *s);
int my_atoi(const char *str);

#endif /* SHELL_H */
