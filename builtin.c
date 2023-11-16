#include "shell.h"
#include "error.h"

/**
 * _myexit - Terminates the shell.
 * @info: Structure of potential arguments. Maintains a function signature.
 * Return: Exits shell with a exit status (0) if info.argv[0] is not "exit."
 */
int _myexit(info_t *info)
{
int exitStatus;

if (info->argv[1]) /* Checks for the presence of an exit argument */
{
exitStatus = _atoi(info->argv[1]);
if (exitStatus == -1)
{
info->status = 2;
print_error(info, "Invalid number: ");
_eputs(info->argv[1]);
_eputchar('\n');
return (1);
}
info->err_num = _atoi(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}

/**
 * _mycd - Alters the current directory of the process.
 * @info: Structure arguments. Maintains a function signature.
 * Return: Always returns 0.
 */
int _mycd(info_t *info)
{
char *currentDir, *dir, buffer[1024];
int chdirRet;

currentDir = getcwd(buffer, 1024);
if (!currentDir)
_puts("TODO: >>getcwd failure message here<<\n");
if (!info->argv[1])
{
dir = _getenv(info, "HOME=");
if (!dir)
chdirRet = /* TODO: this should this be? */
chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
else
chdirRet = chdir(dir);
}
else if (_strncmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(currentDir);
_putchar('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
chdirRet = /* TODO: will this be? */
chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdirRet = chdir(info->argv[1]);
if (chdirRet == -1)
{
print_error(info, "Unable to change directory to ");
_eputs(info->argv[1]), _eputchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * _myhelp - Displays help information (not yet implemented).
 * @info: Structure potential arguments. Maintains a function signature.
 * Return: Always returns 0.
 */
int _myhelp(info_t *info)
{
char **argArray;

argArray = info->argv;
_puts("Help call functions. Function not implemented.\n");
if (0)
_puts(*argArray); /* Temporary att_unused workaround */
return (0);
}

/**
 * get_node_index - Get index of a node in a linked list
 * @head: Head of the linked list
 * @node: Node to find index of
 *
 * Return: Index of the node in the list, or -1 if not found
*/
int get_node_index(list_t *head, list_t *node)
{
int index = 0;
list_t *temp = head;

while (temp)
{
if (temp == node)
}
return (index);
}

index++;
temp = temp->next;
}

return (-1);
}

/**
 * unset_alias - Remove an alias by setting it to an empty string.
 * @info: Parameter structure.
 * @str: The alias string to be removed.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
char *p, c;
int ret;

p = _strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias,
node_starts_with(info->alias, str, -1)));
*p = c;
return (ret);
}

/**
 * set_alias - Set an alias to a specified string.
 * @info: Parameter structure.
 * @str: The string to set as an alias.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
char *p;

p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unset_alias(info, str));
unset_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Print an alias string.
 * @node: The alias node to be printed.
 *
 * Return: Always returns 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
char *p = NULL, *a = NULL;

if (node)
{
p = _strchr(node->str, '=');
for (a = node->str; a <= p; a++)
_putchar(*a);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
 * _myalias - Mimic the alias built-in command (man alias).
 * @info: Structure arguments. Maintains a function signature.
 * Return: Always returns 0.
 */
int _myalias(info_t *info)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
p = _strchr(info->argv[i], '=');
if (p)
set_alias(info, info->argv[i]);
else
print_alias(node_starts_with(info->alias, info->argv[i], '='));
}

return (0);
}

/**
 * _myhistory - Display the command history list with line numbers.
 * @info: Structure holding arguments. Maintains a function signature.
 * Return: Always returns 0.
 */
int _myhistory(info_t *info)
{
print_list(info->history);
return (0);
}
