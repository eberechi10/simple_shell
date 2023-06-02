#include "shell.h"


/**
 * _putchar - a function to print character to stdout.
 *
 * @c: the character
 *
 * Return: if success 1, otherwise -1 and set errno.
 */
int _putchar(char c)
{
	static int index;
	static char buf[BUF_WRITE_SIZE];

	if (c == BUFFER_ONE || index >= BUF_WRITE_SIZE)
	{
		write(1, buf, index);
		index = 0;
	}
	if (c != BUFFER_ONE)

		buf[index++] = c;

	return (1);
}

/**
 * cpy_str - a function to copy the string.
 *
 * @dest: destination of the string.
 * @src: source of the string
 *
 * Return: pointer to destination
 */
char *cpy_str(char *dest, char *src)
{
	int index;

	index = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = 0;
	return (dest);
}


/**
 * _puts - a function to print string input.
 *
 * @str: the string.
 *
 * Return: Nothing
 */

void _puts(char *str)
{
	int index;

	index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}

/**
 * dup_str - a function to duplicate the string.
 *
 * @str: string duplicated.
 *
 * Return: the duplicated string
 */
char *dup_str(const char *str)
{
	int i;
	char *s;

	i = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	for (i++; i--;)
		s[i] = *--str;
	return (s);
}
