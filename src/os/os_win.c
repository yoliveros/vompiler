
u32 os_get_page_size() {
  SYSTEM_INFO sysinfo = {0};
  GetSystemInfo(&sysinfo);

  return sysinfo.dwPageSize;
}

void *os_mem_reserve(u64 size) {
  return VirtualAlloc(nullptr, size, MEM_RESERVE, PAGE_READWRITE);
}

b32 os_mem_commit(void *ptr, u64 size) {
  void *ret = VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE);
  return ret != NULL;
}

b32 os_mem_decommit(void *ptr, u64 size) {
  return VirtualFree(ptr, size, MEM_DECOMMIT);
}

b32 os_mem_release(void *ptr, u64 size) {
  return VirtualFree(ptr, size, MEM_RELEASE);
}

string8 os_read_file(string8 file_route) {
  i32 fd = open(file_route.str, O_RDONLY);
  if (fd == -1)
    return (string8){0};

  off_t len = lseek(fd, 0, SEEK_END);
  void *file = VirtualAlloc(nullptr, len, MEM_RESERVE, PAGE_READONLY);

  close(fd);

  return (string8){.str = file, .len = len};
}
