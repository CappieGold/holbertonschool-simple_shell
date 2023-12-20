#include "shell.h"

/**
 * check_command_path - Verifies if a command exists in PATH or as an absolute
 * or relative path.
 * This function checks if the specified command is an executable file located
 * in one of the directories listed in the PATH environment variable, or if it
 * is specified using an absolute or relative path. If the command is found,
 * the function returns the full path to the executable.
 *
 * @command_tokens: Array of command tokens; the first token is the command
 *                        to be checked.
 * @shell_args: Array of arguments passed to the shell, used for error
 *                    messaging.
 * Return: String containing the path to the executable if found; otherwise,
 *          returns "Path resolution failed" indicating failure to locate the
 *          command.
 *
 * Note: The function uses the access() system call to verify the existence and
 *       executability of the command. It is important to manage memory
 *       effectively, especially when dynamically constructing potential paths
 *       to the executable.
 */


char *check_command_path(char **command_tokens, char **shell_args)
{
	char *resolved_path, *combined_path, *path_separator = "/";
	char **path_directories, path_env_variable[1024];
	int i = 0;

	if (command_tokens[0][0] == '/' || command_tokens[0][0] == '.')
	{
		resolved_path = command_tokens[0];
		if ((access(resolved_path, F_OK) == -1))
		{
			fprintf(stderr, "%s: %d: %s: No such file or directory\n",
			shell_args[0], __LINE__, command_tokens[0]);
			return ("Path resolution failed");
		}
	}
	else
	{
		strcpy(path_env_variable, getenv("PATH"));
		path_directories = tokenizer_path(path_env_variable);
		while (path_directories[i])
		{
			combined_path = str_concat(path_separator, command_tokens[0]);
			resolved_path = str_concat(path_directories[i], combined_path);
			if ((access(resolved_path, F_OK) == -1))
			{
				free(resolved_path), free(combined_path);
			}
			else
			{
				free(path_directories);
				free(combined_path);
				return (resolved_path);
			}
			i++;
		}
		free(path_directories);
		fprintf(stderr, "%s: %d: %s: No such file or directory\n",
		shell_args[0], __LINE__, command_tokens[0]);
		return ("Path resolution failed");
	}
	return (resolved_path);
}

/**
 * check_if_input_is_whitespace - Determines if the user input consists only
 * of whitespace characters (spaces, tabs, or line breaks).
 * This function is utilized to ascertain whether the user's input
 * is effectively empty,
 * containing only whitespace characters, which is useful in deciding
 * whether to ignore such input in a shell environment.
 *
 * @user_input: The string of user input to be checked.
 * Return: Returns 1 (true) if the input contains only whitespace characters;
 *          otherwise, returns 0 (false).
 *
 * Note: The function iterates through each character of the input string to
 *       check for non-whitespace characters. A return value of 0 indicates
 *       the presence of content other than whitespace, suggesting that the
 *       input should be processed further.
 */

int check_if_input_is_whitespace(char *user_input)
{
	int i = 0, is_whitespace = 1, input_lenght = 0;

	input_lenght = strlen(user_input);

	while (user_input[i] == ' ' || user_input[i] == '\n' || user_input[i] == '\t')
		i++;

	if (i != input_lenght)
		is_whitespace = 0;

	return (is_whitespace);
}
