#include "shell.h"


/**
 * hold_builtin - checks for a builtin cmd.
 *
 * @info: holds the parameter and return info.
 *
 * Return: -1 if not exist, 0 if success. 1 if not success
 * 2 if signals exit()
 */
int hold_builtin(shell_info *info)
{

	int index, builtin_re_v;
	builtin_cmds builtinstore[] = {
		{"history", hold_history},
		{"unsetenv", hold_unsetenv},
		{"alias", hold_alias},
		{"setenv", hold_setenv},
		{"cd", hold_cd},
		{"env", hold_env},
		{"exit", hold_exit},
		{"help", hold_help},
		{NULL, NULL} };

	builtin_re_v = -1;

	for (index = 0; builtinstore[index].type; index++)
		if (cmp_str(info->argv[0], builtinstore[index].type) == 0)
		{
			info->count_lines++;
			builtin_re_v = builtinstore[index].func(info);
			break;

		}
	return (builtin_re_v);

}


/**
 * veiw_command - get a cmd in PAYH or current dir.
 * @info: a pointer that holds parameter and return info
 *
 * Return: void.
 */
void veiw_command(shell_info *info)
{
	char * path = NULL;
	int index, count;

	info->path = info->argv[0];
	if (info->counter_flag == 1)
	{
		info->count_lines++;
		info->counter_flag = 0;
	}
	for (index = 0, count = 0; info->arg[index]; index++)
		if (!is_delimiter(info->arg[index], "\t\n"))
			count++;
	if (!count)
		return;
	path = search_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_process(info);
	}
	else
	{
		if ((my_cmd(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_my_exe(info, info->argv[0]))
			fork_process(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			get_error(info, "not Found\n");
		}
	}
}


/**
 * ssh_main - it handles yhe main shell control.
 * @info: a pointer that holds shell_info struct.
 * @av: string that holds the argument.
 *
 * Return: status of the builtin cmd.
 */
int ssh_main(shell_info *info, char **av)
{
	ssize_t scan_r = 0;
	int builtin_re_v = 0;

	while (scan_r != -1 && builtin_re_v != -2)
	{
		empty_info(info);
		if (my_cmd(info))
			_puts("& ");
		putchar_ssh(BUFFER_ONE);
		scan_r = take_input(info);
		if (scan_r != -1)
		{
			set_info(info, av);
			builtin_re_v = hold_builtin(info);
			if (builtin_re_v == -1)
				veiw_command(info);
		}
		else if (my_cmd(info))
			_putchar('\n');
		free_info(info, 0);
	}
	generate_history(info);
	free_info(info, 1);
	if (!my_cmd(info) && info->status)
		exit(info->status);
	if (builtin_re_v == -2)
	{
		if (info->code_er == -1)
			exit(info->status);
		exit(info->code_er);
	}
	return (builtin_re_v);
}


/**
 * fork_process - it forks another executable to run command.
 *
 * @info: a pointer that hols the parameter and return info.
 *
 * Return: void.
 */
void fork_process(shell_info *info)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		/* TODO INSERT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(info->path, info->argv, take_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: INSERT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				get_error(info, "Permission denied\n");
		}
	}
}
