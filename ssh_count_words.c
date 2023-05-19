#include "shell.h"

/**
 * count_word - it counts the amount of words in the string and length.
 * @str: the string.
 * @del: the delimiters to separate the string.
 * @array: the array to hold the word lengths.
 *
 * Return: the amount of words.
 */

int count_word(char *str, char *del, unsigned int *array)
{
	unsigned int c, d, length = 1, count = 0;
	char *s_cpy = str;
	bool start = 0, node;

	if (!str)
		return (0);
	while (!start)
		for (d = 0; del[d]; d++)
		{
			if (*s_cpy == del[d])
				s_cpy++;
			else
				start = 1;
		}
	if (!*(s_cpy + 1))
	{
		array[0] = 1;
		return (1);
	}
	for (c = 1; s_cpy[c]; c++)
	{
		node = is_delimiter(s_cpy[c], del);
		if (node && !(is_delimiter(s_cpy[c - 1], del)))
		{
			array[count] = length;
			count++;
		}
		if ((!s_cpy[c + 1]) && !node)
		{
			length++;
			array[count] = length;
			count++;
			break;
		}
		if (!node)
			length++;
		else
			length = 0;
	}
	return (count);
}
