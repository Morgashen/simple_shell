#include "shell.h"

/**
* _strlen - Returns the length of a string.
*
* @s: The string whose length to determine.
*
* Return: An integer representing the length of the string.
*/
int _strlen(const char *s)
{
int i = 0;

if (!s)
return (0);

while (*s++)
i++;
return (i);
}

/**
* _strcmp - Performs a lexicographic comparison of two strings.
*
* @s1: The first string.
* @s2: The second string.
*
* Return: A negative value if s1 < s2,
* a positive value if s1 > s2, and zero if s1 == s2.
*/
int _strncmp(const char *s1, const char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}

/**
* starts_with - Checks if the 'haystack' starts with the 'needle'.
*
* @haystack: The string to search.
* @needle: The substring to find.
*
* Return: The address of the next character in 'haystack' after 'needle'
* if found, or NULL if not found.
*/
char *starts_with(const char *haystack, const char *needle)
{
size_t needle_len = _strlen(needle);

if ((int)needle_len > _strlen(haystack))
return (NULL);

return (_strncmp(haystack, needle) == 0 ?
(char *)haystack + needle_len : NULL);
}

/**
* _strcat - Concatenates two strings.
*
* @dest: The destination buffer.
* @src: The source buffer.
*
* Return: A pointer to the destination buffer.
*/
char *_strcat(char *dest, const char *src)
{
char *ret = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = '\0';
return (ret);
}


/**
* _strcpy - Copies a string.
*
* @dest: The destination.
* @src: The source.
*
* Return: A pointer to the destination.
*/
char *_strcpy(char *dest, char *src)
{
int i = 0;
if (dest == src || src == NULL)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = '\0';
return (dest);
}

/**
* _strdup - Duplicates a string.
*
* @str: The string to duplicate.
*
* Return: A pointer to the duplicated string.
*/
char *_strdup(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
* _puts - prints an input string
* @str: the string to be printed
*
* Return: Nothing
*/
void _puts(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}

/**
* _putchar - Writes the character 'c' to stdout.
*
* @c: The character to print.
*
* Return: On success, it returns 1. On error, -1 is returned,
* and errno is set appropriately.
*/
int _putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE]
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
