 #include "main.h"

/**
 * cmpre_env_name - compares env variables names
 * with the name passed.
 * @namenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmpre_env_name(const char *namenv, const char *name)
{
	int i;

	for (i = 0; namenv[i] != '='; i++)
	{
		if (namenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **environ)
{
	char *_ptrenv;
	int i, viron;

	/* Initialize ptr_env value */
	_ptrenv = NULL;
	viron = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		viron = cmpre_env_name(_environ[i], name);
		if (viron)
		{
			_ptrenv = _environ[i];
			break;
		}
	}

	return (_ptrenv + viron);
}

/**
 * _env - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int i, a;

	for (i = 0; datash->_environ[i]; i++)
	{

		for (a = 0; datash->_environ[i][a]; a++)
			;

		write(STDOUT_FILENO, datash->_environ[i], a);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}

