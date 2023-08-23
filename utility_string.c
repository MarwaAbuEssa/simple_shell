#include "main.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - string length.
 * @str: A pointer to the characters string.
 * Return: string length.
 */
int _strlen(const char *str)
{
	int length = 0;

	if (!str)
		return (length);
	for (length = 0; str[length]; length++)
		;
	return (length);
}

/**
 * _strcpy - string copy.
 * @dest: destination.
 * @src: src.
 * Return: destination.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - concantenation.
 * @dest: destination.
 * @src: src.
 * Return: destination.
 */
char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp = src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - Concantenation with n.
 * @dest: destination.
 * @src: src.
 * @n: n bytes.
 * Return: destination.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}
