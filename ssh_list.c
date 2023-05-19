#include "shell.h"

/**
 * print_list_str - it prints the string shell_list list.
 *
 * @h: the first node.
 *
 * Return: it return the list.
 */
size_t print_list_str(const shell_list *h)
{
	size_t index;

	index = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * add_node_start - it adds up the node to the list start.
 *
 * @head: holds the pointer to the first node.
 * @str: it the str.
 * @num: it the index history.
 *
 * Return: it return the list.
 */
shell_list *add_node_start(shell_list **head, const char *str, int num)
{
	shell_list *cur_head;

	if (!head)
		return (NULL);
	cur_head = malloc(sizeof(shell_list));

	if (!cur_head)
		return (NULL);
	_memset((void *)cur_head, 0, sizeof(shell_list));
	cur_head->num = num;

	if (str)
	{
		cur_head->str = dup_str(str);

		if (!cur_head->str)
		{
			free(cur_head);
			return (NULL);
		}
	}
	cur_head->next = *head;
	*head = cur_head;
	return (cur_head);
}


/**
 * add_last_node - adds the last node of the list.
 *
 * @head: holds the pointer to head node
 * @str: the string
 * @num: the index history
 *
 * Return: it return the list.
 */
shell_list *add_last_node(shell_list **head, const char *str, int num)
{
	shell_list *cur_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	cur_node = malloc(sizeof(shell_list));
	if (!cur_node)
		return (NULL);
	_memset((void *)cur_node, 0, sizeof(shell_list));
	cur_node->num = num;
	if (str)
	{
		cur_node->str = dup_str(str);
		if (!cur_node->str)
		{
			free(cur_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = cur_node;
	}
	else
		*head = cur_node;
	return (cur_node);
}


/**
 * free_list - it is a function to free all nodes in the list
 *
 * @head_ptr: holds the pointer to head node
 *
 * Return: it returns void.
 */
void free_list(shell_list **head_ptr)
{
	shell_list *n_node, *nx_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	n_node = head;
	while (n_node)
	{
		nx_node = n_node->next;
		free(n_node->str);
		free(n_node);
		n_node = nx_node;
	}
	*head_ptr = NULL;
}

/**
 * delete_first_node - it deletes the first node.
 *
 * @head: holds the pointer to first node
 * @index: the first node
 *
 * Return: if 1 success, otherwise 0
 */
int delete_first_node(shell_list **head, unsigned int index)
{
	shell_list *n_node, *f_node;
	unsigned int s;

	s = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		n_node = *head;
		*head = (*head)->next;
		free(n_node->str);
		free(n_node);
		return (1);
	}
	n_node = *head;
	while (n_node)
	{
		if (s == index)
		{
			f_node->next = n_node->next;
			free(n_node->str);
			free(n_node);
			return (1);
		}
		s++;
		f_node = n_node;
		n_node = n_node->next;
	}
	return (0);
}
