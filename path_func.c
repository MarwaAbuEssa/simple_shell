#include "main.h"

char *copy_path(char *path);
list_t *get_path(char *path);

/**
 * get_command_path - command with PATH.
 * @cmd: The command.
 * Return: If an error - NULL.Otherwise - path.
 */
char *get_command_path(char *cmd)
{
	char **path, *temp;
	list_t *directories, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	directories = get_path(*path + 5);
	head = directories;

	while (directories)
	{
		temp = malloc(_strlen(directories->dir) + _strlen(cmd) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, directories->dir);
		_strcat(temp, "/");
		_strcat(temp, cmd);

		if (stat(temp, &st) == 0)
		{
			free_node_list(head);
			return (temp);
		}

		directories = directories->next;
		free(temp);
	}

	free_node_list(head);

	return (NULL);
}

/**
 * copy_path - get path copy
 * @path: directories.
 * Return: path
 */
char *copy_path(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += _strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path - return pathes
 * @path: path of directories.
 * Return: pointer.
 */
list_t *get_path(char *path)
{
	int i;
	char **directories, *path_copy;
	list_t *head = NULL;

	path_copy = copy_path(path);
	if (!path_copy)
		return (NULL);
	directories = _strtok(path_copy, ":");
	free(path_copy);
	if (!directories)
		return (NULL);

	for (i = 0; directories[i]; i++)
	{
		if (add_end_node(&head, directories[i]) == NULL)
		{
			free_node_list(head);
			free(directories);
			return (NULL);
		}
	}

	free(directories);

	return (head);
}
