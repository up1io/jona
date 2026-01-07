#include <assert.h>
#include <stdio.h>

#include "modeller/math/vec3.h"
#include "test/utils.h"

void test_vec3_add(void) 
{
  vec3_t a = vec3(1.0f, 1.0f, 1.0f);
  vec3_t b = vec3(1.0f, 1.0f, 1.0f);

  test_t test;
  jo_test_init(&test, "test_vec3_add");

  vec3_t result = vec3_add(a, b);

  jo_test_time_stop(&test);

  assert(result.x == 2.0f);
  assert(result.y == 2.0f);
  assert(result.z == 2.0f);

  jo_test_print_ok(&test);
}

void test_vec3_add_negative(void) 
{
  vec3_t a = vec3(-1.0f, -1.0f, -1.0f);
  vec3_t b = vec3(-1.0f, -1.0f, -1.0f);

  test_t test;
  jo_test_init(&test, "test_vec3_add_negative");

  vec3_t result = vec3_add(a, b);

  jo_test_time_stop(&test);

  assert(result.x == -2.0f);
  assert(result.y == -2.0f);
  assert(result.z == -2.0f);

  jo_test_print_ok(&test);
}

void test_vec3_add_mix(void) 
{
  vec3_t a = vec3(1.0f, -5.0f, -1.0f);
  vec3_t b = vec3(-1.0f, 1.0f, -1.0f);

  test_t test;
  jo_test_init(&test, "test_vec3_add_mix");

  vec3_t result = vec3_add(a, b);

  jo_test_time_stop(&test);

  assert(result.x == 0.0f);
  assert(result.y == -4.0f);
  assert(result.z == -2.0f);

  jo_test_print_ok(&test);
}

void test_vec3_sub(void)
{
  vec3_t a = vec3(10.0f, 10.0f, 10.0f);
  vec3_t b = vec3(7.0f, 7.0f, 7.0f);

  test_t test;
  jo_test_init(&test, "test_vec3_sub");

  vec3_t result = vec3_sub(a, b);

  jo_test_time_stop(&test);

  assert(result.x == 3.0f);
  assert(result.y == 3.0f);
  assert(result.z == 3.0f);

  jo_test_print_ok(&test);
}

void test_vec3_sub_negative(void)
{
  vec3_t a = vec3(-2.0f, -2.0f, -2.0f);
  vec3_t b = vec3(3.0f, 3.0f, 3.0f);

  test_t test;
  jo_test_init(&test, "test_vec3_sub_negative");

  vec3_t result = vec3_sub(a, b);

  jo_test_time_stop(&test);

  assert(result.x == -5.0f);
  assert(result.y == -5.0f);
  assert(result.z == -5.0f);

  jo_test_print_ok(&test);
}

void test_vec3_sub_mix(void)
{
  vec3_t a = vec3(10.0f, 0.5f, 20.0f);
  vec3_t b = vec3(2.5f, 0.75f, 5.0f);

  test_t test;
  jo_test_init(&test, "test_vec3_sub_mix");

  vec3_t result = vec3_sub(a, b);

  jo_test_time_stop(&test);

  assert(result.x == 7.5f);
  assert(result.y == -0.25f);
  assert(result.z == 15.0f);

  jo_test_print_ok(&test);
}

void test_vec3_mul(void)
{
  vec3_t a = vec3(5.0f, 5.0f, 5.0f);
  vec3_t b = vec3(2.0f, 2.0f, 2.0f);

  test_t test;
  jo_test_init(&test, "test_vec3_mul");

  vec3_t result = vec3_mul(a, b);

  jo_test_time_stop(&test);

  assert(result.x == 10.0f);
  assert(result.y == 10.0f);
  assert(result.z == 10.0f);

  jo_test_print_ok(&test);
}

void test_vec3_mul_negative(void)
{
  vec3_t a = vec3(-5.0f, -5.0f, -5.0f);
  vec3_t b = vec3(2.0f, 2.0f, 2.0f);

  test_t test;
  jo_test_init(&test, "test_vec3_mul_negative");

  vec3_t result = vec3_mul(a, b);

  jo_test_time_stop(&test);

  assert(result.x == -10.0f);
  assert(result.y == -10.0f);
  assert(result.z == -10.0f);

  jo_test_print_ok(&test);
}

void test_vec3_mul_mix(void)
{
  vec3_t a = vec3(2.0f, 7.5f, 40.0f);
  vec3_t b = vec3(2.0f, 3.0f, 0.5f);

  test_t test;
  jo_test_init(&test, "test_vec3_mul_mix");

  vec3_t result = vec3_mul(a, b);

  jo_test_time_stop(&test);

  assert(result.x == 4.0f);
  assert(result.y == 22.5f);
  assert(result.z == 20.0f);

  jo_test_print_ok(&test);
}

void test_vec3_scale(void)
{
  vec3_t v = vec3(2.0f, 2.0f, 2.0f);
  float32_t s = 2.0f;

  test_t test;
  jo_test_init(&test, "test_vec3_scale");

  vec3_t result = vec3_scale(v, s);

  jo_test_time_stop(&test);

  assert(result.x == 4.0f);
  assert(result.y == 4.0f);
  assert(result.z == 4.0f);

  jo_test_print_ok(&test);
}

void test_vec3_scale_negative()
{
  vec3_t v = vec3(2.0f, 2.0f, 2.0f);
  float32_t s = 0.5f;

  test_t test;
  jo_test_init(&test, "test_vec3_scale_negativ");

  vec3_t result = vec3_scale(v, s);

  jo_test_time_stop(&test);

  assert(result.x == 1.0f);
  assert(result.y == 1.0f);
  assert(result.z == 1.0f);

  jo_test_print_ok(&test);
}

void test_vec3_scale_mix()
{
  vec3_t v = vec3(4.0f, 10.0f, 8.0f);
  float32_t s = 2.0f;

  test_t test;
  jo_test_init(&test, "test_vec3_scale_mix");

  vec3_t result = vec3_scale(v, s);
  
  jo_test_time_stop(&test);

  assert(result.x == 8.0f);
  assert(result.y == 20.0f);
  assert(result.z == 16.0f);

  jo_test_print_ok(&test);
}

void test_vec3_div(void)
{
  vec3_t v = vec3(4.0f, 4.0f, 4.0f);
  float32_t s = 2.0f;

  test_t test;
  jo_test_init(&test, "test_vec3_div");

  vec3_t result = vec3_div(v, s);

  jo_test_time_stop(&test);

  assert(result.x == 2.0f);
  assert(result.y == 2.0f);
  assert(result.z == 2.0f);

  jo_test_print_ok(&test);
}

void test_vec3_div_negative(void)
{
  vec3_t v = vec3(-4.0f, -4.0f, -4.0f);
  float32_t s = 2.0f;

  test_t test;
  jo_test_init(&test, "test_vec3_div_negative");

  vec3_t result = vec3_div(v, s);

  jo_test_time_stop(&test);

  assert(result.x == -2.0f);
  assert(result.y == -2.0f);
  assert(result.z == -2.0f);

  jo_test_print_ok(&test);
}

void test_vec3_div_mix(void)
{
  vec3_t v = vec3(10.0f, -4.0f, 7.5f);
  float32_t s = 2.0f;

  test_t test;
  jo_test_init(&test, "test_vec3_div_mix");
  
  vec3_t result = vec3_div(v, s);

  jo_test_time_stop(&test);

  assert(result.x == 5.0f);
  assert(result.y == -2.0f);
  assert(result.z == 3.75f);

  jo_test_print_ok(&test);
}

void test_vec3_negate(void)
{
  vec3_t v = vec3(2.0f, 2.0f, 2.0f);

  test_t test;
  jo_test_init(&test, "test_vec3_negate");

  vec3_t result = vec3_negate(v);

  jo_test_time_stop(&test);

  assert(result.x == -2.0f);
  assert(result.y == -2.0f);
  assert(result.z == -2.0f);

  jo_test_print_ok(&test);
}

void test_vec3_negate_negative(void)
{
  vec3_t v = vec3(-2.0f, -2.0f, -2.0f);

  test_t test;
  jo_test_init(&test, "test_vec3_negate_negative");

  vec3_t result = vec3_negate(v);

  jo_test_time_stop(&test);

  assert(result.x == 2.0f);
  assert(result.y == 2.0f);
  assert(result.z == 2.0f);

  jo_test_print_ok(&test);
}

void test_vec3_negate_mix(void)
{
  vec3_t v = vec3(10.0f, -4.0f, 3.5f);

  test_t test;
  jo_test_init(&test, "test_vec3_negate_mix");

  vec3_t result = vec3_negate(v);

  jo_test_time_stop(&test);

  assert(result.x == -10.0f);
  assert(result.y == 4.0f);
  assert(result.z == -3.5f);

  jo_test_print_ok(&test);
}

int main(void)
{
  printf("\nRunning vec3 tests\n\n");

  test_vec3_add();
  test_vec3_add_negative();
  test_vec3_add_mix();
  
  printf("\n");

  test_vec3_sub();
  test_vec3_sub_negative();
  test_vec3_sub_mix();

  printf("\n");

  test_vec3_mul();
  test_vec3_mul_negative();
  test_vec3_mul_mix();

  printf("\n");

  test_vec3_scale();
  test_vec3_scale_negative();
  test_vec3_scale_mix();

  printf("\n");

  test_vec3_div();
  test_vec3_div_negative();
  test_vec3_div_mix();

  printf("\n");

  test_vec3_negate();
  test_vec3_negate_negative();
  test_vec3_negate_mix();

  printf("\nAll tests passed!\n");
  return 0;
}
