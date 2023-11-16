#include "shell.h"

/**
 * add_node - It generates a node to begining of list.
 *
 * @head: This addresses the pointer to a head node
 * @str: This is for str field of a node
 * @num: The node of index used by the history
 *
 * Return: The size of the list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
list_t *new_head;

if (!head)
return (NULL);
new_head = malloc(sizeof(list_t));
if (!new_head)
return (NULL);
_memset((void *)new_head, 0, sizeof(list_t));
new_head->num = num;
if (str)
{
new_head->str = _strdup(str);
if (!new_head->str)
{
free(new_head);
return (NULL);
}
}
new_head->next = *head;
*head = new_head;
return (new_head);
}

/**
 * add_node_end - This generates a node at finish of a list
 * @head: This one addresses a pointer of head a node
 * @str: This a str field of a node
 * @num: The node of index used by a history
 *
 * Return: The size of a list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
list_t *new_node, *node;

if (!head)
return (NULL);

node = *head;
new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);
_memset((void *)new_node, 0, sizeof(list_t));
new_node->num = num;
if (str)
{
new_node->str = _strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;
return (new_node);
}

/**
 * print_list_str - This prints a str element only, of the list_t linked t list
 * @h:The pointer to a node that i 1st on the list.
 *
 * Return: whole size of the list
 */
size_t print_list_str(const list_t *h)
{
size_t i = 0;

while (h)
{
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}

/**
 * delete_node_at_index - It gets rid of node at the given index
 * @head: addresses the pointer to a 1st node
 * @index: For a index of node to be deleted
 *
 * Return: 1 on pass, 0 false
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
list_t *node, *prev_node;
unsigned int i = 0;

if (!head || !*head)
return (0);

if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}
node = *head;
while (node)
{
if (i == index)
{
prev_node->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
}
return (0);
}

/**
 * free_list - This relaeases a node of the list
 * @head_ptr: This addresses the pointer head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
list_t *node, *next_node, *head;

if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
node = head;
while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}
*head_ptr = NULL;
}

/**
 * list_len - calculates the size of a linked list
 * @h: pointer to the first node of the list
 * Return: the number of elements in the list
 */

size_t list_len(const list_t *h)
{
size_t i = 0;

if (!h)
return (0);
while (h)
{
h = h->next;
i++;
}
return (i);
}

/**
 * list_to_strings - Converts a linked list of strings into an array of strings.
 * @head: Pointer to the first node of the linked list.
 * Return: An array of strings.
 */
char **list_to_strings(list_t *head)
{
list_t *node = head;
size_t i = list_len(head), j;
char **strs;
char *str;

if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}

str = _strcpy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}

/**
 * convert_number - Converts a number to a string
 * @num: The number to convert
 * @base: The base system
 * @size: The buffer size
 *
 * Return: The converted string
*/

char *convert_number(int num, int base, int size __attribute__((unused)))
{
static char buffer[50];
int i = 0;

do {
buffer[i++] = "0123456789abcdef"[num % base];
num /= base;
} while (num != 0);

buffer[i] = '\0';

return (buffer);
}


/**
 * print_list - Displays all elements of a list_t linked list
 * @h: Pointer to the first node of the list
 * Return: The size of the list
 */

size_t print_list(const list_t *h)
{
size_t i = 0;

while (h)
{
_puts((char *)convert_number(h->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}

/**
 * node_starts_with - Returns a node in the list whose string starts with the given prefix
 * @node: Pointer to the list head
 * @prefix: The string to match at the beginning
 * @c: The next character after the prefix to match
 * Return: The matching node or NULL if not found
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
char *p = NULL;

if (!node)
return (NULL);
while (node)
{
p = starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}
