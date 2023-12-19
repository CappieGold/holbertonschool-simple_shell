#include "shell.h"

/**
 * builtin_exit - Exit the shell with a specified status.
 * @args: List of arguments.
 *
 * Return: Does not return as it exits the shell.
 */
int builtin_exit(char **args)
{
	int status = args[1] ? atoi(args[1]) : EXIT_SUCCESS;

	exit(status);
}
