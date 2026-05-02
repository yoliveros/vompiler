
#include "lexer/lexer.c"

string8 compiler(string8 flag, string8 buff) {
  if (flag.str == nullptr)
    return (string8){.str = nullptr};

  lexer *lexer;
  // TODO parser
  // TODO codegen
  // TODO Assembly

  lexer_init(lexer, buff);
  if (strncmp(flag.str, "--lex", flag.len)) {
    goto out;
  }

  // TODO parser
  if (strncmp(flag.str, "--parse", flag.len)) {
    goto out;
  }
  // TODO codegen
  if (strncmp(flag.str, "--codegen", flag.len)) {
    goto out;
  }
  // TODO Assembly
  if (strncmp(flag.str, "-S", flag.len)) {
    goto out;
  }

out:
  return true;
}
