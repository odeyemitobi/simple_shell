#include "shell.h"

/**
 * execute_line - function to finds builtins and commands
 *
 * @data: data relevant (args)
 * Return: 1 on success.
 */
int execute_line(data_container *data)
{
	int (*built_in)(data_container *datash);

	if (data->args[0] == NULL)
		return (1);

	built_in = obtain_builtin(data->args[0]);

	if (built_in != NULL)
		return (built_in(data));

	return (command_execute(data));
}

