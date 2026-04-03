#include "base.h"
#include <stdio.h>
#include <stdlib.h>

#define FILE_SIZE 256

void preprocess(string file) {
  if (file.len > FILE_SIZE) {
    fprintf(stderr, "File name should not be greater than %d", FILE_SIZE);
    exit(1);
  }

  char cmd[FILE_SIZE];
  snprintf(cmd, sizeof(cmd), "gcc -E -P %s %s", file.str, file.str);
  system(cmd);
}

// void compile(string file) {
// system("gcc");
// }

// void linker(string file) { system("gcc "); }

int main(int argc, char **argv) {
  if (argc < 2) {
    perror("Missing params");
    return 1;
  }

  string file = STRING_LIT(argv[1]);

  preprocess(file);
  return 0;
}
