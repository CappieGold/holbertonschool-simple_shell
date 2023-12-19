#include "shell.h"

/**
 * main - Main entry point for the simple shell.
 * @argc: Argument count.
 * @argv: Arguments.
 *
 * Return: Exit status.
 */
int main(int argc, char **argv)
{
	char *program_name;

	if (argc > 0)
	program_name = argv[0];
	else
	program_name = "hsh";

	return (shell_loop(program_name));
}
