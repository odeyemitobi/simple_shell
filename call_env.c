#include "shell.h"

/**
 * cmp_envn_alias - Compares envn variable names with the name passed.
 * @n_env: the name of the environment variable
 * @alias: the name passed for comparison
 * Return: 0 if they are not equal. Another value if they are.
 */
int cmp_envn_alias(const char *n_env, const char *alias)
{
	int n;

	for (n = 0; n_env[n] != '='; n++)
	{
		if (n_env[n] != alias[n])
		{
			return (0);
		}
	}

	return (n + 1);
}

/**
 * obtain_envn - function to get an envn variable
 * @alias: the name of the environment variable
 * @envn: envn variable
 * Return: value of the envn var if found, if not returns NULL.
 */
char *obtain_envn(const char *alias, char **envn)
{
	char *envn_ptr;
	int n, m;

	envn_ptr = NULL;
	m = 0;

	for (n = 0; envn[n]; n++)
	{
		m = cmp_envn_alias(envn[n], alias);
		if (m)
		{
			envn_ptr = envn[n];
			break;
		}
	}

	return (envn_ptr + m);
}

/**
 * print_envn - prints the environment variables
 * @sh_data: data format
 * Return: 1 on success
 */
int print_envn(data_container *sh_data)
{
	int a, b;

	for (a = 0; sh_data->envn[a]; a++)
	{

		for (b = 0; sh_data->envn[a][b]; b++)
			;

		write(STDOUT_FILENO, sh_data->envn[a], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	sh_data->stat = 0;

	return (1);
}

