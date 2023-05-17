#include "shell.h"


/**
 * puts_str - a function to prints the string input
 * @str: the string
 * @fd: the filedescriptor
 *
 * Return: amount of characters.
 */
int puts_str(char *str, int fd)
{
	int index;

	index = 0;

	if (!str)
		return (0);

	while (*str)
	{
		index += put_str(*str++, fd);
	}

	return (index);
}


/**
 * putchar_ssh - a function to write character to the stderr.
 * @c: the character.
 *
 * Return: 1 if success, otherwise -1
 */
int putchar_ssh(char c)
{
	static int index;
	static char buf[BUF_WRITE_SIZE];

	if (c == BUFFER_ONE || index >= BUF_WRITE_SIZE)
	{
		write(2, buf, index);
		index = 0;
	}

	if (c != BUFFER_ONE)
		buf[index++] = c;

	return (1);
}


/**
 * puts_ssh - a function to prints string input.
 * @str: the string.
 *
 * Return: Nothing
 */
void puts_ssh(char *str)
{
	int index;

	index = 0;


	if (!str)
		return;

	while (str[index] != '\0')
	{
		putchar_err(str[index]);

		index++;
	}
}

/**
 * put_str - a function write character to the fd
 * @c: the character
 * @fd: the filedescriptor.
 *
 * Return: 1 if success, otherwise -1
 */
int put_str(char c, int fd)
{
	static int index;
	static char buf[BUF_WRITE_SIZE];


	if (c == BUFFER_ONE || index >= BUF_WRITE_SIZE)
	{
		write(fd, buf, index);
		index = 0;
	}

	if (c != BUFFER_ONE)
		buf[index++] = c;
	return (1);
}
