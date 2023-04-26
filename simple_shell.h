#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFFSIZE 1024
#define TOK_BUFFSIZE 128
#define TOK_DELIMITER " \t\r\n\a"

extern char **environ;

/**
 * struct info - structure to hold shell information
 * @arguments: array of arguments
 * @user_input: user input string
 * @command_args: array of command arguments
 * @exit_status: exit status of last command
 * @command_counter: counter for number of commands entered
 * @environment_vars: array of environment variables
 * @process_id: process ID of shell
 *
 * Description: This structure holds information about the shell,
 * including arguments, user input, command arguments, exit status,
 * command counter, environment variables, and process ID.
 */

typedef struct info
{
	char **arguments;
	char *user_input;
	char **command_args;
	int exit_status;
	int command_counter;
	char **environment_vars;
	char *process_id;
} shell_info;

/**
 * struct sep_node_s - structure to hold separator information
 * @sep_char: character separator
 * @next_node: pointer to next separator in list
 *
 * Description: This structure holds information about a separator,
 * including the separator character and a pointer to the next separator
 * in the list.
 */
typedef struct sep_node_s
{
	char sep_char;
	struct sep_node_s *next_node;
} sep_node;

/**
 * struct line_node_s - structure to hold line information
 * @line_str: line string
 * @next_node: pointer to next line in list
 *
 * Description: This structure holds information about a line,
 * including the line string and a pointer to the next line in the list.
 */
typedef struct line_node_s
{
	char *line_str;
	struct line_node_s *next_node;
} line_node;

/**
 * struct r_var_node - structure to hold variable information
 * @variable_length: length of variable
 * @value: value of variable
 * @value_length: length of value
 * @next_node: pointer to next variable in list
 *
 * Description: This structure holds information about a variable,
 * including the length of the variable, the value of the variable,
 * the length of the value, and a pointer to the next variable in the list.
 */

typedef struct var_node_s
{
	int variable_length;
	char *value;
	int value_length;
	struct var_node_s *next_node;
} var_node;

/**
 * struct builtin_node - structure to hold builtin command information
 * @cmd_name: name of builtin command
 * @f: function pointer to builtin command
 *
 * Description: This structure holds information about a builtin command,
 * including the name of the command and a function pointer to the command.
 */

typedef struct builtin_node
{
	char *cmd_name;
	int (*f)(shell_info *shell_data);
} builtin_t;

/* lists.c */
sep_node *add_separator_to_end(sep_node **list_head, char sep_char);
void freeSeparator(sep_node **list_head);
line_node *add_line_to_end(line_node **list_head, char *line_str);

/* more_lists.c */
var_node *add_var_node(var_node **list_head, int vlen, char *val, int val_len);
void free_var_node(var_node **list_head);
void free_line_node(line_node **list_head);

/* strings.c */
char *_strcat(char *str1, const char *str2);
char *_strcpy(char *dest, char *src);
int _strcmp(const char *str1, const char *str2);
char *_strdup(const char *str);
char *_strchr(const char *str, char c);

/* more_strings.c */
int _strlen(const char *str);
char *_strtok(char *str, const char *delim);
int _isDigit(const char *s);
void reverse_string(char *str);

/* getline.c */
void copy_line(char **line_ptr, size_t *size, char *buffer, size_t index);
ssize_t read_line(char **line_ptr, size_t *size, FILE *stream);

/* exec_line */
int execute_line(shell_info *shell_data);

/* cmd_exec.c */
int is_current_dir(char *path_str, int *index);
char *find_command_path(char *cmd_str, char **env_vars);
int is_cmd_executable(shell_info *shell_data);
int has_cmd_error(char *dir_str, shell_info *shell_data);
int execute_cmd(shell_info *shell_data);

/* env1.c */
char *get_env_var(const char *name_str, char **env_vars);
int print_env_vars(shell_info *shell_data);

/* env2.c */
char *copy_var_info(char *name_str, char *value_str);
void set_env_var(char *name_str, char *value_str, shell_info *shell_data);
int set_env_var_cmd(shell_info *shell_data);
int unset_env_var_cmd(shell_info *shell_data);

/* cd.c */
void change_dir_dot(shell_info *shell_data);
void change_dir_to(shell_info *shell_data);
void change_dir_previous(shell_info *shell_data);
void change_dir_to_home(shell_info *shell_data);
int cd_command(shell_info *shell_data);

/* builtin */
int (*get_builtin_func(char *cmd_str))(shell_info *shell_data);

/* _exit.c */
int exit_command(shell_info *shell_data);

/* stdlib.c */
int get_num_len(int num);
char *convert_itoa(int num);
int convert_atoi(char *str);

/* error1.c */
char *concat_cd_path(shell_info *, char *, char *, char *);
char *get_cd_error_msg(shell_info *shell_data);
char *get_not_found_error_msg(shell_info *shell_data);
char *get_exit_error_msg(shell_info *shell_data);
int get_error_msg(shell_info *shell_data, int error_val);

/* error2.c */
char *get_alias_error_msg(char **args);
char *get_env_error_msg(shell_info *shell_data);
char *get_syntax_error_msg(char **args);
char *get_permission_error_msg(char **args);
char *get_path_126_error_msg(shell_info *shell_data);

/* sigint.c */
void handle_sigint(int sig);

/* help.c */
void print_help_env(void);
void print_help_setenv(void);
void print_help_unsetenv(void);
void print_general_help(void);
void print_help_exit(void);

/* help2.c */
void print_help(void);
void print_help_alias(void);
void print_help_cd(void);
int help_command(shell_info *shell_data);

#endif
