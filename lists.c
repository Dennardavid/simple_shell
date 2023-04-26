#include "simple_shell.h"

/**
 * add_separator_to_end - adds a separator node to the end of a linked list
 * @list_head: double pointer to the head of the list
 * @sep_char: separator character to be added
 *
 * Return: pointer to the head of the list
 */

sep_node *add_separator_to_end(sep_node **list_head, char sep_char)
{
	sep_node *new_node, *temp;

	new_node = malloc(sizeof(sep_node));
	if (new_node == NULL)
		return (NULL);

	new_node->separator = sep_char;
	new_node->next = NULL;
	temp = *list_head;

	if (temp == NULL)
	{
		*list_head = new_node;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}

	return (*list_head);
}
