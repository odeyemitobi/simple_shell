#include "shell.h"

/**
 * change_directory_command - changes directory
 * @data: data format
 * Return: on success 1
 */
int change_directory_command(data_container *data)
{
	char *directory;
	int is_home, is_home2, is_double_dash;

	directory = data->args[1];

	if (directory != NULL)
	{
		is_home = custom_strcmp("$HOME", directory);
		is_home2 = custom_strcmp("~", directory);
		is_double_dash = custom_strcmp("--", directory);
	}

	if (directory == NULL || !is_home || !is_home2 || !is_double_dash)
	{
		cd_to_home_get(data);
		return (1);
	}

	if (custom_strcmp("-", directory) == 0)
	{
		cd_previous_get(data);
		return (1);
	}

	if (custom_strcmp(".", directory) == 0 || custom_strcmp("..", directory) == 0)
	{
		cd_dot_get(data);
		return (1);
	}

	cd_to_get(data);
	return (1);
}

