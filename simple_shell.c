#include "shell.h"

/**
 * sig_handler - handles ^C signal interrupt
 * @uuv: unused variable (required for signal function prototype)
 *
 * Return: void
 */
static void sig_handler(int uuv)
{
	(void)uuv;
	_puts("\n$ ");
}

/**
 * print_prompt - prints the shell prompt
 */
static void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		_puts("$ ");
}

/**
 * process_input - process the user input
 * @input: user input to process
 * @vars: shell variables
 */
static void process_input(char *input, vars_t *vars)
{
	unsigned int i;

	vars->count++;
	vars->commands = tokenize(input, ";");

	for (i = 0; vars->commands && vars->commands[i] != NULL; i++)
	{
		vars->av = tokenize(vars->commands[i], "\n \t\r");
		if (vars->av && vars->av[0])
			if (check_for_builtins(vars) == NULL)
				check_for_path(vars);
		free(vars->av);
	}

	free(vars->commands);
}

/**
 * main - main function for the shell
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0;
	vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.argv = argv;
	vars.env = make_env(environment);

	signal(SIGINT, sig_handler);

	if (!isatty(STDIN_FILENO))
		is_pipe = 1;

	if (is_pipe == 0)
		print_prompt();

	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		process_input(vars.buffer, &vars);

		free(vars.buffer);
		vars.buffer = NULL;
		if (is_pipe == 0)
			print_prompt();
	}

	if (is_pipe == 0)
		_puts("\n");

	free_env(vars.env);
	free(vars.buffer);
	exit(vars.status);
}

