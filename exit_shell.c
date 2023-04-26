#include "main.h"

/**
 * exit_shell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(data_shell *datash)
{
	unsigned int unstatus;
	int in_digit;
	int str_len;
	int number;

	if (datash->args[1] != NULL)
	{
		unstatus = _atoi(datash->args[1]);
		in_digit = _indigit(datash->args[1]);
		str_len = _strlen(datash->args[1]);
		number = unstatus > (unsigned int)INT_MAX;
		if (!in_digit || str_len > 10 || number)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (unstatus % 256);
	}
	return (0);
}

