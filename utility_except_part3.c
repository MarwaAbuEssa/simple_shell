#include "main.h"

char *exception_126(char **args);
char *exception_127(char **args);
int record; /* Definition here */

/**
 * exception_126 - access denied.
 * @args: arguments.
 * Return:  string.
 */
char *exception_126(char **args)
{
	char *exception, *record_str;
	int len;

	record_str = _itoa(record);
	if (!record_str)
		return (NULL);

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
	_strcat(exception, ": ");
	_strcat(exception, args[0]);
	_strcat(exception, ": Permission denied\n");

	free(record_str);
	return (exception);
}

/**
 * exception_127 - not found.
 * @args: arguments.
 * Return:  string.
 */
char *exception_127(char **args)
{
	char *exception, *record_str;
	int len;

	record_str = _itoa(record);
	if (!record_str)
		return (NULL);

	len = _strlen(name) + _strlen(record_str) + _strlen(args[0]) + 16;
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
	_strcat(exception, ": not found\n");

	free(record_str);
	return (exception);
}
