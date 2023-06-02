#include "shell.h"


/**
 * main - it is the entry point of the shell.
 *
 * @arv: the number of arguments used.
 * @arc: it is the argument vector.
 * Return: if 0 success, otherwise 1
 */
int main(int argc, char **argv)
{
	shell_info info[] = { INFO_S };
	int fdes;

	fdes = 2;

	asm("mov %1, %0\n\t"
			"add $3, %0"
			: "=r"(fdes)
			: "r"(fdes));

	if (argc == 2)

	{
		fdes = open(argv[1], O_RDONLY);

		if (fdes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_ssh(argv[0]);
				puts_ssh(": 0: Can't open ");
				puts_ssh(argv[1]);
				putchar_ssh('\n');
				putchar_ssh(BUFFER_ONE);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_fdes = fdes;
	}
	occupy_env(info);
	scan_history(info);
	ssh_main(info, argv);

	return (EXIT_SUCCESS);
}
