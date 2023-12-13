#include "shell.h"

/**
 * custom_rev_string - function that reverses a string
 * @str: input string
 * Return: nothing
 */
void custom_rev_string(char *str)
{
	int counter = 0, i, j;
	char *string, temp;

	while (counter >= 0)
	{
		if (str[counter] == '\0')
			break;
		counter++;
	}
	string = str;

	for (i = 0; i < (counter - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(string + j);
			*(string + j) = *(string + (j - 1));
			*(string + (j - 1)) = temp;
		}
	}
}

