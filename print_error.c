#include "simple_shell.h"

/**
 * concat_cd_path - concatenates error message for cd command
 * @shell_data: pointer to shell_info struct
 * @error: error message string
 * @str: version string
 * @msg: message string
 *
 * Return: pointer to concatenated error message
 */
char *concat_cd_path(shell_info *shell_data, char *error, char *str, char *msg)
{
	char *not_allowed;

	_strcpy(error, shell_data->arguments[0]);
	_strcat(error, ": ");
	_strcat(error, str);
	_strcat(error, ": ");
	_strcat(error, shell_data->cmd_args[0]);
	_strcat(error, msg);
	if (shell_data->cmd_args[1][0] == '-')
	{
		not_allowed = malloc(3);
		not_allowed[0] = '-';
		not_allowed[1] = shell_data->cmd_args[1][1];
		not_allowed[2] = '\0';
		_strcat(error, not_allowed);
		free(not_allowed);
	}
	else
	{
		_strcat(error, shell_data->cmd_args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * get_cd_error_msg - gets error message for cd command
 * @shell_data: pointer to shell_info struct
 *
 * Return: pointer to error message
 */
char *get_cd_error_msg(shell_info *shell_data)
{
	int length, len_id;
	char *err, *str, *msg;

	str = convert_itoa(shell_data->command_counter);
	if (shell_data->cmd_args[1][0] == '-')
	{
		msg = ": option not allowed ";
		len_id = 2;
	}
	else
	{
		msg = ": can't change directory to ";
		len_id = _strlen(shell_data->cmd_args[1]);
	}

	length = _strlen(shell_data->arguments[0]);
	length += _strlen(shell_data->cmd_args[0]);
	length += _strlen(str) + _strlen(msg) + len_id + 5;
	err = malloc(sizeof(char) * (length + 1));

	if (err == 0)
	{
		free(str);
		return (NULL);
	}

	err = concat_cd_path(shell_data, err, str, msg);

	free(str);

	return (err);
}

/**
 * get_not_found_error_msg - gets error message
 * for command not found
 * @shell_data: pointer to shell_info struct
 *
 * Return: pointer to error message
 */
char *get_not_found_error_msg(shell_info *shell_data)
{
	int length;
	char *err;
	char *str;

	str = convert_itoa(shell_data->command_counter);
	length = _strlen(shell_data->arguments[0]) + _strlen(str);
	length += _strlen(shell_data->cmd_args[0]) + 16;
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
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(str);
	return (err);
}

/**
 * get_exit_error_msg - gets error message for exit command
 * @shell_data: pointer to shell_info struct
 *
 * Return: pointer to error message
 */
char *get_exit_error_msg(shell_info *shell_data)
{
	int length;
	char *err;
	char *str;

	str = convert_itoa(shell_data->command_counter);
	length = _strlen(shell_data->arguments[0]) + _strlen(str);
	length += _strlen(shell_data->cmd_args[0]);
	length += _strlen(shell_data->cmd_args[1]) + 23;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(str);
		return (NULL);
	}
	_strcpy(err, shell_data->arguments[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, shell_data->cmd_args[0]);
	_strcat(err, ": Number not allowed: ");
	_strcat(err, shell_data->cmd_args[1]);
	_strcat(err, "\n\0");
	free(str);

	return (err);
}

/**
 * get_error_msg - gets error message
 * @shell_data: pointer to shell_info struct
 * @error_val: error value
 *
 * Return: error value
 */
int get_error_msg(shell_info *shell_data, int error_val)
{
	char *err;

	switch (error_val)
	{
	case -1:
		err = get_env_error_msg(shell_data);
		break;
	case 126:
		err = get_path_126_error_msg(shell_data);
		break;
	case 127:
		err = get_not_found_error_msg(shell_data);
		break;
	case 2:
		if (_strcmp("exit", shell_data->cmd_args[0]) == 0)
			err = get_exit_error_msg(shell_data);
		else if (_strcmp("cd", shell_data->cmd_args[0]) == 0)
			err = get_cd_error_msg(shell_data);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, _strlen(err));
		free(err);
	}

	shell_data->exit_status = error_val;
	return (error_val);
}
