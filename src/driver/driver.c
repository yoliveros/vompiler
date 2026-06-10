#include "driver.h"
#include "base/base_defs.h"

#define FILE_SIZE 256

static string8 preprocess(string8 file) {
  static char buf[FILE_SIZE];
  snprintf(buf, sizeof(buf), "%.*s", STRING8_FMT(file));

  char *dot = strrchr(buf, '.');
  if (dot)
    *dot = '\0';

  strcat(buf, ".i");

  char cmd[FILE_SIZE];
  snprintf(cmd, sizeof(cmd), "gcc -E -P %.*s -o %s", STRING8_FMT(file), buf);
  system(cmd);

  return STRING8_PTR(buf);
}

static b32 linker(string8 file) {
  static char buf[128];
  snprintf(buf, sizeof(buf), "%.*s", STRING8_FMT(file));

  char *dot = strrchr(buf, '.');
  if (dot)
    *dot = '\0';

  char cmd[FILE_SIZE];
  snprintf(cmd, FILE_SIZE, "gcc %s -o %s", buf, buf);
  system(cmd);
  return true;
}

b32 driver(string8 flags, string8 file) {
  string8 pp_file = preprocess(file);

  string8 file_content = os_read_file(pp_file);

  string8 comp_file = compiler(flags, file_content);

  // b32 success = linker(comp_file);

  // return success;
  return true;
}
