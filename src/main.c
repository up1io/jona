#include "jona/app.h"
#include <stdio.h>

int main()
{
  jo_app_config_t config = {
    .title = JO_APP_TITLE_MAIN,
    .window_width = 800,
    .window_height = 600,
    .target_fps = 60
  };
 
  jo_app_t *app = jo_app_create(&config);

  jo_app_status status = jo_app_run(app);

  if (status != JO_APP_SUCCESS) {
    printf("app was not shutdown successfull\n");
  }

  jo_app_destroy(app);

  return 0;
}
