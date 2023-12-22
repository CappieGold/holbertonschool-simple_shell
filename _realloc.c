#include <stdlib.h>

/**
 * _realloc - Reallocate a memory block.
 * @ptr: Pointer to the previously allocated memory block.
 * @old_size: Old size of the memory block.
 * @new_size: New size to allocate.
 *
 * Return: Pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (new_size == old_size)
		return (ptr);

	if (!ptr)
	{
		new_ptr = malloc(new_size);
		if (!new_ptr)
			return (NULL);
		return (new_ptr);
	}

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	if (new_size < old_size)
		old_size = new_size;

	while (old_size--)
		*((char *)new_ptr + old_size) = *((char *)ptr + old_size);

	free(ptr);

	return (new_ptr);
}
