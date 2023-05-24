#include "simple_shell.h"

/**
 * main - a program that propmts a user to enter a command to be executed
 * @ac: count of arguments passed
 * @av: string array of arguments
 * Return: 0 success, 1 error
 */

int main(__attribute__((unused))int ac, char **av)
{
	char *full_path = NULL;
	char **envp = environ, **args = NULL;
	int isterm;
	input_t *head = NULL, *iter = NULL;
	static int err_count;

	isterm = isatty(STDIN_FILENO);
	do {
		head = readlines(&head, isterm);
		iter = head;
		while (iter)
		{
			if (strcmp(iter->line, "exit") == 0)
			{
				freeinput_t(&head);
				return (0);
			}
			args = get_args(iter->line);
			if (args == NULL || *args == NULL)
				continue;

			full_path = create_path(args[0]);
			if (full_path)
			{
				execute(full_path, args, envp);
				free(full_path);
			}
			else
				printf("%s: %d: %s: not found\n", av[0], ++err_count, args[0]);
			free(args);
			iter = iter->next;
		}
		freeinput_t(&head);
	} while (isterm);
	freeinput_t(&head);
	return (0);
}
