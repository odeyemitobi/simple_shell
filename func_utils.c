#include "shell.h"

/**
 * support_env_tasks - to enhance 'env' command functionality
 *
 * Return: void
 */
void support_env_tasks(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "Print the enviroment of the shell.\n";

	write(STDOUT_FILENO, help, custom_strlen(help));
}
/**
 * env_variable_support - Display assist for the 'setenv' function.
 * Return: void
 */
void env_variable_support(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, custom_strlen(help));
}
/**
 * support_unsetenv_command - function to informats for the builtin unsetenv
 * Return: void
 */
void support_unsetenv_command(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, custom_strlen(help));
}

/**
 * assist_general_command - Display help information for general commands
 * Return: nothing
 */
void assist_general_command(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, custom_strlen(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, custom_strlen(help));
}
/**
 * print_exit_help - Help provide information for exit command.
 *
 * Return: void
 */
void print_exit_help(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, custom_strlen(help));
	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, custom_strlen(help));
}

