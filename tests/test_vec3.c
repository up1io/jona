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

  printf("\nAll tests passed!\n");
  return 0;
}
