#include "simple_shell.h"

/**
 * get_env_error_msg - gets error message for environment variable command
 * @shell_data: pointer to shell_info struct
 *
 * Return: pointer to error message
 */
char *get_env_error_msg(shell_info *shell_data)
{
	int length;
	char *err;
	char *str;
	char *msg;

	str = convert_itoa(shell_data->command_counter);
	msg = ": Unable to perform action\n";
	length = _strlen(shell_data->arguments[0]) + _strlen(str);
	length += _strlen(shell_data->cmd_args[0]) + _strlen(msg) + 4;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(str);
		return (NULL);
	}

	_strcpy(err, shell_data->arguments[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, shell_data->cmd_args[0]);
	_strcat(err, msg);
	_strcat(err, "\0");
	free(str);

	return (err);
}

/**
 * get_path_126_error_msg - generates error message for path 126 error
 * @shell_data: pointer to shell_info struct
 *
 * Return: pointer to error message string
 */
char *get_path_126_error_msg(shell_info *shell_data)
{
	int length;
	char *str;
	char *err;

	str = convert_itoa(shell_data->command_counter);
	length = _strlen(shell_data->arguments[0]) + _strlen(str);
	length += _strlen(shell_data->cmd_args[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(str);
		return (NULL);
	}
	_strcpy(err, shell_data->arguments[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, shell_data->cmd_args[0]);
	_strcat(err, ": Permission denied\n");
	_strcat(err, "\0");
	free(str);
	return (err);
}
