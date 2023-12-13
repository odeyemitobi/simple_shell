#include "shell.h"

/**
 * custom_strdup - Allocates memory for a new string and copies the content..
 * @str: The input string to be dupicated
 * Return: a pointer to the duplicated string on success
 */

char *custom_strdup(const char *str)
{
	char *new_node;
	size_t length;

	length = custom_strlen(str);
	new_node = malloc(sizeof(char) * (length + 1));
	if (new_node == NULL)
		return (NULL);
	custom_memcpy(new_node, str, length + 1);
	return (new_node);
}

/**
 * custom_strlen - computes the length of a string.
 * @str: Input string.
 * Return: Always 0.
 */

int custom_strlen(const char *str)
{
	int length;

	for (length = 0; str[length] != '\0'; length++)
	{
	}
	return (length);
}

/**
 * char_cmp - compare chars of strings
 * @s: input string.
 * @delimiter: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */

int char_cmp(char s[], const char *delimiter)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; s[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (s[i] == delimiter[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);

	return (0);
}

/**
 * custom_strtok - Splits a string by a delimiter.
 * @input_str: input string.
 * @delimiter: delimiter string.
 *
 * Return: Pointer to the next token or NULL if no more tokens
 */

char *custom_strtok(char input_str[], const char *delimiter)
{
	static char *current_token, *str_end;
	char *token_start;
	unsigned int i, bool;

	if (input_str != NULL)
	{
		if (char_cmp(input_str, delimiter))
			return (NULL);
		current_token = input_str;
		i = custom_strlen(input_str);
		str_end = &input_str[i];
	}
	token_start = current_token;
	if (token_start == str_end)
		return (NULL);

	for (bool = 0; *current_token; current_token++)
	{
		if (current_token != token_start)
			if (*current_token && *(current_token - 1) == '\0')
				break;

		for (i = 0; delimiter[i]; i++)
		{
			if (*current_token == delimiter[i])
			{
				*current_token = '\0';
				if (current_token == token_start)
					token_start++;
				break;
			}
		}
		if (bool == 0 && *current_token)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (token_start);
}

/**
 * is_number - Checks if string passed is a number
 *
 * @str: input string
 * Return: 1 if string is a number. otherwise 0.
 */
int is_number(const char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
	}
	return (1);
}

