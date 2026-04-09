#define FILE_SIZE 256

void get_file_name(string8 file) {
  // string8 full_name = STRING8_LIT(strrchr(file.str, '/'));

  // Name without extension
  STRING8_LIT(strtok(file.str, "."));
}

string8 preprocess(string8 file) {
  string8 file_name = STRING8_LIT(strcpy(file_name.str, file.str));
  get_file_name(file_name);

  string8 out_file = file_name;
  strcat(out_file.str, ".i");

  char cmd[FILE_SIZE];
  snprintf(cmd, FILE_SIZE, "gcc -E -P %s -o %s", file.str, out_file.str);
  system(cmd);
  // if (!succ)
  //   exit(succ);

  return out_file;
}

string8 compile(string8 file) {
  string8 file_name = STRING8_LIT(strtok(file.str, "."));

  string8 out_file = STRING8_LIT(strcat(file_name.str, ".s"));
  char cmd[FILE_SIZE];
  snprintf(cmd, FILE_SIZE, "gcc %s.c -o %s", file.str, out_file.str);
  system(cmd);
  system(strcat("rm ", file.str));
  return out_file;
}

b32 linker(string8 file) {
  string8 file_name = STRING8_LIT(strcat(file_name.str, "."));

  char cmd[FILE_SIZE];
  snprintf(cmd, FILE_SIZE, "gcc %s -o %s", file.str, file_name.str);
  system(cmd);
  return true;
}

b32 driver(string8 file) {
  // FILE *p_file = fopen(file.str, "r");

  string8 pp_file = preprocess(file);
  // string8 comp_file = compile(pp_file);
  // b32 success = linker(comp_file);
  // fclose(p_file);
  // return success;
  return 0;
}
