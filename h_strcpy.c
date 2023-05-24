#include "simple_shell.h"

/**
 *_strcpy - copies the string
 *@dest: destination of the string to be copied
 *@src: source of the string to be copied
 *Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	char *start = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return (start);
}
