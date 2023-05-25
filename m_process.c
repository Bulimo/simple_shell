#include "shell.h"

/**
 * process_input - process the user input
 * @input: user input to process
 * @vars: shell variables
 */
void process_input(char *input, inputs_t *vars)
{
	unsigned int i;

	vars->count++;
	vars->commands = get_commands(input, ";");

	for (i = 0; vars->commands && vars->commands[i] != NULL; i++)
	{
		vars->av = get_commands(vars->commands[i], "\n \t\r");
		if (vars->av && vars->av[0])
			if (check_for_builtins(vars) == NULL)
				get_path(vars);
		free(vars->av);
	}

	free(vars->commands);
}

