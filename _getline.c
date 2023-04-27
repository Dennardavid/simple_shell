#include "simple_shell.h"

/**
 * copy_line - Copies a line from a buffer to a pointer
 * @line_ptr: Pointer to the line to be copied
 * @size: Pointer to the size of the line
 * @buffer: Buffer containing the line to be copied
 * @index: Index of the line in the buffer
 */
void copy_line(char **line_ptr, size_t *size, char *buffer, size_t index)
{
	size_t j = index;

	if (*line_ptr == NULL)
	{
		if (j > BUFFSIZE)
			*size = j;
		else
			*size = BUFFSIZE;
		*line_ptr = buffer;
	}
	else if (*size < j)
	{
		if (j > BUFFSIZE)
			*size = j;
		else
			*size = BUFFSIZE;
		*line_ptr = buffer;
	}
	else
	{
		_strcpy(*line_ptr, buffer);
		free(buffer);
	}
}

/**
 * read_line - Reads a line from a stream
 * @line_ptr: Pointer to the line to be read
 * @size: Pointer to the size of the line
 * @stream: Stream to read from
 * Return: bytes else -1
 */
ssize_t read_line(char **line_ptr, size_t *size, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t bytes;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFFSIZE)
			buffer = reallocate_memory(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	copy_line(line_ptr, size, buffer, input);
	bytes = input;
	if (i != 0)
		input = 0;
	return (bytes);
}
