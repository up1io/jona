#ifndef ARENA_H
#define ARENA_H

typedef struct {
  char *buffer;
  size_t size;
  size_t offset;
} arena_t; 

void arena_init(arena_t *arena, size_t size);
void *arena_alloc(arena_t *arena, size_t size);
void arena_reset(arena_t *arena);
void arena_destroy(arena_t *arena);

#endif
