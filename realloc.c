#include "shell.h"

/**
 * _memset - Fills a memory area with a constant byte.
 *
 * @s: A pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: The number of bytes to be filled.
 *
 * Return: A pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
        unsigned int i;

        if (!s)
                return (NULL);

        for (i = 0; i < n; i++)
                s[i] = b;
        return (s);
}

/**
 * ffree - Frees a string of strings.
 *
 * @pp: The string of strings to be freed.
 */
void ffree(char **pp)
{
        if (!pp)
                return;
        for (; *pp; pp++)
                free(*pp);
        free(pp);
}

/**
 * _realloc - Reallocates a block of memory.
 *
 * @ptr: Pointer to the previous malloc'ed block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: A pointer to the old block, if successful.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
        char *p;

        if (!ptr)
                return (malloc(new_size));

        if (!new_size)
        {
                free(ptr);
                return (NULL);
        }

        if (new_size == old_size)
                return (ptr);

        p = malloc(new_size);
        if (!p)
                return (NULL);

        old_size = old_size < new_size ? old_size : new_size;
        while (old_size--)
                p[old_size] = ((char *)ptr)[old_size];
        free(ptr);
        return (p);
}
