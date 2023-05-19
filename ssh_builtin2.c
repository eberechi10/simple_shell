#include "shell.h"

/**
 * hold_cd - function to change current directory.
 * @info: hold simulated arguments.
 *
 * Return: if success 0
 */
int hold_cd(shell_info *info)
{
	char *sk, *dir, buffer[1024];
	int chdir_ret;

	sk = getcwd(buffer, 1024);
	if (!sk)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what can it be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (cmp_str(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(sk);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		get_error(info, "can't cd to ");
		puts_ssh(info->argv[1]), putchar_ssh('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * hold_exit - the function to exits the shell
 * @info: holds simulated arguments.
 *
 * Return: given exit status.
 */
int hold_exit(shell_info *info)
{
	int exitcheck;


	if (info->argv[1]) /* If exit arguement */
	{
		exitcheck = _errbin(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			get_error(info, "Illegal number: ");
			puts_ssh(info->argv[1]);
			putchar_ssh('\n');
			return (1);
		}
		info->code_er = _errbin(info->argv[1]);
		return (-2);
	}
	info->code_er = -1;
	return (-2);
}

/**
 * hold_history - prints the history list.
 *
 * @info: holds simulated arguments
 *
 * Return: if success 0
 */
int hold_history(shell_info *info)
{
	print_list(info->history);

	return (0);
}

/**
 * hold_help - a message for a not implemented functions.
 * @info: holds simulated arguments
 *
 * Return: if success 0
 */
int hold_help(shell_info *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not implemented \n");
	if (0)
		_puts(*arg_array);

	return (0);
}

