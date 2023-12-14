#include "shell.h"


/**
 * assign_line - Assign values to the line
 * variable for assign_line
 * @line_buff: Buffer that stores the input string
 * @buff: string called to line
 * @a: size of the line
 * @b: size of the buffer
 */

void assign_line(char **line_buff, size_t *a, char *buff, size_t b)
{

	if (*line_buff == NULL)
	{
		if  (b > BUFFERSIZE)
			*a = b;
		else
			*a = BUFFERSIZE;
		*line_buff = buff;
	}
	else if (*a < b)
	{
		if (b > BUFFERSIZE)
			*a = b;
		else
			*a = BUFFERSIZE;
		*line_buff = buff;
	}
	else
	{
		custom_strcpy(*line_buff, buff);
		free(buff);
	}
}
/**
 * obtain_line - Read a string from the inputand stores it in the buffer
 * @line_buff: buffer that stores the input string
 * @i: size of buff(line_buff)
 * @str: input string to be read
 *
 * Return: The number of bytes to read.
 */
ssize_t obtain_line(char **line_buff, size_t *i, FILE *str)
{
	int j;
	static ssize_t insert;
	ssize_t value;
	char *buff;
	char a = 'z';

	if (insert == 0)
		fflush(str);
	else
		return (-1);
	insert = 0;

	buff = malloc(sizeof(char) * BUFFERSIZE);
	if (buff == 0)
		return (-1);
	while (a != '\n')
	{
		j = read(STDIN_FILENO, &a, 1);
		if (j == -1 || (j == 0 && insert == 0))
		{
			free(buff);
			return (-1);
		}
		if (j == 0 && insert != 0)
		{
			insert++;
			break;
		}
		if (insert >= BUFFERSIZE)
			buff = custom_realloc(buff, insert, insert + 1);
		buff[insert] = a;
		insert++;
	}
	buff[insert] = '\0';
	assign_line(line_buff, i, buff, insert);
	value = insert;
	if (j != 0)
		insert = 0;
	return (value);
}
