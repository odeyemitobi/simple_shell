#include "shell.h"

/**
 * displayPrompt - displays the first prompt
 * Return: status code 0
 */
void displayPrompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

