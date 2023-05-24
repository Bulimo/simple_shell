#include "simple_shell.h"

/**
  * get_args - creates an array of commands passed
  * @input: line of user input
  * Return: an array of command strings
  */
char **get_args(char *input)
{
	char *token = NULL;
	char *del = " \t";
	char **args;
	int i = 0;

	args = malloc(sizeof(char *) * 1024);
	if (args == NULL)
		return (NULL);
	token = strtok(input, del);
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, del);
	}
	args[i] = NULL;

	return (args);
}
