#include "simple_shell.h"

/**
  * freeinput_t - frees the input_t list
  * @head:  address to the pointer of the node of the list
  * Return: nothing
  */
void freeinput_t(input_t **head)
{
	input_t *node = NULL;
	input_t *node2 = NULL;

	node = *head;
	while (node != NULL)
	{
		node2 = node;
		node = node->next;
		free(node2->line);
		free(node2);
	}
	*head = NULL;
	node = NULL;
}

