#include "shell.h"

/**
* *str_char - it is a function to identifies character in string.
*
* @str: string to parsed
* @ch: the character.
*
* Return: a pointer to the memory area str
*/
char *str_char(char *str, char ch)
{
	do {

		if (*str == ch)
			return (str);

	} while (*str++ != '\0');

	return (NULL);
}

/**
* *cpystr_n - it is function to copy string.
*
* @dest: destination of the string
* @src: source of the string
* @n: number of chars.
*
* Return: it returns concatenated string.
*/
char *cpystr_n(char *dest, char *src, int n)
{
	int index = 0, c;
	char *sto = dest;

	while (src[index] != '\0' && index < n - 1)
	{
		dest[index] = src[index];
		index++;
	}

	if (index < n)
	{
		c = index;
		while (c < n)
		{
			dest[c] = '\0';
			c++;
		}
	}
	return (sto);
}

/**
* *catstr_n - its a function to concatenate two strings.
*
* @str1: first string
* @str2: second string
* @n: the number of bytes used
*
* Return: concatenated string.
*/
char *catstr_n(char *str1, char *str2, int n)
{
	int index = 0, p = 0;
	char *sto = str1;

	while (str1[index] != '\0')
		index++;

	while (str2[p] != '\0' && p < n)
	{
		str1[index] = str2[p];
		index++;
		p++;
	}

	if (p < n)
		str1[index] = '\0';

	return (sto);
}
