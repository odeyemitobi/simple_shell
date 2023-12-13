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

	while (token != NULL && i < MAX_COMMAND_LENGTH - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	free(copy);
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
		char *args[MAX_COMMAND_LENGTH];

		parseArguments(command, args);

		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}

		if (WIFEXITED(status))
		{
			write(1, "Successfully Executed.\n", 24);
		}
		else
		{
			write(1, "Command Failed.\n", 16);
		}
	}
}

