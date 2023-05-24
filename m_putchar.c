#include "simple_shell.h"

/**
  * _putchar - prints a char
  * @c: char to print
  * Return: the number of characters printed
  */
int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
