#include "shell.h"


/**
 * get_commands - extracts commands from buffer
 * @input: buffer to tokenize
 * @delimiter: delimiter to tokenize along
 *
 * Return: pointer to an array of pointers to the tokens
 */

char **get_commands(char *input, char *delimiter)
{
	char **tokens = NULL;
	size_t i = 0, buffsize = 1024;

	if (input == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * buffsize);
	if (tokens == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	tokens[i] = _strtok(input, delimiter);
	while (tokens[i])
	{
		i++;
		if (i == buffsize)
		{
			tokens = _realloc(tokens, &buffsize);
			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		tokens[i] = _strtok(NULL, delimiter);
	}
	return (tokens);
}

