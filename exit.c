#include "simple_shell.h"

/**
 * exit_command - Handles the exit command
 * @shell_data: Pointer to the shell data structure
 * Return: 0
 */
int exit_command(shell_info *shell_data)
{
	unsigned int u_status;
	int is_digit;
	int len;
	int max_int;

	if (shell_data->arguments[1])
	{
		u_status = convert_atoi(shell_data->arguments[1]);
		is_digit = _isDigit(shell_data->arguments[1]);
		len = _strlen(shell_data->arguments[1]);
		max_int = u_status > (unsigned int)INT_MAX;
		if (!is_digit || len > 10 || max_int)
		{
			get_error_msg(shell_data, 2);
			shell_data->exit_status = 2;
			return (1);
		}
		shell_data->exit_status = (u_status % 256);
	}
	return (0);
}
