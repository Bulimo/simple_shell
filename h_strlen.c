#include "simple_shell.h"

/**
  * _strlen - returns the length of a string
  * @s: pointer
  * Return: length of character
  */

size_t _strlen(char *s)
{
	size_t count = 0, i = 0;

	while (s[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

