
// #include <stdio.h>
#include <sys/mman.h>
u32 os_get_page_size() { return (u32)sysconf(_SC_PAGESIZE); }

void *os_mem_reserve(u64 size) {
  void *out =
      mmap(nullptr, size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
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

string8 os_read_file(string8 file_route) {
  i32 fd = open(file_route.str, O_RDONLY);
  if (fd == -1)
    return (string8){0};

  off_t len = lseek(fd, 0, SEEK_END);
  void *file = mmap(nullptr, len, PROT_READ, MAP_PRIVATE, fd, 0);

  close(fd);

  return (string8){.str = file, .len = len};
}
