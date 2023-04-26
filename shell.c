#include "simple_shell.h"

/**
 * free_shell_data - frees memory allocated for shell data
 * @shell_data: pointer to shell data structure
 *
 * Return: void
 */

void free_shell_data(shell_info *shell_data)
{
	unsigned int index;

	/* Free each environment variable */
	for (index = 0; shell_data->environment_vars[index]; index++)
	{
		free(shell_data->environment_vars[index]);
	}

	/* Free environment variables array */
	free(shell_data->environment_vars);

	/* Free process ID */
	free(shell_data->process_id);
}

/**
 * set_shell_data - initializes shell data structure
 * @shell_data: pointer to shell data structure
 * @args: command line arguments
 *
 * Return: void
 */
void set_shell_data(shell_info *shell_data, char **args)
{
	unsigned int index;

	/* Set command line arguments */
	shell_data->arguments = args;

	/* Initialize other members */
	shell_data->user_input = NULL;
	shell_data->arguments = NULL;
	shell_data->exit_status = 0;
	shell_data->command_counter = 1;

	/* Count environment variables */
	for (index = 0; environ[index]; index++)
		;

	/* Allocate memory for environment variables */
	shell_data->environment_vars = malloc(sizeof(char *) * (index + 1));

	/* Copy environment variables */
	for (index = 0; environ[index]; index++)
	{
		shell_data->environment_vars[index] = _strdup(environ[index]);
	}

	/* Set last element to NULL */
	shell_data->environment_vars[index] = NULL;

	/* Set process ID */
	shell_data->process_id = convert_itoa(getpid());
}
