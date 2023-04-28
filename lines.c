#include "simple_shell.h"

/**
 * execute_line - Executes a line of input
 * @shell_data: Pointer to the shell data structure
 * Return: 1
 */
int execute_line(shell_info *shell_data)
{
	int (*builtin_func)(shell_info *data);

	if (shell_data->cmd_args[0] == NULL)
	{
		return (1);
	}

	builtin_func = get_builtin_func(shell_data->cmd_args[0]);

	if (builtin_func != NULL)
	{
		return (builtin_func(shell_data));
	}

	return (execute_cmd(shell_data));
}

/**
 * read_input_line - Reads a line of input
 * @is_eof: Pointer to a flag indicating if end-of-file was reached
 * Return: input
 */
char *read_input_line(int *is_eof)
{
	char *input = NULL;
	size_t buffer_size = 0;

	*is_eof = getline(&input, &buffer_size, stdin);

	return (input);
}
