#include "shell.h"

/**
 * is_current_dir - Checks if the character at index i in the path is ':'
 * @path: Pointer to a character array (string) representing the path.
 * @i: Index indicating the position in the path to check.
 * Return:  1 if the path character is ':', 0 otherwise
 */
int is_current_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
		*i += 1;

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * custom_which - Locates the executable path of a command.
 * @command: The name of the command to locate.
 * @environment_variable: environment variable containing the command's path.
 *
 * Return: location of the command(executable path).
 */

char *custom_which(char *command, char **environment_variable)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = obtain_envn("PATH", environment_variable);
	if (path)
	{
		ptr_path = custom_strdup(path);
		len_cmd = custom_strlen(command);
		token_path = custom_strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_current_dir(path, &i))
				if (stat(command, &st) == 0)
					return (command);
			len_dir = custom_strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			custom_strcpy(dir, token_path);
			custom_strcat(dir, "/");
			custom_strcat(dir, command);
			custom_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = custom_strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (stat(command, &st) == 0)
			return (command);
	return (NULL);
}

/**
 * custom_is_executable - To checks if is an executable
 * @data: The data representing the file format.
 * Return: 0 if the file is not an executable, a non-zero number if it is.
 */
int custom_is_executable(data_container *data)
{
	struct stat st;
	int i;
	char *insert;

	insert = data->args[0];
	for (i = 0; insert[i]; i++)
	{
		if (insert[i] == '.')
		{
			if (insert[i + 1] == '.')
				return (0);
			if (insert[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (insert[i] == '/' && i != 0)
		{
			if (insert[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(insert + i, &st) == 0)
	{
		return (i);
	}
	obtain_error(data, 127);
	return (-1);
}

/**
 * verify_error_command - checks if the user has permissions
 * to access the directory
 * @dir:  The destination directory to be checked for access permissions.
 * @data: Data structure containing relevant information for the operation.
 * Return: 1 if there is an error, 0 if not
 */
int verify_error_command(char *dir, data_container *data)
{
	if (dir == NULL)
	{
		obtain_error(data, 127);
		return (1);
	}

	if (custom_strcmp(data->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			obtain_error(data, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(data->args[0], X_OK) == -1)
		{
			obtain_error(data, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * command_execute - Executes command lines
 * @data: data that are relevant to the command execution.
 * Return: on success 1
 */
int command_execute(data_container *data)
{
	pid_t pd;
	pid_t wpd;
	int state, execute;
	char *dir;
	(void)wpd;

	execute = custom_is_executable(data);
	if (execute == -1)
		return (1);
	if (execute == 0)
	{
		dir = custom_which(data->args[0], data->envn);
		if (verify_error_command(dir, data) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (execute == 0)
			dir = custom_which(data->args[0], data->envn);
		else
			dir = data->args[0];
		execve(dir + execute, data->args, data->envn);
	}
	else if (pd < 0)
	{
		perror(data->argv[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	data->stat = state / 256;
	return (1);
}
