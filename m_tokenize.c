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
	size_t bufsize = 64, position = 0;
	char **tokens = (char **)malloc(bufsize * sizeof(char *));
	char *token, *input_copy = strdup(input);

	if (tokens == NULL)
	{
		perror("Allocation error");
		exit(1);
	}
	if (input_copy == NULL)
	{
		perror("Allocation error");
		exit(1);
	}
	token = strtok(input_copy, delimiter);
	while (token != NULL)
	{
		tokens[position] = strdup(token);
		if (tokens[position] == NULL)
		{
			perror("Allocation error");
			exit(1);
		}
		position++;
		if (position >= bufsize)
		{
			bufsize += bufsize;
			tokens = (char **)realloc(tokens, bufsize * sizeof(char *));
			if (tokens == NULL)
			{
				perror("Allocation error");
				exit(1);
			}
		}
		token = strtok(NULL, delimiter);
	}
	tokens[position] = NULL;
	free(input_copy);
	return (tokens);
}
