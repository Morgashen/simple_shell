#include "shell.h"

/**
 * bfree - Releases the memory pointed to by a pointer and sets the address to NULL.
 *
 * @ptr: The address of the pointer to be freed.
 * Description:
 * This function deallocates the memory pointed to by the pointer and sets the address to NULL.
 *
 * Return: 1 if memory was freed, otherwise 0.
 */
int bfree(void **ptr)
{
        if (ptr && *ptr)
        {
                free(*ptr);
                *ptr = NULL;
                return (1);
        }
        return (0);
}
