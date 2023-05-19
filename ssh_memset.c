#include "shell.h"


/**
 * take_zeros - it takes the integer byte to 0.
 *
 * @array: the initialized array.
 * @size: the size.
 *
 * Return: it returns nothing.
 */
void take_zeros(unsigned int *array, size_t size)
{

	size_t i;

	for (i = 0; i < size; i++)


		array[i] = 0;
}


/**
 * set_nulls - sets all the charcters in array to nullS.
 *
 * @array: the array.
 * @size: the size.
 *
 *Return: it return nothing.
 */
void set_nulls(char *array, size_t size)
{

	size_t i;

	for (i = 0; i < size; i++)

		array[i] = '\0';

}

/***simple shell memset ***/
