#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * parseArguments - parses a command string into arguments
 * parseArguments - stores arguments in an array
 * @command: pointer to the command string
 * @args: Array for parsed arguments
 */
void parseArguments(const char *command, char *args[])
{
	char *copy = strdup(command);
	char *token = strtok(copy, " ");
	int i = 0;

	while (token != NULL)
	{
		if (strchr(token, ';') || strchr(token, '|') || strchr(token, '>'))
		{
			write(STDERR_FILENO, "Error: failed.\n", sizeof("Error: failed.\n") - 1);
			free(copy);
			_exit(EXIT_FAILURE);
		}

		args[i++] = token;
		token = strtok(NULL, " ");
	}

	if (i != 1)
	{
		write(STDERR_FILENO, "Error: Single-word commands only.\n",
			  sizeof("Error: Single-word commands only.\n") - 1);
		free(copy);
		_exit(EXIT_FAILURE);
	}
	args[i] = NULL;

	free(copy);
}

/**
 * executeChild - forks a child process and executes the command in the CP.
 * @command: pointer to the command string
 */

void executeChild(const char *command)
{
	char *args[MAX_COMMAND_LENGTH];

	parseArguments(command, args);

	if (execvp(args[0], args) == -1)
	{
		char errorMessage[] = "Error: Command not found\n";

		write(STDERR_FILENO, errorMessage, sizeof(errorMessage) - 1);
		_exit(EXIT_FAILURE);
	}
}

/**
 * executeParent - forks a child process and executes the command in the CP.
 * @pid: pointer to the command string
 */

void executeParent(pid_t pid)
{
	int status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}

	if (WIFEXITED(status))
	{
		char successMessage[] = "Successfully Executed.\n";

		write(STDOUT_FILENO, successMessage, sizeof(successMessage) - 1);
	}
	else
	{

		char errorMessage[] = "Command Failed.\n";

		write(STDOUT_FILENO, errorMessage, sizeof(errorMessage) - 1);
	}
}

/**
 * executeCommand - forks a child process and executes the command in the CP.
 * @command: pointer to the command string
 */

void executeCommand(const char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		executeChild(command);
	}
	else
	{
		executeParent(pid);
	}
}

