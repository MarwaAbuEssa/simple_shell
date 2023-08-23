#include "main.h"

int except_file_open(char *fpath);
int file_cmds(char *fpath, int *exe_cmd);
int record; /* Definition here */

/**
 * except_file_open - file doesn't exist
 * @fpath: Path .
 * Return: 127.
 */

int except_file_open(char *fpath)
{
	char *exception, *record_str;
	int len;

	record_str = _itoa(record);
	if (!record_str)
		return (127);

	len = _strlen(name) + _strlen(record_str) + _strlen(fpath) + 16;
	exception = malloc(sizeof(char) * (len + 1));
	if (!exception)
	{
		free(record_str);
		return (127);
	}

	_strcpy(exception, name);
	_strcat(exception, ": ");
	_strcat(exception, record_str);
	_strcat(exception, ": Can't open ");
	_strcat(exception, fpath);
	_strcat(exception, "\n");

	free(record_str);
	write(STDERR_FILENO, exception, len);
	free(exception);
	return (127);
}

/**
 * file_cmds - file commands
 * @fpath: Path to the file.
 * @exe_cmd: Return value.
 * Return: -1 or  - 127
 */
int file_cmds(char *fpath, int *exe_cmd)
{
	ssize_t file, b_read, i;
	unsigned int route_size = 0;
	unsigned int old_size = 120;
	char *route, **args, **front;
	char buffer[120];
	int ret;

	record = 0;
	file = open(fpath, O_RDONLY);
	if (file == -1)
	{
		*exe_cmd = except_file_open(fpath);
		return (*exe_cmd);
	}
	route = malloc(sizeof(char) * old_size);
	if (!route)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && route_size == 0)
			return (*exe_cmd);
		buffer[b_read] = '\0';
		route_size += b_read;
		route = _realloc(route, old_size, route_size);
		_strcat(route, buffer);
		old_size = route_size;
	} while (b_read);
	for (i = 0; route[i] == '\n'; i++)
		route[i] = ' ';
	for (; i < route_size; i++)
	{
		if (route[i] == '\n')
		{
			route[i] = ';';
			for (i += 1; i < route_size && route[i] == '\n'; i++)
				route[i] = ' ';
		}
	}
	var_proxy(&route, exe_cmd);
	imp_route(&route, route_size);
	args = _strtok(route, " ");
	free(route);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_cmd = 2;
		free_memory_arg(args, args);
		return (*exe_cmd);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_args(args, front, exe_cmd);
			args = &args[++i];
			i = 0;
		}
	}

	ret = call_args(args, front, exe_cmd);

	free(front);
	return (ret);
}
