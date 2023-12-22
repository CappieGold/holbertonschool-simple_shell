#include "shell.h"

/**
 * builtin_exit - Exit the shell with a specified status.
 * @args: List of arguments.
 * @line: The input line.
 *
 * Return: Does not return as it exits the shell.
 */
void builtin_exit(char **args, char *line)
{
	int status = args[1] ? my_atoi(args[1]) : EXIT_SUCCESS;

	clean_up(line, args);

	exit(status);
}
