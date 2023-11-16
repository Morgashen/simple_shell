#include "shell.h"

/**
 * is_delim - This checks that character is the delimeter
 * @c: A char to be checked in this del
 * @delim: The string of delimeter
 * Return: When postive 1, 0 when negative
 */
int is_delim(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);
return (0);
}


/**
 * interactive - This Provides Positive if shell is in interactive mode
 * @info: struct the addresses
 *
 * Return: 1 if interactive mode, 0 when not
 */

int interactive(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 *_isalpha - This checeds for non numeric values but alphabetic character
 *@c: character inputed
 *Return: when c alphabetic give 1, and 0 if negative
 */

int _isalpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}

/**
 *_atoi - It converted the string into an a integer
 *@s: String to be converted into integers
 *Return: 0 if false, convert to a number if true
 */

int _atoi(char *s)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;

for (i = 0;  s[i] != '\0' && flag != 2; i++)
{
if (s[i] == '-')
sign *= -1;

if (s[i] >= '0' && s[i] <= '9')
{
flag = 1;
result *= 10;
result += (s[i] - '0');
}
else if (flag == 1)
flag = 2;
}

if (sign == -1)
output = -result;
else
output = result;

return (output);
}
