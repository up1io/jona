#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct jo_shader_t {
  unsigned int id;
};

/* 
 * INTERNAL:
 * Load entire file into memory 
 */
static jo_shader_error_t load_file(const char *path, char **out_source) {
  if (path == NULL || out_source == NULL) {
    return JO_SHADER_ERR_INVALID_ARGUMENT;
  }

  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    return JO_SHADER_ERR_FILE_IO;
  }

  if (fseek(file, 0, SEEK_END) != 0) {
    fclose(file);
    return JO_SHADER_ERR_FILE_IO;
  }

  long size = ftell(file);
  if (size < 0) {
    fclose(file);
    return JO_SHADER_ERR_FILE_IO;
  }

  rewind(file);

  char *buffer = malloc((size_t)size+1);
  if (buffer == NULL) {
    fclose(file);
    return JO_SHADER_ERR_FILE_IO;
  }

  size_t read_count = fread(buffer, 1, (size_t)size, file);
  if (read_count != (size_t)size) {
     free(buffer);
     fclose(file);
     return JO_SHADER_ERR_FILE_IO;
  }

  buffer[size] = '\0';
  *out_source = buffer;

  fclose(file);
  return JO_SHADER_OK;
}

/*
 * INTERNAL
 */
static jo_shader_error_t compile_shader(
    unsigned int *shader_id, 
    GLenum type, 
    const char *source
) {
  if (shader_id == NULL || source == NULL) {
    return JO_SHADER_ERR_INVALID_ARGUMENT;
  }

  unsigned int id = glCreateShader(type);
  if (id == 0) {
    return JO_SHADER_ERR_FILE_IO;
  }

  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);

  int success = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (success == 0) {
    char info_log[512];
    glGetShaderInfoLog(id, 512, NULL, info_log);
    fprintf(stderr, "Shader compilation error: %s\n", info_log);
    glDeleteShader(id);
    return (type == GL_VERTEX_SHADER) 
      ? JO_SHADER_ERR_VERTEX_COMPILE
      : JO_SHADER_ERR_FRAGMENT_COMPILE;
  }

  *shader_id = id;

  return JO_SHADER_OK;
}

jo_shader_error_t jo_shader_create(
    jo_shader_t **out_shader,
    const char *vertex_path,
    const char *fragment_path
) {
  if (out_shader == NULL || vertex_path == NULL || fragment_path == NULL) {
    return JO_SHADER_ERR_INVALID_ARGUMENT;
  }

  jo_shader_t *shader = malloc(sizeof(jo_shader_t));
  if (shader == NULL) {
    return JO_SHADER_ERR_FILE_IO;
  }

  shader->id = 0;
  
  char *vertex_source = NULL;
  char *fragment_source = NULL;
  jo_shader_error_t err;

  err = load_file(vertex_path, &vertex_source);
  if (err != JO_SHADER_OK) {
    free(shader);
    return err;
  }

  err = load_file(fragment_path, &fragment_source);
  if (err != JO_SHADER_OK) {
    free(vertex_source);
    free(shader);
    return err;
  }

  unsigned int vertex_id = 0;
  unsigned int fragment_id = 0;

  err = compile_shader(&vertex_id, GL_VERTEX_SHADER, vertex_source);
  free(vertex_source);
  if (err != JO_SHADER_OK) {
    free(fragment_source);
    free(shader);
    return err;
  }

  err = compile_shader(&fragment_id, GL_FRAGMENT_SHADER, fragment_source);
  free(fragment_source);
  if (err != JO_SHADER_OK) {
    glDeleteShader(vertex_id);
    free(shader);
    return err;
  }
  
  unsigned int program_id = glCreateProgram();
  if (program_id == 0) {
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
    free(shader);
    return JO_SHADER_ERR_LINK;
  }

  glAttachShader(program_id, vertex_id);
  glAttachShader(program_id, fragment_id);
  glLinkProgram(program_id);
 
  int success = 0;
  glGetProgramiv(program_id, GL_LINK_STATUS, &success);
  glDeleteShader(vertex_id);
  glDeleteShader(fragment_id);

  if (success == 0) {
    char info_log[512];
    glGetProgramInfoLog(program_id, 512, NULL, info_log);
    fprintf(stderr, "Shader linking error: %s\n", info_log);
    free(shader);
    return JO_SHADER_ERR_LINK;
  }

  shader->id = program_id;
  *out_shader = shader;
  return JO_SHADER_OK;
}

void jo_shader_destroy(jo_shader_t *shader) {
  if (shader == NULL) {
    return;
  }
  if (shader->id != 0) {
    glDeleteProgram(shader->id);
  }
  free(shader);
}

void jo_shader_use(const jo_shader_t *shader) {
  if (shader == NULL || shader->id == 0) {
    return;
  }
  glUseProgram(shader->id);
}

void jo_shader_set_bool(
    const jo_shader_t *shader,
    const char *name,
    int value
) {
  if (shader == NULL || shader->id == 0 || name == NULL) {
    return;
  }
  int loc = glGetUniformLocation(shader->id, name); 
  if (loc != -1) {
    glUniform1i(loc, value);
  }
}

void jo_shader_set_int(
    const jo_shader_t *shader,
    const char *name,
    int value
) {
  if (shader == NULL || shader->id == 0 || name == NULL) {
    return;
  }
  int loc = glGetUniformLocation(shader->id, name);
  if (loc != -1) {
    glUniform1i(loc, value);
  }
}

void jo_shader_set_float(const jo_shader_t *shader, const char *name, float value) {
  if (shader == NULL || shader->id == 0 || name == NULL) {
    return;
  }
  int loc = glGetUniformLocation(shader->id, name);
  if (loc != -1) {
    glUniform1f(loc, value);
  }
}

void jo_shader_set_mat4(const jo_shader_t *shader, const char *name, const float *value) {
  if (shader == NULL || shader->id == 0 || name == NULL) {
    return;
  }
  int loc = glGetUniformLocation(shader->id, name);
  if (loc != -1) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, value);
  }
}
