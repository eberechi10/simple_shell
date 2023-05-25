#include "shell.h"


/**
 * sub_vars - it is a function to replace vars in the tokenized string
 *
 * @info: it holds the parameter.
 *
 * Return: if success 1, 0 otherwise
 */
int sub_vars(shell_info *info)
{
	int index;
	shell_list *node;

	index = 0;

	for (index = 0; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
			continue;
		if (!cmp_str(info->argv[index], "$?"))
		{
			sub_string(&(info->argv[index]),

				dup_str(sub_base(info->status, 10, 0)));
			continue;
		}
		if (!cmp_str(info->argv[index], "$$"))
		{
			sub_string(&(info->argv[index]),

				dup_str(sub_base(getpid(), 10, 0)));
			continue;
		}
		node = start_node_char(info->env, &info->argv[index][1], '=');
		if (node)
		{
			sub_string(&(info->argv[index]),

				dup_str(str_char(node->str, '=') + 1));

			continue;
		}
		sub_string(&info->argv[index], dup_str(""));
	}
	return (0);
}

/**
 * is_chain - check to see if current buffer char is chain delimeter
 *
 * @info: it the hold parameter
 * @buf: the pointer to char buffer
 * @ptr: the addr of the current position
 *
 * Return: if chain delimeter 1, otherwise 0
 */
bool is_chain(shell_info *info, char *buf, size_t *ptr)
{
	size_t j;

	j = *ptr;


	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->sh_buf_type = LINE_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->sh_buf_type = LINE_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->sh_buf_type = LINE_CHAIN;
	}
	else
		return (false);

	*ptr = j;

	return (true);
}

/**
 * check_chain - it checks to continue chaining pending last status
 * @info: it the holds parameter
 * @buf: holds the char buffer
 * @i: it holds a parameter.
 *
 * @p: it is the addr in buffer of current position.
 * @len: the length of the buffer
 *
 * Return: Void
 */
void check_chain(shell_info *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j;

	j = *p;

	if (info->sh_buf_type == LINE_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->sh_buf_type == LINE_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * sub_string - a function to replace a string.
 *
 * @prev: address of old string
 * @cur: the new string
 *
 * Return: if success 1, 0 otherwise
 */
int sub_string(char **prev, char *cur)
{

	free(*prev);

	*prev = cur;

	return (1);
}
