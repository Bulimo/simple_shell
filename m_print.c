#include "shell.h"

/**
 * print_error - prints error messages to standard error
 * @vars: pointer to struct of variables
 * @msg: message to print
 *
 * Return: void
 */
void print_error(inputs_t *vars, char *msg)
{
	char *count;

	_puts(vars->argv[0]);
	_puts(": ");
	count = _uitoa(vars->count);
	_puts(count);
	free(count);
	_puts(": ");
	_puts(vars->av[0]);
	if (msg)
	{
		_puts(msg);
	}
	else
		perror("");
}

/**
 * _puts - writes a string to standard output
 * @str: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t _puts(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDOUT_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (len);
}


/**
 * print_prompt - prints the shell prompt
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		_puts("$ ");
}

