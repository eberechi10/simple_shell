#include "shell.h"

/**
 * is_my_exe - it determines file is executable cmd.
 * @info: holds the parameter of info.
 * @path: a pointer to path of the file.
 *
 * Return: if success 1, 0 otherwise
 */
bool is_my_exe(shell_info *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _dupchar - it is a function to duplicate characters
 * @pathstr: it is the PATH of the string.
 * @start: the start index
 * @stop: the end index
 *
 * Return: a pointer of the new buffer
 */
char *_dupchar(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int index = 0, ken = 0;

	for (ken = 0, index = start; index < stop; index++)
		if (pathstr[index] != ':')
			buf[ken++] = pathstr[index];
	buf[ken] = 0;
	return (buf);
}

/**
 * search_path - search for this command in the PATH.
 * @info: it holds the info paramters.
 * @pathstr: it is the PATH
 * @cmd: the command to be searched.
 *
 * Return: the complete path of the command.
 */
char *search_path(shell_info *info, char *pathstr, char *cmd)
{
	int index, current_pos;
	char *path;

	index = 0;
	current_pos = 0;

	if (!pathstr)
		return (NULL);
	if ((len_str(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_my_exe(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[index] || pathstr[index] == ':')
		{
		path = _dupchar(pathstr, current_pos, index);
			if (!*path)
				cat_str(path, cmd);
			else
			{
				cat_str(path, "/");
				cat_str(path, cmd);
			}
			if (is_my_exe(info, path))
				return (path);
			if (!pathstr[index])
				break;
			current_pos = index;
		}
		index++;
	}
	return (NULL);
}
