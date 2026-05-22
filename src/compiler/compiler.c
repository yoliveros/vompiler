
string8 compiler(string8 flag, string8 buff) {
  mem_arena *perm_arena = arena_create(GiB(1), MiB(1));

  if (flag.str == nullptr)
    return (string8){0};

  lexer lexer;
  // TODO parser
  // TODO codegen
  // TODO Assembly

  mem_arena_temp scratch = arena_scratch_get(nullptr, 0);
  lexer_init(scratch.arena, &lexer, buff);

  if (strncmp(flag.str, "--lex", flag.len)) {
    goto out;
  }
  arena_scratch_release(scratch);

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
  arena_destroy(perm_arena);
  return (string8){0};
}
