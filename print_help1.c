#include "simple_shell.h"

/**
 * print_help - prints help message
 */
void print_help(void)
{
	char *help_msg = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "Show information on builtin commands.\n ";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "Show brief summary of builtin commands.\n";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}

/**
 * print_help_alias - Help information on aliases.
 */
void print_help_alias(void)
{
	char *help_msg = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "Show aliases.\n ";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}

/**
 * print_help_cd - Help information for the builtin alias.
 */
void print_help_cd(void)
{
	char *help_msg = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "Change the shell working directory.\n ";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}

/**
 * help_command - prints help message for a command
 * @shell_data: pointer to shell_info struct
 *
 * Return: 1 on success
 */
int help_command(shell_info *shell_data)
{
	if (shell_data->cmd_args[1] == NULL)
		print_general_help();
	else if (_strcmp(shell_data->cmd_args[1], "setenv") == 0)
		print_help_setenv();
	else if (_strcmp(shell_data->cmd_args[1], "env") == 0)
		print_help_env();
	else if (_strcmp(shell_data->cmd_args[1], "unsetenv") == 0)
		print_help_unsetenv();
	else if (_strcmp(shell_data->cmd_args[1], "help") == 0)
		print_help();
	else if (_strcmp(shell_data->cmd_args[1], "exit") == 0)
		print_help_exit();
	else if (_strcmp(shell_data->cmd_args[1], "cd") == 0)
		print_help_cd();
	else if (_strcmp(shell_data->cmd_args[1], "alias") == 0)
		print_help_alias();
	else
		write(STDERR_FILENO, shell_data->cmd_args[0],
		      _strlen(shell_data->cmd_args[0]));

	shell_data->exit_status = 0;
	return (1);
}
