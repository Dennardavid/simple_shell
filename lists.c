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
	{
		return (NULL);
	}

	new_node->sep_char = sep_char;
	new_node->next_node = NULL;
	temp = *list_head;

	if (temp == NULL)
	{
		*list_head = new_node;
	}
	else
	{
		while (temp->next_node != NULL)
		{
			temp = temp->next_node;
		}
		temp->next_node = new_node;
	}

	return (*list_head);
}

/**
 * freeSeparator - frees a linked list of separator nodes
 * @list_head: double pointer to the head of the list
 */

void freeSeparator(sep_node **list_head)
{
	sep_node *temp;
	sep_node *current;

	if (list_head != NULL)
	{
		current = *list_head;
		while ((temp = current))
		{
			current = current->next_node;
			free(temp);
		}
		*list_head = NULL;
	}
}

/**
 * add_line_to_end - adds a line node to the end of a linked list
 * @list_head: double pointer to the head of the list
 * @line_str: line string to be added
 *
 * Return: pointer to the head of the list
 */

line_node *add_line_to_end(line_node **list_head, char *line_str)
{
	line_node *new_node, *temp_node;

	new_node = malloc(sizeof(line_node));
	if (new_node == NULL)
	{
		return (NULL);
	}

	new_node->line_str = line_str;
	new_node->next_node = NULL;
	temp_node = *list_head;

	if (temp_node == NULL)
	{
		*list_head = new_node;
	}
	else
	{
		while (temp_node->next_node != NULL)
		{
			temp_node = temp_node->next_node;
		}
		temp_node->next_node = new_node;
	}

	return (*list_head);
}
