#include "shell.h"


/**
 * is_delimiter - a function to checks character is delimiter.
 *
 * @c: the character.
 * @del: delimiter string
 *
 * Return: if delimiter 1, otherwise 0
 */

bool is_delimiter(char c, char *del)
{
	int str;

	for (str = 0; del[str]; str++)

		if (c == del[str])
			return (1);
	return (0);
}


/**
 * _isalpha - a function to checks for alphabetic.
 *
 * @c: the character
 *
 * Return: if alphabetic 1, otherwise 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

		return (1);

	else
		return (0);
}

/**
 * _atoi - function that convert string to integer.
 *
 * @str: the string
 *
 * Return: if no numbers in string 0, otherwise the converted integer.
 */

int _atoi(char *str)
{
	int index, sign;
	int flag, output;
	unsigned int ret;

	sign = 1;
	flag = 0;

	ret = 0;

	for (index = 0; str[index] != '\0' && flag != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;

			ret *= 10;
			ret += (str[index] - '0');
		}

		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -ret;

	else
		output = ret;

	return (output);
}


/**
 * my_cmd - it returns true if shell is interactive mode.
 *
 * @info: holds the address
 *
 * Return: if my_cmd mode 1, otherwise 0
 */

int my_cmd(shell_info *info)
{
	return (isatty(STDIN_FILENO) && info->read_fdes <= 2);
}
