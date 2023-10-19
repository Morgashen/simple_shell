#include "shell.h"
#define MAX_ALIAS 50

/**
* is_chain - Tests if the current character in the buffer is a chain delimiter.
*
* @info: The parameter struct.
* @buf: The character buffer.
* @p: The address of the current position in buf.
*
* Return: 1 if it is a chain delimiter, 0 otherwise.
*/
int is_chain(info_t *info, char *buf, size_t *p)
{
        size_t j = *p;

        if (buf[j] == '|' && buf[j + 1] == '|')
        {
                buf[j] = 0;
                j++;
                info->cmd_buf_type = CMD_OR;
                return (1);
        }
        else if (buf[j] == '&' && buf[j + 1] == '&')
        {
                buf[j] = 0;
                j++;
                info->cmd_buf_type = CMD_AND;
                return (1);
        }
        else if (buf[j] == ';') /* found end of this command */
        {
                buf[j] = 0; /* replace semicolon with null */
                info->cmd_buf_type = CMD_CHAIN;
                return (1);
        }
        else
                return (0);
}

/**
* check_chain - checks we should continue chaining based on last status
* @info: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
* @i: starting position in buf
* @len: length of buf
*
* Return: Void
*/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
        size_t j = *p;

        if (info->cmd_buf_type == CMD_AND)
        {
                if (info->status)
                {
                        buf[i] = 0;
                        j = len;
                }
        }
        if (info->cmd_buf_type == CMD_OR)
        {
                if (!info->status)
                {
                        buf[i] = 0;
                        j = len;
                }
        }

        *p = j;
}

/**
* replace_alias - Replaces aliases in the tokenized string.
*
* @info: The parameter struct.
*
* Return: 1 if aliases were replaced, 0 otherwise.
*/
int replace_alias(info_t *info)
{
        int i;
        list_t *node;
        char *p;

        for (i = 0; i < MAX_ALIAS; i++)
        {
                node = node_starts_with(info->alias, info->argv[0], '=');
                if (!node)
                        return (0);
                free(info->argv[0]);
                p = _strchr(node->str, '=');
                if (!p)
                        return (0);
                p = _strdup(p + 1);
if
        (!p)
                        return (0);
                info->argv[0] = p;
        }
        return (1);
        }
/**
* replace_vars - replaces vars in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int convert_number(int num, int base, int uppercase);
int convert_number(int, int, int);
int replace_vars(info_t *info)
{
        int i = 0;
        list_t *node;
        char buffer[20];

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
        {
            continue;
        }

        if (!_strncmp(info->argv[i], "$?"))
        {
            snprintf(buffer, sizeof(buffer), "%d", info->status);
            replace_string(&(info->argv[i]), _strdup(buffer));
            continue;
        }
        if (!_strncmp(info->argv[i], "$$"))
        {
            snprintf(buffer, sizeof(buffer), "%d", getpid());
            replace_string(&(info->argv[i]), _strdup(buffer));
            continue;
        }

        node = node_starts_with(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
            continue;
        }

        replace_string(&info->argv[i], _strdup(""));
    }
    return (0);
}

/**
* replace_string - replaces string
* @old: address of old string
* @new: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **old, char *new)
{
        free(*old);
        *old = new;
        return (1);
}
