#include "shell.h"


/**
 * _realloc - it reallocates a memory block.
 *
 * @ptr: pointer to previou memory block.
 * @o_size: old byte size.
 * @n_size: new byte size.
 *
 * Return: old memory block.
 */
void *_realloc(void *ptr, unsigned int o_size, unsigned int n_size)
{
	char *i;

	if (!ptr)
		return (malloc(n_size));

	if (!n_size)
		return (free(ptr), NULL);

	if (n_size == o_size)
		return (ptr);

	i = malloc(n_size);
	if (!i)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;

	while (o_size--)
		i[o_size] = ((char *)ptr)[o_size];
	free(ptr);

	return (i);
}


/**
 * _memset - it sets memory with constance byte.
 *
 * @st: holds pointer to memory.
 * @byte: the byte.
 * @n: amount of byte>
 *
 * Return: it returns st.
 */
char *_memset(char *st, char byte, unsigned int n)
{

	unsigned int index;

	for (index = 0; index < n; index++)
	st[index] =  byte;

	return (st);
}


/**
 * free_space- it sets free the memoryallocation for string.
 *
 * @sp: it is the string.
 *
 * Return: it returns void.
 */
void free_space(char **sp)
{
	char **i = sp;

	if (!sp)
		return;
	while (*sp)

		free(*sp++);

	free(i);
}


#include "shell.h"


/**
 * bfree - it free pointer and set the addressto NULL.
 *
 * @p: holds the pointer.
 *
 * Return: if success 1, 0 if otherwise.
 */
int bfree(void **p)
{

	if (p && *p)
	{
		free(*p);
		*p = NULL;

		return (1);
	}

	return (0);

}
