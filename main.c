#include "shell.h"

/**
 * main - Entry point of the program.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
        info_t info[] = { INFO_INIT };
        int fd = 2;

        if (av == NULL)
        {
                _eputs("Error: av is NULL\n");
                exit(EXIT_FAILURE);
        }

        if (ac == 2)
        {
                fd = open(av[1], O_RDONLY);
                if (fd == -1)
                {
                        if (errno == EACCES)
                                exit(126);
                        if (errno == ENOENT)
                        {
                                _eputs(av[0]);
                                _eputs(": 0: Can't open ");
                                _eputs(av[1]);
                                _eputs("\n");
                                _eputchar(BUF_FLUSH);
                                exit(127);
                        }
                        return (EXIT_FAILURE);
                }
                info->readfd = fd;
        }
        populate_env_list(info);
        read_history(info);
        hsh(info, av);
        return (EXIT_SUCCESS);
}
