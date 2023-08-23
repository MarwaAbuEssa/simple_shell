#include "main.h"

void free_memory_arg(char **args, char **front);
char *get_pid(void);
char *env_value(char *start, int len);
void var_proxy(char **args, int *exe_cmd);

/**
 * free_memory_arg - memory.
 * @args: arguments.
 * @front: a pointer.
 */
void free_memory_arg(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * get_pid - current process ID.
 * Description: current process ID.
 * Return: ID or NULL.
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * env_value - value to env.
 * @start: env start.
 * @len: The length of var.
 * Return: found or not.
 * Description: VARIABLE=VALUE.
 */
char *env_value(char *start, int len)
{
	char **var_addr;
	char *rproxy = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, start, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		rproxy = malloc(_strlen(temp) + 1);
		if (rproxy)
			_strcpy(rproxy, temp);
	}

	return (rproxy);
}

/**
 * var_proxy -  variable proxy.
 * @line: a pointer.
 * @exe_cmd: a pointer.
 * Description: variable proxy.
 */
void var_proxy(char **line, int *exe_cmd)
{
	int j, k = 0, len;
	char *rproxy = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
			old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				rproxy = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				rproxy = _itoa(*exe_cmd);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				for (k = j + 1; old_line[k] &&
								old_line[k] != '$' &&
								old_line[k] != ' ';
					 k++)
					;
				len = k - (j + 1);
				rproxy = env_value(&old_line[j + 1], len);
			}
			new_line = malloc(j + _strlen(rproxy) + _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (rproxy)
			{
				_strcat(new_line, rproxy);
				free(rproxy);
				rproxy = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
