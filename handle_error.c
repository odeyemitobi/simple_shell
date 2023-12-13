#include "shell.h"

/**
 * strcat_custom - Concatenates a message with custom behavior.
 *
 * @data: data container
 * @message: message to be shown
 * @err: Message going out
 * @ver: Lines to count
 *
 * Return: error message
 */
char *strcat_custom(data_container *data, char *message, char *err, char *ver)
{
	char *error_flag;

	custom_strcpy(err, data->argv[0]);
	custom_strcat(err, ": ");
	custom_strcat(err, ver);
	custom_strcat(err, ": ");
	custom_strcat(err, data->args[0]);
	custom_strcat(err, message);

	if (data->args[1][0] == '-')
	{
		error_flag = malloc(3);
		error_flag[0] = '-';
		error_flag[1] = data->args[1][1];
		error_flag[2] = '\0';
		custom_strcat(err, error_flag);
		free(error_flag);
	}
	else
		custom_strcat(err, data->args[1]);

	custom_strcat(err, "\n");
	custom_strcat(err, "\0");
	return (err);
}

/**
 * fetch_error_custom - error message
 * @data: relevant data or file.
 * Return: Inputs that are messages.
 */
char *fetch_error_custom(data_container *data)
{
	int len, id;
	char *err, *ver, *message;

	ver = intToStr(data->count);
	if (data->args[1][0] == '-')
	{
		message = ": Illegal option ";
		id = 2;
	}
	else
	{
		message = ": can't cd to ";
		id = custom_strlen(data->args[1]);
	}

	len = custom_strlen(data->argv[0]) + custom_strlen(data->args[0]);
	len += custom_strlen(ver) + custom_strlen(message) + id + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(ver);
		return (NULL);
	}

	err = strcat_custom(data, message, err, ver);
	free(ver);

	return (err);
}

/**
 * missing_file_error - Error msg for commands missing.
 * @data: Important file
 * Return: Messages that show error
 */
char *missing_file_error(data_container *data)
{
	int len;
	char *err, *ver;

	ver = intToStr(data->count);
	len = custom_strlen(data->argv[0]) + custom_strlen(ver);
	len += custom_strlen(data->args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(ver);
		return (NULL);
	}
	custom_strcpy(err, data->argv[0]);
	custom_strcat(err, ": ");
	custom_strcat(err, ver);
	custom_strcat(err, ": ");
	custom_strcat(err, data->args[0]);
	custom_strcat(err, ": not found\n");
	custom_strcat(err, "\0");
	free(ver);
	return (err);
}

/**
 * shell_terminate_error- Error message for exit in get_exit
 * @data: file that are relevant
 * Return: Error message
 */
char *shell_terminate_error(data_container *data)
{
	int len;
	char *err;
	char *ver;

	ver = intToStr(data->count);
	len = custom_strlen(data->argv[0]) + custom_strlen(ver);
	len += custom_strlen(data->args[0]) + custom_strlen(data->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(ver);
		return (NULL);
	}
	custom_strcpy(err, data->argv[0]);
	custom_strcat(err, ": ");
	custom_strcat(err, ver);
	custom_strcat(err, ": ");
	custom_strcat(err, data->args[0]);
	custom_strcat(err, ": Illegal number: ");
	custom_strcat(err, data->args[1]);
	custom_strcat(err, "\n\0");
	free(ver);

	return (err);
}

