#include "shell.h"


/**
 * generate_history - generates the history file or appends to old file.
 *
 * @info: it is the parameter pointer
 *
 * Return: if 1 success, otherwise -1
 */
int generate_history(shell_info *info)
{
	ssize_t fde;
	char *filename = scan_history_f(info);
	shell_list *node = NULL;

	if (!filename)
		return (-1);

	fde = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fde == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		puts_str(node->str, fde);
		put_str('\n', fde);
	}
	put_str(BUFFER_ONE, fde);
	close(fde);
	return (1);
}

/**
 * scan_history_f - a function that scans the history files
 *
 * @info: holds the parameter pointer
 *
 * Return: it returns the history files
 */

char *scan_history_f(shell_info *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (len_str(dir) + len_str(HISTORY_NAME) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	cpy_str(buf, dir);
	cat_str(buf, "/");
	cat_str(buf, HISTORY_NAME);
	return (buf);
}
/**
 * scan_history - scans the history from file
 *
 * @info: the parameter of the function
 *
 * Return: if success history, esle 0
 */
int scan_history(shell_info *info)
{
	int index, end = 0, linecount = 0;
	ssize_t fde, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *fname = scan_history_f(info);

	if (!fname)
		return (0);

	fde = open(fname, O_RDONLY);
	free(fname);
	if (fde == -1)
		return (0);
	if (!fstat(fde, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fde, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fde);
	for (index = 0; index < fsize; index++)
		if (buf[index] == '\n')
		{
			buf[index] = 0;
			develop_history(info, buf + end, linecount++);
			end = index + 1;
		}
	if (end != index)
		develop_history(info, buf + end, linecount++);
	free(buf);
	info->histcounter = linecount;
	while (info->histcounter-- >= HISTORY_MX)
		delete_first_node(&(info->history), 0);
	rearrange_history(info);
	return (info->histcounter);
}


/**
 * develop_history - it adds up the history list.
 *
 * @info: holds the arguments for a function
 * @buf: it is the buffer.
 * @linecount: the linecount and histcounter of the history
 *
 * Return: if success 0
 */
int develop_history(shell_info *info, char *buf, int linecount)
{
	shell_list *node = NULL;

	if (info->history)
		node = info->history;
	add_last_node(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * rearrange_history - it rearranges the history list after any changes
 *
 * @info: it is arguments for a function
 *
 * Return: the updated histcounter.
 */
int rearrange_history(shell_info *info)
{
	shell_list *node = info->history;
	int index;

	index = 0;

	while (node)
	{
		node->num = index++;
		node = node->next;
	}
	return (info->histcounter = index);
}
