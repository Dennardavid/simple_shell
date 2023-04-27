#include "simple_shell.h"

/**
 * get_builtin_func - returns a pointer to the function that
 * matches the command string
 * @cmd_str: command string
 *
 * Return: pointer to the function that matches the command string
 */
int (*get_builtin_func(char *cmd_str))(shell_info *)
{
	builtin_t builtin[] = {
		{ "env", print_env_vars },
		{ "exit", exit_command },
		{ "setenv", set_env_var_cmd },
		{ "unsetenv", unset_env_var_cmd },
		{ "cd", cd_command },
		{ "help", help_command },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].cmd_name; i++)
	{
		if (_strcmp(builtin[i].cmd_name, cmd_str) == 0)
			break;
	}

	return (builtin[i].f);
}
