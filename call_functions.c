#include "shell.h"

/**
 *cd_dot_get - Changes the current working directory to the parent directory.
 *
 * @data: Pointer to data relevant to the operation
 * (e.g., environment variable).
 *
 * Return: does not return any value
 */
void cd_dot_get(data_container *data)
{
	char current_path[PATH_MAX];
	char *target_dir, *copy_current_path, *tokenized_path;

	getcwd(current_path, sizeof(current_path));
	copy_current_path = custom_strdup(current_path);
	put_envn("OLDPWD", copy_current_path, data);
	target_dir = data->args[1];
	if (custom_strcmp(".", target_dir) == 0)
	{
		put_envn("PWD", copy_current_path, data);
		free(copy_current_path);
		return;
	}
	if (custom_strcmp("/", copy_current_path) == 0)
	{
		free(copy_current_path);
		return;
	}
	tokenized_path = copy_current_path;
	custom_rev_string(tokenized_path);
	tokenized_path = custom_strtok(tokenized_path, "/");
	if (tokenized_path != NULL)
	{
		tokenized_path = custom_strtok(NULL, "\0");

		if (tokenized_path != NULL)
			custom_rev_string(tokenized_path);
	}
	if (tokenized_path != NULL)
	{
		chdir(tokenized_path);
		put_envn("PWD", tokenized_path, data);
	}
	else
	{
		chdir("/");
		put_envn("PWD", "/", data);
	}
	data->stat = 0;
	free(copy_current_path);
}

/**
 * cd_to_get - Changes the current working directory
 * to a user-specified directory
 *
 * @data: Pointer to data relevant to the operation (e.g., directories).
 * Return: This function does not return any value.
 */
void cd_to_get(data_container *data)
{
	char current_path[PATH_MAX];
	char *target_dir, *copy_current_path, *copy_target_dir;

	getcwd(current_path, sizeof(current_path));

	target_dir = data->args[1];
	if (chdir(target_dir) == -1)
	{
		obtain_error(data, 2);
		return;
	}

	copy_current_path = custom_strdup(current_path);
	put_envn("OLDPWD", copy_current_path, data);

	copy_target_dir = custom_strdup(target_dir);
	put_envn("PWD", copy_target_dir, data);

	free(copy_current_path);
	free(copy_target_dir);

	data->stat = 0;
	chdir(target_dir);
}

/**
 * cd_previous_get -  Changes the current working
 * directory to the previous directory.
 *
 * @data:  Pointer to data relevant to the operation
 * (e.g., environment variables).
 * Return: void
 */
void cd_previous_get(data_container *data)
{
	char current_path[PATH_MAX];
	char *previous_pwd, *old_pwd, *copy_current_path, *copy_old_pwd;

	getcwd(current_path, sizeof(current_path));
	copy_current_path = custom_strdup(current_path);

	old_pwd = obtain_envn("OLDPWD", data->envn);

	if (old_pwd == NULL)
		copy_old_pwd = copy_current_path;
	else
		copy_old_pwd = custom_strdup(old_pwd);

	put_envn("OLDPWD", copy_current_path, data);

	if (chdir(copy_old_pwd) == -1)
		put_envn("PWD", copy_current_path, data);
	else
		put_envn("PWD", copy_old_pwd, data);

	previous_pwd = obtain_envn("PWD", data->envn);

	write(STDOUT_FILENO, previous_pwd, custom_strlen(previous_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(copy_current_path);
	if (old_pwd)
		free(copy_old_pwd);

	data->stat = 0;
	chdir(previous_pwd);
}

/**
 * cd_to_home_get - Changes the current working directory
 * to the user's home directory.
 *
 * @data:  Pointer to data relevant to the operation
 * (e.g., environment variables).
 * Return: void
 */
void cd_to_home_get(data_container *data)
{
	char *previous_pwd, *home_directory;
	char current_path[PATH_MAX];

	getcwd(current_path, sizeof(current_path));
	previous_pwd = custom_strdup(current_path);

	home_directory = obtain_envn("HOME", data->envn);

	if (home_directory == NULL)
	{
		put_envn("OLDPWD", previous_pwd, data);
		free(previous_pwd);
		return;
	}
	if (chdir(home_directory) == -1)
	{
		obtain_error(data, 2);
		free(previous_pwd);
		return;
	}

	put_envn("OLDPWD", previous_pwd, data);
	put_envn("PWD", home_directory, data);
	free(previous_pwd);
	data->stat = 0;
}

