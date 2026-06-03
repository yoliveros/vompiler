#include <stdio.h>

// unity build
#include "ub.h"
#include "ub.c"

int main(int argc, char **argv) {
  if (argc < 2) {
    perror("Missing params");
    return 1;
  }

  if (argv[1][0] == '\0') {
    perror("File name missing");
    goto exit_failure;
  }
  string8 file = STRING8_PTR(argv[1]);

  string8 flags = {0};
  if (argc > 2 && argv[2][0] != '\0')
    flags = STRING8_PTR(argv[2]);

  b32 succ = driver(flags, file);

  if (succ)
    return 0;

exit_failure:
  return 1;
}
