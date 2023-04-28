#include "simple_shell.h"

/**
 * check_env_vars - Checks for environment variables in a string
 * @list_head: Pointer to the head of the list of environment variables
 * @str: String to check for environment variables
 * @data: Pointer to the shell data structure
 */
void check_env_vars(var_node **list_head, char *str, shell_info *data)
{
	int row, chr, j, value_len;
	char **env_vars;

	env_vars = data->ev;
	for (row = 0; env_vars[row]; row++)
	{
		for (j = 1, chr = 0; env_vars[row][chr]; chr++)
		{
			if (env_vars[row][chr] == '=')
			{
				value_len = _strlen(env_vars[row] + chr + 1);
				add_var_node(list_head, j, env_vars[row] + chr + 1, value_len);
				return;
		}

		if (str[j] == env_vars[row][chr])
			j++;
		else
			break;
		}
	}

	for (j = 0; str[j]; j++)
	{
		if (str[j] == ' ' || str[j] == '\t' || str[j] == ';' || str[j] == '\n')
			break;
	}

	add_var_node(list_head, j, NULL, 0);
}

/**
 * check_vars - Checks a string for variables
 * @list_head: Pointer to the head of the list of variables
 * @str: String to check for variables
 * @s_str: String containing the status variable
 * @data: Pointer to the shell data structure
 * Return: i
 */
int check_vars(var_node **list_head, char *str, char *s_str, shell_info *data)
{
	int i, status_len, pid_len;

	status_len = _strlen(s_str);
	pid_len = _strlen(data->process_id);

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				add_var_node(list_head, 2, s_str, status_len), i++;
			else if (str[i + 1] == '$')
				add_var_node(list_head, 2, data->process_id, pid_len), i++;
			else if (str[i + 1] == '\n')
				add_var_node(list_head, 0, NULL, 0);
			else if (str[i + 1] == '\0')
				add_var_node(list_head, 0, NULL, 0);
			else if (str[i + 1] == ' ')
				add_var_node(list_head, 0, NULL, 0);
			else if (str[i + 1] == '\t')
				add_var_node(list_head, 0, NULL, 0);
			else if (str[i + 1] == ';')
				add_var_node(list_head, 0, NULL, 0);
			else
				check_env_vars(list_head, str + i, data);
		}
	}

	return (i);
}

/**
 * replace_input - Replaces variables in a string
 * @list_head: Pointer to the head of the list of variables
 * @str: String to replace variables in
 * @n_str: New string with variables replaced
 * @n_len: Length of the new string
 * Return: new string
 */
char *replace_input(var_node **list_head, char *str, char *n_str, int n_len)
{
	var_node *index;
	int i, j, k;

	index = *list_head;
	for (j = i = 0; i < n_len; i++)
	{
		if (str[j] == '$')
		{
			if (!(index->vlen) && !(index->val_len))
			{
				n_str[i] = str[j];
				j++;
			}
			else if (index->vlen && !(index->val_len))
			{
				for (k = 0; k < index->vlen; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->val_len; k++)
				{
					n_str[i] = index->val[k];
					i++;
				}
				j += (index->vlen);
				i--;
			}
		index = index->next_node;
		}
		else
		{
			n_str[i] = str[j];
			j++;
		}
	}

	return (n_str);
}

/**
 * replace_var - Replaces variables in a string
 * @input_str: String to replace variables in
 * @shell_data: Pointer to the shell data structure
 * Return: new input
 */
char *replace_var(char *input_str, shell_info *shell_data)
{
	var_node *head, *index;
	char *status, *new_input;
	int old_len, new_len;

	status = convert_itoa(shell_data->exit_status);
	head = NULL;

	old_len = check_vars(&head, input_str, status, shell_data);

	if (head == NULL)
	{
		free(status);
		return (input_str);
	}

	index = head;
	new_len = 0;

	while (index != NULL)
	{
		new_len += (index->val_len - index->vlen);
		index = index->next_node;
	}

	new_len += old_len;

	new_input = malloc(sizeof(char) * (new_len + 1));
	new_input[new_len] = '\0';

	new_input = replace_input(&head, input_str, new_input, new_len);

	free(input_str);
	free(status);
	free_var_node(&head);

	return (new_input);
}
