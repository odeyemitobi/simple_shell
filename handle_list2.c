#include "shell.h"

/**
 * append_to_rva - Add a new r_var at the end
 * of a linked list
 * @list: pointer to the linked list.
 * @lvar: variable's length.
 * @value: variable's value.
 * @lval: length of the value.
 * Return: poinetr to the updates head of the linked list.
 */

r_var *append_to_rva(r_var **list, int lvar, char *value, int lval)
{
	r_var *new_node, *temp;

	new_node = malloc(sizeof(r_var));
	if (new_node == NULL)
		return (NULL);

	new_node->len_var = lvar;
	new_node->len_value = lval;
	new_node->value = value;

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
 * deallocate_rvar_list - releases the memory associated
 * with an r_var list
 * @list: pointer to the head of the linked list.
 * Return: void
 */

void deallocate_rvar_list(r_var **list)
{
	r_var *temp;
	r_var *current;

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

