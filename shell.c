#include "shell.h"

int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		displayPrompt();

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		command[strcspn(command, "\n")] = '\0';
		if (strcmp(command, "exit") == 0)
		{
			printf("Exit Tobi and Ella's List.\n");
			break;
		}

		executeCommand(command);
	}

	return (0);
}