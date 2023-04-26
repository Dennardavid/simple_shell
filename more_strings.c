#include "simple_shell.h"

/**
 * _strlen - returns the length of a string
 * @str: the string to check
 *
 * Return: the length of the string
 */
int _strlen(const char *str)
{
	int length = 0;

	while (str[len] != '\0')
	{
		length++;
	}

	return (length);
}

/**
 * _isDigit - checks if a string contains only digits
 * @str: the string to check
 *
 * Return: 1 if the string contains only digits else 0
 */
int _isDigit(const char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

/**
 * reverse_string - reverses a string
 * @str: the string to reverse
 */
void reverse_string(char *str)
{
	int len = 0, i;
	char temp;

	while (str[len] != '\0')
	{
		len++;
	}

	for (i = 0; i < len / 2; i++)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
	}
}

/**
 * compare_chars - checks if a string contains only
 * characters from a set of delimiters
 * @str: the string to check
 * @delim: the set of delimiters
 *
 * Return: 1 if the string contains only characters
 * from the set of delimiters, 0 otherwise
 */
int compare_chars(char *str, const char *delim)
{
	unsigned int i, j;

	for (i = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				break;
			}
		}
		if (delim[j] == '\0')
		{
			return (0);
		}
	}
	return (1);
}

/**
 * _strtok - splits a string into tokens based on a set of delimiters
 * @str: the string to split
 * @delim: the set of delimiters
 *
 * Return: a pointer to the next token or NULL if there are no more tokens
 */
char *_strtok(char *str, const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, found_delim;

	if (str)
	{
		if (compare_chars(str, delim))
			return (NULL);
		splitted = str;
		i = _strlen(str);
		str_end = &str[i];
	}

	str_start = splitted;

	if (str_start == str_end)
		return (NULL);

	for (found_delim = 0; *splitted; splitted++)
	{
		if (splitted != str_start && *splitted && *(splitted - 1) == '\0')
			break;
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (found_delim == 0 && *splitted)
			found_delim = 1;
	}

	if (found_delim == 0)
		return (NULL);
	return (str_start);
}
