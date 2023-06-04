#include "shell.h"
/**
 * _echo - prints on the terminal
 * @vars: contains members of the struct
 */

void _echo(inputs_t *vars)
{
	pid_t pid = getpid();
	char buff_pid[32];
	char buff_status[3];
	char *path = NULL, *env = NULL;
	int p = sprintf(buff_pid, "%d", pid);
	int s = sprintf(buff_status, "%d", vars->status);
	int i = 1;

	while (vars->av[i] != NULL)
	{
		if (i > 1)
			_puts(" ");
		if (vars->av[i][0] == '$')
		{
			if (vars->av[i][1] == '?')
			{
				write(STDOUT_FILENO, buff_status, s);
			}

			else if (vars->av[i][1] == '$')
			{
				write(STDOUT_FILENO, buff_pid, p);
			}

			else
			{
				path = &(vars->av[i][1]);
				env = _getenv(vars, path);

				if (env)
					_puts(env);
			}
		}
		else
			_puts(vars->av[i]);
		i++;
	}

	_puts("\n");
	vars->status = 0;
}
