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
#define TOKEN_BUFFSIZE 128
#define TOKEN_DELIMITER " \t\r\n\a"

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
	char **cmd_args;
	int exit_status;
	int command_counter;
	char **ev;
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
 * struct var_node_s - structure to hold variable information
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
	int vlen;
	char *val;
	int val_len;
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
char *_strchr(char *str, char c);

/* more_strings.c */
int _strlen(const char *str);
char *_strtok(char *str, const char *delim);
int _isDigit(const char *str);
void reverse_string(char *str);
int compare_chars(char *str, const char *delim);

/* exit.c */
int exit_command(shell_info *shell_data);

/* memory_management.c */
void copy_memory(void *new_ptr, const void *old_ptr, unsigned int new_size);
void *reallocate_memory(void *old_ptr, unsigned int old_s, unsigned int new_s);
char **redbptr(char **old_ptr, unsigned int old_s, unsigned int new_s);

/* shell.c */
void free_shell_data(shell_info *shell_data);
void set_shell_data(shell_info *shell_data, char **args);

/* lines */
int execute_line(shell_info *shell_data);
char *read_input_line(int *is_eof);

/* _getline.c */
void copy_line(char **line_ptr, size_t *size, char *buffer, size_t index);
ssize_t read_line(char **line_ptr, size_t *size, FILE *stream);

/* loop.c */
char *remove_comment(char *is);
void run_shell_loop(shell_info *shell_data);

/* variables.c */
void check_env_vars(var_node **list_head, char *str, shell_info *data);
int check_vars(var_node **list_head, char *str, char *s_str, shell_info *data);
char *replace_input(var_node **list_head, char *str, char *n_str, int n_len);
char *replace_var(char *input_str, shell_info *shell_data);

/* sigint.c */
void handle_sigint(int sig);

/* change_directory.c */
void change_dir_dot(shell_info *shell_data);
void change_dir_to(shell_info *shell_data);
void change_dir_previous(shell_info *shell_data);
void change_dir_to_home(shell_info *shell_data);
int cd_command(shell_info *shell_data);

/* builtin.c */
int (*get_builtin_func(char *cmd_str))(shell_info *);

/* exit_shell.c */
int exit_command(shell_info *shell_data);

/* syntax_error.c */
int is_repeated_char(char *input_str, int index);
int is_error_separator_operator(char *input_str, int index, char last_char);
int find_first_char(char *input_str, int *index);
void print_syn_err(shell_info *shell_data, char *str, int index, int bool_val);
int has_syntax_error(shell_info *shell_data, char *input_str);

/* split.c */
char *replace_char(char *input_str, int bool_val);
void add_sep_line_nodes(sep_node **sep_head, line_node **line_head, char *str);
void move_to_next(sep_node **s_ptr, line_node **l_ptr, shell_info *shell_data);
int split_input_commands(shell_info *shell_data, char *input_str);
char **split_input_line(char *input_str);

/* execute_command.c */
int is_current_dir(char *path_str, int *index);
char *find_command_path(char *cmd_str, char **env_vars);
int is_cmd_executable(shell_info *shell_data);
int has_cmd_error(char *dir_str, shell_info *shell_data);
int execute_cmd(shell_info *shell_data);

/* environ.c */
char *get_env_var(const char *name_str, char **env_vars);
int print_env_vars(shell_info *shell_data);
char *copy_var_info(char *name_str, char *value_str);

/* environ1.c */
void set_env_var(char *name_str, char *value_str, shell_info *shell_data);
int set_env_var_cmd(shell_info *shell_data);
int unset_env_var_cmd(shell_info *shell_data);

/* print_help.c */
void print_help_env(void);
void print_help_setenv(void);
void print_help_unsetenv(void);
void print_general_help(void);
void print_help_exit(void);

/* print_help1.c */
void print_help(void);
void print_help_alias(void);
void print_help_cd(void);
int help_command(shell_info *shell_data);

/* standard_library.c */
int get_num_len(int num);
char *convert_itoa(int num);
int convert_atoi(char *str);

/* print_error.c */
char *concat_cd_path(shell_info *, char *, char *, char *);
char *get_cd_error_msg(shell_info *shell_data);
char *get_not_found_error_msg(shell_info *shell_data);
char *get_exit_error_msg(shell_info *shell_data);
int get_error_msg(shell_info *shell_data, int error_val);

/* print_error.c */
char *get_alias_error_msg(char **args);
char *get_env_error_msg(shell_info *shell_data);
char *get_syntax_error_msg(char **args);
char *get_permission_error_msg(char **args);
char *get_path_126_error_msg(shell_info *shell_data);

#endif
