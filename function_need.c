#include "shell.h"

/**
 * concatenate_strings - Concatenates two strings into a new string.
 * This function creates a new string which is the result of concatenating
 * two given strings. It allocates memory for the new string, which needs to
 * be freed by the caller. If either input string is NULL, it is treated as
 * an empty string.
 *
 * @first_string: The first string to concatenate. Treated as empty if NULL.
 * @second_string: The second string to concatenate. Treated as empty if NULL.
 * Return: A pointer to the newly allocated concatenated string, or NULL if
 *         memory allocation fails.
 *
 * Note: The caller is responsible for freeing the memory allocated for the
 *       concatenated string. If either input string is NULL, it doesn't cause
 *       a crash; instead, NULL is treated as an empty string.
 */

char *concatenate_strings(char *first_string, char *second_string)
{
	char *concatenated_str;
	unsigned int length_first, length_second, index;

	length_first = (first_string == NULL) ? 0 : strlen(first_string);
	length_second = (second_string == NULL) ? 0 : strlen(second_string);

	concatenated_str = malloc((length_first + length_second + 1) * sizeof(char));
	if (concatenated_str == NULL)
	{
		return (NULL);
	}

	for (index = 0; index < length_first; index++)
		concatenated_str[index] = first_string[index];
	for (index = 0; index <= length_second; index++)
		concatenated_str[length_first + index] = second_string[index];

	return (concatenated_str);
}


/**
 * _realloc - Safely reallocates a memory block.
 * This function adjusts the size of the memory block
 * pointed to by 'original_ptr'
 * to the new specified size 'new_size'.
 * If 'original_ptr' is NULL, the function
 * behaves like malloc. If 'new_size' is 0, and 'original_ptr' is not NULL, the
 * memory is freed and NULL is returned. The function handles copying of old
 * content to the new block and ensures proper memory freeing.
 *
 * @original_ptr: Pointer to the previously allocated memory, or NULL.
 * @original_size: The original size of the memory block.
 * @new_size: The new size for the memory block.
 * Return: Pointer to the reallocated memory block with new size, or NULL if
 *         allocation fails or new_size is 0.
 *
 * Note: The caller is responsible for managing the memory returned by this
 *       function. It ensures safe memory operations, avoiding common pitfalls
 *       like freeing the original pointer only when allocation is successful.
 */

void *_realloc(void *original_ptr, unsigned int original_size,
				unsigned int new_size)
{
	char *new_ptr;
	unsigned int copy_size, index;

	if (new_size == 0)
	{
		free(original_ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size * sizeof(char));

	if (new_ptr == NULL)
		return (NULL);

	copy_size = (new_size > original_size) ? original_size : new_size;

	for (index = 0; index < copy_size; index++)
		new_ptr[index] = ((char *)original_ptr)[index];

	free(original_ptr);
	return (new_ptr);
}
