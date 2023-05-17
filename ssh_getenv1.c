#include "shell.h"

/**
 * _setenv - it setup environ variable or modify it.
 * @info: holds the environ variables.
 *
 * @var: variable to be add or update.
 * @value: value of variable to add or update.
 * Return: 0 if success, otherwise 1.
 */

int _setenv(shell_info *info, char *var, char *value)
{
	char *buf = NULL;
	shell_list *node;
	char *p;

	if (!var || !value)
		return (1);

	buf = malloc(len_str(var) + len_str(value) + 2);
	if (!buf)
		return (1);

	/* variable name and value are joined. */
	cpy_str(buf, var);
	cat_str(buf, "=");
	cat_str(buf, value);

	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{

			free(node->str);
			node->str = buf;
			info->env_sub = 1;
			return (0);
		}

		/* the next variable. */
		node = node->next;
	}


	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_sub = 1;
	return (0);
}

/**
 * take_environ - it prints the environment variables strings.
 * @info: it holds the environment variables.
 *
 * Return: environment variables.
 */

char **take_environ(shell_info *info)
{
	/* update environment variables if not set. */
	if (!info->environ || info->env_sub)
	{
		info->environ = list_to_chars(info->env);
		info->env_sub = 0;
	}
	return (info->environ);
}


/**
 * _unsetenv - it unsets environ var.
 * @info: it holds environment var.
 *
 * @var: environment variable.
 * Return: 1 if success, otherwise 0.
 */
int _unsetenv(shell_info *info, char *var)
{
	shell_list *node = info->env;
	size_t ic;
	char *p;

	ic = 0;

	if (!node || !var)
		return (0);

	/* Looping environ variables. */
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			/* unset current var. */
			info->env_sub = delete_first_node(&(info->env), ic);

			/* go to the index variable. */
			ic = 0;
			node = info->env;
			continue;
		}

		/* get next variable . */
		node = node->next;
		ic++;
	}

	return (info->env_sub);
}
