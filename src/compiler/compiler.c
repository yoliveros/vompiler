
#include "lexer/lexer.c"

i32 compiler(string8 flag) {
  if (flag.str == nullptr)
    return -1;

  if (strncmp(flag.str, "--lex", flag.len)) {
    return 0;
  } else if (strncmp(flag.str, "--parse", flag.len)) {
    return 0;
  } else if (strncmp(flag.str, "--codegen", flag.len)) {
    return 0;
  } else if (strncmp(flag.str, "-S", flag.len)) {
    return 0;
  }
}
