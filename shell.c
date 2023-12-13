#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - runs the core logic of the shell
 * Return: status code 0
 */

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	size_t len;
	ssize_t read_bytes;

	while (1)
	{
		displayPrompt();

		read_bytes = read(STDIN_FILENO, command, sizeof(command));

		if (read_bytes == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		else if (read_bytes == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}

		len = (size_t)read_bytes;

		if (len > 0 && command[len - 1] == '\n')
		{
			command[len - 1] = '\0';
		}

		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0)
		{
			write(STDOUT_FILENO, "Exit the shell.\n", sizeof("Exit the shell.\n") - 1);
			break;
		}

		executeCommand(command);
	}

	return (0);
}

