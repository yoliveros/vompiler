// unity build
#include "ub.h"
#include "ub.c"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Missing params\n");
    return EXIT_FAILURE;
  }

  if (argv[1][0] == '\0') {
    fprintf(stderr, "File name missing\n");
    return EXIT_FAILURE;
  }

  string8 file = {0};
  // string8 flags[MAX_FLAGS];
  string8 flags = {0};

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-')
      flags = STRING8_PTR(argv[i]);
    else
      file = STRING8_PTR(argv[i]);
  }

  b32 succ = driver(flags, file);

  if (succ)
    return 0;
}
