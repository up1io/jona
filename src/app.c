#define _POSIX_C_SOURCE 199309L

#include "jona/app.h"
#include "jona/platform.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct jo_app_t {
  jo_app_config_t config;

  jo_platform_t *platform;

  int is_running;
  struct timespec last_frame_time;
};

jo_app_t *jo_app_create(const jo_app_config_t *config)
{
  assert(config != NULL);

  jo_app_t *app = (jo_app_t*)malloc(sizeof(jo_app_t));
  assert(app != NULL);

  app->config = *config;
  app->is_running = 0;

  const char *title;
  switch (config->title) {
    case JO_APP_TITLE_MAIN:
      title = "JONA";
      break;
    case JO_APP_TITLE_COUNT:
    default:
      title = "Default";
      break;
  }

  jo_platform_t *platform = jo_platform_create(title, config->window_width, config->window_height);
  assert(platform != NULL);

  app->platform = platform;

  // TODO(john): add here the creations of the modules

  clock_gettime(CLOCK_MONOTONIC, &app->last_frame_time);

  return app;
}

void jo_app_destroy(jo_app_t *app)
{
  assert(app != NULL);

  if (app->platform) {
    jo_platform_destroy(app->platform);
  }

  free(app);
}

static float64_t jo_app_get_delta_time(jo_app_t *app)
{
  struct timespec current_time;
  clock_gettime(CLOCK_MONOTONIC, &current_time);

  float64_t sec_diff = current_time.tv_sec - app->last_frame_time.tv_sec;
  float64_t nsec_diff = current_time.tv_nsec - app->last_frame_time.tv_nsec;

  // Note(john): avoid negative nsec
  if (nsec_diff < 0) {
    sec_diff -= 1;
    nsec_diff += 1000000000L;
  }

  float64_t delta = (float64_t)sec_diff + (float64_t)nsec_diff * 1e-9;

  app->last_frame_time = current_time;
  return delta;
}

jo_app_status jo_app_run(jo_app_t *app)
{
  assert(app != NULL);

  if (app->config.callbacks.on_init) {
    app->config.callbacks.on_init(app);
  }

  app->is_running = 1;

  while(app->is_running) {
    float64_t delta = jo_app_get_delta_time(app);

    jo_platform_poll_events(app->platform);

    jo_platform_event_t evt;
    while(jo_platform_get_event(app->platform, &evt)) {
      switch(evt.type) {
        case JO_PLATFORM_EVENT_QUIT:
          printf("Close event\n");
          app->is_running = 0;
          break;
        default:
          printf("event %d\n", evt.type);
          break;
      }
    }

    if (app->config.callbacks.on_update) {
      app->config.callbacks.on_update(app, delta);
    }

    jo_platform_swap_buffers(app->platform);
  }

  if (app->config.callbacks.on_shutdown) {
    app->config.callbacks.on_shutdown(app);
  }

  return JO_APP_SUCCESS;
}
