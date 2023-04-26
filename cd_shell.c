#include "main.h"

/**
 * cd_shell - changes current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int cd_shell(data_shell *datash)
{
	char *currdir;
	int home, home1, sddash;

	currdir = datash->args[1];

	if (currdir != NULL)
	{
		home = _strcmp("$HOME", currdir);
		home1 = _strcmp("~", currdir);
		sddash = _strcmp("--", currdir);
	}

	if (currdir == NULL || !home || !home1 || !sddash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", currdir) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", currdir) == 0 || _strcmp("..", currdir) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}

