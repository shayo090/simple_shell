#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

/**
 * builtin_cmd - print environment variables
 * @env: environment array
 * @command: command input
 * Return: Nothing
 */
void builtin_cmd(char *command[], char **env)
{
	builtin my_builtins[] = {
		{"exit", __exit},
		{"env", _env},
		{NULL, NULL},
	};
	int a = 0;

	while (my_builtins[a].name != NULL)
	{
		if (strcmp(command[0], my_builtins[0].name) == 0)
			my_builtins[a].func(command[1]);
		if (strcmp(command[0], my_builtins[a].name) == 0)
			my_builtins[a].func(env);
		a++;
	}
}


/**
 * _getenv - get an environment value
 * @var: variable
 * @env: environment array
 * Return: a specific value
 */

char *_getenv(char *var, char **env)
{
	char *str, *token;
	int i = 0;

	while (env[i])
	{
		str = env[i];
		token = strtok(str, "=");
		if (strcmp(token, var) == 0)
		{
			token = strtok(NULL, "=");
			return (token);
		}
		i++;
	}
	free(str), free(var), free(env);
	return (token);
}

/**
 * _env - print environment variables
 * @env: environment array
 * Return: Nothing
 */

void _env(char **env)
{
	unsigned int i = 0;

	while (env[i])
	{
		write(1, env[i], strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
	free(env);
}

/**
 * __exit - implement builtin exit
 * @ss: exit code
 * Return: Nothing
 */

void __exit(char *ss)
{
	int s;

	if (ss == NULL)
		s = 0;
	else
		s = atoi(ss);
	free(ss);
	_exit(s);
}

/**
 * find_command - find command
 * @cmd: command to find
 * @str: string containing path
 * Return: Nothing
 */

char *find_command(char *cmd, char *str)
{

	char *token, *trace;
	struct stat st;

	token = strtok(str, ":");
	while (token != NULL)
	{
		token = strtok(NULL, ":");
		if (token == NULL)
			break;
		trace = strdup(token);
		trace = strcat(trace, "/");
		strcat(trace, cmd);
		if (stat(trace, &st) == 0)
			token = NULL;
		else
			continue;
	}
	free(token), free(str), free(cmd);
	return (trace);
}
