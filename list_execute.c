#include "shell.h"

extern char **environ;

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

		/* Parse the command and its arguments */
		char *args[MAX_COMMAND_LENGTH];
		char *token = strtok((char *)command, " ");

		int i = 0;
		while (token != NULL && i < MAX_COMMAND_LENGTH - 1)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		if (strcmp(args[0], "env") == 0)
		{
			char **env = environ;
			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
			exit(EXIT_SUCCESS);
		}

		char *path = getenv("PATH");
		if (path == NULL)
		{
			fprintf(stderr, "Error: PATH environment variable not set.\n");
			exit(EXIT_FAILURE);
		}

		char executable[MAX_COMMAND_LENGTH];
		for (token = strtok(path, ":"); token != NULL; token = strtok(NULL, ":"))
		{
			snprintf(executable, sizeof(executable), "%s/%s", token, args[0]);

			if (access(executable, X_OK) == 0)
			{
				if (execv(executable, args) == -1)
				{
					perror("execv");
					exit(EXIT_FAILURE);
				}
			}
		}

		fprintf(stderr, "Error: Command not found: %s\n", args[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
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
}