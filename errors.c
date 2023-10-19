#include "shell.h"
#include "error.h"

/**
* print_error - Prints an error message
* @info: Info struct containing arguments
* @msg: Error message to print
*/

void print_error(info_t *info __attribute__((unused)), char *msg) {
printf("%s\n", msg);
}

/**
 * _putfd - Outputs the character 'c' to the provided file descriptor 'fd'.
 * @c: The character to be output.
 * @fd: The file descriptor for writing.
 *
 * Return: Return 1 on success, -1 case of error, with errno set accordingly.
 */

int _putfd(char c, int fd)
{
        static int i;
        static char buf[WRITE_BUF_SIZE];

        if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
        {
                write(fd, buf, i);
                i = 0;
        }
        if (c != BUF_FLUSH)
                buf[i++] = c;
        return (1);
}

/**
 * _eputchar - Outputs the character 'c' to the standard error stream.
 * @c: The character to be output.
 *
 * Return: Returns 1 on success, -1 case of error, with errno set accordingly.
 */

int _eputchar(char c)
{
        static int i;
        static char buf[WRITE_BUF_SIZE];

        if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
        {
                write(2, buf, i);
                i = 0;
        }
        if (c != BUF_FLUSH)
                buf[i++] = c;
        return (1);
}

/**
 * _eputs - Outputs the input string 'str' to the standard error stream.
 * @str: The string to be output.
 *
 * Return: There is no return value.
 */

void _eputs(char *str)
{
        int i = 0;

        if (!str)
                return;
        while (str[i] != '\0')
        {
                _eputchar(str[i]);
                i++;
        }
}

/**
 * _putsfd - Output a provided string 'str' to the given file descriptor 'fd'.
 * @str: The string to be output.
 * @fd: The file descriptor for writing.
 *
 * Return: Returns the count of characters that were written.
 */

int _putsfd(char *str, int fd)
{
        int i = 0;

        if (!str)
                return (0);
        while (*str)
        {
                i += _putfd(*str++, fd);
        }
        return (i);
}

/**
 * number_converter - Converter function, a clone of itoa.
 * @num: Number.
 * @base: Base.
 * @flags: Argument flags.
 * Return: String.
 */
char *number_converter(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do

{
*--ptr = array[n % base];
n /= base;
} while (n != 0);

if (sign)
*--ptr = sign;
return (ptr);
}

/**
 * eliminate_comments - Function replaces first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 * Return: Always 0.
 */
void eliminate_comments(char *buf)
{
int i;

for (i = 0; buf[i] != '\0'; i++)
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}

/**
 * print_integer - Prints a decimal (integer) number (base 10).
 * @input: The input.
 * @fd: The file descriptor to write to.
 * Return: Number of characters printed.
 */
int print_integer(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int i, count = 0;
unsigned int absolute_value, current;

if (fd == STDERR_FILENO)
__putchar = _eputchar;
if (input < 0)
{
absolute_value = -input;
__putchar('-');
count++;
}
else
absolute_value = input;
current = absolute_value;
for (i = 1000000000; i > 1; i /= 10)
{
if (absolute_value / i)
{
__putchar('0' + current / i);
count++;
}
current %= i;
}
__putchar('0' + current);
count++;

return (count);
}

/**
 * display_error_message - Prints an error message.
 * @info: The parameter and return info struct.
 * @error_string: String containing specified error type.
 * Return: None.
 */
void display_error_message(info_t *info, char *error_string)
{
_eputs(info->fname);
_eputs(": ");
print_integer(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(error_string);
}

/**
 * _str_to_int_err - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: 0 if no numbers in the string, converted number otherwise.
 * -1 on error.
 */
int _str_to_int_err(char *s)
{
int i = 0;
unsigned long int result = 0;

if (*s == '+')
s++; /* Note: Invstigate why it affect a main functions return value of 255. */
for (i = 0; s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
result *= 10;
result += (s[i] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}
