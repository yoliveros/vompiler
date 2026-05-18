
#include <stdio.h>
#if OS_LINUX
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#elif OS_WIN
#include <windows.h>
#endif

u32 os_get_page_size(void);

void *os_mem_reserve(u64 size);
b32 os_mem_commit(void *ptr, u64 size);
b32 os_mem_decommit(void *ptr, u64 size);
b32 os_mem_release(void *ptr, u64 size);

// File reader/mapper with mmap
string8 os_read_file(string8 file_route);
