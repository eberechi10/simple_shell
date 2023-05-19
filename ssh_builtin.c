#include "shell.h"

/**
 * unset_alias -it is a function to set the alias.
 *
 * @info: it holds the parameter.
 * @str: it is the string of the alias.
 *
 * Return: if success 0, otherwise 1
 */
int unset_alias(shell_info *info, char *str)
{
	char *p = 0, c;
	int ret;

	p = str_char(str, '=');
	if (!p)
		return (1);
	c = *p;
	ret = delete_first_node(&(info->alias),
		take_first_node(info->alias, start_node_char(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - a function to set the alias to the string.
 *
 * @info: holds the parameter
 * @str: it is the string of the alias
 *
 * Return: if success 0,  otherwise 0
 */
int set_alias(shell_info *info, char *str)
{
	char *p;

	p = str_char(str, '=');

	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);

	return (add_last_node(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - a function to print the alias string
 *
 * @node: it is the node of the alias
 *
 * Return: if 0 success, otherwise 1
 */
int print_alias(shell_list *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = str_char(node->str, '=');

		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');

		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * hold_alias - creates similar alias builtin (man alias)
 *
 * @info: the simulated arguments
 *
 * Return: Always 0
 */
int hold_alias(shell_info *info)
{
	int index;
	char *p = NULL;
	shell_list *node = NULL;

	index = 0;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		p = str_char(info->argv[index], '=');
		if (p)
			set_alias(info, info->argv[index]);
		else
			print_alias(start_node_char(info->alias, info->argv[index], '='));
	}
	return (0);
}

/**
 * sub_alias - it sub an aliases in the tokenized string
 *
 * @info: the parameter holds
 *
 * Return: success 1, otherwise 0
 */
int sub_alias(shell_info *info)
{
	int index;
	shell_list *node;
	char *p;

	for (index = 0; index < 10; index++)
	{
		node = start_node_char(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = str_char(node->str, '=');

		if (!p)
			return (0);
		p = dup_str(p + 1);

		if (!p)
			return (0);
		info->argv[0] = p;
	}

	return (1);
}
