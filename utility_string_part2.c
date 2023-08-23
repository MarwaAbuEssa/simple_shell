#include "main.h"

char *_strchr(char *str, char charact);
int _strspn(char *str, char *prefix);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);

/**
 * _strchr - character.
 * @str: string.
 * @charact: The character.
 * Return: found or NULL.
 */
char *_strchr(char *str, char charact)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == charact)
			return (str + i);
	}

	return (NULL);
}

/**
 * _strspn - prefix.
 * @str: The string to be searched.
 * @prefix: The prefix.
 * Return: num of bytes.
 */
int _strspn(char *str, char *prefix)
{
	int bytes = 0;
	int i;

	while (*str)
	{
		for (i = 0; prefix[i]; i++)
		{
			if (*str == prefix[i])
			{
				bytes++;
				break;
			}
		}
		str++;
	}
	return (bytes);
}

/**
 * _strcmp - Compares two strings.
 * @str1: first string.
 * @str2: second string.
 * Return: positive or 0 or negative
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/**
 * _strncmp - Compare two strings with n.
 * @str1: first string.
 * @str2: second string.
 * @n: n bytes.
 * Return: 0 or less.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; str1[i] && str2[i] && i < n; i++)
	{
		if (str1[i] > str2[i])
			return (str1[i] - str2[i]);
		else if (str1[i] < str2[i])
			return (str1[i] - str2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
