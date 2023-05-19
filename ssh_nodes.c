#include "shell.h"


/**
 * len_of_list - it prints the length of string.
 *
 * @h: holds the pointer of the node index.
 *
 * Return: the list size.
 */
size_t len_of_list(const shell_list *h)
{

	size_t index = 0;

	while (h)
	{
		h = h->next;
		index++;
	}

	return (index);
}

/**
 * list_to_chars - the string of the list.
 *
 * @head: holds the pointer to first mode.
 *
 * Return: the strings list.
 */
char **list_to_chars(shell_list *head)
{
	shell_list *node = head;
	size_t index, j;
	char **strs;
	char *str;

	index = len_of_list(head);

	if (!head || !index)
		return (NULL);
	strs = malloc(sizeof(char *) * (index + 1));

	if (!strs)
		return (NULL);
	for (index = 0; node; node = node->next, index++)
	{
		str = malloc(len_str(node->str) + 1);

		if (!str)
		{
			for (j = 0; j < index; j++)
				free(strs[j]);
			free(strs);

			return (NULL);
		}
		str = cpy_str(str, node->str);
		strs[index] = str;
	}
	strs[index] = NULL;

	return (strs);
}


/**
 * print_list - it prints all elements of the shell_list list.
 *
 * @h: it holds the pointer to the list.
 *
 * Return: it returns the size of the list.
 */
size_t print_list(const shell_list *h)
{

	size_t index;

	index = 0;

	while (h)
	{
		_puts(sub_base(h->num, 10, 0));

		_putchar(':');
		_putchar(' ');

		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;

		index++;

	}

	return (index);
}


/**
 * start_node_char - returns node whose string starts with prefix.
 *
 * @node: pointer to the list.
 * @prefix: it is the string.
 *
 * @c: next char after the prefix.
 *
 * Return: match the nodes.
 */
shell_list *start_node_char(shell_list *node, char *prefix, char c)
{

	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);

		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);

		node = node->next;
	}
	return (NULL);
}


/**
 * take_first_node - it takes the first node of the list.
 *
 * @head: holds the pointer to the list head.
 * @node: holds the pointer to node
 *
 * Return: -1 if success otherwise thr node index>
 */
ssize_t take_first_node(shell_list *head, shell_list *node)
{

	size_t index;

	index = 0;

	while (head)

	{

		if (head == node)
			return (index);

		head = head->next;
		index++;
	}

	return (-1);

}

/** shell project **/
