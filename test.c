#include "include/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int file = open("test.txt", O_RDONLY);
  if (!file)
    printf("wops\n");

  char *line = get_next_line(file);
  char *second_line = get_next_line(file);

  printf("%s", line);
  printf("%s", second_line);

  free(line);
  free(second_line);

  close(file);
}
