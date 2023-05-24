#include "simple_shell.h"

/**
 * create_path - creates the complete path of the executable command
 * @command: command to create its path
 * Return: pointer to command full path
 */
char *create_path(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = NULL, *dir = NULL, *full_path = NULL;

	if (access(command, X_OK) == 0)
		return (_strdup(command));
	path_copy = _strdup(path);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(sizeof(char) * _strlen(command) * _strlen(dir) + 2);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			dir = NULL;
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	dir = NULL;
	return (NULL);
}

