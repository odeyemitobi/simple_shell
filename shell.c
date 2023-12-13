#include "shell.h"

/**
 * main - runs the core logic of the shell
 * Return: status code 0
 */

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	size_t len;

	while (1)
	{
		displayPrompt();

		if (getline(command, &len, stdin) == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		len = strlen(command);

		if (len > 0 && command[len - 1] == '\n')
		{
			command[len - 1] = '\0';
		}

		if (strcmp(command, "exit") == 0)
		{
			write(STDOUT_FILENO, "Exit Tobi and Ella's List.\n", 28);
			break;
		}

		executeCommand(command);
	}

	return (0);
}
