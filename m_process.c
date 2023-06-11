#include "shell.h"

/**
 * process_input - process the user input
 * @input: user input to process
 * @vars: shell variables
 */
void process_input(char *input, inputs_t *vars)
{
	unsigned int i = 0;

	vars->count++;
	/* extract a line of command together with options */
	vars->commands = get_commands(input, ";");

	for (i = 0; vars->commands && vars->commands[i] != NULL; i++)
	{
		vars->str_cmd = _strdup(vars->commands[i]);
		vars->ops_cmd = get_commands(vars->str_cmd, "&|");
		check_logical_ops(vars, vars->commands[i]);
		free(vars->str_cmd);
		free(vars->ops_cmd);
	}
	free(vars->commands);
}

/**
 * check_logical_ops - executes according to logical operators
 * @vars: input variables struct
 * @cmd_str: current command
 */
void check_logical_ops(inputs_t *vars, char *cmd_str)
{
	unsigned int j = 0, index = 0;
	char op = '\0';
	int result = 0;

	while (vars->ops_cmd[j])
	{
		if (j == 0)
			result = run_command(vars, vars->ops_cmd[j]);
		op = get_operator(cmd_str, &index);
		if (op)
		{
			if (result == 0)
			{
				if (op == '&')
				{
					j++;
					result = run_command(vars, vars->ops_cmd[j]);
				}
				else /* operator == | */
					j++;
			}
			else /* if status > 0 */
			{
				if (op == '&')
					j++;
				else /* operator == | */
				{
					j++;
					result = run_command(vars, vars->ops_cmd[j]);
				}
			}
		}
		else /* no next operator */
			j++;
	}
}

/**
 * run_command - gets command with arguments and calls executing function
 * @vars: input variables struct
 * @cmd_str: current command
 * Return: status after execution
 */
int run_command(inputs_t *vars, char *cmd_str)
{
	size_t len = _strlen("alias");

	/* extract command & options, store in a string array */
	if ((strncmp(cmd_str, "alias", len) == 0) && (cmd_str[len] == ' '))
		vars->av = get_aliases(cmd_str, "\n \t\r");
	else
		vars->av = get_commands(cmd_str, "\n \t\r");
	if (vars->av && vars->av[0])
	{
		sub_env(vars);
		sub_alias(vars);
		/*if (check_for_builtins(vars) == NULL)*/
		if (exe_builtin(vars))
			get_path(vars);
	}
	free_av_and_alias(vars->av);
	return (vars->status);
}

/**
 * get_operator - check for logical operators in a line of command
 * @command: current command
 * @index: pointer to the logical operator index in command string
 * Return: the type of logical operator
 */
char get_operator(char *command, unsigned int *index)
{
	unsigned int i = *index;

	for (; command[i]; i++)
	{
		if (command[i] == '&' || command[i] == '|')
		{
			++i;
			if (command[i] == '&' || command[i] == '|')
				*index = i + 1;
			else
				return ('\0');

			return (command[i]);
		}
	}
	return ('\0');
}

