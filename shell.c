#include "shell.h"

char *program_name;
/**
 * main - Main entry point for the simple shell.
 * @argc: Argument count.
 * @argv: Arguments.
 *
 * Return: Exit status.
 */
int main(int argc, char **argv)
{
    program_name = argv[0];
	(void)argc;
	(void)argv;

	return (shell_loop());
}
