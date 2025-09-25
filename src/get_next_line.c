#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 8192

char *get_next_line(int fd) {
  static char buffer[MAX_LINE_LENGTH] = {0};
  static unsigned int buffer_cursor = 0;

  for (unsigned int k = 0; k < buffer_cursor; ++k) {
    if (buffer[k] == '\n') {
      char *res = malloc(k + 2);
      if (res) {
        for (unsigned int m = 0; m <= k; ++m) {
          res[m] = buffer[m];
        }
        res[k + 1] = '\0';
      }

      for (unsigned int m = k + 1; m < buffer_cursor; ++m) {
        buffer[m - k - 1] = buffer[m];
      }
      buffer_cursor -= (k + 1);
      buffer[buffer_cursor] = '\0';

      return res;
    }
  }

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
        if (res) {
          for (unsigned int i = 0; i < buffer_cursor; ++i) {
            res[i] = buffer[i];
          }
          res[buffer_cursor] = '\0';
        }

        buffer[0] = '\0';
        buffer_cursor = 0;
      }
      break;
    }

    for (unsigned int i = 0; i < bytes_read; ++i) {
      if (chunk[i] != '\n') {
        if (buffer_cursor >= MAX_LINE_LENGTH - 1) {
          buffer[MAX_LINE_LENGTH - 1] = '\0';
          res = malloc(MAX_LINE_LENGTH);
          if (res) {
            strcpy(res, buffer);
          }
          buffer_cursor = 0;
          buffer[0] = '\0';
          return res;
        }

        buffer[buffer_cursor] = chunk[i];
        buffer_cursor++;
      } else {
        res = malloc(buffer_cursor + 2);
        if (res) {
          for (unsigned int j = 0; j < buffer_cursor; ++j) {
            res[j] = buffer[j];
          }
          res[buffer_cursor] = '\n';
          res[buffer_cursor + 1] = '\0';
        }

        buffer[0] = '\0';
        buffer_cursor = 0;

        for (unsigned int j = i + 1; j < bytes_read; ++j) {
          if (buffer_cursor >= MAX_LINE_LENGTH - 1) {
            buffer[MAX_LINE_LENGTH - 1] = '\0';
            break;
          }
          buffer[buffer_cursor] = chunk[j];
          buffer_cursor++;
        }
        buffer[buffer_cursor] = '\0';

        endl_flag = 1;
        break;
      }
    }
    ++chunk_id;
  }
  return res;
}
