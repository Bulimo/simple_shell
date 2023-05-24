include "simple_shell.h"

/**
  * _strdup - duplicate a string
  * @src: source string
  * Return: pointer to copied string
  */
char *_strdup(char *src)
{
	size_t len = 0;
	char *dest = NULL;

	len = _strlen(src) + 1;

	dest = malloc(sizeof(char) * len);
	if (dest == NULL)
		return (NULL);
	_strncpy(dest, src, len);
	return (dest);
}
