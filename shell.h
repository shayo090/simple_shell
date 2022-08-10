#ifndef SHELL_H
#define SHELL_H

/**
 * struct builtins - a struct
 * @name: member
 * @func: pointer to fucntion
 */
typedef struct builtins
{
char *name;
void (*func)();
} builtin;

char *_getenv(char *var, char **env);

void _env(char **env);

void __exit(char *ss);

char *find_command(char *, char *);

void prompt(void);

void builtin_cmd(char *command[], char **env);

#endif
