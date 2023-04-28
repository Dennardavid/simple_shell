#include "simple_shell.h"

/**
 * change_dir_to - changes the current working directory
 * @shell_data: pointer to the shell_info structure
 *
 * Return: void
 */
void change_dir_to(shell_info *shell_data)
{
	char current_dir[PATH_MAX];
	char *new_dir, *copy_current_dir, *copy_new_dir;

	getcwd(current_dir, sizeof(current_dir));

	new_dir = shell_data->cmd_args[1];
	if (chdir(new_dir) == -1)
	{
		get_error_msg(shell_data, 2);
		return;
	}

	copy_current_dir = _strdup(current_dir);
	set_env_var("OLDPWD", copy_current_dir, shell_data);

	copy_new_dir = _strdup(new_dir);
	set_env_var("PWD", copy_new_dir, shell_data);

	free(copy_current_dir);
	free(copy_new_dir);

	shell_data->exit_status = 0;

	chdir(new_dir);
}

/**
 * change_dir_dot - changes the directory to the parent directory
 * @shell_data: pointer to the shell_info structure
 *
 * Return: void
 */
void change_dir_dot(shell_info *shell_data)
{
	char current_dir[PATH_MAX];
	char *new_dir, *copy_current_dir, *copy_new_dir;

	getcwd(current_dir, sizeof(current_dir));

	new_dir = shell_data->cmd_args[1];
	if (chdir(new_dir) == -1)
	{
		get_error_msg(shell_data, 2);
		return;
	}

	copy_current_dir = _strdup(current_dir);
	set_env_var("OLDPWD", copy_current_dir, shell_data);

	copy_new_dir = _strdup(new_dir);
	set_env_var("PWD", copy_new_dir, shell_data);

	free(copy_current_dir);
	free(copy_new_dir);

	shell_data->exit_status = 0;

	chdir(new_dir);
}

/**
 * change_dir_to_home - changes the current directory to the home directory
 * @shell_data: pointer to the shell_info structure
 *
 * Return: void
 */
void change_dir_to_home(shell_info *shell_data)
{
	char *copy_current_dir, *home_dir;
	char current_dir[PATH_MAX];

	getcwd(current_dir, sizeof(current_dir));
	copy_current_dir = _strdup(current_dir);

	home_dir = get_env_var("HOME", shell_data->ev);

	if (home_dir == NULL)
	{
		set_env_var("OLDPWD", copy_current_dir, shell_data);
		free(copy_current_dir);
		return;
	}

	if (chdir(home_dir) == -1)
	{
		get_error_msg(shell_data, 2);
		free(copy_current_dir);
		return;
	}

	set_env_var("OLDPWD", copy_current_dir, shell_data);
	set_env_var("PWD", home_dir, shell_data);
	free(copy_current_dir);
	shell_data->exit_status = 0;
}

/**
 * change_dir_previous - change the current directory to the previous directory
 * @shell_data: pointer to the shell_info structure
 *
 * Return: void
 */
void change_dir_previous(shell_info *shell_data)
{
	char current_dir[PATH_MAX];
	char *copy_current_dir, *copy_old_dir, *old_dir, *new_dir;

	getcwd(current_dir, sizeof(current_dir));
	copy_current_dir = _strdup(current_dir);

	old_dir = get_env_var("OLDPWD", shell_data->ev);

	if (old_dir == NULL)
		copy_old_dir = copy_current_dir;
	else
		copy_old_dir = _strdup(old_dir);

	set_env_var("OLDPWD", copy_current_dir, shell_data);

	if (chdir(copy_old_dir) == -1)
		set_env_var("PWD", copy_current_dir, shell_data);
	else
		set_env_var("PWD", copy_old_dir, shell_data);

	new_dir = get_env_var("PWD", shell_data->ev);

	write(STDOUT_FILENO, new_dir, _strlen(new_dir));
	write(STDOUT_FILENO, "\n", 1);

	free(copy_current_dir);
	if (old_dir)
	{
		free(copy_old_dir);
	}

	shell_data->exit_status = 0;

	chdir(new_dir);
}

/**
 * cd_command - changes the current working directory
 * @shell_data: pointer to the shell_info structure
 *
 * Return: 1 on success
 */
int cd_command(shell_info *shell_data)
{
	char *new_dir;
	int is_home, is_home2, is_ddash;

	new_dir = shell_data->cmd_args[1];

	if (new_dir != NULL)
	{
		is_home = _strcmp("$HOME", new_dir);
		is_home2 = _strcmp("~", new_dir);
		is_ddash = _strcmp("--", new_dir);
	}

	if (new_dir == NULL || !is_home || !is_home2 || !is_ddash)
	{
		change_dir_to_home(shell_data);
		return (1);
	}

	if (_strcmp("-", new_dir) == 0)
	{
		change_dir_previous(shell_data);
		return (1);
	}

	if (_strcmp(".", new_dir) == 0 || _strcmp("..", new_dir) == 0)
	{
		change_dir_dot(shell_data);
		return (1);
	}

	change_dir_to(shell_data);

	return (1);
}
