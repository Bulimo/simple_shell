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

/**
  * _malloc - allocates a specific size of memeory
  * @size: size of memory to create
  * Return: pointer to allocated memory
  */
char *_malloc(size_t size)
{
	char *buff = NULL;

	buff = malloc(sizeof(char) * size);
	if (buff == NULL)
	{
		perror("Fatal error");
		exit(1);
	}
	return (buff);
}
