#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <error.h>
#include <limits.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for convert_number() */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096
#define MAX_MEMSET_SIZE UINT_MAX 
#define MAX_SIZE UINT_MAX

extern char **environ;


/**
 * struct liststr - Singly linked list structure.
 *
 * @num: The number field.
 * @str: A string.
 * @next: Points to the next node in the list.
 */
typedef struct liststr
{
        int num;
        char *str;
        struct liststr *next;
} list_t;
/**
 * struct passinfo - Contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for a function pointer struct
 * @arg: A string generated from getline containing arguments
 * @argv: An array of strings generated from arg
 * @path: A string path for the current command
 * @argc: The argument count
 * @line_count: The error count
 * @err_num: The error code for exit()s
 * @linecount_flag: If on, count this line of input
 * @fname: The program filename
 * @env: A linked list local copy of environ
 * @environ: A custom modified copy of environ from LL env
 * @history: The history node
 * @alias: The alias node
 * @env_changed: On if environ was changed
 * @status: The return status of the last exec'd command
 * @cmd_buf: Address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type (||, &&, ;)
 * @readfd: The fd from which to read line input
 * @histcount: The history line number count
 */
typedef struct passinfo
{
        char *arg;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        list_t *env;
        list_t *history;
        list_t *alias;
        char **environ;
        int env_changed;
        int status;

        char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
        int cmd_buf_type; /* CMD_type ||, &&, ; */
        int readfd;
        int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
                0, 0, 0}

/**
 * struct builtin - Contains a builtin string and its related function.
 *
 * @type: The builtin command flag.
 * @func: The function associated with the builtin command.
 */
typedef struct builtin
{
        char *type;
        int (*func)(info_t *);
} builtin_table;


/* toem_shell_loop.c */
int hsh(info_t *info, char **av);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
void print_error(info_t *info, char *msg);

/* toem_parser.c */
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
char *number_converter(long int num, int base, int flags);
void eliminate_comments(char *buf);
int print_integer(int input, int fd);
void display_error_message(info_t *info, char *error_string);
int _str_to_int_err(char *s);

/* toem_string.c */
int _strlen(const char *s);
int _strncmp(const char *s1, const char *s2);
char *_strcat(char *dest, const char *src);
char *starts_with(const char *haystack, const char *needle);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *);
int _putchar(char c);

/* toem_exits.c */
char *_strncat(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);
char *_strchr(char *s, char c);

/* toem_tokenizer.c */
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);

/* toem_realloc.c */
char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* toem_memory.c */
int bfree(void **ptr);

/* toem_atoi.c */
int is_delim(char c, char *delim);
int interactive(info_t *info);
int _isalpha(int c);
int _atoi(char *s);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);
int _myhistory(info_t *info);

/*toem_getLine.c */
ssize_t input_buf(info_t *info, char **buf);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

/* toem_getinfo.c */
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);
void clear_info(info_t *info);

/* toem_environ.c */
char *_getenv(info_t *info, const char *name);
int populate_env_list(info_t *info);
int _myunsetenv(info_t *info);
int _mysetenv(info_t *info);
int _myenv(info_t *info);

/* toem_getenv.c */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *node, char *prefix, char c);

/* toem_vars.c */
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **old, char *new);

#endif
