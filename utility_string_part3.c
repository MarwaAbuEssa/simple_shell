#include "main.h"

int delimator_len(char *str, char *delimator);
int delimator_count(char *str, char *delimator);
char **_strtok(char *route, char *delimator);

/**
 * delimator_len - the delimatoratoriter length.
 * @str: The string.
 * @delimator: The delimatoriter.
 * Return: indexes.
 */
int delimator_len(char *str, char *delimator)
{
	int index = 0, len = 0;

	while (*(str + index) && *(str + index) != *delimator)
	{
		len++;
		index++;
	}

	return (len);
}

/**
 * delimator_count - counts of delimatorited.
 * @str: The string .
 * @delimator: The delimatoriter character.
 * Return: num of words.
 */
int delimator_count(char *str, char *delimator)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delimator)
		{
			tokens++;
			index += delimator_len(str + index, delimator);
		}
	}

	return (tokens);
}

/**
 * _strtok - a string.
 * @route: The string.
 * @delimator: The delimatoriter.
 * Return: pointer.
 */
char **_strtok(char *route, char *delimator)
{
	char **ptr;
	int index = 0, tokens, t, letters, l;

	tokens = delimator_count(route, delimator);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (route[index] == *delimator)
			index++;

		letters = delimator_len(route + index, delimator);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = route[index];
			index++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
