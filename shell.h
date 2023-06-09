#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>


/**
 * struct inputs - variables
 * @av: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: count of commands entered
 * @argv: arguments at opening of shell
 * @commands: commands to be executed
 * @status: exit status
 * @str_cmd: copy of individual commands separated by ;
 * @ops_cmd: string of commands separated by logical operators
 * @aliases: contains the alias commands
 */
typedef struct inputs
{
	char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
	char *str_cmd;
	char **ops_cmd;
	char **aliases;
} inputs_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(inputs_t *);
} builtins_t;

/* m_shell.c files */
void free_commands(inputs_t *vars);

/* m_environment.c files */
char **copy_env(char **env);
void free_env(char **env);
void add_key(inputs_t *vars);
char **find_key(char **env, char *key);
char *add_value(char *key, char *value);

/* m_helper.c files */
char *_strdup(char *strtodup);
int _strcmp(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);
void print_vars(char **str);

/* m_strtok.c files */
char *_strtok(char *str, const char *delim);
unsigned int check_match(char c, const char *str);
char *_strcpy(char *dest, char *src);

/* m_get_commands.c files */
char **get_commands(char *buffer, char *delimiter);
char **get_aliases(char *buffer, char *delimeter);
int char_found(char c, const char *del);
char *alias_strtok(char *str, const char *del);

/* m_echo.c files */
void sub_env(inputs_t *vars);
void free_av_and_alias(char **s);

/* m_realloc.c files*/
char **_realloc(char **ptr, size_t old_size, size_t new_size);
char *_malloc(size_t size);

/* m_process.c file */
void process_input(char *input, inputs_t *vars);
int run_command(inputs_t *vars, char *cmd_str);
char get_operator(char *command, unsigned int *index);
void check_logical_ops(inputs_t *vars, char *cmd_str);

/* m_builtins.c files */
int exe_builtin(inputs_t *vars);
void my_exit(inputs_t *vars);
void _env(inputs_t *vars);
void _setenv(inputs_t *vars);
void _unsetenv(inputs_t *vars);

/* m_path.c files */
void get_path(inputs_t *vars);
int execute_cmd(char *command, inputs_t *args);

/* m_print.c files */
void print_error(inputs_t *vars, char *msg);
ssize_t _puts(char *str);
void _puts2(char *str);
void print_error2(inputs_t *vars, char *msg);
void print_prompt(void);

/* m_char_conversion.c*/
char *_uitoa(unsigned int count);
int _atoi(char *str);
int _chrcmp(char a, char b);

/* m_cd.c files */
void _cd(inputs_t *vars);
void change_dir(inputs_t *args, char *pathname);
int _setenv2(inputs_t *args, const char *name, const char *val, int o_write);
char *_getenv(inputs_t *vars, const	char *name);

/* m_alias.c file */
int check_name_match(char *an_alias, char *input);
void update_alias(inputs_t *vars, unsigned int k);
void _alias(inputs_t *vars);
char *store_alias(char *str);
void sub_alias(inputs_t *vars);

#endif /* _SHELL_H_ */
