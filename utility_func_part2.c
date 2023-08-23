#include "main.h"

void imp_route(char **route, ssize_t route_size);
ssize_t new_route_fun(char *route);
void check_route(char *route, ssize_t *new_len);

/**
 * imp_route - standard input.
 * @route:  pointer.
 * @route_size: length.
 * Description: '\0'.
 */
void imp_route(char **route, ssize_t route_size)
{
	char *old_route, *new_route;
	char previous, current, next;
	size_t i, j;
	ssize_t new_len;

	new_len = new_route_fun(*route);
	if (new_len == route_size - 1)
		return;
	new_route = malloc(new_len + 1);
	if (!new_route)
		return;
	j = 0;
	old_route = *route;
	for (i = 0; old_route[i]; i++)
	{
		current = old_route[i];
		next = old_route[i + 1];
		if (i != 0)
		{
			previous = old_route[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new_route[j++] = ' ';
					new_route[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new_route[j++] = ';';
					new_route[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_route[j++] = ' ';
				new_route[j++] = ';';
				if (next != ' ')
					new_route[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_route[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_route[j++] = '&';
					new_route[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_route[j++] = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_route[j++] = '|';
					new_route[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old_route[i - 1] != ' ')
				new_route[j++] = ' ';
			new_route[j++] = ';';
			if (next != ' ' && next != ';')
				new_route[j++] = ' ';
			continue;
		}
		new_route[j++] = old_route[i];
	}
	new_route[j] = '\0';

	free(*route);
	*route = new_route;
}

/**
 * new_route_fun - new length of a route.
 * @route: The route.
 * Return: new route.
 * Description: new length of a route..
 */

ssize_t new_route_fun(char *route)
{
	size_t i;
	ssize_t new_len = 0;
	char current, next;

	for (i = 0; route[i]; i++)
	{
		current = route[i];
		next = route[i + 1];
		if (current == '#')
		{
			if (i == 0 || route[i - 1] == ' ')
			{
				route[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && route[i - 1] != ' ' && route[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (route[i - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (route[i - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				check_route(&route[i], &new_len);
		}
		else if (current == ';')
		{
			if (i != 0 && route[i - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
/**
 * check_route - Checks a route.
 * @route: pointer.
 * @new_len: Pointer to new_len.
 */
void check_route(char *route, ssize_t *new_len)
{
	char previous, current, next;

	previous = *(route - 1);
	current = *route;
	next = *(route + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
	}
}
