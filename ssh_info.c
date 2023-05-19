#include "shell.h"


/**
 * free_info - its a functiom to free shell_info
 *
 * @info: holds address of the struct
 * @all: holds the freeing all fields
 *
 * Return: void
 */

void free_info(shell_info *info, int all)
{
	free_space(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)

	{
		if (!info->sh_buf)
			free(info->arg);

		if (info->env)
			free_list(&(info->env));

		if (info->history)
			free_list(&(info->history));

		if (info->alias)
			free_list(&(info->alias));

		free_space(info->environ);
		info->environ = NULL;
		bfree((void **)info->sh_buf);

		if (info->read_fdes > 2)
			close(info->read_fdes);
		_putchar(BUFFER_ONE);
	}
}

/**
 * empty_info - it is the start of the shell_info
 *
 * @info: holds address shel_info
 *
 * Return: void
 */

void empty_info(shell_info *info)
{
	info->path = NULL;
	info->arg = NULL;

	info->argv = NULL;

	info->argc = 0;
}


/**
 * set_info - it is the start of the shell_info
 *
 * @info: holds address shell_info
 * @av: the vector of the argument
 *
 * Return: info value
 */

void set_info(shell_info *info, char **av)
{
	int index;

	index = 0;

	info->name_file = av[0];

	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");

		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);

			if (info->argv)
			{
				info->argv[0] = dup_str(info->argv[0]);
				info->argv[1] = NULL;
			}
		}

		for (index = 0; info->argv && info->argv[index]; index++)
			;
		info->argc = index;
		sub_alias(info);
		sub_vars(info);
	}
}
