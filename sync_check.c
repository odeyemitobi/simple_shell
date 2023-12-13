#include "shell.h"

/**
 * char_dup - To count repetitions of a char
 * @insert: inserted string
 * @n: the index number
 * Return: the repetitions
 */

int char_dup(char *insert, int n)
{
	if (*(insert - 1) == *insert)
		return (char_dup(insert - 1, n + 1));

	return (n);
}

/**
 * err_sep_op - To finds syntax errors
 * @insert: inserted string
 * @n: index number
 * @final: last char to read
 * Return: index num of error. 0 when no errors
 */

int err_sep_op(char *insert, int n, char final)
{
	int len;

	len = 0;
	if (*insert == '\0')
		return (0);

	if (*insert == ' ' || *insert == '\t')
		return (err_sep_op(insert + 1, n + 1, final));

	if (*insert == ';')
		if (final == '|' || final == '&' || final == ';')
			return (n);

	if (*insert == '|')
	{
		if (final == ';' || final == '&')
			return (n);

		if (final == '|')
		{
			len = char_dup(insert, 0);
			if (len == 0 || len > 1)
				return (n);
		}
	}

	if (*insert == '&')
	{
		if (final == ';' || final == '|')
			return (n);

		if (final == '&')
		{
			len = char_dup(insert, 0);
			if (len == 0 || len > 1)
				return (n);
		}
	}

	return (err_sep_op(insert + 1, n + 1, *insert));
}

/**
 * initial_char - finds index of first char
 * @insert: inserted string
 * @n: index num
 * Return: -1 if there is error. 0 otherwise
 */

int initial_char(char *insert, int *n)
{

	for (*n = 0; insert[*n]; *n += 1)
	{
		if (insert[*n] == ' ' || insert[*n] == '\t')
			continue;

		if (insert[*n] == ';' || insert[*n] == '|' || insert[*n] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syn_err - To prints when syntax error is found
 * @sh_data: data
 * @insert: inserted string
 * @n: index num of the error
 * @bool: to control the msg error
 */

void print_syn_err(data_container *sh_data, char *insert, int n, int bool)
{
	char *msg_1, *msg_2, *msg_3, *err, *count;
	int len;

	if (insert[n] == ';')
	{
		if (bool == 0)
			msg_1 = (insert[n + 1] == ';' ? ";;" : ";");
		else
			msg_1 = (insert[n - 1] == ';' ? ";;" : ";");
	}

	if (insert[n] == '|')
		msg_1 = (insert[n + 1] == '|' ? "||" : "|");

	if (insert[n] == '&')
		msg_1 = (insert[n + 1] == '&' ? "&&" : "&");

	msg_2 = ": Syntax error: \"";
	msg_3 = "\" unexpected\n";
	count = intToStr(sh_data->count);
	len = custom_strlen(sh_data->argv[0]) + custom_strlen(count);
	len += custom_strlen(msg_1) + custom_strlen(msg_2) + custom_strlen(msg_3) + 2;

	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(count);
		return;
	}
	custom_strcpy(err, sh_data->argv[0]);
	custom_strcat(err, ": ");
	custom_strcat(err, count);
	custom_strcat(err, msg_2);
	custom_strcat(err, msg_1);
	custom_strcat(err, msg_3);
	custom_strcat(err, "\0");

	write(STDERR_FILENO, err, len);
	free(err);
	free(count);
}

/**
 * verify_syn_err - to find and print a syntax error
 * @sh_data: data
 * @insert: inserted string
 * Return: 1 if there is error. 0 otherwise
 */

int verify_syn_err(data_container *sh_data, char *insert)
{
	int start = 0;
	int ini_char = 0;
	int n = 0;

	ini_char = initial_char(insert, &start);
	if (ini_char == -1)
	{
		print_syn_err(sh_data, insert, start, 0);
		return (1);
	}

	n = err_sep_op(insert + start, 0, *(insert + start));
	if (n != 0)
	{
		print_syn_err(sh_data, insert, start + n, 1);
		return (1);
	}

	return (0);
}

