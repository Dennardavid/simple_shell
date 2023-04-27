#include "simple_shell.h"

/**
 * copy_var_info - copies the name and value of an 
 * environment variable into a new string
 * @name_str: name of the environment variable
 * @value_str: value of the environment variable
 *
 * Return: pointer to the new string
 */
char *copy_var_info(char *name_str, char *value_str)
{
	char *new_str;
	int len_name, len_value, len;

	len_name = _strlen(name_str);
	len_value = _strlen(value_str);
	len = len_name + len_value + 2;
	new_str = malloc(sizeof(char) * (len));
	_strcpy(new_str, name_str);
	_strcat(new_str, "=");
	_strcat(new_str, value_str);
	_strcat(new_str, "\0");

	return (new_str);
}

/**
 * set_env_var - sets the value of an environment variable
 * @name_str: name of the environment variable
 * @value_str: value of the environment variable
 * @shell_data: pointer to the shell_info structure
 *
 * Return: void
 */
void set_env_var(char *name_str, char *value_str, shell_info *shell_data)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; shell_data->environment_vars[i]; i++)
	{
		var_env = _strdup(shell_data->environment_vars[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name_str) == 0)
		{
			free(shell_data->environment_vars[i]);
			shell_data->environment_vars[i] = copy_var_info(name_env, value_str);
			free(var_env);
			return;
		}
		free(var_env);
	}

	shell_data->environment_vars = realloc_db_ptr(shell_data->environment_vars, i, sizeof(char *) * (i + 2));
	shell_data->environment_vars[i] = copy_var_info(name_str, value_str);
	shell_data->environment_vars[i + 1] = NULL;
}

/**
 * set_env_var_cmd - sets an environment variable
 * @shell_data: pointer to shell_info struct
 *
 * Return: 1 on success
 */
int set_env_var_cmd(shell_info *shell_data)
{
	/* check if two arguments are provided */
	if (shell_data->arguments[1] == NULL || shell_data->arguments[2] == NULL)
	{
		get_error_msg(shell_data, -1);
		return (1);
	}

	/* set environment variable */
	set_env_var(shell_data->arguments[1], shell_data->arguments[2], shell_data);

	return (1);
}

/**
 * unset_env_var_cmd - unsets an environment variable
 * @shell_data: pointer to shell_info struct
 *
 * Return: 1 on success
 */
int unset_env_var_cmd(shell_info *shell_data)
{
	char **new_environ;
	char *env_var, *env_name;
	int i, j, k;

	/* check if argument is provided */
	if (shell_data->arguments[1] == NULL)
	{
		get_error_msg(shell_data, -1);
		return (1);
	}

	k = -1;
	/* find index of environment variable to unset */
	for (i = 0; shell_data->environment_vars[i]; i++)
	{
		env_var = _strdup(shell_data->environment_vars[i]);
		env_name = _strtok(env_var, "=");
		if (_strcmp(env_name, shell_data->arguments[1]) == 0)
			k = i;
		free(env_var);
	}

	if (k == -1)
	{
		get_error_msg(shell_data, -1);
		return (1);
	}

	new_environ = malloc(sizeof(char *) * i);

	for (i = j = 0; shell_data->environment_vars[i]; i++)
	{
		if (i != k)
			new_environ[j++] = shell_data->environment_vars[i];
	}

	new_environ[j] = NULL;
	free(shell_data->environment_vars[k]);
	free(shell_data->environment_vars);
	shell_data->environment_vars = new_environ;

	return (1);
}
