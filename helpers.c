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

/**
 * is_absolute_or_relative_path - Check if a path is absolute or relative.
 * @path: The path to be checked.
 *
 * Return: 1 if the path is absolute or relative, 0 otherwise.
 */
int is_absolute_or_relative_path(char *path)
{
	return (path[0] == '/' || strchr(path, '/'));
}

/**
 * my_strcpy - Copy a string into another, checking for limits.
 * @dest: Destination string.
 * @src: Source string.
 * @n: Maximum size of the destination string.
 *
 * Return: Pointer to the destination string.
 */
char *my_strcpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n - 1 && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';
	return (dest);
}
