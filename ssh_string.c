#include "shell.h"


/**
 * cat_str - it is a function to concatenates two strings.
 *
 * @dest: it is the buffer destination.
 * @src: it is the source of the buffer.
 *
 * Return: destination buffer
 */
char *cat_str(char *dest, char *src)
{
	char *sun = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;
	*dest = *src;

/* it will return sun */
	return (sun);
}


/**
 * len_str - a function to count string length.
 *
 * @str: the string
 *
 * Return: the length of the string.
 */
int len_str(char *str)
{
	int index = 0;

	if (!str)
		return (0);

	while (*str++)
		index++;

/* it will return index */
	return (index);
}

/**
 * cmp_str - a function to comparison of two strangs.
 *
 * @str1: first strang
 * @str2: second strang
 *
 * Return: str1 < str2 if negative, str1 > str2 if positive,
 * str1 == str2 if zero.
 */
int cmp_str(char *str1, char *str2)
{
	while (*str1 && *str2)
	{

		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);

	else

		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - a function to checks needle starts with haystack
 *
 * @haystack: the string
 * @needle: it is the substring.
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)

		if (*needle++ != *haystack++)

			return (NULL);

/* it will return haystack */
	return ((char *)haystack);
}
