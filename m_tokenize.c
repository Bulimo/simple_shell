#include "shell.h"


/**
 * tokenize - tokenizes a buffer with a delimiter
 * @input: buffer to tokenize
 * @delimiter: delimiter to tokenize along
 *
 * Return: pointer to an array of pointers to the tokens
 */

char **tokenize(char *input, char *delimiter)
{
	char **tokens = NULL;
	size_t i = 0, mcount = 10;

	if (input == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * mcount);
	if (tokens == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((tokens[i] = new_strtok(input, delimiter)) != NULL)
	{
		i++;
		if (i == mcount)
		{
			tokens = _realloc(tokens, &mcount);
			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		input = NULL;
	}
	return (tokens);
}

