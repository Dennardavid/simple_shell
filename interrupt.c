#include "simple_shell.h"

/**
 * handle_sigint - Handles the SIGINT signal (CTRL+C)
 * @sig: Signal number
 */
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}
