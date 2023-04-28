#include "simple_shell.h"

/**
 * is_current_dir - checks if current character in path string is ':'
 * @path_str: path string to check
 * @index: pointer to index of current character in path string
 *
 * Return: 1 if current character is ':', 0 otherwise
 */
int is_current_dir(char *path_str, int *index)
{
	if (path_str[*index] == ':')
		return (1);

	while (path_str[*index] != ':' && path_str[*index])
		(*index)++;

	if (path_str[*index])
		(*index)++;

	return (0);
}

/**
 * find_command_path - finds the path of a command
 * @cmd_str: command to find path of
 * @env_vars: environment variables
 *
 * Return: pointer to path of command
 */
char *find_command_path(char *cmd_str, char **env_vars)
{
	char *path, *path_copy, *path_token, *dir;
	int dir_len, cmd_len, i;
	struct stat st;

	path = get_env_var("PATH", env_vars);
	if (path)
	{
		path_copy = _strdup(path);
		cmd_len = _strlen(cmd_str);
		path_token = _strtok(path_copy, ":");
		i = 0;
		while (path_token != NULL)
		{
			if (is_current_dir(path, &i))
				if (stat(cmd_str, &st) == 0)
					return (cmd_str);
			dir_len = _strlen(path_token);
			dir = malloc(dir_len + cmd_len + 2);
			_strcpy(dir, path_token);
			_strcat(dir, "/");
			_strcat(dir, cmd_str);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(path_copy);
				return (dir);
			}
			free(dir);
			path_token = _strtok(NULL, ":");
		}
		free(path_copy);
		if (stat(cmd_str, &st) == 0)
			return (cmd_str);
		return (NULL);
	}
	if (cmd_str[0] == '/')
		if (stat(cmd_str, &st) == 0)
			return (cmd_str);
	return (NULL);
}

/**
 * is_cmd_executable - checks if command is executable
 * @shell_data: pointer to shell_info struct
 *
 * Return: index of command in input string if executable, -1 otherwise
 */
int is_cmd_executable(shell_info *shell_data)
{
	struct stat st;
	int i;
	char *input;

	input = shell_data->cmd_args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}

	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
		return (i);

	get_error_msg(shell_data, 127);
	return (-1);
}

/**
 * has_cmd_error - checks if command has an error
 * @dir_str: directory string
 * @shell_data: pointer to shell_info struct
 *
 * Return: 1 if command has an error, 0 otherwise
 */
int has_cmd_error(char *dir_str, shell_info *shell_data)
{
	if (dir_str == NULL)
	{
		get_error_msg(shell_data, 127);
		return (1);
	}

	if (_strcmp(shell_data->cmd_args[0], dir_str) != 0)
	{
		if (access(dir_str, X_OK) == -1)
		{
			get_error_msg(shell_data, 126);
			free(dir_str);
			return (1);
		}
		free(dir_str);
	}
	else
	{
		if (access(shell_data->cmd_args[0], X_OK) == -1)
		{
			get_error_msg(shell_data, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * execute_cmd - executes a command
 * @shell_data: pointer to shell_info struct
 *
 * Return: 1 on success
 */
int execute_cmd(shell_info *shell_data)
{
	pid_t pid;
	pid_t wpid;
	int status;
	int exec;
	char *dir;
	(void) wpid;

	exec = is_cmd_executable(shell_data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = find_command_path(shell_data->cmd_args[0], shell_data->ev);
		if (has_cmd_error(dir, shell_data) == 1)
			return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (exec == 0)
			dir = find_command_path(shell_data->cmd_args[0], shell_data->ev);
		else
			dir = shell_data->cmd_args[0];
		execve(dir + exec, shell_data->cmd_args, shell_data->ev);
	}
	else if (pid < 0)
	{
		perror(shell_data->arguments[0]);
		return (1);
	}
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	shell_data->exit_status = status / 256;
	return (1);
}
