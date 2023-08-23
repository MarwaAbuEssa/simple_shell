#include "main.h"

void sig_handler(int sig);
int execute(char **args, char **front);
int record; /* Definition here */

/**
 * sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute - Executes a command.
 * @args: An array of arguments.
 * @front: a pointer.
 * Return:  O/w .
 */
int execute(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = get_command_path(cmd);
	}

	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (create_error(args, 126));
		else
			ret = (create_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				ret = (create_error(args, 126));
			free_env();
			free_memory_arg(args, front);
			free_alias_list(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmd);
	return (ret);
}

/**
 * main - Entry Point.
 * @argc: The number of arguments.
 * @argv: An array of arguments.
 * Return: The return value.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_cmd = &retn;
	char *prompt = "$ ", *new_route = "\n";

	name = argv[0];
	record = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*exe_cmd = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = file_cmds(argv[1], exe_cmd);
		free_env();
		free_alias_list(aliases);
		return (*exe_cmd);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handle_args(exe_cmd);
		free_env();
		free_alias_list(aliases);
		return (*exe_cmd);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handle_args(exe_cmd);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_route, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_cmd);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_cmd);
}
