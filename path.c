#include "shell.h"

/**
 * str_concat -concaten 2 string of character.
 * @str1: first string.
 * @str2: second string.
 *
 * Return:Pointer to the new string, or NULL if fail.
 */
char *str_concat(const char *str1, const char *str2)
{
	char *result;

	if (!str1 || !str2)
	{
		return (NULL);
	}

	result = malloc(strlen(str1) + strlen(str2) + 1);
	if (!result)
	{
		return (NULL);
	}

	strcpy(result, str1);
	strcat(result, str2);

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
    char *result = NULL;

    if (path == NULL)
    {
        return (NULL);
    }

    path_copy = my_strdup(path);
    if (path_copy == NULL)
    {
        return (NULL);
    }

    for (token = strtok(path_copy, ":"); token != NULL; token = strtok(NULL, ":"))
    {
        char *temp = str_concat(token, "/");

        full_path = str_concat(temp, cmd);
        free(temp);

        if (is_executable(full_path))
        {
            result = my_strdup(full_path);
            free(full_path);
            break;
        }

        free(full_path);
    }

    free(path_copy);
    return (result);
}
