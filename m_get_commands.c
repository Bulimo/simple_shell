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
			tokens = _realloc(tokens, buffsize, 2 * buffsize);
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

/**
 * get_aliases - extracts aliases from buffer
 * @input: buffer to tokenize
 * @delimiter: delimiter to tokenize along
 *
 * Return: pointer to an array of pointers to the tokens
 */

char **get_aliases(char *input, char *delimiter)
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
	tokens[i] = alias_strtok(input, delimiter);
	while (tokens[i])
	{
		i++;
		if (i == buffsize)
		{
			tokens = _realloc(tokens, buffsize, 2 * buffsize);
			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		tokens[i] = alias_strtok(NULL, delimiter);
	}
	return (tokens);
}

/**
 * alias_strtok - own implementation of strtok function
 * @str: the string to be parsed
 * @del: end of word delimeters
 * Return: pointer to start of word, or NULL
 */
char *alias_strtok(char *str, const char *del)
{
	char *token = NULL;
	static size_t start_index, len;
	size_t comma = 0;
	static char *s;

	if (del == NULL || del[0] == '\0')
		return (str);
	start_index = (str != NULL) ? 0 : start_index;
	s = (str != NULL) ? str : s;
	len = (str != NULL) ? strlen(str) : len;
	while (s[start_index]) /* get start of the word */
	{
		if (char_found(s[start_index], del) == -1)
		{
			token = &s[start_index];
			if (char_found('\'', &s[start_index]) != -1)
				comma = start_index + char_found('\'', &s[start_index]);
			break;
		}
		start_index++;
	}
	if (s[start_index] == '\0' || s[start_index] == '#')
		return (NULL);
	if (s[start_index] == '\'' || s[start_index] == '\"')
		token = &s[++start_index];
	while (s[start_index])/* get end ofthe word */
	{
		if (char_found(s[start_index], del) != -1)
			break;
		start_index++;
	}
	if (comma && start_index > comma)
		start_index = comma + char_found('\'', &s[comma + 1]) + 2;
	s[start_index] = '\0';
	start_index += (start_index < len) ? 1  : 0;
	return (token);
}

/**
 * char_found - returns index of 1st instance of a char in a string
 * @c: char to to search
 * @del: string of characters to search c in
 * Return: index of 1st instance, -1 otherwise
 */
int char_found(char c, const char *del)
{
	int j = 0;

	for (j = 0; del[j]; j++)
	{
		if (c == del[j])
			return (j);
	}
	return (-1);	/* return -1 if xter is not found */
}

