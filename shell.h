#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 100
#define DELIM " \t\n"

extern char **environ;

/**
 * struct builtin_command - Represents a builtin command in the shell.
 * This structure maps a command name to its corresponding function pointer,
 * enabling the shell to execute builtin commands efficiently. It is used to
 * maintain a list of all available builtin commands and their handlers.
 *
 * @command_name: The name of the builtin command.
 * @command_func: Function pointer to the handler of the command.
 */
typedef struct builtin_command
{
	char *command_name;
	int (*command_func)(char **, char *, int *);
} builtins_command_t;

int execute_command(char **args, char **shell_args, int *shell_exit_status);
int execute_builtin_or_command(char **args, char *user_input,
		char **shell_args, int *shell_exit_status);

char *check_command_path(char **command_tokens, char **shell_args);
int check_if_input_is_whitespace(char *user_input);
int is_absolute_or_relative_path(char *path);
char **get_path_directories();
char *build_and_verify_path(char *directory, char *command,
		char *path_separator);

char **tokenize_command_input(char *input_line);
char **tokenize_environment_path(char *path_variable);

int print_environment_variables(char **args, char *user_input,
int *shell_exit);
int exit_shell(char **args, char *user_input, int *shell_exit_status);

char *concatenate_strings(char *first_string, char *second_string);
void *_realloc(void *original_ptr, unsigned int original_size,
				unsigned int new_size);

#endif
