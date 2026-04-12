#include <stdio.h>
#include <string.h>

// unity build
#include "base/base_defs.h"
#include "ub.h"
#include "ub.c"

int main(int argc, char **argv) {
  if (argc < 2) {
    perror("Missing params");
    return 1;
  }

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
  if (succ)
    return 0;

  return 1;
}
