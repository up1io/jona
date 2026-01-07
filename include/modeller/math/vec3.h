#ifndef MODELLER_VEC3_H
#define MODELLER_VEC3_H

#include"modeller/types.h"

typedef struct {
  float32_t x;
  float32_t y;
  float32_t z;
} vec3_t;

//
// Constructor
//
vec3_t vec3(float32_t x,float32_t y, float32_t z);
vec3_t vec3_zero(void);

//
// Basic arithmetic
//
vec3_t vec3_add(const vec3_t a,const vec3_t b);
vec3_t vec3_sub(const vec3_t a,const vec3_t b);
vec3_t vec3_mul(const vec3_t a,const vec3_t b);
vec3_t vec3_scale(const vec3_t a,const float32_t s);
vec3_t vec3_div(const vec3_t a,const float32_t s);
vec3_t vec3_negate(const vec3_t v);

//
// Vector math
//
float32_t vec3_dot(const vec3_t a,const vec3_t b);
vec3_t vec3_cross(const vec3_t a,const vec3_t b);
float32_t vec3_length(const vec3_t v);
float32_t vec3_length_squared(const vec3_t v);
vec3_t vec3_normalize(const vec3_t v);
vec3_t vec3_normalize_safe(const vec3_t v);

//
// Geometric operations
//
float32_t vec3_distance(const vec3_t a,const vec3_t b);
float32_t vec3_distance_squared(const vec3_t a,const vec3_t b);
vec3_t vec3_lerp(const vec3_t a,const vec3_t b,const float32_t t);
vec3_t vec3_reflect(const vec3_t v,const vec3_t normal);

//
// Min/Max operations
//
vec3_t vec3_min(const vec3_t a, const vec3_t b);
vec3_t vec3_max(const vec3_t a, const vec3_t b);

// 
// Utility
//
// int vec3_equal(const vec3_t a,const vec3_t b,const float32_t epsilon);
// int vec3_equal_default(const vec3_t a, const vec3_t b);

#endif
