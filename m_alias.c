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

	while (vars->aliases[i][j] != '\0' && vars->aliases[i][j] != '=')
	{
		if (_chrcmp(vars->av[k][j], vars->aliases[i][j]) == 0)
		{
			j++;
			return (1);
		}
		j++;
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
 * sub_alias - substitutes alias for commands
 * @vars: contains members of the struct
 */
void sub_alias(inputs_t *vars)
{
	size_t i = 0, j = 0, k = 0, len = 0;
	char alias_copy[1024];

	while (vars->aliases != NULL && vars->aliases[i] != NULL)
	{
		len = _strlen(vars->av[0]);
		if (strncmp(vars->aliases[i], vars->av[0], len) == 0)
		{
			for (j = len, k = 0; vars->aliases[i][j]; j++)
			{
				if (vars->aliases[i][j] == '=' || vars->aliases[i][j] == '\'')
					continue;
				else
				{
					alias_copy[k] = vars->aliases[i][j];
					k++;
				}
			}
			alias_copy[k] = '\0';
			free(vars->av[0]);
			vars->av[0] = malloc(sizeof(char) * _strlen(alias_copy) + 1);
			if (vars->av[0] == NULL)
			{
				perror("Fatal error");
				exit(1);
			}
			vars->av[0] = _strcpy(vars->av[0], alias_copy);
		}
		i++;
	}
}
