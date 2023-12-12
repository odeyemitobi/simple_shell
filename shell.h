#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

extern char **environ;

void displayPrompt(void);
void executeCommand(const char *command);
void parseArguments(const char *command, char *args[]);
void printEnvironment(void);
void executeChild(const char *command);
void executeParent(pid_t pid);

#endif /* SHELL_H */
