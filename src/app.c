#define _POSIX_C_SOURCE 199309L

#include "jona/app.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct jo_app_t {
  jo_app_config_t config;

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

  // TODO(john): add here the creations of the modules

  clock_gettime(CLOCK_MONOTONIC, &app->last_frame_time);

  return app;
}

void jo_app_destroy(jo_app_t *app)
{
  assert(app != NULL);

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

  float64_t shutdownTimer = 0;
  while(app->is_running) {
    float64_t delta = jo_app_get_delta_time(app);

    if (shutdownTimer > 10) {
      app->is_running = 0;
    }

    shutdownTimer += delta;
    printf("Time: %f\n", shutdownTimer);

    if (app->config.callbacks.on_update) {
      app->config.callbacks.on_update(app);
    }
  }

  if (app->config.callbacks.on_shutdown) {
    app->config.callbacks.on_shutdown(app);
  }

  return JO_APP_SUCCESS;
}
