#include "simple_shell.h"

/**
 * replace_char - replaces characters in the input string
 * @input_str: input string
 * @bool_val: boolean value indicating if the characters should
 * be replaced or restored
 *
 * Return: pointer to the modified input string
 */
char *replace_char(char *input_str, int bool_val)
{
	int i;

	if (bool_val == 0)
	{
		for (i = 0; input_str[i]; i++)
		{
			if (input_str[i] == '|')
			{
				if (input_str[i + 1] != '|')
					input_str[i] = 16;
				else
					i++;
			}

			if (input_str[i] == '&')
			{
				if (input_str[i + 1] != '&')
					input_str[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input_str[i]; i++)
		{
			input_str[i] = (input_str[i] == 16 ? '|' : input_str[i]);
			input_str[i] = (input_str[i] == 12 ? '&' : input_str[i]);
		}
	}
	return (input_str);
}

/**
 * add_sep_line_nodes - adds separator and line nodes to their
 * respective linked lists
 * @sep_head: pointer to the head of the separator linked list
 * @line_head: pointer to the head of the line linked list
 * @str: input string
 *
 * Return: void
 */
void add_sep_line_nodes(sep_node **sep_head, line_node **line_head, char *str)
{
	int i;
	char *line;

	str = replace_char(str, 0);

	for (i = 0; str[i]; i++)
	{
		if (str[i] == ';')
			add_separator_to_end(sep_head, str[i]);

		if (str[i] == '|' || str[i] == '&')
		{
			add_separator_to_end(sep_head, str[i]);
			i++;
		}
	}

	line = _strtok(str, ";|&");
	do {
		line = replace_char(line, 1);
		add_line_to_end(line_head, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * move_to_next - moves the separator and line pointers
 * to the next node
 * @s_ptr: pointer to the separator pointer
 * @l_ptr: pointer to the line pointer
 * @shell_data: pointer to the shell_info structure
 *
 * Return: void
 */
void move_to_next(sep_node **s_ptr, line_node **l_ptr, shell_info *shell_data)
{
	int loop_sep;
	sep_node *sep_list;
	line_node *line_list;

	loop_sep = 1;
	sep_list = *s_ptr;
	line_list = *l_ptr;

	while (sep_list != NULL && loop_sep)
	{
		if (shell_data->exit_status == 0)
		{
			if (sep_list->sep_char == '&' || sep_list->sep_char == ';')
				loop_sep = 0;
			if (sep_list->sep_char == '|')
				line_list = line_list->next_node, sep_list = sep_list->next_node;
		}
		else
		{
			if (sep_list->sep_char == '|' || sep_list->sep_char == ';')
				loop_sep = 0;
			if (sep_list->sep_char == '&')
				line_list = line_list->next_node, sep_list = sep_list->next_node;
		}
		if (sep_list != NULL && !loop_sep)
			sep_list = sep_list->next_node;
	}

	*s_ptr = sep_list;
	*l_ptr = line_list;
}

/**
 * split_input_commands - splits the input string into
 * commands and executes them
 * @shell_data: pointer to the shell_info structure
 * @input_str: input string
 *
 * Return: 0 if the loop should be exited, 1 otherwise
 */
int split_input_commands(shell_info *shell_data, char *input_str)
{

	sep_node *head_s, *list_s;
	line_node *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_sep_line_nodes(&head_s, &head_l, input_str);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		shell_data->user_input = list_l->line_str;
		shell_data->arguments = split_input_line(shell_data->user_input);
		loop = execute_line(shell_data);
		free(shell_data->arguments);

		if (loop == 0)
			break;

		move_to_next(&list_s, &list_l, shell_data);

		if (list_l != NULL)
			list_l = list_l->next_node;
	}

	freeSeparator(&head_s);
	free_line_node(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_input_line - splits the input string into tokens
 * @input_str: input string
 *
 * Return: pointer to an array of tokens
 */
char **split_input_line(char *input_str)
{
	size_t buffer_size;
	size_t i;
	char **tokens;
	char *token;

	buffer_size = TOKEN_BUFFSIZE;
	tokens = malloc(sizeof(char *) * (buffer_size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input_str, TOKEN_DELIMITER);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == buffer_size)
		{
			buffer_size += TOKEN_BUFFSIZE;
			tokens = realloc_db_ptr(tokens, i, sizeof(char *) * buffer_size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOKEN_DELIMITER);
		tokens[i] = token;
	}

	return (tokens);
}
