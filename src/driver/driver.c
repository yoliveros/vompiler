#define FILE_SIZE 256

void get_file_name(string8 file) {
  // string8 full_name = STRING8_LIT(strrchr(file.str, '/'));

  // Name without extension
  STRING8_LIT(strtok(file.str, "."));
}

static string8 preprocess(string8 file) {
  printf("%.*s\n", STRING8_FMT(file));
  string8 file_name = STRING8_LIT(strcpy(file_name.str, file.str));
  printf("%.*s\n", STRING8_FMT(file_name));
  get_file_name(file_name);

  string8 out_file = file_name;
  strcat(out_file.str, ".i");

  char cmd[FILE_SIZE];
  snprintf(cmd, FILE_SIZE, "gcc -E -P %s -o %s", file.str, out_file.str);
  system(cmd);

  return out_file;
}

static b32 linker(string8 file) {
  char buf[FILE_SIZE];
  snprintf(buf, sizeof(buf), "%.*s", STRING8_FMT(file));
  string8 file_name = STRING8_PTR(strrchr(buf, '.'));

  char cmd[FILE_SIZE];
  snprintf(cmd, FILE_SIZE, "gcc %s -o %s", file.str, file_name.str);
  system(cmd);
  return true;
}

b32 driver(string8 flags, string8 file) {
  printf("%.*s\n", STRING8_FMT(file));
  string8 pp_file = preprocess(file);
  printf("%.*s\n", STRING8_FMT(pp_file));

  string8 file_name = STRING8_PTR(strtok(pp_file.str, "."));
  printf("%.*s", STRING8_FMT(file_name));

  string8 comp_file = compiler(flags, file_name);

  b32 success = linker(comp_file);

  return success;
}
