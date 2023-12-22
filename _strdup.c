#include "shell.h"

/**
 * my_strdup - Duplicate a string.
 * @s: The input string to duplicate.
 *
 * Return: A pointer to the duplicated string or NULL if allocation fails.
 */
char *my_strdup(const char *s)
{
    char *dup = malloc(strlen(s) + 1);

    if (dup == NULL)
        return (NULL);

    strcpy(dup, s);
    return (dup);
}
