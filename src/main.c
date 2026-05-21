#include <stdio.h>

// unity build
#include "ub.h"
#include "ub.c"

int main(int argc, char **argv) {
  if (argc < 2) {
    perror("Missing params");
    return 1;
  }

  string8 file = STRING8_LIT(argv[1]);
  string8 flags = STRING8_LIT(argv[2]);

  b32 succ = driver(flags, file);

  if (succ)
    return 0;

  return 1;
}
