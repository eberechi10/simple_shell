#include "shell.h"


/**
 * take_input - it takes line without the newline.
 * @info: it holds the parameter info
 *
 * Return: the bytes value
 */
ssize_t take_input(shell_info *info)
{
	static char *buf;
	static size_t index, j, len;
	ssize_t s = 0;
	char **buf_po = &(info->arg), *p;

	_putchar(BUFFER_ONE);
	s = buffer_input(info, &buf, &len);
	if (s == -1)
		return (-1);
	if (len)
	{
		j = index;
		p = buf + index;
		check_chain(info, buf, &j, index, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		index = j + 1;
		if (index >= len)
		{
			index = len = 0;
			info->sh_buf_type = LINE_ORI;
		}
		*buf_po = p;
		return (len_str(p));
	}
	*buf_po = buf;

	return (s);
}


/**
 * hold_sigint - if is the function that blocks ctrl-C
 * @sig_num: it is signal number
 *
 * Return: void
 */
void hold_sigint(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_ONE);
}

/**
 * scan_buffer - it scans the buffer
 * @info: it holds the parameter
 * @buf: it is the buffer
 * @i: the size of the buffer
 *
 * Return: it will return s
 */
ssize_t scan_buffer(shell_info *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	s = read(info->read_fdes, buf, BUF_READ_SIZE);
	if (s >= 0)
		*i = s;
	return (s);
}


/**
 * buffer_input - it is the chained commands buffer.
 * @info: it is parameter
 * @buf: the address of the buf.
 * @len: the address of lenght variable
 *
 * Return: if success read the bytes.
 */
ssize_t buffer_input(shell_info *info, char **buf, size_t *len)
{
	ssize_t s;
	size_t len_v;

	s = 0;
	len_v = 0;
	if (!*len)
	{
		/*bfree((void **)info->sh_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, hold_sigint);
#if USE_GETLINE
		s = getline(buf, &len_v, stdin);
#else
		s = _getline(info, buf, &len_v);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0';
				s--;
			}
			info->counter_flag = 1;
			hold_comment(*buf);
			develop_history(info, *buf, info->histcounter++);
			/* if (str_char(*buf, ';')) is this a command chain? */
			{
				*len = s;
				info->sh_buf = buf;
			}
		}
	}
	return (s);
}



/**
 * _getline - it gets next input line.
 * @info: the parameter
 * @ptr: it holds the pointer to the buf.
 * @length: the size of the buf if not NULL
 *
 * Return: q
 */
int _getline(shell_info *info, char **ptr, size_t *length)
{
	static char buf[BUF_READ_SIZE];
	static size_t index, len;
	size_t k;
	ssize_t j, q;
	char *p = NULL, *new_po = NULL, *c;


	q = 0;
	j = 0;
	p = *ptr;
	if (p && length)
		q = *length;
	if (index == len)
		index = len = 0;

	j = scan_buffer(info, buf, &len);
	if (j == -1 || (j == 0 && len == 0))
		return (-1);
	c = str_char(buf + index, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_po = _realloc(p, q, q ? q + k : k + 1);
	if (!new_po)
		return (p ? free(p), -1 : -1);
	if (q)
		catstr_n(new_po, buf + index, k - index);
	else
		cpystr_n(new_po, buf + index, k - index + 1);

	q += k - index;
	index = k;
	p = new_po;

	if (length)
		*length = q;
	*ptr = p;
	return (q);
}
