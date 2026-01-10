#ifndef JO_APP_H
#define JO_APP_H

#include "jona/types.h"

typedef enum {
  JO_APP_SUCCESS      = 0,
  JO_APP_ERROR_INIT   = 1,
  JO_APP_ERROR_CRASH  = 2
} jo_app_status;

typedef enum {
  JO_APP_TITLE_MAIN = 0,
  JO_APP_TITLE_COUNT
} jo_app_title_t;

typedef struct jo_app_t jo_app_t;

typedef struct {
  void (*on_init)(jo_app_t *app);
  void (*on_update)(jo_app_t *app);
  void (*on_render)(jo_app_t *app);
  void (*on_shutdown)(jo_app_t *app);
} jo_app_callbacks_t;

typedef struct {
  uint32_t window_width;
  uint32_t window_height;
  uint32_t target_fps;

  jo_app_title_t title;

  jo_app_callbacks_t callbacks;
} jo_app_config_t;

/* 
 * Creates application instance.
 * Returns NULL on failiure.
 */
jo_app_t *jo_app_create(const jo_app_config_t *config);

void jo_app_destroy(jo_app_t *app);

jo_app_status jo_app_run(jo_app_t *app);

#endif // JO_APP_H
