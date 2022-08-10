#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h>
#include "shell.h"

/**
 * main - simple shell program
 * @argc: unused argument
 * @argv: filename only used
 * @env: environment variable
 * Return: O for success
 */

int main(int __attribute__((unused)) argc, char *argv[], char *env[])
{
	pid_t child;
	char *command[16], *cwd = _getenv("PATH", env), *line = NULL;
	int i, status;
	struct stat st;
	size_t len = 0;
	char *trace, *tok, *path, *str;

	path = malloc(sizeof(char) * PATH_MAX);
	while (1)
	{
		prompt();
		if (getline(&line, &len, stdin) == -1)
			break;
		for (i = 0; i < 16; i++, line = NULL)
			tok = strtok(line, " \t\n\r\0"), command[i] = tok;
		command[i] = NULL;
		if (command[0] == NULL)
			continue;
		builtin_cmd(command, env);
		if (stat(command[0], &st) == 0)
			trace = strdup(command[0]);
		else
			str = strdup(cwd), trace = find_command(command[0], str);
		if (stat(trace, &st) == 0)
		{
			child = fork();
			if (!child)
			{
				if (execve(trace, command, NULL) == -1)
					perror("execve"), exit(EXIT_FAILURE); }
			else
				wait(&status); }
		else
		{
			write(1, argv[0], strlen(argv[0])), write(1, ": No such file or directory\n", 18);
			continue;
		}}
	free(path), free(line), exit(status);
	return (0);
}
