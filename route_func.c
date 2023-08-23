#include "main.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_routeptr(char **routeptr, size_t *n, char *buffer, size_t b);
ssize_t _getroute(char **routeptr, size_t *n, FILE *stream);

/**
 * _realloc - Reallocates.
 * @ptr:  pointer.
 * @old_size: old size.
 * @new_size: new size.
 * Return: size ptr
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *mem;
	char *ptr_copy, *filler;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	mem = malloc(sizeof(*ptr_copy) * new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = mem;

	for (index = 0; index < old_size && index < new_size; index++)
		filler[index] = *ptr_copy++;

	free(ptr);
	return (mem);
}

/**
 * assign_routeptr - assigns the routeptr.
 * @routeptr: route of pointer.
 * @n: size of routeptr.
 * @buffer: buffer.
 * @b: size .
 */
void assign_routeptr(char **routeptr, size_t *n, char *buffer, size_t b)
{
	if (*routeptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*routeptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*routeptr = buffer;
	}
	else
	{
		_strcpy(*routeptr, buffer);
		free(buffer);
	}
}

/**
 * _getroute - input stream.
 * @routeptr:  buffer .
 * @n:  size of routeptr.
 * @stream: The stream .
 * Return: bytes read.
 */
ssize_t _getroute(char **routeptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_routeptr(routeptr, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
