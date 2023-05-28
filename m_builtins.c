#include "shell.h"

/**
 * exe_builtin - checks if the command is a builtin
 * @vars: variables
 * Return: pointer to the function or NULL
 */
/*void (*check_for_builtins(inputs_t *vars))(inputs_t *vars)*/
int exe_builtin(inputs_t *vars)
{
	unsigned int i = 0;
	builtins_t builtin[] = {
		{"exit", my_exit},
		{"env", _env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}
	};

	while (builtin[i].f)
	{
		if (_strcmp(vars->av[0], builtin[i].name) == 0)
		{
			builtin[i].f(vars);
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * my_exit - exit program
 * @vars: variables
 * Return: void
 */
void my_exit(inputs_t *vars)
{
	int status = 0;

	if (_strcmp(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			print_error(vars, ": Illegal number: ");
			_puts2(vars->av[1]);
			_puts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
	exit(vars->status);
}

/**
 * _env - prints the current environment
 * @vars: struct of variables
 * Return: void.
 */
void _env(inputs_t *vars)
{
	unsigned int i = 0;

	while (vars->env[i])
	{
		_puts(vars->env[i]);
		_puts("\n");
		i++;
	}
	vars->status = 0;
}

/**
 * _setenv - create a new environment variable, or edit an existing variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void _setenv(inputs_t *vars)
{
	char **key;
	char *var;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
		add_key(vars);
	else
	{
		var = add_value(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			print_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_env(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}

/**
 * _unsetenv - remove an environment variable
 * @vars: pointer to a struct of variables
 *
 * Return: void
 */
void _unsetenv(inputs_t *vars)
{
	char **key, **newenv;

	unsigned int i, j;

	if (vars->av[1] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_key(vars->env, vars->av[1]);
	if (key == NULL)
	{
		print_error(vars, ": No variable to unset\n");
		return;
	}
	for (i = 0; vars->env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * i);
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		my_exit(vars);
	}
	for (i = 0; vars->env[i] != *key; i++)
		newenv[i] = vars->env[i];
	for (j = i + 1; vars->env[j] != NULL; j++, i++)
		newenv[i] = vars->env[j];
	newenv[i] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}


