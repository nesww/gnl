#include <stdlib.h> //for malloc
#include <sys/stat.h>
#include <unistd.h>

char *get_next_line(int fd) {
  static char buffer[4096] = {0};
  static unsigned int buffer_cursor = 0;

  char chunk[CHUNK_SIZE];
  unsigned int bytes_read = 1;
  int endl_flag = 0;
  char *res = NULL;
  int chunk_id = 0;
  while (!endl_flag && bytes_read > 0) {
    bytes_read = read(fd, chunk, CHUNK_SIZE);
    if (bytes_read <= 0) {
      if (buffer_cursor > 0) {
        res = malloc(buffer_cursor + 1);
        for (unsigned int i = 0; i < buffer_cursor; ++i) {
          res[i] = buffer[i];
        }
        res[buffer_cursor] = '\0';

        // clear buffer
        buffer[0] = '\0';
        buffer_cursor = 0;
      }
      break;
    }

    // copy chunk into buffer
    for (unsigned int i = 0; i < bytes_read; ++i) {
      if (chunk[i] != '\n') {
        buffer[buffer_cursor] = chunk[i];
        buffer_cursor++;
      }

      // found endl
      else {
        res = malloc(buffer_cursor + 2);

        // copy buffer into result buffer
        for (unsigned int j = 0; j < buffer_cursor; ++j) {
          res[j] = buffer[j];
        }

        res[buffer_cursor] = '\n';
        res[buffer_cursor + 1] = '\0';

        // clear the buffer
        buffer[0] = '\0';
        buffer_cursor = 0;

        for (unsigned int j = i + 1; j < bytes_read; ++j) {
          buffer[buffer_cursor] = chunk[j];
          buffer_cursor++;
        }
        buffer[buffer_cursor] = '\0';

        // raise endl flag
        endl_flag = 1;
        break;
      }
    }
    ++chunk_id;
  }
  return res;
}
