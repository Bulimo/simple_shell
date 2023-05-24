#include "simple_shell.h"

/**
  * readlines - creates a struct of user inputs
  * @head: address to the pointer of first node
  * @isterm: 1 if is a terminal, 0 if not
  * Return: the head node
  */
input_t *readlines(input_t **head, int isterm)
{
	ssize_t nread;
	char *user_input = NULL;
	size_t len = 0;

	if (head == NULL)
		return (NULL);
	if (isterm)
		write(STDOUT_FILENO, "$ ", 2);
	/* loop through stdin buffer */
	nread = getline(&user_input, &len, stdin);
	while (nread != -1)
	{
		if (nread > 1 && user_input[nread - 1] == '\n')
			user_input[nread - 1] = '\0';
		else
		{
			free(user_input);
			return (*head);
		}
		addinput_t(head, user_input);
		user_input = NULL;
		if (isterm)
			return (*head);
		nread = getline(&user_input, &len, stdin);
	}
	return (*head);
}

