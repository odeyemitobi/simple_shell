#include "shell.h"

/**
 * obtain_help - obtains and displays the help msg for a
 * spcific builtin in command
 * @data: data of  the structure (args and input)
 *
 * Return: 0
*/

int obtain_help(data_container *data)
{

	if (data->args[1] == 0)
		assist_general_command();
	else if (custom_strcmp(data->args[1], "setenv") == 0)
		env_variable_support();
	else if (custom_strcmp(data->args[1], "env") == 0)
		support_env_tasks();
	else if (custom_strcmp(data->args[1], "unsetenv") == 0)
		support_unsetenv_command();
	else if (custom_strcmp(data->args[1], "help") == 0)
		env_assist();
	else if (custom_strcmp(data->args[1], "exit") == 0)
		print_exit_help();
	else if (custom_strcmp(data->args[1], "cd") == 0)
		env_assist_cd();
	else if (custom_strcmp(data->args[1], "alias") == 0)
		env_assist_alias();
	else
		write(STDERR_FILENO, data->args[0],
		      custom_strlen(data->args[0]));

	data->stat = 0;
	return (1);
}

