#include "simple_shell.h"

/**
 * main - entry point for shell program
 * @argc: number of command line arguments
 * @args: array of command line arguments
 *
 * Return: exit status
 */
int main(int argc, char **args)
{
	shell_info shell_data;

	/* Suppress unused variable warning */
	(void) argc;

	/* Handle SIGINT signal */
	signal(SIGINT, handle_sigint);

	/* Initialize shell data */
	set_shell_data(&shell_data, args);

	/* Run shell loop */
	run_shell_loop(&shell_data);

	/* Free shell data */
	free_shell_data(&shell_data);

	/* Return exit status */
	if (shell_data.exit_status < 0)
	{
		return (255);
	}
	return (shell_data.exit_status);
}
