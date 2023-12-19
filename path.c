#include "shell.h"

/**
 * find_command_in_path - Searches for a command
 * in the system's PATH directories.
 * This function attempts to locate the command
 * specified by 'cmd' in the directories
 * listed in the system's PATH environment variable.
 * It checks each directory to see if
 * it contains an executable file matching the command name.
 *
 * @cmd: The command to find in PATH.
 * Return: A dynamically allocated string
 * containing the full path to the executable if found,
 * NULL otherwise.
 */

char *find_command_in_path(const char *cmd)
{
	char *path, *token, *full_path;

	path = duplicate_path();
	if (path == NULL)
		return (NULL);

	token = strtok(path, ":");
	while (token != NULL)
	{
		full_path = build_full_path(token, cmd);
		if (full_path == NULL)
		{
			free(path);
			return (NULL);
		}

		if (is_executable(full_path))
		{
			free(path);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path);
	return (NULL);
}

/**
 * duplicate_path - Creates a duplicate of the PATH environment variable.
 * This function is used to safely work with the PATH variable
 * without altering the original.
 *
 * Return: A dynamically allocated copy of the PATH variable,
 * or NULL on failure.
 */

char *duplicate_path(void)
{
	char *path_copy;
	char *path = getenv("PATH");

	if (path == NULL)
	{
		perror("getenv");
		return (NULL);
	}

	path_copy = malloc(strlen(path) + 1);

	if (path_copy == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	strcpy(path_copy, path);
	return (path_copy);
}

/**
 * build_full_path - Constructs a full file path from a directory
 * and a command name.
 * This function concatenates a directory path
 * and a command name to form a full path.
 *
 * @directory: The directory path.
 * @cmd: The command name.
 * Return: A dynamically allocated string containing the full path,
 * or NULL on failure.
 */

char *build_full_path(const char *directory, const char *cmd)
{
	size_t length = strlen(directory) + strlen(cmd) + 2;

	char *full_path = malloc(length);

	if (full_path == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	sprintf(full_path, "%s/%s", directory, cmd);
	return (full_path);
}

/**
 * is_executable - Checks if a file is executable.
 * This function checks whether the given file path points
 * to an executable file.
 *
 * @path: The path to the file to check.
 * Return: 1 if the file is executable, 0 otherwise.
 */

int is_executable(const char *path)
{
	return (access(path, X_OK) == 0);
}
