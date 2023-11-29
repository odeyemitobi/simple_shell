#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function Declarations */
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
void free_memory(char **args);

#endif /* HOLBERTON_H */

