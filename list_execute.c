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
	char *token = strtok((char *)command, " ");

	int i = 0;

	while (token != NULL && i < MAX_COMMAND_LENGTH - 1)
	{
		if (i > 0)
		{
			fprintf(stderr, "Error: Only single-word commands are allowed.\n");
			exit(EXIT_FAILURE);
		}
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}

/**
 * printEnvironment - prints all environment variables to the console
 */

void printEnvironment(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * executeChild - takes a command string and executes it as a child process
 * @command: pointer to the command string
 */

void executeChild(const char *command)
{
	char *args[MAX_COMMAND_LENGTH];
	char *path;
	char executable[MAX_COMMAND_LENGTH];

	parseArguments(command, args);

	if (strcmp(args[0], "env") == 0)
	{
		printEnvironment();
		exit(EXIT_SUCCESS);
	}

	path = getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not set.\n");
		exit(EXIT_FAILURE);
	}

	snprintf(executable, sizeof(executable), "%s/%s", path, args[0]);

	if (access(executable, X_OK) == 0)
	{
		if (execv(executable, args) == -1)
		{
			perror("execv");
			fprintf(stderr, "Error: Execution failed for command: %s\n", args[0]);
			exit(EXIT_FAILURE);
		}
	}

	fprintf(stderr, "Error: Command not found: %s\n", args[0]);
	exit(EXIT_FAILURE);
}

/**
 * executeParent - waits for a child process execution and report its status
 * @pid:  Process ID of the child process to wait for
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
		printf("Successfully Executed.\n");
	}
	else
	{
		printf("Command Failed.\n");
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
		/* Child process */
		executeChild(command);
	}
	else
	{
		/* Parent process */
		executeParent(pid);
	}
}
