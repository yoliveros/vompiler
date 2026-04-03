#include "comp_driver.h"
#include "base.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_SIZE 256

void get_file_name(string file) {
  // string full_name = STRING_LIT(strrchr(file.str, '/'));

  // Name without extension
  STRING_LIT(strtok(file.str, "."));
}

string preprocess(string file) {
  string file_name = STRING_LIT(strcpy(file_name.str, file.str));
  get_file_name(file_name);

  string out_file = STRING_LIT(strcat(file_name.str, ".i"));
  char cmd[FILE_SIZE];
  snprintf(cmd, FILE_SIZE, "gcc -E -P %s -o %s", file.str, out_file.str);
  system(cmd);
  // if (!succ)
  //   exit(succ);

  return out_file;
}

string compile(string file) {
  string file_name = STRING_LIT(strtok(file.str, "."));

  string out_file = STRING_LIT(strcat(file_name.str, ".s"));
  char cmd[FILE_SIZE];
  snprintf(cmd, FILE_SIZE, "gcc %s.c -o %s", file.str, out_file.str);
  system(cmd);
  system(strcat("rm ", file.str));
  return out_file;
}

b32 linker(string file) {
  string file_name = STRING_LIT(strcat(file_name.str, "."));

  char cmd[FILE_SIZE];
  snprintf(cmd, FILE_SIZE, "gcc %s -o %s", file.str, file_name.str);
  system(cmd);
  return TRUE;
}

b32 comp_driver(string file) {
  // FILE *p_file = fopen(file.str, "r");

  string pp_file = preprocess(file);
  // string comp_file = compile(pp_file);
  // b32 success = linker(comp_file);
  // fclose(p_file);
  // return success;
  return 0;
}
