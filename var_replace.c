#include "shell.h"

/**
 * verify_envn - to verift if the ariable is an envnironment variable
 * @heads: the linked list
 * @insert: The input string conatining comments
 * @data: structure of data
 */
void verify_envn(r_var **heads, char *insert, data_container *data)
{
	int rows, col, n, value;
	char **envn;

	envn = data->envn;
	for (rows = 0; envn[rows]; rows++)
	{
		for (n = 1, col = 0; envn[rows][col]; col++)
		{
			if (envn[rows][col] == '=')
			{
				value = custom_strlen(envn[rows] + col + 1);
				append_to_rva(heads, n, envn[rows] + col + 1, value);
				return;
			}

			if (insert[n] == envn[rows][col])
				n++;
			else
				break;
		}
	}

	for (n = 0; insert[n]; n++)
	{
		if (insert[n] == ' ' || insert[n] == '\t' ||
			insert[n] == ';' || insert[n] == '\n')
			break;
	}

	append_to_rva(heads, n, NULL, 0);
}

/**
 * verify_var - to verify if the typed var is $$ or $?
 * @heads: The linked list
 * @insert: insert string containing commdnrts
 * @stat: last status of the Shell
 * @data: The format of data
 * Return: 1 if the variable is valid, 0 otherwise.
 */
int verify_var(r_var **heads, char *insert, char *stat, data_container *data)
{
	int n, list, lpid;

	list = custom_strlen(stat);
	lpid = custom_strlen(data->pid);

	for (n = 0; insert[n]; n++)
	{
		if (insert[n] == '$')
		{
			if (insert[n + 1] == '?')
				append_to_rva(heads, 2, stat, list), n++;
			else if (insert[n + 1] == '$')
				append_to_rva(heads, 2, data->pid, lpid), n++;
			else if (insert[n + 1] == '\n')
				append_to_rva(heads, 0, NULL, 0);
			else if (insert[n + 1] == '\0')
				append_to_rva(heads, 0, NULL, 0);
			else if (insert[n + 1] == ' ')
				append_to_rva(heads, 0, NULL, 0);
			else if (insert[n + 1] == '\t')
				append_to_rva(heads, 0, NULL, 0);
			else if (insert[n + 1] == ';')
				append_to_rva(heads, 0, NULL, 0);
			else
				verify_envn(heads, insert + n, data);
		}
	}

	return (n);
}

/**
 * rep_insert - function that replaces string to variables
 * @list: head of linked list
 * @insert: insert string
 * @new_insert: new inserted string to replace
 * @n_len: the new length
 * Return: replaced insert string
 */
char *rep_insert(r_var **list, char *insert, char *new_insert, int n_len)
{
	r_var *index;
	int a, b, n;

	index = *list;
	for (b = a = 0; a < n_len; a++)
	{
		if (insert[b] == '$')
		{
			if (!(index->len_var) && !(index->len_value))
			{
				new_insert[a] = insert[b];
				b++;
			}
			else if (index->len_var && !(index->len_value))
			{
				for (n = 0; n < index->len_var; n++)
					b++;
				a--;
			}
			else
			{
				for (n = 0; n < index->len_value; n++)
				{
					new_insert[a] = index->value[n];
					a++;
				}
				b += (index->len_var);
				a--;
			}
			index = index->next;
		}
		else
		{
			new_insert[a] = insert[b];
			b++;
		}
	}

	return (new_insert);
}

/**
 * replace_var - To call the functions to replace the string into variable
 * @insert: the insert string
 * @data: structure of data
 * Return: replace insert string
 */
char *replace_var(char *insert, data_container *data)
{
	r_var *list, *index;
	char *stat, *new_insert;
	int o_len, n_len;

	stat = intToStr(data->stat);
	list = NULL;
	o_len = verify_var(&list, insert, stat, data);

	if (list == NULL)
	{
		free(stat);
		return (insert);
	}

	index = list;
	n_len = 0;

	while (index != NULL)
	{
		n_len += (index->len_value - index->len_var);
		index = index->next;
	}

	n_len += o_len;
	new_insert = malloc(sizeof(char) * (n_len + 1));
	new_insert[n_len] = '\0';
	new_insert = rep_insert(&list, insert, new_insert, n_len);
	free(insert);
	free(stat);
	deallocate_rvar_list(&list);

	return (new_insert);
}
