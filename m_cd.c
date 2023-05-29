#include "shell.h"

/**
 * _cd - change directory builtin command
 * @vars: command variables
 * Return: nothing
 */
void _cd(inputs_t *vars)
{
	char *home_dir = getenv("HOME"), *pathname = NULL, *pwd = NULL;
	struct stat sb;

	if (vars->av[1] == NULL)	/* cd command without argument */
	{
		pathname = home_dir;
		change_dir(vars, pathname);
	}
	else if (_strcmp(vars->av[1], "-") == 0)
	{
		pathname = getenv("OLDPWD");
		change_dir(vars, pathname);
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
		if (stat(pathname, &sb) == 0)
		{
			if (S_ISDIR(sb.st_mode))
				change_dir(vars, pathname);
			else
			{
				print_error2(vars, "Not a directory\n");
				vars->status = 2;
			}
		}
		else
		{
			print_error2(vars, NULL);
			vars->status = 2;
		}
		free(pathname);
	}
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
			else
			{
				free(new_envr);
				new_envr = NULL;
			}
			vars->status = 0;
			return (0);
		}
		i++;
	}
	vars->env[i++] = new_envr;
	free(new_envr);
	vars->env[i] = NULL;
	new_envr = NULL;
	vars->status = 0;
	return (0);
}

/**
 * print_error2 - prints error messages to standard error
 * @vars: pointer to struct of variables
 * @msg: message to print
 *
 * Return: void
 */
void print_error2(inputs_t *vars, char *msg)
{
	char *count;

	_puts2(vars->argv[0]);
	_puts2(": ");
	count = _uitoa(vars->count);
	_puts2(count);
	free(count);
	_puts2(": ");
	_puts2(vars->av[0]);
	if (vars->av[1])
	{
		_puts2(": ");
		_puts2(vars->av[1]);
		_puts2(": ");
	}
	if (msg)
		_puts2(msg);
	else
	{
		perror("");
	}
}
