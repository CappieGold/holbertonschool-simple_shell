#include "shell.h"

/**
 * str_concat - Concatenates two strings, allocating necessary space.
 * @s1: First string.
 * @s2: Second string.
 *
 * Return: Pointer to the newly allocated string.
 */
char *str_concat(char *s1, char *s2)
{
	char *result;

	result = malloc(strlen(s1) + strlen(s2) + 1);

	if (result == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	my_strcpy(result, s1, strlen(s1) + 1);
	strcat(result, s2);
	return (result);
}

/**
 * is_executable - Checks if a file exists and can be executed.
 * @path: File path.
 *
 * Return: 1 if the file exists and can be executed, 0 otherwise.
 */
int is_executable(char *path)
{
	return (access(path, X_OK) == 0);
}

/**
 * find_command_in_path - Searches for a command in the
 * directories of the PATH.
 * @cmd: Command to search for.
 *
 * Return: Full path of the command if found, otherwise NULL.
 */
char *find_command_in_path(char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy, *token, *full_path;

	if (path == NULL)
		return (NULL);
	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		char *temp = str_concat(token, "/");

		full_path = str_concat(temp, cmd);
		free(temp);

		if (is_executable(full_path))
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
