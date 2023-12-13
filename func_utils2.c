#include "shell.h"

/**
 * env_assist - Display brief summaries of builtin commands.
 * Return: void.
 */

void env_assist(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "\tDisplay information about builtin commands.\n";
	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "Displays brief summaries of builtin commands.\n";

	write(STDOUT_FILENO, help, custom_strlen(help));
}

/**
 * env_assist_alias - Access help documentation
 * for the built-in 'alias' command.
 *
 * Return: void
 */

void env_assist_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "\tDefine or display aliases.\n ";

	write(STDOUT_FILENO, help, custom_strlen(help));
}

/**
 * env_assist_cd - Assist information for the built-in cd command.
 *
 * Return: no return
 */

void env_assist_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "\tChange the shell working directory.\n ";

	write(STDOUT_FILENO, help, custom_strlen(help));
}

