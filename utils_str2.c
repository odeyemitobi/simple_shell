#include "shell.h"

/**
 * custom_strcat - function for append 2 strings
 * @custom_dest: pointer the destination of the copied string
 * @source: const char pointer of string's source
 * Return: dest
 */
char *custom_strcat(char *custom_dest, const char *source)
{
	int a, b;

	for (a = 0; custom_dest[a] != '\0'; a++)
		;

	for (b = 0; source[b] != '\0'; b++)
	{
		custom_dest[a] = source[b];
		a++;
	}

	custom_dest[a] = '\0';
	return (custom_dest);
}

/**
 * *custom_strcpy - Copy the string pointed to by src
 * @custom_dest: Type char pointer to the dest of the copied str
 * @source: Type char pointer to the source of str
 * Return: dest
 */

char *custom_strcpy(char *custom_dest, char *source)
{

	size_t a;

	for (a = 0; source[a] != '\0'; a++)
	{
		custom_dest[a] = source[a];
	}
	custom_dest[a] = '\0';
	return (custom_dest);
}
/**
 * custom_strcmp - Function that compares two strings
 * @str1: The first string to be compared
 * @str2: The second to be compared
 * Return: 0 if the strings are equal, a positive value if str1 is greater,
 */

int custom_strcmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] == str2[i] && str1[i]; i++)
		;

	if (str1[i] > str2[i])
		return (1);
	if (str1[i] < str2[i])
		return (-1);
	return (0);
}
/**
 * custom_strchr - locates the first occurence
 * of a character in a string
 * @str: string to be searched
 * @c: character to be located
 * Return: the pointer to the first occurrence of the character
 * or NULL if not found.
 */

char *custom_strchr(char *str, char c)
{
	unsigned int i = 0;

	for (; *(str + i) != '\0'; i++)
		if (*(str + i) == c)
			return (str + i);
	if (*(str + i) == c)
		return (str + i);
	return ('\0');
}

/**
 * custom_strspn - Computes the length of a prefix substring
 * consiting of received bytes.
 * @str: The initial segment to be checked.
 * @receive: The string conatining accepted bytes.
 *
 * Return: the number of accepted bytes
 */

int custom_strspn(char *str, char *receive)
{
	int i, j, bool;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(receive + j) != '\0'; j++)
		{
			if (*(str + i) == *(receive + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}

