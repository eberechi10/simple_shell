#include "shell.h"


/**
 * occupy_env - it enlarges the environ list.
 * @info: holds the arguments function pointer.
 *
 * Return: if success 0
 */
int occupy_env(shell_info *info)
{
	shell_list *node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		add_last_node(&node, environ[index], 0);
	info->env = node;
	return (0);
}

/**
 * hold_setenv - gets a new environ var.
 * @info: holds the arguments pointer.
 *
 * Return: if success 0, otherwise 1.
 */

int hold_setenv(shell_info *info)
{
	if (info->argc != 3)
	{
		puts_ssh("Incorrect number\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * hold_env - prints the current working environ.
 * @info: holds the arguments function pointer,
 *
 * Return: if success 0
 */
int hold_env(shell_info *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * hold_unsetenv - unsets the environ var.
 * @info: holds the arguments pointer
 *
 * Return: if success 0, esle 1
 */
int hold_unsetenv(shell_info *info)
{
	int index;

	if (info->argc == 1)
	{
		puts_ssh("Too few arguements.\n");
		return (1);
	}
	for (index = 1; index <= info->argc; index++)
		_unsetenv(info, info->argv[index]);

	return (0);
}

/**
 * _getenv - prints value of the environment var.
 * @info: holds simulated arguments.
 * @name: the environ variable
 *
 * Return: value of the environ var.
 */

char *_getenv(shell_info *info, const char *name)
{
	char *p;
	shell_list *node = info->env;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

