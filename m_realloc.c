#include "shell.h"

/**
 * _realloc - reallocates a pointer to double the space
 * @ptr: pointer to the old array
 * @old_size: number of elements in the old array
 * @new_size: the size of the new array
 * Return: pointer to the new array
 */
char **_realloc(char **ptr, size_t old_size, size_t new_size)
{
	char **new_ptr;
	size_t i;

	new_ptr = malloc(sizeof(char *) * new_size);
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (i = 0; i < old_size; i++)
	{
		new_ptr[i] = ptr[i];
	}
	free(ptr);
	return (new_ptr);
}
