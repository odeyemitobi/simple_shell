#include "shell.h"


/**
 * obtain_signal - function that handle the crtl + c call in promp
 * t
 * @sig_val: handles the signal
 */

void obtain_signal(int sig_val)
{
	(void)sig_val;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
