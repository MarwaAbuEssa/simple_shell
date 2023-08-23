#include "main.h"

int count_num(int num);
char *_itoa(int num);
int throw_except(char **args, int except);

/**
 * count_num - number counts.
 * @num: The number.
 * Return: length.
 */
int count_num(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * _itoa - integer to a string.
 * @num: The number.
 * Return:   string.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = count_num(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}

/**
 * throw_except - throw exception stderr.
 * @args:  arguments.
 * @except: exception.
 * Return: exception.
 */
int throw_except(char **args, int except)
{
	char *exception;

	switch (except)
	{
	case -1:
		exception = exception_env(args);
		break;
	case 1:
		exception = exception_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			exception = exception_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			exception = exception_syx(args);
		else
			exception = exception_cd(args);
		break;
	case 126:
		exception = exception_126(args);
		break;
	case 127:
		exception = exception_127(args);
		break;
	}
	write(STDERR_FILENO, exception, _strlen(exception));

	if (exception)
		free(exception);
	return (except);
}
