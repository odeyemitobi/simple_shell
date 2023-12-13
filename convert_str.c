#include "shell.h"

/**
 * count_digit - function to get the length of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */

int count_digit(int n)
{
	unsigned int i;
	int length = 1;

	if (n < 0)
	{
		length++;
		i = n * -1;
	}
	else
	{
		i = n;
	}
	while (i > 9)
	{
		length++;
		i = i / 10;
	}

	return (length);
}

/**
 * intToStr - Converts an integer to string.
 * @n: The integer to be converted
 * Return: A dynamically allocated string representing the integer.
 */
char *intToStr(int n)
{
	unsigned int i = n < 0 ? -n : n;
	int len = n < 0 ? 2 : 1;

	char *buff;
	unsigned int temp = i;

	for (; temp /= 10; len++)
		;

	buff = malloc(len + 1);
	if (buff == NULL)
		return (NULL);

	buff[len--] = '\0';
	if (n < 0)
		buff[0] = '-';

	do {
		buff[len--] = i % 10 + '0';
		i /= 10;
	} while (i > 0);

	return (buff);
}

/**
 * custom_atoi - converts a string to an integer.
 * @str: input string.
 * Return: integer.
 */

int custom_atoi(const char *str)
{
	unsigned int len = 0, size = 0, i = 0, n = 1, b = 1, a;

	while (*(str + len) != '\0')
	{
		if (size > 0 && (*(str + len) < '0' || *(str + len) > '9'))
			break;

		if (*(str + len) == '-')
			n *= -1;

		if ((*(str + len) >= '0') && (*(str + len) <= '9'))
		{
			if (size > 0)
				b *= 10;
			size++;
		}
		len++;
	}

	for (a = len - size; a < len; a++)
	{
		i = i + ((*(str + a) - 48) * b);
		b /= 10;
	}
	return (i * n);
}
