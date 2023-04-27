#include "simple_shell.h"

/**
 * is_repeated_char - counts number of time a character is repeated
 *
 * @input_str: input string
 * @index: index
 * Return: number of repetitions
 */
int is_repeated_char(char *input_str, int index)
{
	if (*(input_str - 1) == *input_str)
	{
		return (is_repeated_char(input_str - 1, index + 1));
	}

	return (index);
}

/**
 * is_error_separator_operator - checks for errors in the separator operators
 * @str: input string
 * @index: index of the input string
 * @last_char: last character in the input string
 *
 * Return: index of the error or 0 if no error is found
 */
int is_error_separator_operator(char *str, int index, char last_char)
{
	int count;

	count = 0;
	if (*str == '\0')
		return (0);

	if (*str == ' ' || *str == '\t')
		return (is_error_separator_operator(str + 1, index + 1, last_char));

	if (*str == ';')
		if (last_char == '|' || last_char == '&' || last_char == ';')
			return (index);

	if (*str == '|')
	{
		if (last_char == ';' || last_char == '&')
			return (index);

		if (last_char == '|')
		{
			count = is_repeated_char(str, 0);
			if (count == 0 || count > 1)
				return (index);
		}
	}

	if (*str == '&')
	{
		if (last_char == ';' || last_char == '|')
			return (index);

		if (last_char == '&')
		{
			count = is_repeated_char(str, 0);
			if (count == 0 || count > 1)
				return (index);
		}
	}

	return (is_error_separator_operator(str + 1, index + 1, *str));
}

/**
 * find_first_char - finds first char
 *
 * @input_str: input string
 * @i: index
 * Return: 0 if success else -1
 */
int find_first_char(char *input_str, int *i)
{
	for (*i = 0; input_str[*i]; *i += 1)
	{
		if (input_str[*i] == ' ' || input_str[*i] == '\t')
			continue;

		if (input_str[*i] == ';' || input_str[*i] == '|' || input_str[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syn_err - prints a syntax error message
 * @shell_data: pointer to the shell_info structure
 * @str: input string
 * @index: index of the error in the input string
 * @bool_val: boolean value indicating if the error is
 * before or after the index
 *
 * Return: void
 */
void print_syn_err(shell_info *shell_data, char *str, int index, int bool_val)
{
	char *msg, *msg2, *msg3, *error_msg, *counter_str;
	int length;

	if (str[index] == ';')
	{
		if (bool_val == 0)
			msg = (str[index + 1] == ';' ? ";;" : ";");
		else
			msg = (str[index - 1] == ';' ? ";;" : ";");
	}

	if (str[index] == '|')
		msg = (str[index + 1] == '|' ? "||" : "|");

	if (str[index] == '&')
		msg = (str[index + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter_str = convert_itoa(shell_data->command_counter);
	length = _strlen(shell_data->arguments[0]) + _strlen(counter_str);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error_msg = malloc(sizeof(char) * (length + 1));
	if (error_msg == 0)
	{
		free(counter_str);
		return;
	}
	_strcpy(error_msg, shell_data->arguments[0]);
	_strcat(error_msg, ": ");
	_strcat(error_msg, counter_str);
	_strcat(error_msg, msg2);
	_strcat(error_msg, msg);
	_strcat(error_msg, msg3);
	_strcat(error_msg, "\0");

	write(STDERR_FILENO, error_msg, length);
	free(error_msg);
	free(counter_str);
}

/**
 * has_syntax_error - checks if the input string has a syntax error
 * @shell_data: pointer to the shell_info structure
 * @input_str: input string
 *
 * Return: 1 if there is a syntax error, 0 otherwise
 */
int has_syntax_error(shell_info *shell_data, char *input_str)
{
	int begin = 0;
	int first_char_index = 0;
	int i = 0;

	first_char_index = find_first_char(input_str, &begin);
	if (first_char_index == -1)
	{
		print_syn_err(shell_data, input_str, begin, 0);
		return (1);
	}

	i = is_error_separator_operator(input_str + begin, 0, *(input_str + begin));
	if (i != 0)
	{
		print_syn_err(shell_data, input_str, begin + i, 1);
		return (1);
	}

	return (0);
}
