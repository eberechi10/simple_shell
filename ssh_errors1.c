#include "shell.h"

/**
 * get_error - gets the error message.
 * @info: holds the parameter and the return info
 * @estr: holds specified error type
 *
 * Return: if sucess 0, otherwise -1
 */
void get_error(shell_info *info, char *estr)
{
	puts_ssh(info->name_file);
	puts_ssh(": ");
	hold_dec(info->conut_lines, STDERR_FILENO);
	puts_ssh(": ");
	puts_ssh(info->argv[0]);
	puts_ssh(": ");
	puts_ssh(estr);
}

/**
 * hold_comment - it subs the instance of '#' with '\0'
 * @buf: the string
 *
 * Return: if success 0;otherwise 1
 */

void hold_comment(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
}

/**
 * print_dec - it prints a decimal number in base 10
 * @input: it is the input.
 * @fd: it is the filedescriptor.
 *
 * Return: the printed chars number.
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int index, total;
	unsigned int _abs_, current;

	total = 0;

	if (fd == STDERR_FILENO)
		__putchar = putchar_ssh;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		total++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (index = 1000000000; index > 1; index /= 10)
	{

		if (_abs_ / index)
		{
			__putchar('0' + current / index);
			total++;
		}
		current %= index;
	}
	__putchar('0' + current);
	total++;
	return (total);
}

/**
 * err_num - a function to convert string to integer.
 * @s: it is the string.
 *
 * Return: if success 0, otherwise -1
 */
int err_num(char *s)
{
	int index;
	unsigned long int ret;

	index = 0;
	ret = 0;

	if (*s == '+')
		s++;
	for (index = 0; s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			ret *= 10;
			ret += (s[index] - '0');
			if (ret > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (ret);
}

/**
 * sub_base - a function to convert or similar to itoa
 * @num: it is the number.
 * @base: it the base.
 * @flags: it is the argument flags
 *
 * Return: it returns the string values
 */
char *sub_base(long int num, int base, int flags)
{
	char sign;
	char *ptr;
	unsigned long i;

	sign = 0;
	i = num;

	static char *arr;
	static char buffer[50];

	if (!(flags & CONV_UNSIG) && num < 0)
	{
		i = -num;
		sign = '-';
	}
	arr = flags & CONV_LOWER_CHAR ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = arr[i % base];
		i /= base;
	} while (i != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}
