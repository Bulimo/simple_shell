#include "simple_shell.h"

/**
  * printnode - prints a node
  * @head: address of the pointer to 1st node
  * Return: nothing
  */
void printnode(input_t **head)
{

	input_t *iter = *head;

	while (iter)
	{
		if (iter->line != NULL)
			printf("%s\n", iter->line);
		else
			printf("no dat added in the node\n");
		iter = iter->next;
	}
}

