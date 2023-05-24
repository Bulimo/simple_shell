#ifndef	SIMPLE_SHELL_H_INCLUDED
#define SIMPLE_SHELL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <signal.h>

extern char **environ;

/**
  * struct input - struct to store user input
  * @line: line read from the input
  * @next: address of the next line
  */
typedef struct input
{
	char *line;
	struct input *next;
} input_t;

char **get_args(char *input);
char *create_path(char *command);
void execute(char *path, char **arg, char **envp);
input_t *addinput_t(input_t **head, char *user_input);
void freeinput_t(input_t **head);
input_t *readlines(input_t **head, int isterm);
int _putchar(char c);
void printerr(const char *s, ...);
void printnode(input_t **head);


#endif
