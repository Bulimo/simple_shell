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
	char *path = _getenv(vars, "PATH");
	int p = sprintf(buff_pid, "%d", pid);
	int s = sprintf(buff_status, "%d", vars->status);

	if ((strncmp(vars->av[1], "$?", 2)) == 0)
	{
		write(STDOUT_FILENO, buff_status, s);
		_puts("\n");
	}

	else if ((strncmp(vars->av[1], "$$", 2)) == 0)
	{
		write(STDOUT_FILENO, buff_pid, p);
		_puts("\n");
	}

	else if ((strncmp(vars->av[1], "$PATH", 5)) == 0)
	{
		_puts(path);
		_puts("\n");
	}
}
