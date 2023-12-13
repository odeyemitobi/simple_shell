#include "shell.h"

/**
 * append_sep_to_end - function to append separator
 * @list: pointer ot the linked list head
 * @separator: separator charcter (; | &).
 * Return: pointer to the updated list
 */

separator_list *append_sep_to_end(separator_list **list, char separator)
{
	separator_list *new_node, *temp;

	new_node = malloc(sizeof(separator_list));
	if (new_node == NULL)
		return (NULL);

	new_node->sep = separator;
	new_node->next = NULL;
	temp = *list;
	if (list == NULL)
		*list = new_node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}

	return (*list);
}

/**
 * deallocate_sep_list - function to deallocate memory used by sep_list
 * @list: pointer to the linked list head.
 */

void deallocate_sep_list(separator_list **list)
{
	separator_list *current;
	separator_list *tmp;

	if (list != NULL)
	{
		current = *list;
		while ((tmp = current) != NULL)
		{
			current = current->next;
			free(tmp);
		}
		*list = NULL;
	}
}

/**
 * append_line_to_end - function to adds command line
 * @list: head of linked list
 * @line: command line
 * Return: The head address
 */

c_line_list *append_line_to_end(c_line_list **list, char *line)
{
	c_line_list *new_node, *temp;

	new_node = malloc(sizeof(c_line_list));
	if (new_node == NULL)
		return (NULL);

	new_node->line = line;
	new_node->next = NULL;
	temp = *list;

	if (temp == NULL)
		*list = new_node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}

	return (*list);
}

/**
 * free_line_list - function to free line_list
 * @list: linked list
 * Return: void
 */
void free_line_list(c_line_list **list)
{
	c_line_list *temp;
	c_line_list *current;

	if (list != NULL)
	{
		current = *list;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*list = NULL;
	}
}

