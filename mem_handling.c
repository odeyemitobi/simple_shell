#include "shell.h"

/**
 * custom_memcpy - Copies data between memory locations
 * @destination: pointer to destination memory location
 * @src: source memory location
 * @size: Number of bytes to copy
 * Return: void
 */
void custom_memcpy(void *destination, const void *src, unsigned int size)
{
	char *char_src = (char *)src;
	char *char_destination = (char *)destination;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_destination[i] = char_src[i];
}

/**
 * custom_realloc - reallocates for a new block of the given size
 * @src: pointer to the memory block to be reallocated
 * @orig_size: The original size, in bytes, of the memory block
 * @new_size: new size, in bytes, for the reallocated memory block
 * Return: A pointer to the reallocated memory block
 * if new_size == old_size, returns ptr without changes
 */

void *custom_realloc(void *src, unsigned int orig_size, unsigned int new_size)
{
	void *destination;

	if (src == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(src);
		return (NULL);
	}

	if (new_size == orig_size)
		return (src);

	destination = malloc(new_size);
	if (destination == NULL)
		return (NULL);

	if (new_size < orig_size)
		custom_memcpy(destination, src, new_size);
	else
		custom_memcpy(destination, src, orig_size);

	free(src);
	return (destination);
}

/**
 * resizedp - reallocates a memory block for a double pointer
 * @src: double pointer to the memory block to be reallocated
 * @orig_size: The orignal size, in bytes, of the allocated space
 * @new_size: new size, in bytes, of the new memory block
 * Return: Apointer to the reallocated memory block
 * if new_size == old_size, returns ptr without changes
 */

char **resizedp(char **src, unsigned int orig_size, unsigned int new_size)
{
	char **destination;
	unsigned int i;

	if (src == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == orig_size)
		return (src);

	destination = malloc(sizeof(char *) * new_size);
	if (destination == NULL)
		return (NULL);

	for (i = 0; i < orig_size; i++)
		destination[i] = src[i];

	free(src);

	return (destination);
}
