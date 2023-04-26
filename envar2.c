#include "holberton.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int i;
	char *varab_env, *name_env;

	for (i = 0; datash->_environ[i]; i++)
	{
		varab_env = _strdup(datash->_environ[i]);
		name_env = _strtok(varab_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = copy_info(name_env, value);
			free(varab_env);
			return;
		}
		free(varab_env);
	}

	datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = copy_info(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *varab_env, *name_env;
	int a, b, c;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	c = -1;
	for (a = 0; datash->_environ[a]; a++)
	{
		varab_env = _strdup(datash->_environ[a]);
		name_env = _strtok(varab_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			c = a;
		}
		free(varab_env);
	}
	if (c == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (a));
	for (a = b = 0; datash->_environ[a]; a++)
	{
		if (a != c)
		{
			realloc_environ[j] = datash->_environ[a];
			b++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[c]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}

