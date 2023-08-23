#include "main.h"

int cant_open(char *file_path);
int proc_file_commands(char *file_path, int *exe_cmd);
int hist; /* Definition here */

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * proc_file_commands - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_cmd: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int proc_file_commands(char *file_path, int *exe_cmd)
{
	ssize_t file, b_read, i;
	unsigned int route_size = 0;
	unsigned int old_size = 120;
	char *route, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_cmd = cant_open(file_path);
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
