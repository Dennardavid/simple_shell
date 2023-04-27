#include "simple_shell.h"

/**
 * get_num_len - gets the length of a number
 * @num: number to get length of
 *
 * Return: length of number
 */
int get_num_len(int num)
{
	unsigned int abs_num;
	int length = 1;

	if (num < 0)
	{
		length++;
		abs_num = num * -1;
	}
	else
	{
		abs_num = num;
	}

	while (abs_num > 9)
	{
		length++;
		abs_num /= 10;
	}

	return (length);
}

/**
 * convert_itoa - converts an integer to a string
 * @num: integer to convert
 *
 * Return: pointer to string representation of integer
 */
char *convert_itoa(int num)
{
	unsigned int abs_num;
	int length = get_num_len(num);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	buffer[length] = '\0';

	if (num < 0)
	{
		abs_num = num * -1;
		buffer[0] = '-';
	}
	else
	{
		abs_num = num;
	}

	length--;
	do {
		buffer[length] = (abs_num % 10) + '0';
		abs_num /= 10;
		length--;
	} while (abs_num > 0);

	return (buffer);
}

/**
 * convert_atoi - converts a string to an integer
 * @str: string to convert
 *
 * Return: integer representation of string
 */
int convert_atoi(char *str)
{
	unsigned int count = 0, size = 0, result = 0, sign = 1, mult = 1, i;

	while (*(str + count) != '\0')
	{
		if (size > 0 && (*(str + count) < '0' || *(str + count) > '9'))
			break;

		if (*(str + count) == '-')
			sign *= -1;

		if ((*(str + count) >= '0') && (*(str + count) <= '9'))
		{
			if (size > 0)
				mult *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		result = result + ((*(str + i) - 48) * mult);
		mult /= 10;
	}

	return (result * sign);
}
