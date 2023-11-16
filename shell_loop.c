#include "shell.h"
#include "error.h"

/**
* hsh - Main shell loop.
*
* @info: The parameter and return Info struct.
* @av: The argument vector from main().
*
* Return: 0 on success, 1 on error, or an error code.
*/
int hsh(info_t *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;

while (r != -1 && builtin_ret != -2)
{
clear_info(info);

if (interactive(info))
_puts("$ ");

_eputchar(BUF_FLUSH);

r = get_input(info);

if (r != -1)
{
set_info(info, av);

builtin_ret = find_builtin(info);

if (builtin_ret == -1)
find_cmd(info);
}
else if (interactive(info))
_putchar('\n');

free_info(info, 0);
}

write_history(info);


if (info->argv)
{
free(info->argv);
}


if (info->path)
{
free(info->path)
}

free_info(info, 1);

if (!interactive(info) && info->status)
exit(info->status);

if (builtin_ret == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}

return (builtin_ret);
}

/**
* find_builtin - Finds a builtin command.
*
* @info: The parameter and return Info struct.
*
* Return: -1 if the builtin is not found,
* 0 if the builtin executed successfully,
* 1 if the builtin was found but not successful,
* 2 if the builtin signals exit().
*/
int find_builtin(info_t *info)
{
int i, built_in_ret = -1;

const builtin_table builtintbl[] = {

{"exit", _myexit},
{"env", _myenv},
{"help", _myhelp},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL};
};

for (i = 0; builtintbl[i].type; i++)
{
if (_strncmp(info->argv[0], builtintbl[i].type) == 0)
{
info->line_count++;
built_in_ret = builtintbl[i].func(info);
break;
}
}

return (built_in_ret);
}

/**
* find_cmd - Finds a command in the PATH.
*
* @info: The parameter and return Info struct.
*
* Return: Void.
*/

void find_cmd(info_t *info)
{
char *path = NULL;
int i, k;

info->path = info->argv[0];

if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}

for (i = 0, k = 0; info->arg[i]; i++)
{
if (!is_delim(info->arg[i], " \t\n"))
{
k++;
}
}

if (!k)
{
return;
}

path = find_path(info, _getenv(info, " PATH = "), info->argv[0]);

if (path)
{
info->path = path;

if (path == NULL)
{
perror("Error:");
return;
}

fork_cmd(info);

free(path);
}
else
{
if ((interactive(info) || _getenv(info, " PATH = ") ||
info->argv[0][0] == '/') && is_cmd(info, info->argv[0])) {
fork_cmd(info);
}
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}

/**
* fork_cmd - Forks an exec thread to run a command.
*
* @info: The parameter and return Info struct.
*
* Return: Void.
*/

void fork_cmd(info_t *info)
{
pid_t child_pid;

child_pid = fork();

if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}

if (child_pid == 0)
{
if (execvp(info->path, info->argv) == -1)
{
free_info(info, 1);

if (errno == EACCES)
{
exit(126);
}

exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(info->status));

if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);

if (info->status == 126)
{
print_error(info, "Permission denied\n");
}
}
return;
}
}
