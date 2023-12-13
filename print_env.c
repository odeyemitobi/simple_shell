#include "shell.h"

/**
 * cpy_data - copies the information to be create a new environment
 * @alias: name of the alias
 * @val: value associated with the alias
 * Return: The new alias created with the provided name and value.
 */
char *cpy_data(char *alias, char *val)
{
	char *n;
	int len_alias, len_val, length;

	len_alias = custom_strlen(alias);
	len_val = custom_strlen(val);
	length = len_alias + len_val + 2;
	n = malloc(sizeof(char) * (length));
	custom_strcpy(n, alias);
	custom_strcat(n, "=");
	custom_strcat(n, val);
	custom_strcat(n, "\0");

	return (n);
}

/**
 * put_envn - to set the envn variable
 * @alias: envn variable's name
 * @val: environment variable value
 * @sh_data: data structure containing relevant information
 */
void put_envn(char *alias, char *val, data_container *sh_data)
{
	int n;
	char *envn_var, *envn_alias;

	for (n = 0; sh_data->envn[n]; n++)
	{
		envn_var = custom_strdup(sh_data->envn[n]);
		envn_alias = custom_strtok(envn_var, "=");
		if (custom_strcmp(envn_alias, alias) == 0)
		{
			free(sh_data->envn[n]);
			sh_data->envn[n] = cpy_data(envn_alias, val);
			free(envn_var);
			return;
		}
		free(envn_var);
	}

	sh_data->envn = resizedp(sh_data->envn, n, sizeof(char *) * (n + 2));
	sh_data->envn[n] = cpy_data(alias, val);
	sh_data->envn[n + 1] = NULL;
}

/**
 * cmp_envn - compares envn var name with the name passed.
 * @sh_data: data structure comtaining env name
 * and env value
 * Return: 1 on success
 */
int cmp_envn(data_container *sh_data)
{

	if (sh_data->args[1] == NULL || sh_data->args[2] == NULL)
	{
		obtain_error(sh_data, -1);
		return (1);
	}

	put_envn(sh_data->args[1], sh_data->args[2], sh_data);

	return (1);
}

/**
 * del_envn - Deletes a environment variable.
 * del_envn - to deletes a environment variable
 * @sh_data: data relevant (env name)
 * Return: on success 1
 */
int del_envn(data_container *sh_data)
{
	char **realloc_envn;
	char *envn_var, *envn_alias;
	int a, b, n;

	if (sh_data->args[1] == NULL)
	{
		obtain_error(sh_data, -1);
		return (1);
	}
	n = -1;
	for (a = 0; sh_data->envn[a]; a++)
	{
		envn_var = custom_strdup(sh_data->envn[a]);
		envn_alias = custom_strtok(envn_var, "=");
		if (custom_strcmp(envn_alias, sh_data->args[1]) == 0)
		{
			n = a;
		}
		free(envn_var);
	}
	if (n == -1)
	{
		obtain_error(sh_data, -1);
		return (1);
	}
	realloc_envn = malloc(sizeof(char *) * (a));
	for (a = b = 0; sh_data->envn[a]; a++)
	{
		if (a != n)
		{
			realloc_envn[b] = sh_data->envn[a];
			b++;
		}
	}
	realloc_envn[b] = NULL;
	free(sh_data->envn[n]);
	free(sh_data->envn);
	sh_data->envn = realloc_envn;
	return (1);
}

