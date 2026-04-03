#include "base.h"
#include "comp_driver.h"
#include <stdio.h>

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
