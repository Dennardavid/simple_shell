#include "simple_shell.h"

/**
 * add_var_node - adds a variable node to a linked list
 * @list_head: double pointer to the head of the list
 * @vlen: length of the variable name
 * @val: value of the variable
 * @val_len: length of the value
 *
 * Return: pointer to the new node
 */
var_node *add_var_node(var_node **list_head, int vlen, char *val, int val_len)
{
	var_node *new_node;
	var_node *temp_node;

	new_node = malloc(sizeof(var_node));
	if (!new_node)
	{
		return (NULL);
	}

	new_node->vlen = vlen;
	new_node->val = val;
	new_node->val_len = val_len;
	new_node->next = NULL;

	if (*list_head == NULL)
	{
		*list_head = new_node;
	}
	else
	{
		temp_node = *list_head;
		while (temp_node->next != NULL)
		{
			temp_node = temp_node->next;
		}
		temp_node->next = new_node;
	}

	return (new_node);
}

/**
 * free_var_node - frees a linked list of variable nodes
 * @list_head: double pointer to the head of the list
 */

void free_var_node(var_node **list_head)
{
	var_node *temp_node;
	var_node *curr_node;

	if (!list_head)
	{
		current_node = *list_head;
		while ((temp_node = current_node) != NULL)
		{
			current_node = current_node->next;
			free(temp_node);
		}
		*list_head = NULL;
	}
}

/**
 * free_line_node - frees a linked list of line nodes
 * @list_head: double pointer to the head of the list
 */
void free_line_node(line_node **list_head)
{
	line_node *temp_node;
	line_node *current_node;

	if (!list_head)
	{
		current_node = *list_head;
		while ((temp_node = current_node) != NULL)
		{
			current_node = current_node->next;
			free(temp_node);
		}
		*list_head = NULL;
	}
}
