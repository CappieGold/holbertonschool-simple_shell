#include "shell.h"

/**
 * find_command_in_path - Search for a cmd in the PATH directories
 * @cmd: the cmd to find
 * Return: Path to the executable if found, otherwise NULL
*/

char *find_command_in_path(const char *cmd)
{
	char *path, *path_copy, *full_path, *token;
	size_t path_lenght, cmd_lenght;

	path = getenv("PATH");
	if (path == NULL)
	{
		perror("getenv");
		return (NULL);
	}
	path_lenght = strlen(path);
	path_copy = malloc(path_lenght + 1);
	if (path_copy == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	strcpy(path_copy, path);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		cmd_lenght = strlen(token) + strlen(cmd) + 2;
		full_path = malloc(cmd_lenght);
		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", token, cmd);
		if (access(full_path, X_OK) == 0)
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
