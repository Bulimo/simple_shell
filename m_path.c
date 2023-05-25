#include "shell.h"

/**
 * execute_command - executes the command
 * @command: command to execute
 * @vars: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */

int execute_command(char *command, vars_t *vars)
{
	struct stat buf;
	pid_t child_pid;

	if (stat(command, &buf) == 0)
	{
		if (access(command, X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				print_error(vars, NULL);
			if (child_pid == 0)
			{
				if (execve(command, vars->av, vars->env) == -1)
					print_error(vars, NULL);
			}
			else
			{
				wait(&vars->status);
				if (WIFEXITED(vars->status))
					vars->status = WEXITSTATUS(vars->status);
				else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
					vars->status = 130;
				return (0);
			}
			vars->status = 127;
			return (1);
		}
		else
		{
			print_error(vars, ": Permission denied\n");
			vars->status = 126;
		}
		return (0);
	}
	print_error(vars, ": not found\n");
	vars->status = 127;
	return (0);
}

/**
 * check_for_path - checks if the command is in the PATH or current directory
 * @vars: variables
 *
 * Return: void
 */
void check_for_path(vars_t *vars)
{
	char *path = getenv("PATH");
	char *command = vars->av[0];
	char *command_path = NULL;
	char *token;
	struct stat buf;
	char *path_copy;

	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &buf) == 0 && access(command, X_OK) == 0)
		{
			execute_command(command, vars);
			return;
		}
	}
	else if (path != NULL)
	{
		path_copy = _strdup(path);
		token = new_strtok(path_copy, ":");
		while (token != NULL)
		{
			command_path = malloc(strlen(token) + strlen(command) + 2);
			sprintf(command_path, "%s/%s", token, command);
			if (stat(command_path, &buf) == 0 && access(command_path, X_OK) == 0)
			{
				execute_command(command_path, vars);
				free(command_path);
				free(path_copy);
				return;
			}
			free(command_path);
			token = new_strtok(NULL, ":");
		}
		free(path_copy);
	}

	print_error(vars, ": not found\n");
	vars->status = 127;
}
