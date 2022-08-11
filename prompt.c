#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include <unistd.h>

/**
 * prompt - to get started or file indirection used
 * Return: Nothing
 */
void prompt(void)
{
	int int_mode;

	int_mode = isatty(STDIN_FILENO);
	if (int_mode == 1)
		write(STDOUT_FILENO, "$", 2);
}


