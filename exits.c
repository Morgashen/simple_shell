#include "shell.h"

/**
 * _strncat - Concatenate two strings.
 * @dest: The first string to which the second string will be concatenated.
 * @src: The second string to concatenate.
 * @n: The maximum number of bytes to use.
 *
 * Return: A pointer to the concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;
j = 0;
while (dest[i] != '\0')
i++;
while (src[j] != '\0' && j < n)
{
dest[i] = src[j];
i++;
j++;
}
if (j < n)
dest[i] = '\0';
return (s);
}

/**
 * _strncpy - Copy a string from source to destination.
 * @dest: The destination string where data will be copied.
 * @src: The source string to copy from.
 * @n: The maximum number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;
while (src[i] != '\0' && i < n - 1)
{
dest[i] = src[i];
i++;
}
if (i < n)
{
j = i;
while (j < n)
{
dest[j] = '\0';
j++;
}
}
return (s);
}

/**
 * _strchr - Locate a character in a string.
 * @s: The string to search within.
 * @c: The character to find.
 *
 * Return: A pointer to the first occurrence of 'c' in 's'.
 */
char *_strchr(char *s, char c)
{
do

{
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}
