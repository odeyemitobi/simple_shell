#include "shell.h"

/**
 * free_datash - function that frees data structure
 *
 * @data: data structure
 */
void free_datash(data_container *data)
{
	unsigned int n;

	for (n = 0; data->envn[n]; n++)
	{
		free(data->envn[n]);
	}

	free(data->envn);
	free(data->pid);
}

/**
 * set_datash - function for Initialize data structure
 * @data: data
 * @av: argument vector
 * Return: no return
 */
void set_datash(data_container *data, char **av)
{
	unsigned int n;

	data->argv = av;
	data->insert = NULL;
	data->args = NULL;
	data->stat = 0;
	data->count = 1;

	for (n = 0; environ[n]; n++)
		;

	data->envn = malloc(sizeof(char *) * (n + 1));

	for (n = 0; environ[n]; n++)
	{
		data->envn[n] = custom_strdup(environ[n]);
	}

	data->envn[n] = NULL;
	data->pid = intToStr(getpid());
}

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success.
 */
int main(int argc, char **argv)
{
	data_container data;
	(void)argc;

	signal(SIGINT, obtain_signal);
	set_datash(&data, argv);
	looping_sh(&data);
	free_datash(&data);
	if (data.stat < 0)
		return (255);
	return (data.stat);
}
