# 0x16. C - Simple Shell

## Objectives

	. How does a shell work
	. What is a pid and a ppid
	. How to manipulate the environment of the current process
	. What is the difference between a function and a system call
	. How to create processes
	. What are the three prototypes of main
	. How does the shell use the PATH to find the programs
	. How to execute another program with the execve system call
	. How to suspend the execution of a process until one of its children terminates
	. What is EOF / “end-of-file”?

## Requirements

	. Editors: vi, vim, emacs
	. Ubuntu 20.04 LTS and gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
	. Betty style compliant code. It will be checked using betty-style.pl and betty-doc.pl
	. Your shell should not have any memory leaks
	. All your header files should be include guarded
	. Write a README with the description of your project
	. You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker

## List of allowed functions and system calls

	. access (man 2 access)
	. chdir (man 2 chdir)
	. close (man 2 close)
	. closedir (man 3 closedir)
	. execve (man 2 execve)
	. exit (man 3 exit)
	. _exit (man 2 _exit)
	. fflush (man 3 fflush)
	. fork (man 2 fork)
	. free (man 3 free)
	. getcwd (man 3 getcwd)
	. getline (man 3 getline)
	. getpid (man 2 getpid)
	. isatty (man 3 isatty)
	. kill (man 2 kill)
	. malloc (man 3 malloc)
	. open (man 2 open)
	. opendir (man 3 opendir)
	. perror (man 3 perror)
	. read (man 2 read)
	. readdir (man 3 readdir)
	. signal (man 2 signal)
	. stat (__xstat) (man 2 stat)
	. lstat (__lxstat) (man 2 lstat)
	. fstat (__fxstat) (man 2 fstat)
	. strtok (man 3 strtok)
	. wait (man 2 wait)
	. waitpid (man 2 waitpid)
	. wait3 (man 2 wait3)
	. wait4 (man 2 wait4)
	. write (man 2 write)

## Compilation

Your shell will be compiled this way:

	`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`


## Testing

Your shell should work like this in interactive mode:

	'$ ./hsh
	($) /bin/ls
	hsh main.c shell.c
	($)
	($) exit
	$`

But also in non-interactive mode:

	'$ echo "/bin/ls" | ./hsh
	hsh main.c shell.c test_ls_2
	$
	$ cat test_ls_2
	/bin/ls
	/bin/ls
	$
	$ cat test_ls_2 | ./hsh
	hsh main.c shell.c test_ls_2
	hsh main.c shell.c test_ls_2
	$`

## Description of files in the repository

	1. m_shell.c - main simple shell function
	2. shell.h - header file of the simple shell project
	3. m_builtins.c - contains function on execution of builtin commands
	4. m_char_conversions.c - contains functions to convert from string to unsigned int and vise versa
	5. m_environment.c - contains function to work on environment variables
	6. m_get_commands.c - contains functions to extract commands from input
	7. m_helper.c - contains functions that help in string manupulation
	8. m_path.c - contains functions to create a path to file and execute the file
	9. m_print.c - contains functions for printing errors, prompt and general output
	10. m_process.c - contains function to readline and initiate the path search and execution of a file
	11. m_realloc.c - contains implementation of realloc function
	12. m_strtok.c - contains implementation of strtok() function
	13. m_cd.c - contains implementation of cd builtin command
	14. m_echo.c - contains function to implement environment substitutions
	15. m_alias.c - contains functions to implement alias built in command

