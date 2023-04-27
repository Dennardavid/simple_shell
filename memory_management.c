#include "simple_shell.h"

/**
 * copy_memory - Copies memory from one location to another
 * @new_ptr: Pointer to the destination memory block
 * @old_ptr: Pointer to the source memory block
 * @new_size: Number of bytes to copy
 */

void copy_memory(void *new_ptr, const void *old_ptr, unsigned int new_size)
{
	char *src_ptr = (char *)old_ptr;
	char *dst_ptr = (char *)new_ptr;
	unsigned int i;

	for (i = 0; i < new_size; i++)
	{
		dst_ptr[i] = src_ptr[i];
	}
}

/**
 * reallocate_memory - Reallocates memory
 * @old_ptr: Pointer to the old memory block
 * @old_s: Size of the old memory block
 * @new_s: Size of the new memory block
 * Return: Pointer to new memory
 */
void *reallocate_memory(void *old_ptr, unsigned int old_s, unsigned int new_s)
{
	void *new_ptr;

	if (old_ptr == NULL)
	{
		return (malloc(new_s));
	}

	if (new_s == 0)
	{
		free(old_ptr);
		return (NULL);
	}

	if (new_s == old_s)
	{
		return (old_ptr);
	}

	new_ptr = malloc(new_s);
	if (new_ptr == NULL)
	{
		return (NULL);
	}

	if (new_s < old_s)
	{
		copy_memory(new_ptr, old_ptr, new_s);
	}
	else
	{
		copy_memory(new_ptr, old_ptr, old_s);
	}

	free(old_ptr);
	return (new_ptr);
}

/**
 * realloc_db_ptr - Reallocates a double pointer
 * @old_ptr: Pointer to the old double pointer
 * @old_s: Size of the old double pointer
 * @new_s: Size of the new double pointer
 * Return: Pointer to new memory
 */
char **realloc_db_ptr(char **old_ptr, unsigned int old_s, unsigned int new_s)
{
	char **new_ptr;
	unsigned int i;

	if (old_ptr == NULL)
	{
		return (malloc(sizeof(char *) * new_s));
	}

	if (new_s == old_s)
	{
		return (old_ptr);
	}

	new_ptr = malloc(sizeof(char *) * new_s);
	if (new_ptr == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < old_s; i++)
	{
		new_ptr[i] = old_ptr[i];
	}

	free(old_ptr);

	return (new_ptr);
}
