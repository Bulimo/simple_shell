#include "simple_shell.h"

/**
  * execute - executes the shell commands
  * @path: command path
  * @arg: command flags and options
  * @envp: environment variable
  * Return: nothing
  */
void execute(char *path, char **arg, char **envp)
{
	pid_t pid;
	int error = 0;

	if (path == NULL || arg == NULL)
	{
		perror("path");
		return;
	}
	fflush(stdout);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		error = execve(path, arg, envp);
		if (error == -1)
			perror("execve");
	}
	else
		wait(NULL);
}

