#include "shell.h"


/**
 * obtain_builtin - Finds and returns the function
 * pointer for a given built-in command.
 * @command: the command string
 * Return: Function pointer to the corresponding built-in cmdd
 */

int (*obtain_builtin(char *command))(data_container *)
{
	builtin built_in[] = {
		{ "env", print_envn },
		{ "exit", close_shell },
		{ "setenv", cmp_envn },
		{ "unsetenv", del_envn },
		{ "cd", change_directory_command },
		{ "help", obtain_help },
		{ NULL, NULL }
	};
	int n;

	for (n = 0; built_in[n].alias; n++)
	{
		if (custom_strcmp(built_in[n].alias, command) == 0)
			break;
	}

	return (built_in[n].f);
}

