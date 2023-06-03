#include "shell.h"

/**
 * _alias - displays and alias commands
 * @vars: contains struct members
 */
void _alias(inputs_t *vars)
{
	unsigned int i = 0, k = 1;

	if (vars->av[1] == NULL)
		print_alias(vars);
	else
	{
		while (vars->av[k])
		{
			if (strchr(vars->av[k], '=') != NULL)
				update_alias(vars, k);
			else
			{
				while (vars->aliases[i])
				{
					if (check_name_match(vars, i, k))
					{
						_puts(vars->aliases[i]);
						_puts("\n");
						break;
					}
					i++;
				}

			}
			k++;
		}
	}
	vars->status = 0;
}

/**
 * check_name_match - checks if av name matches aliases
 * @vars: contains struct members
 * @i: vars->alias at the position
 * @k: vars->av at the position
 * Return: 1 if match, 0 if no match
 */
int check_name_match(inputs_t *vars, unsigned int i, unsigned int k)
{
	unsigned int j = 0;

	while (vars->aliases[i][j] != '=')
	{
		if (_chrcmp(vars->av[k][j], vars->aliases[i][j]) == 0)
		{
			j++;
			return (1);
		}
	}
	return (0);
}


/**
 * update_alias-updates alias
 * @vars: contains struct members
 * @k: vars->av at the position
 */
void update_alias(inputs_t *vars, unsigned int k)
{
	unsigned int i = 0;

	if (vars->aliases == NULL)
		vars->aliases = malloc(sizeof(char *) * 2);
	else
	{
		while (vars->aliases[i])
		{
			if (check_name_match(vars, i, k))
			{
				free(vars->aliases[i]);
				vars->aliases[i] = _strdup(vars->av[k]);
				return;
			}
			i++;
		}

		vars->aliases = _realloc(vars->aliases, i, i + 2);
	}
	if (vars->aliases == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	vars->aliases[i] = _strdup(vars->av[k]);
	i++;
	vars->aliases[i] = NULL;
}

/**
 * print_alias - prints alias commands if av[1] is NULL
 * @vars: contains members of the struct
 */
void print_alias(inputs_t *vars)
{
	unsigned int i = 0;

	if (vars->aliases != NULL)
	{
		while (vars->aliases[i] != NULL)
		{
			_puts(vars->aliases[i]);
			_puts("\n");
			i++;
		}
	}
}

/**
 * free_commands - frees alias commands/inputs
 * @vars: contains struct members
 */

void free_commands(inputs_t *vars)
{
	unsigned int i = 0;

	free(vars->buffer);
	free(vars->commands);
	free(vars->str_cmd);
	free(vars->ops_cmd);
	free(vars->av);
	free_env(vars->env);
	if (vars->aliases != NULL)
	{
		while (vars->aliases[i])
			free(vars->aliases[i]);
		free(vars->aliases);
	}
}
