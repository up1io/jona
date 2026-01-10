#include "jona/platform.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define RGFW_DEBUG
#define RGFW_OPENGL
#define RGFW_IMPLEMENTATION

#include "RGFW/RGFW.h"

#ifdef RGFW_MACOS
#include <OpenGL/gl.h>
#else
#include <glad/glad.h>
#include <GL/gl.h>
#endif

#define JO_PLATFORM_EVENT_QUEUE_SIZE 16

struct jo_platform_t {
  RGFW_window *win;

  jo_platform_event_t events[JO_PLATFORM_EVENT_QUEUE_SIZE];
  int event_count;
};

static void jo_platform_key_callback(RGFW_window* win, RGFW_key key, u8 keyChar, RGFW_keymod keyMod, RGFW_bool repeat, RGFW_bool pressed) 
{
  RGFW_UNUSED(repeat);
  RGFW_UNUSED(keyChar);
  RGFW_UNUSED(keyMod);

  if (key == RGFW_escape && pressed) {
    RGFW_event evt;
    evt.type = RGFW_quit;
    evt.common.win = win;
    RGFW_eventQueuePush(&evt);
  }
}

jo_platform_t *jo_platform_create(const char *title, uint32_t width, uint32_t height)
{
  RGFW_window *win = RGFW_createWindow(title, 0, 0, width, height, RGFW_windowOpenGL);
  RGFW_setKeyCallback(jo_platform_key_callback);

  RGFW_window_makeCurrentContext_OpenGL(win);

  jo_platform_t *platform = malloc(sizeof(*platform));
  if (platform == NULL) {
    free(win);
    return NULL;
  }

  platform->win = win;
  platform->event_count = 0;

  return platform;
}

void jo_platform_destroy(jo_platform_t *platform)
{
  if (!platform) {
    return;
  }

  if (platform->win) {
    RGFW_window_close(platform->win);
  }

  free(platform);
}

void jo_platform_poll_events(jo_platform_t *platform)
{
  RGFW_event e; 
  platform->event_count = 0;

  while(RGFW_window_checkEvent(platform->win, &e)) {
    if (platform->event_count >= 16) {
      printf("[WARN] event poll is full.\n");
      break;
    }

    jo_platform_event_t *evt = &platform->events[platform->event_count];

    switch(e.type) {
      case RGFW_quit:
        evt->type = JO_PLATFORM_EVENT_QUIT;
        platform->event_count++;
        break;
      case RGFW_windowResized:
        evt->type = JO_PLATFORM_EVENT_WINDOW_RESIZE;
        evt->data.window_resize.width = e.common.win->w;
        evt->data.window_resize.height = e.common.win->h;
        platform->event_count++;
        break;
      default:
        break;
    }
  }
}

int jo_platform_get_event(jo_platform_t *platform, jo_platform_event_t *out_event)
{
  if (platform->event_count == 0) {
    return 0;
  }

  *out_event = platform->events[0];

  if (platform->event_count > 1) {
    memmove(&platform->events[0], 
        &platform->events[1], 
        sizeof(jo_platform_event_t) * (platform->event_count -1));
  } 

  platform->event_count--;

  return 1;
}

void jo_platform_swap_buffers(jo_platform_t *platform)
{
  RGFW_window_swapBuffers_OpenGL(platform->win);
}

