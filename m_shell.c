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
	unsigned int is_term = 0;
	inputs_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL, NULL, NULL, NULL};

	vars.argv = argv;
	vars.env = copy_env(environment);

	signal(SIGINT, sig_handler);

	is_term = isatty(STDIN_FILENO);

	if (is_term)
		print_prompt();

	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		process_input(vars.buffer, &vars);

		free(vars.buffer);
		vars.buffer = NULL;
		if (is_term)
			print_prompt();
	}

	if (is_term)
		_puts("\n");

	free_env(vars.env);
	free_av_and_alias((&vars)->aliases);
	free(vars.buffer);
	exit(vars.status);
}

/**
 * free_commands - frees alias commands/inputs
 * @vars: contains struct members
 */

void free_commands(inputs_t *vars)
{
	free(vars->buffer);
	free(vars->commands);
	free(vars->str_cmd);
	free(vars->ops_cmd);
	free_av_and_alias(vars->av);
	free_env(vars->env);
	free_av_and_alias(vars->aliases);
}

