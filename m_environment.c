#include "shell.h"

/**
 * copy_env - make the shell environment from the environment passed to main
 * @env: environment passed to main
 *
 * Return: pointer to the new environment
 */
char **copy_env(char **env)
{
	char **newenv = NULL;
	size_t i;

	if (env == NULL)
		return (NULL);
	for (i = 0; env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * (i + 1));
	if (newenv == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	i = 0;
	while (env[i])
	{
		newenv[i] = _strdup(env[i]);
		i++;
	}
	newenv[i] = NULL;
	return (newenv);
}

/**
 * free_env - free the shell's environment
 * @env: shell's environment
 *
 * Return: void
 */
void free_env(char **env)
{
	unsigned int i = 0;

	while (env[i])
		free(env[i++]);
	free(env);
}


/**
 * add_key - create a new environment variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void add_key(inputs_t *vars)
{
	unsigned int i = 0;
	char **newenv;

	for (i = 0; vars->env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * (i + 2));
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		my_exit(vars);
	}
	i = 0;
	while (vars->env[i])
	{
		newenv[i] = vars->env[i];
		i++;
	}
	newenv[i] = add_value(vars->av[1], vars->av[2]);
	if (newenv[i] == NULL)
	{
		print_error(vars, NULL);
		free_commands(vars);
		free(newenv);
		exit(127);
	}
	newenv[i + 1] = NULL;
	free(vars->env);
	vars->env = newenv;
}

/**
 * find_key - finds an environment variable
 * @env: array of environment variables
 * @key: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */
char **find_key(char **env, char *key)
{
	unsigned int i, j, len;

	len = _strlen(key);
	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
			if (key[j] != env[i][j])
				break;
		if (j == len && env[i][j] == '=')
			return (&env[i]);
	}
	return (NULL);
}

/**
 * add_value - create a new environment variable string
 * @key: variable name
 * @value: variable value
 *
 * Return: pointer to the new string;
 */
char *add_value(char *key, char *value)
{
	unsigned int len1, len2, i = 0, j = 0;
	char *new;

	len1 = _strlen(key);
	len2 = _strlen(value);
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (new == NULL)
		return (NULL);

	while (key[i] != '\0')
	{
		new[i] = key[i];
		i++;
	}
	new[i] = '=';
	for (j = 0; value[j] != '\0'; j++)
		new[i + 1 + j] = value[j];
	new[i + 1 + j] = '\0';
	return (new);
}
