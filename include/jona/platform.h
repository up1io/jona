#ifndef JO_PLATFORM_H
#define JO_PLATFORM_H

#include "jona/types.h"

typedef struct jo_platform_t jo_platform_t;

typedef enum {
  JO_PLATFORM_EVENT_NONE,
  JO_PLATFORM_EVENT_QUIT,
  JO_PLATFORM_EVENT_KEY_PRESS,
  JO_PLATFORM_EVENT_KEY_RELEASE,
  JO_PLATFORM_EVENT_WINDOW_RESIZE,
} jo_platform_event_type;

typedef enum {
  JO_PLATFORM_KEY_UNKNOWN = 0,
  JO_PLATFORM_KEY_ESCAPE,
} jo_platform_key_t;

typedef struct {
  jo_platform_event_type type;
  union {
    struct {
      jo_platform_key_t key;
      int is_pressed;
    } key;
    struct {
      uint32_t width;
      uint32_t height;
    } window_resize;
  } data;
} jo_platform_event_t;

jo_platform_t *jo_platform_create(const char *title, uint32_t width, uint32_t height);
void jo_platform_destroy(jo_platform_t *platform);

void jo_platform_poll_events(jo_platform_t *platform);
int jo_platform_get_event(jo_platform_t *platform, jo_platform_event_t *out_event);

void jo_platform_swap_buffers(jo_platform_t *platform);

#endif // JO_PLATFORM_H
