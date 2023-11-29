#ifndef _HOLBERTON_H_
#define _HOLBERTON_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* Function Declarations */
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
void free_memory(char **args);

#endif /* _HOLBERTON_H_ */

#include "holberton.h"

/**
 * read_line - Read a line of input from stdin
 *
 * Return: The line inputted by the user
 */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

/**
 * split_line - Split a line into tokens
 * @line: The line to be tokenized
 *
 * Return: An array of tokens (commands and arguments)
 */
char **split_line(char *line)
{
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

/**
 * execute - Execute a command
 * @args: Array of arguments
 *
 * Return: Status of the execution
 */
int execute(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("Error");
    }
    else
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/**
 * free_memory - Free memory allocated for arguments
 * @args: Array of arguments
 */
void free_memory(char **args)
{
    int i;
    for (i = 0; args[i] != NULL; i++)
    {
        free(args[i]);
    }
    free(args);
}


