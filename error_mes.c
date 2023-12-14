#include "shell.h"


/**
 * obtain_error - To call the error according the builtin
 * @data: the structure of the data that contains arg
 * @val: the value of the error
 * Return: the error
 */
int obtain_error(data_container *data, int val)
{
	char *err;

	switch (val)
	{
	case -1:
		err = system_environment_error(data);
		break;
	case 126:
		err = route_126_error_alert(data);
		break;
	case 127:
		err = missing_file_error(data);
		break;
	case 2:
		if (custom_strcmp("exit", data->args[0]) == 0)
			err = shell_terminate_error(data);
		else if (custom_strcmp("cd", data->args[0]) == 0)
			err = fetch_error_custom(data);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, custom_strlen(err));
		free(err);
	}

	data->stat = val;
	return (val);
}

