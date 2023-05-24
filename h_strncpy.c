#include "simple_shell.h"

/**
 * _strncpy - copies a string
 * @dest: char type
 * @src: char type
 * @n: integer type
 * Return: destination pointer
 */
char *_strncpy(char *dest, char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}
