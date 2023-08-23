#include "main.h"

char *arg_get(char *route, int *exe_cmd);
int arg_call(char **args, char **front, int *exe_cmd);
int arg_run(char **args, char **front, int *exe_cmd);
int arg_handle(int *exe_cmd);
int arg_check(char **args);
int record; /* Definition here */

/**
 * arg_get - get args of a command.
 * @route: route.
 * @exe_cmd: command.
 * Return: error or - NULL.
 */
char *arg_get(char *route, int *exe_cmd)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (route)
		free(route);

	read = _getroute(&route, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		record++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (arg_get(route, exe_cmd));
	}

	route[read - 1] = '\0';
	var_proxy(&route, exe_cmd);
	imp_route(&route, read);

	return (route);
}

/**
 * arg_call - calls .
 * @args: arguments.
 * @front: pointer.
 * @exe_cmd:  value.
 * Return: value.
 */
int arg_call(char **args, char **front, int *exe_cmd)
{
	int ret, index;

	if (!args[0])
		return (*exe_cmd);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = arg_run(args, front, exe_cmd);
			if (*exe_cmd != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = arg_run(args, front, exe_cmd);
			if (*exe_cmd == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = arg_run(args, front, exe_cmd);
	return (ret);
}

/**
 * arg_run - run arguments.
 * @args: arguments.
 * @front: pointer .
 * @exe_cmd: command.
 * Return: value .
 */
int arg_run(char **args, char **front, int *exe_cmd)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_cmd = ret;
	}
	else
	{
		*exe_cmd = execute(args, front);
		ret = *exe_cmd;
	}

	record++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * arg_handle - handle arguments.
 * @exe_cmd: command.
 * Return: O/w.
 */
int arg_handle(int *exe_cmd)
{
	int ret = 0, index;
	char **args, *route = NULL, **front;

	route = arg_get(route, exe_cmd);
	if (!route)
		return (END_OF_FILE);

	args = _strtok(route, " ");
	free(route);
	if (!args)
		return (ret);
	if (arg_check(args) != 0)
	{
		*exe_cmd = 2;
		free_memory_arg(args, args);
		return (*exe_cmd);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = arg_call(args, front, exe_cmd);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = arg_call(args, front, exe_cmd);

	free(front);
	return (ret);
}

/**
 * arg_check - checks specials in arguments.
 * @args: arguments.
 * Return: - 2/- 0.
 */
int arg_check(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (throw_except(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (throw_except(&args[i + 1], 2));
		}
	}
	return (0);
}
