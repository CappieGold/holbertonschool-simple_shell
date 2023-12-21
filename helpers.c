#include "shell.h"

/**
 * free_args - Free the memory allocated for an array of strings.
 * @args: The array of strings to be freed.
 */
void free_args(char **args)
{
	int i = 0;

	if (!args)
	{
		return;
	}

	while (args[i])
	{
		free(args[i]);
		i++;
	}

	free(args);
}
