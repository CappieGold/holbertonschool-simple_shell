#include "shell.h"

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/**
 * resize_tokens - Resize the tokens array.
 * @tokens: The tokens array.
 * @bufsize: Pointer to the current buffer size.
 *
 * Return: The resized tokens array.
 */
char **resize_tokens(char **tokens, size_t *bufsize)
{
	size_t old_size = *bufsize * sizeof(char *);
	char **new_tokens = _realloc(tokens, old_size, *bufsize * sizeof(char *));
	*bufsize += TOK_BUFSIZE;

	if (!new_tokens)
	{
		fprintf(stderr, "shell: allocation error\n");
		exit(EXIT_FAILURE);

	}
	return (new_tokens);
}

/**
 * split_line - Split a line into tokens.
 * @line: The line to split.
 *
 * Return: Array of tokens.
 */
char **split_line(char *line)
{
	char **tokens;
	size_t bufsize = TOK_BUFSIZE;
	size_t position = 0;
	char *token;

	if (line == NULL)
	{
		fprintf(stderr, "split_line: received null pointer\n");
		return (NULL);
	}

	tokens = malloc(bufsize * sizeof(char *));
	if (!tokens)
	{
		perror("allocation error");
		return (NULL);
	}

	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[position++] = token;
		if (position >= bufsize)
		{
			tokens = resize_tokens(tokens, &bufsize);
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}
