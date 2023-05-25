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

/* m_environment.c files */
char **copy_env(char **env);
void free_env(char **env);
void add_key(inputs_t *vars);
char **find_key(char **env, char *key);
char *add_value(char *key, char *value);

/* m_helper.c files */
ssize_t _puts(char *str);
char *_strdup(char *strtodup);
int _strcmp(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);

/* individual files */
char **get_commands(char *buffer, char *delimiter);
char **_realloc(char **ptr, size_t *size);
char *_strtok(char *str, const char *delim);
void process_input(char *input, inputs_t *vars);

/* m_builtins.c files */
void (*check_for_builtins(inputs_t *vars))(inputs_t *vars);
void my_exit(inputs_t *vars);
void _env(inputs_t *vars);
void _setenv(inputs_t *vars);
void _unsetenv(inputs_t *vars);

/* m_path.c files */
void get_path(inputs_t *vars);
int execute_cmd(char *command, inputs_t *args);

/* m_print.c files */
void print_error(inputs_t *vars, char *msg);
void _puts2(char *str);
void print_prompt(void);

/* m_char_conversion.c*/
char *_uitoa(unsigned int count);
int _atoi(char *str);

#endif /* _SHELL_H_ */
