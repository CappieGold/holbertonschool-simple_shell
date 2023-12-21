#include "shell.h"

/**
 * tokenize_command_input - Splits an input string into an array of arguments.
 * This function takes a command line input and divides it into a series of
 * tokens (arguments), based on specified delimiters. It dynamically allocates
 * memory for an array of tokens, which should be freed by the caller. The
 * function expands the token array size as needed to accommodate all tokens.
 *
 * @input_line: The string of input to be tokenized. This is typically the
 *              raw input received from the command line.
 * Return: A pointer to an array of string tokens, or NULL if memory allocation
 *         fails. The last element in the array is NULL to indicate the end.
 *
 * Note: The caller is responsible for freeing the memory allocated for the
 *       array of tokens. The function uses dynamic memory allocation to handle
 *       variable-length input and adjusts the array size as needed.
 */

char **tokenize_command_input(char *input_line)
{
	char **argument_tokens = NULL, *current_token = NULL;
	int token_capacity = BUFSIZE, extended_capacity = 0, token_index = 0;
	char **temp_tokens = NULL;

	argument_tokens = malloc(token_capacity * sizeof(char *));
	if (argument_tokens == NULL)
	{
		fprintf(stderr, "Error allocating memory\n");
		exit(EXIT_FAILURE);
	}
	current_token = strtok(input_line, DELIM);
	while (current_token != NULL)
	{
		argument_tokens[token_index] = current_token;
		token_index++;
		if (token_index >= token_capacity)
		{
			extended_capacity = BUFSIZE * 2;
			temp_tokens = argument_tokens;

			argument_tokens = _realloc(argument_tokens, token_capacity,
			extended_capacity * sizeof(char *));

			if (argument_tokens == NULL)
			{
				free(temp_tokens);
				free(argument_tokens);
				fprintf(stderr, "Error reallocating memory\n");
				exit(EXIT_FAILURE);
			}
		}
		current_token = strtok(NULL, DELIM);
	}
	argument_tokens[token_index] = NULL;
	return (argument_tokens);
}

/**
 * tokenize_environment_path - Splits the PATH environment variable into paths.
 * This function takes the PATH environment variable
 * and divides it into an array of directory paths, using ':' as a delimiter.
 * It dynamically allocates memory for the array of path strings,
 * which should be freed by the caller.
 * The function expands the array as needed to fit all the extracted paths.
 *
 * @path_variable: The PATH environment variable string to be tokenized.
 * Return: A pointer to an array of directory path tokens, or NULL if memory
 *         allocation fails. The last element in the array is NULL to indicate
 *         the end.
 *
 * Note: The caller is responsible for freeing the memory allocated for the
 *       array of path tokens. This function is essential for parsing the PATH
 *       variable to search for executable commands in the shell.
 */

char **tokenize_environment_path(char *path_variable)
{
	int path_capacity = BUFSIZE, extended_capacity = 0, path_index = 0;
	char **path_tokens = NULL, *current_path_token = NULL;
	char **temp_tokens = NULL;

	path_tokens = malloc(path_capacity * sizeof(char *));
	if (path_tokens == NULL)
	{
		fprintf(stderr, "Error allocating memory\n");
		exit(EXIT_FAILURE);
	}

	current_path_token = strtok(path_variable, ":");
	while (current_path_token != NULL)
	{
		path_tokens[path_index] = current_path_token;
		path_index++;

		if (path_index >= path_capacity)
		{
			extended_capacity = BUFSIZE * 2;
			temp_tokens = path_tokens;

			path_tokens = _realloc(path_tokens, path_capacity,
			extended_capacity * sizeof(char *));

			if (path_tokens == NULL)
			{
				free(temp_tokens);
				free(path_tokens);
				fprintf(stderr, "Error reallocating memory\n");
				exit(EXIT_FAILURE);
			}
		}
		current_path_token = strtok(NULL, ":");
	}

	path_tokens[path_index] = NULL;
	return (path_tokens);
}
