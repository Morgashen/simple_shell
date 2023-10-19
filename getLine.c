#include "shell.h"

/**
 * remove_comments - Removes comments from a string
 * @buf: The string to remove comments from
*/
void remove_comments(char *buf) {

  int i = 0;
  int in_comment = 0;

  while (buf[i]) {

    if (buf[i] == '#') {
      in_comment = 1;
    }

    if (in_comment == 0) {

    } else {

      buf[i] = '\0';
    }

    if (buf[i] == '\n') {
      in_comment = 0;
    }

    i++;
  }

}

/**
 * input_buf - This will buffer chained commands
 * @info:it is a parameter struct
 * @buf: It addresses the buffer
 * @len: This addresses the len var
 *
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
        ssize_t r = 0;
        size_t len_p = 0;

        if (!*len) /* if the buffer is empty, populate it */
        {
                /*bfree((void **)info->cmd_buf);*/
                free(*buf);
                *buf = NULL;
                signal(SIGINT, sigintHandler);
#if USE_GETLINE
                r = getline(buf, &len_p, stdin);
#else
                r = _getline(info, buf, &len_p);
#endif
                if (r > 0)
                {
                        if ((*buf)[r - 1] == '\n')
                        {
                                (*buf)[r - 1] = '\0'; /* removes the trailing newline */
                                r--;
                        }
                        info->linecount_flag = 1;
                        remove_comments(*buf);
                        build_history_list(info, *buf, info->histcount++);
                        /* if (_strchr(*buf, ';')) Investigate if command is a chain? */
                        {
                                *len = r;
                                info->cmd_buf = buf;
                        }
                }
        }
        return (r);
}

/**
 * get_input - This gets the line minus a newline
 * @info: It is a parameter of struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
        static char *buf; /* the ';' commands the chain buffer */
        static size_t i, j, len;
        ssize_t r = 0;
        char **buf_p = &(info->arg), *p;

        _putchar(BUF_FLUSH);
        r = input_buf(info, &buf, &len);
        if (r == -1) /* EOF */
                return (-1);
        if (len)        /* There are commands still in the chain's buffer */
        {
                j = i; /* init new iterator to the current position */
                p = buf + i; /* locate a pointer for the return */

                check_chain(info, buf, &j, i, len);
                while (j < len) /* iterates to the semicolon or complete */
                {
                        if (is_chain(info, buf, &j))
                                break;
                        j++;
                }

                i = j + 1; /* increases the past nulled ';'' */
                if (i >= len) /* Investigate if buffer end reached? */
                {
                        i = len = 0; /* reset the position and the  length */
                        info->cmd_buf_type = CMD_NORM;
                }

                *buf_p = p; /* It passes back the pointer to command */
                return (_strlen(p)); /* return of length of current of command */
        }

        *buf_p = buf; /* else if not chain, pass buffer _getline() */
        return (r); /* It returns length of the buffer from _getline() */
}

/**
 * read_buf - It reads a buffer
 * @info: the parameter of struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
        ssize_t r = 0;

        if (*i)
                return (0);
        r = read(info->readfd, buf, READ_BUF_SIZE);
        if (r >= 0)
                *i = r;
        return (r);
}

/**
 * _getline - This finds a next line of input STDIN
 * @info: the parameter of struct
 * @ptr: addresses a pointer to a buffer, false locate or NULL
 * @length: size of the allocated ptr buffer, NULL if not
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
        static char buf[READ_BUF_SIZE];
        static size_t i, len;
        size_t k;
        ssize_t r = 0, s = 0;
        char *p = NULL, *new_p = NULL, *c;

        p = *ptr;
        if (p && length)
                s = *length;
        if (i == len)
                i = len = 0;

        r = read_buf(info, buf, &len);
        if (r == -1 || (r == 0 && len == 0))
                return (-1);

        c = _strchr(buf + i, '\n');
        k = c ? 1 + (unsigned int)(c - buf) : len;
        new_p = _realloc(p, s, s ? s + k : k + 1);
        if (!new_p) /*A MALLOC FAILURE! */
                return (p ? free(p), -1 : -1);

        if (s)
                _strncat(new_p, buf + i, k - i);
        else
                _strncpy(new_p, buf + i, k - i + 1);

        s += k - i;
        i = k;
        p = new_p;

        if (length)
                *length = s;
        *ptr = p;
        return (s);
}

/**
 * sigintHandler - It will block ctrl-C
 * @sig_num: It is a signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
        _puts("\n");
        _puts("$ ");
        _putchar(BUF_FLUSH);
}
