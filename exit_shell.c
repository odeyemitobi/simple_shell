#include "shell.h"

/**
 * close_shell -  Closes the shell and sets the exit
 * status based on the provided argument
 * @data: Pointer to the data_container structure containing shell data.
 * Return: 0
 */
int close_shell(data_container *data)
{
	unsigned int status;
	int is_dig, len, b_num;

	if (data->args[1] != NULL)
	{
		status = custom_atoi(data->args[1]);
		is_dig = is_number(data->args[1]);
		len = custom_strlen(data->args[1]);
		b_num = status > (unsigned int)INT_MAX;
		if (!is_dig || len > 10 || b_num)
		{
			obtain_error(data, 2);
			data->stat = 2;
			return (1);
		}
		data->stat = (status % 256);
	}
	return (0);
}

