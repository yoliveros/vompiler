#include <stdio.h>

// ub.h
#include "ub.h"
// ub.c
#include "ub.c"

int main(int argc, char **argv) {
  if (argc < 2) {
    perror("Missing params");
    return 1;
  }

  string file = STRING_LIT(argv[1]);

  b32 succ = comp_driver(file);
  if (succ)
    return 0;

  return 1;
}
