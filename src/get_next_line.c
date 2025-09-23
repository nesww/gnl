#include <stdio.h>
#include <stdlib.h> //for malloc
#include <sys/stat.h>
#include <unistd.h>

unsigned int get_index_start_line_n(char *buffer, unsigned int n) {
  unsigned int count = 0;
  unsigned int i = 0;
  while (buffer[i] && count < n) {
    if (buffer[i] == '\n')
      ++count;
    ++i;
  }
  return i;
}

char *get_next_line(int fd) {
  static int read_lines = 1;
  struct stat sbuf;
  fstat(fd, &sbuf);
  unsigned long long content_len = sbuf.st_size;
  char *buffer = malloc(content_len);
  read(fd, buffer, content_len);
  unsigned int start = get_index_start_line_n(buffer, read_lines);
  unsigned int end = get_index_start_line_n(buffer, read_lines + 1);
  printf("start= %u\n", start);
  printf("end= %u\n", end);
  char *res = malloc(end - start + 1);
  for (unsigned int i = 0; i < end - start; ++i)
    res[i] = buffer[start + i];
  res[end - start] = '\0';
  ++read_lines;
  free(buffer);
  return "";
}
