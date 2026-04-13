
u32 os_get_page_size() { return (u32)sysconf(_SC_PAGESIZE); }

void *os_mem_reserve(u64 size) {
  void *out = mmap(NULL, size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (out == MAP_FAILED)
    return NULL;

  return out;
}

b32 os_mem_commit(void *ptr, u64 size) {
  i32 ret = mprotect(ptr, size, PROT_READ | PROT_WRITE);
  return ret == 0;
}

b32 os_mem_decommit(void *ptr, u64 size) {
  i32 ret = mprotect(ptr, size, PROT_NONE);
  return ret == 0;
}

b32 os_mem_release(void *ptr, u64 size) {
  i32 ret = munmap(ptr, size);
  return ret == 0;
}
