#include "simple_shell.h"

/**
 * print_help_env - Help information for the builtin env
 * Return: no return
 */
void print_help_env(void)
{
	char *help_msg = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "Print help information about shell enviroment.\n";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));

}
/**
 * print_help_setenv - Help information for the builtin setenv
 * Return: no return
 */
void print_help_setenv(void)
{
	char *help_msg = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "int replace)\n\t";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}
/**
 * print_help_unsetenv - Help information for the builtin unsetenv
 * Return: no return
 */
void print_help_unsetenv(void)
{
	char *help_msg = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}


/**
 * print_general_help - Entry point for help information for the help builtin
 */
void print_general_help(void)
{
	char *help_msg = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "These commands are defined internally.Type 'help' to see list";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "Type 'help name' to find out more about the function 'name'.\n\n";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "[dir]\nexit: exit [n]\n env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}
/**
 * print_help_exit - Help information fot the builint exit
 */
void print_help_exit(void)
{
	char *help_msg = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
	help_msg = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help_msg, _strlen(help_msg));
}
