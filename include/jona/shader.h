#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

typedef struct jo_shader_t jo_shader_t;

typedef enum jo_shader_error_t {
  JO_SHADER_OK = 0,
  JO_SHADER_ERR_INVALID_ARGUMENT,
  JO_SHADER_ERR_FILE_IO,
  JO_SHADER_ERR_VERTEX_COMPILE,
  JO_SHADER_ERR_FRAGMENT_COMPILE,
  JO_SHADER_ERR_LINK
} jo_shader_error_t;

/*
 * Create a shader program from vertex and fragment shader files.
 * On success, writes the result into `out_shader`.
 */
jo_shader_error_t jo_shader_create(jo_shader_t **out_shader, const char *vertex_path, const char *fragment_path);

void jo_shader_destroy(jo_shader_t *shader);

void jo_shader_use(const jo_shader_t *shader);

void jo_shader_set_bool(const jo_shader_t *shader, const char *name, int value);

void jo_shader_set_int(const jo_shader_t *shader, const char *name, int value);

void jo_shader_set_float(const jo_shader_t *shader, const char *name, float value);

void jo_shader_set_mat4(const jo_shader_t *shader, const char *name, const float *value);

#endif
