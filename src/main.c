#include <stdio.h>
#include <string.h>

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

  if (argv[2] != NULL) {
    string8 flag = STRING8_LIT(argv[2]);
    if (strncmp(flag.str, "--lex", flag.len))
      return 0;
    else if (strncmp(flag.str, "--parse", flag.len))
      return 0;
    else if (strncmp(flag.str, "--codegen", flag.len))
      return 0;
    else if (strncmp(flag.str, "-S", flag.len))
      return 0;
  }

  b32 succ = driver(file);
  arena_destroy(perm_arena);
  if (succ)
    return 0;

  return 1;
}
