#include "shell.h"


/**
 * **strtow - a functionn to splits a string into words.
 *
 * @str: it is the string
 * @d: it is the delimeter
 * Return: a pointer to the strings if success, null if failure.
 */
char **strtow(char *str, char *d)
{
	int p, c, k, m, amount = 0;
	char **sto;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (p = 0; str[p] != '\0'; p++)
		if (!is_delimiter(str[p], d) && (is_delimiter(str[p + 1], d) || !str[p + 1]))
			amount++;
	if (amount == 0)
		return (NULL);
	sto = malloc((1 + amount) * sizeof(char *));
	if (!sto)
		return (NULL);
	for (p = 0, c = 0; c < amount; c++)
	{
		while (is_delimiter(str[p], d))
			p++;
		k = 0;
		while (!is_delimiter(str[p + k], d) && str[ + k])
			k++;
		sto[c] = malloc((k + 1) * sizeof(char));
		if (!sto[c])
		{
			for (k = 0; k < c; k++)
				free(sto[k]);
			free(sto);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			sto[c][m] = str[p++];
		sto[c][m] = 0;
	}
	sto[c] = NULL;
	return (sto);
}

/**
 * str_split - it is a func to splits string to words,
 * delimiters repeating is not allowed.
 *
 * @str: it is the string.
 * @del: it is the delim to split.
 *
 * Return: a pointer to the strings if success, null if failure.
 */
char **str_split(char *str, char del)
{
	int str_p, index, w_size, s, amount = 0;
	char **words;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (str_p = 0; str[str_p] != '\0'; str_p++)
		if ((str[str_p] != del && str[str_p + 1] == del) ||
			(str[str_p] != del && !str[str_p + 1]) || str[str_p + 1] == del)
			amount++;

	if (amount == 0)
		return (NULL);
	words = malloc((1 + amount) * sizeof(char *));

	if (!words)
		return (NULL);
	for (str_p = 0, index = 0; index < amount; index++)
	{
		while (str[str_p] == del && str[str_p] != del)
			str_p++;
		w_size = 0;
		while (str[str_p + w_size] != del && str[str_p + w_size] &&
				str[str_p + w_size] != del)
			w_size++;
		words[index] = malloc((w_size + 1) * sizeof(char));

		if (!words[index])
		{
			for (w_size = 0; w_size < index; w_size++)
				free(words[w_size]);
			free(words);
			return (NULL);
		}
		for (s = 0; s ; s++)
			words[index][s] = str[str_p++];
		words[index][s] = 0;
	}
	words[index] = NULL;
	return (words);
}
