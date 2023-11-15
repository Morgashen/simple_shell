#include "shell.h"

/**
 * set_info - Initializes an info_t structure with the provided arguments.
 * @info: The address of the structure to be initialized.
 * @av: The argument vector.
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Deallocates memory and resets fields of an info_t structure.
 * @info: The address of the structure to be freed.
 * @all: If true, frees all fields including environment variables and history.
 */
void free_list(list_t **head_ptr);
void free_info(info_t *info, int all)

{

 ffree(info->argv);
  
  if(info->arg)
    free(info->arg);

  if(info->env) {
    if(!info->env)
      free_list(&(info->env));
{
 if (info->env)
free_list(&info->env);
if (info->history)
free_list(&info->history);
 if (info->alias)
free_list(&info->alias);
ffree(info->environ);
info->environ = NULL;
free(info->cmd_buf);
 if (info->readfd > 2)
close(info->readfd);
_putchar(BUF_FLUSH);
 
 return;
}
}
}

/**
 * clear_info - Initializes an info_t structure by setting its fields to NULL.
 * @info: The address of the structure to be initialized.
 */
void clear_info(info_t *info)
{
info->arg = NULL;
  info->argv = NULL;
  info->path = NULL;
  info->env = NULL;
  info->alias = NULL;
  info->history = NULL;

   return;
}
