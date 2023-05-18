#ifndef SHELL_H_
#define SHELL_H_

#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dirent.h>
#include <limits.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

extern char **environ;

#define INFO_S	\
	{	NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, \
		 NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0	}


/**
 * struct NodeLIST - it is a singly linked list
 * @num: it is the number
 * @str: it is a string
 * @next: it is the next node
 */
typedef struct NodeLIST
{
	int num;
	char *str;
	struct NodeLIST *next;
} shell_list;

#define BUF_READ_SIZE 1024
#define BUF_WRITE_SIZE 1024
#define COUNT_WORD_MX 100
#define BUFFER_ONE -1
#define LINE_ORI 0
#define LINE_OR 1
#define LINE_AND 2
#define LINE_CHAIN 3
#define CONV_LOWER_CHAR 1
#define CONV_UNSIG 2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HISTORY_NAME     " .ssh_history_file "
#define HISTORY_MX 4096


/**
 * struct NodeINFO - it holds arguments for a function pointer,
 *
 * @arg: it is a string from getline that holds arguments
 * @argv: it is a strings from arg.
 * @path: it is the current commend path string.
 * @argc: it is the count of the arguments
 * @count_lines: the count of errors.
 * @code_er: it is the error code for the exit().
 * @counter_flag: it show the input line to be counted.
 * @name_file: it is the name of the file
 * @env: a local copy of linked list in the environment.
 * @environ: custom-modified environ from the linked list environ.
 * @history: the node for history.
 * @alias: the node for alias
 * @changed_env: show when environ changed
 * @status: status of most recent executed command.
 * @sh_buf: holds address of pointer to sh_buf for chaining
 * @sh_buf_type: the buffer commend type CMD_type ||, &&, ;
 * @read_fdes: it is the file descriptor for reading line input
 * @histcounter: counts the lines in history.
 */

typedef struct NodeINFO
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	size_t count_lines;
	int code_er;
	int counter_flag;
	char *name_file;
	shell_list *env;
	shell_list *history;
	shell_list *alias;
	char **environ;
	int changed_env;
	int status;

	char **sh_buf;
	int sh_buf_type;
	int read_fdes;
	int histcounter;
} shell_info;


/**
 * struct builtin - it holds a builtin string and function.
 * @type: it is the builtin command flag.
 * @func: it is the function
 */

typedef struct builtin
{
        char *type;
        int (*func)(shell_info *);
} builtin_cmds;


int main(int arc, char **arv);


/*1******ssh_args_hold******/
bool is_my_exe(shell_info *info, char *path);
char *_dupchar(char *pathstr, int start, int stop);
char *search_path(shell_info *info, char *pathstr, char *cmd);

/*2******ssh_builtin2*******/
int hold_cd(shell_info *info);
int hold_exit(shell_info *info);
int hold_history(shell_info *info);
int hold_help(shell_info *info);

/*3******ssh_builtin1******/
int unset_alias(shell_info *info, char *str);
int set_alias(shell_info *info, char *str);
int print_alias(shell_list *node);
int hold_alias(shell_info *info);
int change_alias(shell_info *info);

/*4******ssh_count_word******/
int count_word(char *str, char *del, unsigned int *array);

/*5******ssh_errors******/
int puts_str(char *str, int fd);
int putchar_ssh(char c);
void puts_ssh(char *str);
int put_str(char c, int fd);

/*6******ssh-errors1******/
void get_error(shell_info *info, char *estr);
void hold_comment(char *buf);
int print_dec(int input, int fd);
int err_num(char *s);
char *sub_base(long int num, int base, int flags);

/*7******ssh_getenv1******/
int _setenv(shell_info *info, char *var, char *value);
char **take_environ(shell_info *info);
int _unsetenv(shell_info *info, char *var);

/*8******ssh_getenv2******/
int occupy_env(shell_info *info);
int hold_setenv(shell_info *info);
int hold_env(shell_info *info);
int hold_unsetenv(shell_info *info);
char *_getenv(shell_info *info, const char *name);

/*9******ssh_history******/
int generate_history(shell_info *info);
char *scan_history_f(shell_info *info);
int scan_history(shell_info *info);
int develop_history(shell_info *info, char *buf, int linecount);
int rearrange_history(shell_info *info);

/*10******ssh_info******/
void free_info(shell_info *info, int all);
void empty_info(shell_info *info);
void set_info(shell_info *info, char **av);

/*11******ssh_input_hold******/
ssize_t take_input(shell_info *info);
void hold_sigint(__attribute__((unused)) int sig_num);
ssize_t scan_buffer(shell_info *info, char *buf, size_t *i);
ssize_t buffer_input(shell_info *info, char **buf, size_t *len);
int _getline(shell_info *info, char **ptr, size_t *length);

/*12******ssh-list******/
size_t print_list_str(const shell_list *h);
shell_list *add_node_start(shell_list **head, const char *str, int num);
shell_list *add_last_node(shell_list **head, const char *str, int num);
void free_list(shell_list **head_ptr);
int delete_first_node(shell_list **head, unsigned int index);

/*13******ssh_main******/
int main(int arc, char **arv);

/*14******ssh_memory******/
void *_realloc(void *ptr, unsigned int o_size, unsigned int n_size);
char *_memset(char *st, char byte, unsigned int n);
void free_space(char **sp);
int bfree(void **p);

/*15******ssh_memset******/
void take_zeros(unsigned int *array, size_t size);
void set_nulls(char *array, size_t size);

/*16******ssh_nodes******/
size_t len_of_list(const shell_list *h);
char **list_to_chars(shell_list *head);
size_t print_list(const shell_list *h);
shell_list *start_node_char(shell_list *node, char *prefix, char c);
ssize_t take_first_node(shell_list *head, shell_list *node);

/*17******ssh_pointof_entry******/
int hold_builtin(shell_info *info);
void view_command(shell_info *info);
int ssh_main(shell_info *info, char **av);
void fork_process(shell_info *info);

/*18******ssh_string******/
char *cat_str(char *dest, char *src);
int len_str(char *str);
int cmp_str(char *str1, char *str2);
char *starts_with(const char *haystack, const char *needle);

/*19******ssh_string1******/
char *str_char(char *str, char ch);
char *cpystr_n(char *dest, char *src, int n);
char *catstr_n(char *str1, char *str2, int n);

/*20*****ssh_string2*******/
int _putchar(char c);
char *cpy_str(char *dest, char *src);
void _puts(char *str);
char *dup_str(const char *str);

/*21******ssh_strtoken******/
char **strtow(char *str, char *d);
char **str_split(char *str, char del);

/*22******ssh_utils******/
bool is_delimiter(char c, char *del);
int _isalpha(int c);
int _atoi(char *str);
int my_cmd(shell_info *info);

/*23******ssh_vars******/
int sub_vars(shell_info *info);
bool is_chain(shell_info *info, char *buf, size_t *ptr);
void check_chain(shell_info *info, char *buf, size_t *p, size_t i, size_t len);
int sub_string(char **prev, char *cur);

/**the shell project**/

#endif
