#ifndef GNL_H
#define GNL_H

/*
 * get_next_line - Read a single line from the file descriptor provided.
 * @param fd (int): the file descriptor
 *
 * Read a single line from the file descriptor provided.
 * The line returned has new line if not OEF.
 * If line read is OEF, returns NULL.
 *
 * Return: the line read from the file descriptor, NULL if EOF
 */
char *get_next_line(int fd);

#endif
