#include "simple_shell.h"

/**
 * run_shell_loop - Runs a shell loop
 * @shell_data: Pointer to the shell data structure
 */
void run_shell_loop(shell_info *shell_data)
{
	int loop, eof_flag;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "$ ", 3);
		input = read_input_line(&eof_flag);
		if (eof_flag != -1)
		{
			input = remove_comment(input);
			if (!input)
			{
				continue;
			}

			if (has_syntax_error(shell_data, input) == 1)
			{
				shell_data->exit_status = 2;
				free(input);
				continue;
			}
			input = replace_var(input, shell_data);
			loop = split_input_commands(shell_data, input);
			shell_data->command_counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

/**
 * remove_comment - Removes a comment from a string
 * @is: String containing the comment
 * Return: Comments
 */
char *remove_comment(char *is)
{
	int i, comment_start;

	comment_start = 0;
	for (i = 0; is[i]; i++)
	{
		if (is[i] == '#')
		{
			if (i == 0)
			{
				free(is);
				return (NULL);
			}

			if (is[i - 1] == ' ' || is[i - 1] == '\t' || is[i - 1] == ';')
				comment_start = i;
		}
	}

	if (comment_start != 0)
	{
		is = reallocate_memory(is, i, comment_start + 1);
		is[comment_start] = '\0';
	}

	return (is);
}
