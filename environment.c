#include "shell.h"

/**
 * builtin_env - Display the environment.
 * @args: List of arguments (unused).
 *
 * Return: Always 1 to continue the shell.
 */
int builtin_env(char **args)
{
	int i;
	(void)args;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}

	return (1);
}
