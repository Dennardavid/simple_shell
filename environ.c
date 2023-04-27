#include "simple_shell.h"

/**
 * cmp_env_name - compares the name of an environment variable
 * with a given name
 * @nenv: name of the environment variable
 * @name: given name
 *
 * Return: index of the equal sign + 1 if the names are equal, 0 otherwise
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * get_env_var - gets the value of an environment variable
 * @name_str: name of the environment variable
 * @env_vars: array of environment variables
 *
 * Return: pointer to the value of the environment variable
 */
char *get_env_var(const char *name_str, char **env_vars)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; env_vars[i]; i++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(env_vars[i], name_str);
		if (mov)
		{
			ptr_env = env_vars[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * print_env_vars - prints the environment variables
 * @shell_data: pointer to the shell_info structure
 *
 * Return: 1 on success
 */
int print_env_vars(shell_info *shell_data)
{
	int i, j;

	for (i = 0; shell_data->environment_vars[i]; i++)
	{

		for (j = 0; shell_data->environment_vars[i][j]; j++)
			;

		write(STDOUT_FILENO, shell_data->environment_vars[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	shell_data->exit_status = 0;

	return (1);
}
