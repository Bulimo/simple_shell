#include "shell.h"

/**
 * _cd - change directory builtin command
 * @vars: command variables
 * Return: nothing
 */
void _cd(inputs_t *vars)
{
	char *home_dir = _getenv(vars, "HOME"), *pathname = NULL, *pwd = NULL;
	struct stat sb;

	if (vars->av[1] == NULL || vars->av[1][0] == '\0')
		pathname = home_dir ? _strdup(home_dir) : getcwd(pathname, 0);
	else if (_strcmp(vars->av[1], "-") == 0)
	{
		pathname = (_getenv(vars, "OLDPWD")) ? _strdup(_getenv(vars, "OLDPWD")) :
					getcwd(pathname, 0);
		_puts(pathname);
		_puts("\n");
	}
	else
	{
		if (vars->av[1][0] == '/')
			pathname = _strdup(vars->av[1]);
		else
		{
			pwd = getcwd(pwd, 0);
			pathname = _strcat(pwd, vars->av[1]);
			free(pwd);
		}
	}
	if (stat(pathname, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
			change_dir(vars, pathname);
		else
		{
			print_error2(vars, "can't cd to ");
			vars->status = 2;
		}
	}
	else
	{
		print_error2(vars, "can't cd to ");
		vars->status = 2;
	}
	free(pathname);
}


/**
 * change_dir - changes process working dir and updates env elements
 * @vars: input variables
 * @pathname: new path to switch new
 */
void change_dir(inputs_t *vars, char *pathname)
{
	char *old_pwd = NULL;

	old_pwd = getcwd(old_pwd, 0);

	if (access(pathname, R_OK) == -1)
	{
		print_error2(vars, "can't cd to ");
		vars->status = 2;
		return;
	}

	if (chdir(pathname) == -1)
	{
		print_error(vars, NULL);
		return;
	}
	_setenv2(vars, "OLDPWD", old_pwd, 1);
	_setenv2(vars, "PWD", pathname, 1);
	free(old_pwd);
	old_pwd = NULL;
	vars->status = 0;
}

/**
 * _setenv2 - changes or adds an environment variable
 * @name: variable name
 * @val: value of the variable
 * @o_write: flag to determine if change value of existing varable
 * @vars: input variables
 * Return: 0 on success, -1 otherwise
 */
int _setenv2(inputs_t *vars, const char *name, const char *val, int o_write)
{
	int				i = 0;
	char			*new_envr = NULL;
	size_t			len = 0, name_len = 0, val_len  = 0;
	char **env;

	env = copy_env(vars->env);
	free_env(vars->env);
	vars->env = env;
	name_len = strlen(name);
	val_len = strlen(val);
	len = 2 + name_len + val_len;
	new_envr = malloc(sizeof(char) * len);
	if (new_envr == NULL)
		return (-1);
	if ((snprintf(new_envr, len, "%.*s=%s", (int)name_len, name, val)) == -1)
		return (-1);
	while (vars->env[i])
	{
		if (strncmp(new_envr, vars->env[i], name_len) == 0)
		{
			if (o_write)
			{
				free(vars->env[i]);
				vars->env[i] = new_envr;
			}
			new_envr = NULL;
			vars->status = 0;
			return (0);
		}
		i++;
	}
	vars->env[i] = new_envr;
	env = copy_env(vars->env);
	free_env(vars->env);
	vars->env = env;
	new_envr = NULL;
	vars->status = 0;
	return (0);
}

/**
  * _getenv - gets value of environment variable
  * @vars: input variables
  * @name: environment variable to search
  * Return: value or NULL
  */
char *_getenv(inputs_t *vars, const char *name)
{
	int i = 0;
	char *value = NULL;
	size_t len = strlen(name);

	while (vars->env[i])
	{
		if (strncmp(vars->env[i], name, len) == 0)
		{
			value = &(vars->env[i][len + 1]);
			return (value);
		}
		i++;
	}
	return (NULL);
}

