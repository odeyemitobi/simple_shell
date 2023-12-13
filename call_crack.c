#include "shell.h"

/**
 * replace_char - Replace non-printable characters with '|' or '&'.
 * @insert: The string in which replacements are made.
 * @bool: A flag indicating the type of replacement ('|' or '&').
 * Return: The updated string after replacement.
 */

char *replace_char(char *insert, int bool)
{
	int n;

	if (bool == 0)
	{
		for (n = 0; insert[n]; n++)
		{
			if (insert[n] == '|')
			{
				if (insert[n + 1] != '|')
					insert[n] = 16;
				else
					n++;
			}

			if (insert[n] == '&')
			{
				if (insert[n + 1] != '&')
					insert[n] = 12;
				else
					n++;
			}
		}
	}
	else
	{
		for (n = 0; insert[n]; n++)
		{
			insert[n] = (insert[n] == 16 ? '|' : insert[n]);
			insert[n] = (insert[n] == 12 ? '&' : insert[n]);
		}
	}
	return (insert);
}

/**
 * add_sep - Insert and categorize separators or command lines.
 * @sep_head: head of the  separator list
 * @line_head: The head of the command lines list.
 * @insert: string to be inserted, which may contain sep or command lines.
 */
void add_sep(separator_list **sep_head, c_line_list **line_head, char *insert)
{
	int n;
	char *c_line;

	insert = replace_char(insert, 0);

	for (n = 0; insert[n]; n++)
	{
		if (insert[n] == ';')
			append_sep_to_end(sep_head, insert[n]);

		if (insert[n] == '|' || insert[n] == '&')
		{
			append_sep_to_end(sep_head, insert[n]);
			n++;
		}
	}

	c_line = custom_strtok(insert, ";|&");
	do {
		c_line = replace_char(c_line, 1);
		append_line_to_end(line_head, c_line);
		c_line = custom_strtok(NULL, ";|&");
	} while (c_line != NULL);
}

/**
 * next_line - Move to the next stored command line or separator entry.
 * @sep_list: The list of separator.
 * @line_list: The list of command line.
 * @data: data format
 */
void next_line(separator_list **sep_list,
			   c_line_list **line_list, data_container *data)
{
	int s_loop;
	separator_list *sep_ls;
	c_line_list *line_ls;

	s_loop = 1;
	sep_ls = *sep_list;
	line_ls = *line_list;

	while (sep_ls != NULL && s_loop)
	{
		if (data->stat == 0)
		{
			if (sep_ls->sep == '&' || sep_ls->sep == ';')
				s_loop = 0;
			if (sep_ls->sep == '|')
				line_ls = line_ls->next, sep_ls = sep_ls->next;
		}
		else
		{
			if (sep_ls->sep == '|' || sep_ls->sep == ';')
				s_loop = 0;
			if (sep_ls->sep == '&')
				line_ls = line_ls->next, sep_ls = sep_ls->next;
		}
		if (sep_ls != NULL && !s_loop)
			sep_ls = sep_ls->next;
	}

	*sep_list = sep_ls;
	*line_list = line_ls;
}

/**
 * crack_cmd - Parse and execute commands separated by ;, |, and &.
 * @data: shell's data structure
 * @insert: An optional inserted string
 * Return: 0 to quit, 1 to contiune processing
 */
int crack_cmd(data_container *data, char *insert)
{

	separator_list *sep_head, *sep_list;
	c_line_list *line_head, *line_list;
	int sl_loop;

	sep_head = NULL;
	line_head = NULL;

	add_sep(&sep_head, &line_head, insert);

	sep_list = sep_head;
	line_list = line_head;

	while (line_list != NULL)
	{
		data->insert = line_list->line;
		data->args = crack_line(data->insert);
		sl_loop = execute_line(data);
		free(data->args);

		if (sl_loop == 0)
			break;

		next_line(&sep_list, &line_list, data);

		if (line_list != NULL)
			line_list = line_list->next;
	}

	deallocate_sep_list(&sep_head);
	free_line_list(&line_head);

	if (sl_loop == 0)
		return (0);
	return (1);
}

/**
 * crack_line - Tokenize the input string into individual parts.
 * @insert: insert string to be tokenized
 * Return: An array of tokens extracted from the input string.
 */
char **crack_line(char *insert)
{
	size_t bt_size;
	size_t n;
	char **toks;
	char *tok;

	bt_size = TOKEN_BUFFERSIZE;
	toks = malloc(sizeof(char *) * (bt_size));
	if (toks == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	tok = custom_strtok(insert, TOKEN_SEP);
	toks[0] = tok;

	for (n = 1; tok != NULL; n++)
	{
		if (n == bt_size)
		{
			bt_size += TOKEN_BUFFERSIZE;
			toks = resizedp(toks, n, sizeof(char *) * bt_size);
			if (toks == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		tok = custom_strtok(NULL, TOKEN_SEP);
		toks[n] = tok;
	}

	return (toks);
}
