
u32 os_get_page_size(void) {
  SYSTEM_INFO sysinfo = {0};
  GetSystemInfo(&sysinfo);

  return sysinfo.dwPageSize;
}

void *os_mem_reserve(u64 size) {
  return VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_READWRITE);
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
