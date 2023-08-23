#include "main.h"

char *exception_env(char **args);
char *exception_1(char **args);
char *exception_exit(char **args);
char *exception_cd(char **args);
char *exception_syx(char **args);
int record; /* Definition here */
char *name;

/**
 * exception_env -  exception_env.
 * @args: arguments.
 * Return: string.
 */
char *exception_env(char **args)
{
	char *exception, *record_str;
	int len;
	int record1 = record;

	record_str = _itoa(record1);
	if (!record_str)
		return (NULL);

	args--;
	len = _strlen(name) + _strlen(record_str) + _strlen(args[0]) + 45;
	exception = malloc(sizeof(char) * (len + 1));
	if (!exception)
	{
		free(record_str);
		return (NULL);
	}

	_strcpy(exception, name);
	_strcat(exception, ": ");
	_strcat(exception, record_str);
	_strcat(exception, ": ");
	_strcat(exception, args[0]);
	_strcat(exception, ": Unable to add/remove from environment\n");

	free(record_str);
	return (exception);
}

/**
 * exception_1 - exception _alias .
 * @args: arguments.
 * Return:  string.
 */
char *exception_1(char **args)
{
	char *exception;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	exception = malloc(sizeof(char) * (len + 1));
	if (!exception)
		return (NULL);

	_strcpy(exception, "alias: ");
	_strcat(exception, args[0]);
	_strcat(exception, " not found\n");

	return (exception);
}

/**
 * exception_exit - exception _exit.
 * @args: arguments .
 * Return:  string.
 */
char *exception_exit(char **args)
{
	char *exception, *record_str;
	int len;
	int record2 = record;

	record_str = _itoa(record2);
	if (!record_str)
		return (NULL);

	len = _strlen(name) + _strlen(record_str) + _strlen(args[0]) + 27;
	exception = malloc(sizeof(char) * (len + 1));
	if (!exception)
	{
		free(record_str);
		return (NULL);
	}

	_strcpy(exception, name);
	_strcat(exception, ": ");
	_strcat(exception, record_str);
	_strcat(exception, ": exit: Illegal number: ");
	_strcat(exception, args[0]);
	_strcat(exception, "\n");

	free(record_str);
	return (exception);
}

/**
 * exception_cd -  exception _cd .
 * @args: arguments .
 * Return: string.
 */
char *exception_cd(char **args)
{
	char *exception, *record_str;
	int len;
	int record3 = record;

	record_str = _itoa(record3);
	if (!record_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(record_str) + _strlen(args[0]) + 24;
	exception = malloc(sizeof(char) * (len + 1));
	if (!exception)
	{
		free(record_str);
		return (NULL);
	}

	_strcpy(exception, name);
	_strcat(exception, ": ");
	_strcat(exception, record_str);
	if (args[0][0] == '-')
		_strcat(exception, ": cd: Illegal option ");
	else
		_strcat(exception, ": cd: can't cd to ");
	_strcat(exception, args[0]);
	_strcat(exception, "\n");

	free(record_str);
	return (exception);
}

/**
 * exception_syx - throw exception syntax.
 * @args: arguments .
 * Return: string.
 */
char *exception_syx(char **args)
{
	char *exception, *record_str;
	int len;
	int record4 = record;

	record_str = _itoa(record4);
	if (!record_str)
		return (NULL);

	len = _strlen(name) + _strlen(record_str) + _strlen(args[0]) + 33;
	exception = malloc(sizeof(char) * (len + 1));
	if (!exception)
	{
		free(record_str);
		return (NULL);
	}

	_strcpy(exception, name);
	_strcat(exception, ": ");
	_strcat(exception, record_str);
	_strcat(exception, ": exception Syntax: \"");
	_strcat(exception, args[0]);
	_strcat(exception, "\" unexpected\n");

	free(record_str);
	return (exception);
}
