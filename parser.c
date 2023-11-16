#include "shell.h"

/**
 * is_cmd - Checks if a file is an executable command.
 *
 * @info: The info struct.
 * @path: The path to the file.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
struct stat st;
(void)info;
if (!path)
return (0);

if (stat(path, &st))
return (0);

if ((st.st_mode & S_IFREG) && (st.st_mode & S_IXUSR))
{
return (1);
}
return (0);
}

/**
 * dup_chars - Duplicates characters from a string.
 *
 * @pathstr: The PATH string.
 * @start: The starting index.
 * @stop: The stopping index.
 *
 * Return: A pointer to a new buffer containing the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}

/**
 * find_path - Searches for the specified command in the PATH string.
 *
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);

if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_cmd(info, cmd))
return (cmd);
}
while (pathstr[i])
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_cmd(info, path))
return (path);
curr_pos = i + 1;
}
i++;
}
return (NULL);
}
