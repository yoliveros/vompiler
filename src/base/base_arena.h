#pragma once

#define ARENA_BASE_POS (sizeof(mem_arena))
#define ARENA_ALIGN (sizeof(void *))

typedef struct {
  u64 reserve_size;
  u64 commit_size;

  u64 pos;
  u64 commit_pos;
} mem_arena;

mem_arena *arena_create(u64 reserve_size, u64 commit_size);
void arena_destroy(mem_arena *arena);
void *arena_push(mem_arena *arena, u64 size);
void arena_pop(mem_arena *arena, u64 size);
void arena_pop_to(mem_arena *arena, u64 pos);
void arena_clear(mem_arena *arena);

u32 os_get_page_size(void);

void *os_mem_reserve(u64 size);
b32 os_mem_commit(void *ptr, u64 size);
b32 os_mem_decommit(void *ptr, u64 size);
b32 os_mem_release(void *ptr, u64 size);

#define PUSH_STRUCT(arena, T) (T *)arena_push((arena), sizeof(T))
#define PUSH_ARRAY(arena, T, n) (T *)arena_push((arena), sizeof(T) * (n))
