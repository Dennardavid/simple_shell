#include "simple_shell.h"

/**
 * _strcat - concatenates two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: str1
 */
char *_strcat(char *str1, const char *str2)
{
	int str1_len;
	int str2_index;

	for (str1_len = 0; str1[str1_len] != '\0'; str1_len++)
		;

	for (str2_index = 0; str2[str2_index] != '\0'; str2_index++)
	{
		str1[str1_len] = str2[str2_index];
		str1_len++;
	}

	str1[str1_len] = '\0';
	return (str1);
}

/**
 * _strcpy - copies the string pointed to by src to dest
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to the destination string dest
 */
char *_strcpy(char *dest, char *src)
{
	size_t index;

	for (index = 0; src[index] != '\0'; index++)
	{
		dest[index] = src[index];
	}
	dest[index] = '\0';

	return (dest);
}

/**
 * _strcmp - compares two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: 0 if str1 and str2 are equal, 1 if str1 > str2, -1 if str1 < str2
 */
int _strcmp(const char *str1, const char *str2)
{
	int index;

	for (index = 0; str1[index] == str2[index] && str1[index]; index++)
		;

	if (str1[index] > str2[index])
	{
		return (1);
	}
	if (str1[index] < str2[index])
	{
		return (-1);
	}
	return (0);
}

/**
 * _strchr - locates a character in a string
 * @str: string to search
 * @c: character to search for
 *
 * Return: pointer to the first occurrence of the character c in the
 * string str else NULL
 */
char *_strchr(char *str, char c)
{
	unsigned int index = 0;

	for (; *(str + index) != '\0'; index++)
	{
		if (*(str + index) == c)
		{
			return (str + index);
		}
	}
	if (*(str + index) == c)
	{
		return (str + index);
	}

	return ('\0');
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string else NULL
 */
char *_strdup(const char *str)
{
	char *new_str;
	size_t str_len;

	str_len = _strlen(str);
	new_str = malloc(sizeof(char) * (str_len + 1));
	if (new_str == NULL)
	{
		return (NULL);
	}
	copy_memory(new_str, str, str_len + 1);

	return (new_str);
}
