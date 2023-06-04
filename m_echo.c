#include "shell.h"
/**
 * sub_env - substitutes the environment variables
 * @vars: contains members of the struct
 */

void sub_env(inputs_t *vars)
{
	size_t i = 0;
	char **av_copy = copy_env(vars->av);
	pid_t pid = getpid();
	char *path = NULL, *env = NULL;


	while (av_copy != NULL && av_copy[i] != NULL)
	{
		if (_strcmp(av_copy[i], "$?") == 0)
		{
			vars->av[i] = _malloc(32);
			sprintf(vars->av[i], "%d", vars->status);
		}
		else if (_strcmp(av_copy[i], "$$") == 0)
		{
			vars->av[i] = _malloc(32);
			sprintf(vars->av[i], "%d", pid);
		}
		else if (av_copy[i][0] == '$' && av_copy[i][1] != '\0')
		{
			path = &(av_copy[i][1]);
			env = _getenv(vars, path);
			if (env)
				vars->av[i] = _strdup(env);
			else
				vars->av[i] = _strdup("");
		}
		else
			vars->av[i] = _strdup(av_copy[i]);
		i++;
	}
	free_av_and_alias(av_copy);
}


/**
  * free_av_and_alias - free av commands
  * @s: vars->av or vars->alias inputs
  * Return: nothing
  */
void free_av_and_alias(char **s)
{
	size_t i = 0;

	if (s == NULL)
		return;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
