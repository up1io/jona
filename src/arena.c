#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jona/arena.h"

void arena_init(arena_t *arena, size_t size)
{
  arena->buffer = malloc(size);
  arena->size = size;
  arena->offset = 0;
}

void *arena_alloc(arena_t *arena, size_t size)
{
  if (arena->offset + size > arena->size) {
    return NULL;
  }

  void *ptr = arena->buffer + arena->offset;
  arena->offset += size;
 
  return ptr;
}

void arena_reset(arena_t *arena)
{

  arena->offset = 0;
}

void arena_destroy(arena_t *arena)
{
  free(arena->buffer);
}
