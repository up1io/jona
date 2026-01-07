#include "modeller/math/vec3.h"
#include <math.h>
#include <assert.h>

#define IS_FINITE(x) (isfinite(x))
#define IS_VALID_VEC3(v) (IS_FINITE((v).x) && IS_FINITE((v).y) && IS_FINITE((v).z))
#define IS_NONZERO(x) (fabsf(x) > FLOAT32_EPSILON)

//
// Constructors
//

vec3_t vec3(float32_t x, float32_t y, float32_t z) {
  assert(IS_FINITE(x));
  assert(IS_FINITE(y));
  assert(IS_FINITE(z));

  vec3_t out;
  out.x = x;
  out.y = y;
  out.z = z;

  assert(IS_VALID_VEC3(out));
  return out;
}

vec3_t vec3_zero(void) {
  return vec3(0.0f, 0.0f, 0.0f);
}

//
// Basic arithemtic
//

vec3_t vec3_add(const vec3_t a, const vec3_t b) {
  assert(IS_VALID_VEC3(a));
  assert(IS_VALID_VEC3(b));

  vec3_t out;
  out.x = a.x + b.x;
  out.y = a.y + b.y;
  out.z = a.z + b.z;

  assert(IS_VALID_VEC3(out));
  return out;
}

vec3_t vec3_sub(const vec3_t a, const vec3_t b) {
  assert(IS_VALID_VEC3(a));
  assert(IS_VALID_VEC3(b));

  vec3_t out;
  out.x = a.x - b.x;
  out.y = a.y - b.y;
  out.z = a.z - b.z;

  assert(IS_VALID_VEC3(out));
  return out;
}

vec3_t vec3_mul(const vec3_t a, const vec3_t b) {
  assert(IS_VALID_VEC3(a));
  assert(IS_VALID_VEC3(b));

  vec3_t out;
  out.x = a.x * b.x;
  out.y = a.y * b.y;
  out.z = a.z * b.z;

  assert(IS_VALID_VEC3(out));
  return out;
}

vec3_t vec3_scale(const vec3_t v, const float32_t s) {
  assert(IS_VALID_VEC3(v));
  assert(IS_FINITE(s));

  vec3_t out;
  out.x = v.x * s;
  out.y = v.y * s;
  out.z = v.z * s;

  assert(IS_VALID_VEC3(out));
  return out;
}

vec3_t vec3_div(const vec3_t v, const float32_t s) {
  assert(IS_VALID_VEC3(v));
  assert(IS_FINITE(s));
  assert(IS_NONZERO(s));
  
  float32_t inv = 1.0f / s;
  assert(IS_FINITE(inv));

  vec3_t out;
  out.x = v.x * inv;
  out.y = v.y * inv;
  out.z = v.z * inv;

  assert(IS_VALID_VEC3(out));
  return out;
}

vec3_t vec3_negate(const vec3_t v) {
  assert(IS_VALID_VEC3(v));

  vec3_t out;
  out.x = -v.x;
  out.y = -v.y;
  out.z = -v.z;
  
  assert(IS_VALID_VEC3(out));
  return out;
}

//
// Vector math
//

float32_t vec3_dot(const vec3_t a, const vec3_t b) {
  assert(IS_VALID_VEC3(a));
  assert(IS_VALID_VEC3(b));

  float32_t out = a.x * b.x + a.y * b.y + a.z * b.z;

  assert(IS_FINITE(out));
  return out;
}

vec3_t vec3_cross(const vec3_t a, const vec3_t b) {
  assert(IS_VALID_VEC3(a));
  assert(IS_VALID_VEC3(b));

  vec3_t out;
  out.x = a.y * b.z - a.z * b.y;
  out.y = a.z * b.x - a.x * b.z;
  out.z = a.x * b.y - a.y * a.x;

  assert(IS_VALID_VEC3(out));
  return out;
}

float32_t vec3_length_squared(const vec3_t v) {
  assert(IS_VALID_VEC3(v));

  float32_t out = v.x * v.x + v.y * v.y + v.z * v.z;

  assert(IS_FINITE(out));
  assert(out >= 0.0f);
  return out;
}

float32_t vec3_length(const vec3_t v) {
  assert(IS_VALID_VEC3(v));

  float32_t len_sq = vec3_length_squared(v);
  assert(len_sq >= 0.0f);

  float32_t out = sqrtf(len_sq);

  assert(IS_FINITE(out));
  assert(out >= 0.0f);
  return out;
}

vec3_t vec3_normalize(const vec3_t v) {
  assert(IS_VALID_VEC3(v));

  float32_t len = vec3_length(v);
  assert(IS_NONZERO(len));

  vec3_t out = vec3_div(v, len);

  assert(IS_VALID_VEC3(out));
  return out;
}

vec3_t vec3_normalize_safe(const vec3_t v) {
  assert(IS_VALID_VEC3(v));

  float32_t len_sq = vec3_length_squared(v);
  assert(len_sq >= 0.0f);

  vec3_t out;
  if (len_sq < FLOAT32_EPSILON * FLOAT32_EPSILON) {
    out = vec3_zero();
  } else {
    float32_t len = sqrtf(len_sq);
    assert(IS_NONZERO(len));
    out = vec3_div(v, len);
  }

  assert(IS_VALID_VEC3(out));
  return out;
}

//
// Geometric operations
//

float32_t vec3_distance_squared(const vec3_t a, const vec3_t b) {
  assert(IS_VALID_VEC3(a));
  assert(IS_VALID_VEC3(b));

  vec3_t diff = vec3_sub(a, b);
  float32_t out = vec3_length_squared(diff);

  assert(IS_FINITE(out));
  assert(out >= 0.0f);
  return out;
}

float32_t vec3_distance(const vec3_t a, const vec3_t b) {
  assert(IS_VALID_VEC3(a));
  assert(IS_VALID_VEC3(b));

  float32_t dist_sq = vec3_distance_squared(a, b);
  float32_t out = sqrtf(dist_sq);

  assert(IS_FINITE(out));
  assert(out >= 0.0f);
  return out;
}

vec3_t vec3_lerp(const vec3_t a, const vec3_t b, const float32_t t) {
  assert(IS_VALID_VEC3(a));
  assert(IS_VALID_VEC3(b));
  assert(IS_FINITE(t));

  vec3_t out;
  out.x = a.x + t * (b.x - a.x);
  out.y = a.y + t * (b.y - a.y);
  out.z = a.z + t * (b.z - a.z);

  assert(IS_VALID_VEC3(out));
  return out;
}

vec3_t vec3_reflect(const vec3_t v, const vec3_t normal) {
  assert(IS_VALID_VEC3(v));
  assert(IS_VALID_VEC3(normal));

  float32_t dot = vec3_dot(v, normal);
  assert(IS_FINITE(dot));

  vec3_t scaled_normal = vec3_scale(normal, 2.0f * dot);
  vec3_t out = vec3_sub(v, scaled_normal);
  
  assert(IS_VALID_VEC3(out));
  return out;
}

//
// Min/Max operations
//

vec3_t vec3_min(const vec3_t a, const vec3_t b) {
  assert(IS_VALID_VEC3(a));
  assert(IS_VALID_VEC3(b));

  vec3_t out;
  out.x = fminf(a.x, b.x);
  out.y = fminf(a.y, b.y);
  out.z = fminf(a.z, b.z);

  assert(IS_VALID_VEC3(out));
  return out;
}

vec3_t vec3_max(const vec3_t a, const vec3_t b) {
  assert(IS_VALID_VEC3(a));
  assert(IS_VALID_VEC3(b));

  vec3_t out;
  out.x = fmaxf(a.x, b.x);
  out.y = fmaxf(a.y, b.y);
  out.z = fmaxf(a.z, b.z);

  assert(IS_VALID_VEC3(out));
  return out;
}

//
// Utility
//

// Todo(john): add utitilies func
