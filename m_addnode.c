#include "simple_shell.h"

/**
 * addinput_t - adds input_t node at the end
 * @head: pointer to the head of the list
 * @user_input: pointer to string with directory path
 * Return: pointer to the head node
 */
input_t *addinput_t(input_t **head, char *user_input)
{
	input_t	*iter = NULL;
	input_t	*new = NULL;

	if (head == NULL)
		return (NULL);
	new = malloc(sizeof(input_t));
	if (new == NULL)
		return (NULL);
	new->line = user_input;
	new->next = NULL;

	/* check if the head of list is not NULL */
	if (*head == NULL)
	{
		*head = new;
		return (*head);
	}
	iter = *head;
	/* loop till last element that is not NULL */
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = new;
	iter = NULL;
	new = NULL;
	return (*head);
}

