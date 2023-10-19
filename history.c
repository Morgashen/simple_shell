#include "shell.h"

/**
 * get_history_file - This will get the history file
 * @info: The parameter of struct
 *
 * Return: The allocated string will contain a history file
 */

char *get_history_file(info_t *info)
{
        char *buf, *dir;

        dir = _getenv(info, "HOME=");
        if (!dir)
                return (NULL);
        buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
        if (!buf)
                return (NULL);
        buf[0] = 0;
        _strcpy(buf, dir);
        _strcat(buf, "/");
        _strcat(buf, HIST_FILE);
        return (buf);
}

/**
 * write_history - This generates a file, or write on the existing file
 * @info: the parameter of the struct
 *
 * Return: 1 only on positive, negative return -1
 */
int write_history(info_t *info)
{
        ssize_t fd;
        char *filename = get_history_file(info);
        list_t *node = NULL;

        if (!filename)
                return (-1);

        fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
        free(filename);
        if (fd == -1)
                return (-1);
        for (node = info->history; node; node = node->next)
        {
                _putsfd(node->str, fd);
                _putfd('\n', fd);
        }
        _putfd(BUF_FLUSH, fd);
        close(fd);
        return (1);
}

/**
 * read_history - This scans the history of file
 * @info: the parameter of the struct
 *
 * Return: The histcount on positive, 0 on negative
 */
int read_history(info_t *info)
{
        int i, last = 0, linecount = 0;
        ssize_t fd, rdlen, fsize = 0;
        struct stat st;
        char *buf = NULL, *filename = get_history_file(info);

        if (!filename)
                return (0);

        fd = open(filename, O_RDONLY);
        free(filename);
        if (fd == -1)
                return (0);
        if (!fstat(fd, &st))
                fsize = st.st_size;
        if (fsize < 2)
                return (0);
        buf = malloc(sizeof(char) * (fsize + 1));
        if (!buf)
                return (0);
        rdlen = read(fd, buf, fsize);
        buf[fsize] = 0;
        if (rdlen <= 0)
                return (free(buf), 0);
        close(fd);
        for (i = 0; i < fsize; i++)
                if (buf[i] == '\n')
                {
                        buf[i] = 0;
                        build_history_list(info, buf + last, linecount++);
                        last = i + 1;
                }
        if (last != i)
                build_history_list(info, buf + last, linecount++);
        free(buf);
        info->histcount = linecount;
        while (info->histcount-- >= HIST_MAX)
                delete_node_at_index(&(info->history), 0);
        renumber_history(info);
        return (info->histcount);
}

/**
 * build_history_list - This adds entry to the history list
 * @info: The Structure contains the arguments. It is used to maintain
 * @buf: buffer
 * @linecount: Here the history of linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
        list_t *node = NULL;

        if (info->history)
                node = info->history;
        add_node_end(&node, buf, linecount);

        if (!info->history)
                info->history = node;
        return (0);
}

/**
 * renumber_history - Chnages the num of history linked to list after a change
 * @info: The structure contains the arguments.
 *
 * Return: the newely genarated histcount
 */
int renumber_history(info_t *info)
{
        list_t *node = info->history;
        int i = 0;

        while (node)
        {
                node->num = i++;
                node = node->next;
        }
        return (info->histcount = i);
}
