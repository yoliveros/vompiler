#include <stdio.h>

// unity build
#include "ub.h"
#include "ub.c"

int main(int argc, char **argv) {
  if (argc < 2) {
    perror("Missing params");
    return 1;
  }

  mem_arena *perm_arena = arena_create(GiB(1), MiB(16));

  string8 file = STRING8_LIT(argv[1]);
  string8 flags = STRING8_LIT(argv[2]);

  b32 succ = driver(flags, file);

  arena_destroy(perm_arena);
  if (succ)
    return 0;

  return 1;
}
