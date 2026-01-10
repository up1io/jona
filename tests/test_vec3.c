#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "jona/math/vec3.h"
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

void test_vec3_dot(void)
{
  vec3_t a = vec3(2.0f, 2.0f, 2.0f);
  vec3_t b = vec3(2.0f, 2.0f, 2.0f);

  test_t test;
  jo_test_init(&test, "test_vec3_dot");

  float64_t result = vec3_dot(a, b);

  jo_test_time_stop(&test);

  assert(result == 12.0f);

  jo_test_print_ok(&test);
}

void test_vec3_dot_negative(void)
{
  vec3_t a = vec3(-2.0f, -2.0f, -2.0f);
  vec3_t b = vec3(5.0f, 5.0f, 5.0f);
  
  test_t test;
  jo_test_init(&test, "test_vec3_dot_negative");

  float64_t result = vec3_dot(a, b);

  jo_test_time_stop(&test);

  assert(result == -30.0f);

  jo_test_print_ok(&test);
}

void test_vec3_dot_mix(void)
{
  vec3_t a = vec3(5.0f, 10.0f, -2.0f);
  vec3_t b = vec3(2.0f, -1.5f, -2.0f);
  
  test_t test;
  jo_test_init(&test, "test_vec3_dot_mix");

  float64_t result = vec3_dot(a, b);

  jo_test_time_stop(&test);

  assert(result == -1.0f);

  jo_test_print_ok(&test);
}

void test_vec3_cross(void)
{
  vec3_t a = vec3(10.0f, 5.0f, 15.0f);
  vec3_t b = vec3(5.0f, 2.0f, 3.0f);

  // x = 5 * 3 - 15 * 2 = 15 - 30 = -15
  // y = 15 * 5 - 10 * 3 = 75 - 30 = 45
  // z = 10 * 2 - 5 * 5 = 20 - 25 = -5

  test_t test;
  jo_test_init(&test, "test_vec3_cross");

  vec3_t result = vec3_cross(a, b);

  jo_test_time_stop(&test);

  assert(result.x == -15.0f);
  assert(result.y == 45.0f);
  assert(result.z == -5.0f);

  jo_test_print_ok(&test);
}

void test_vec3_cross_negative(void)
{
  vec3_t a = vec3(-50.0f, -2.5f, -15.0f);
  vec3_t b = vec3(-2.0f, -3.0f, -18.0f);

  // x = -2.5 * (-18) - (-15) * (-3) = 45 - 45 = 0
  // y = -15 * (-2) - (-50) * (-18) = 30 - 900 = -870
  // z = -50 * (-3) - (-2.5) * (-2) = 150 - 5 = 145

  test_t test;
  jo_test_init(&test, "test_vec3_cross_negativ");

  vec3_t result = vec3_cross(a, b);

  jo_test_time_stop(&test);

  assert(result.x == -0.0f);
  assert(result.y == -870.0f);
  assert(result.z == 145.0f);

  jo_test_print_ok(&test);
}

void test_vec3_cross_mix(void)
{
  vec3_t a = vec3(5.0f, 12.0f, 2.0f);
  vec3_t b = vec3(7.5f, -3.0f, 8.0f);

  // x = 12 * 8 - 2 * (-3) = 96 - (-6) = 102
  // y = 2 * 7.5 - 5 * 8 = (-25) - 40 = -25 
  // z = 5 * (-3) - 12 * 7.5 = -15 - 90 = -105 

  test_t test;
  jo_test_init(&test, "test_vec3_cross_mix");

  vec3_t result = vec3_cross(a, b);

  jo_test_time_stop(&test);

  assert(result.x == 102.0f);
  assert(result.y == -25.0f);
  assert(result.z == -105.0f);

  jo_test_print_ok(&test);
}

void test_vec3_length_squared(void)
{
  vec3_t v = vec3(1.0f, 2.0f, 3.0f);

  // len = 1 * 1 + 2 * 2 + 3 * 3 = 14

  test_t test;
  jo_test_init(&test, "test_vec3_length_squared");

  float32_t result = vec3_length_squared(v);

  jo_test_time_stop(&test);

  assert(result == 14.0f);

  jo_test_print_ok(&test);
}

void test_vec3_length_squared_negative(void)
{
  vec3_t v = vec3(-5.0f, -2.0f, -3.0f);

  // len = -5 * (-5) + (-2) * (-2) + (-3) * (-3) = 38

  test_t test;
  jo_test_init(&test, "test_vec3_length_squared");

  float32_t result = vec3_length_squared(v);

  jo_test_time_stop(&test);

  assert(result == 38.0f);

  jo_test_print_ok(&test);
}

void test_vec3_length_squared_mix(void)
{
  vec3_t v = vec3(20.0f, -2.0f, 3.5f);

  // len = 20 * 20) + (-2) * (-2) + 3.5 * 3.5 = 416.25

  test_t test;
  jo_test_init(&test, "test_vec3_length_squared");

  float32_t result = vec3_length_squared(v);

  jo_test_time_stop(&test);

  assert(result == 416.25f);

  jo_test_print_ok(&test);
}

// Todo(john): investiagte why this take so long
void test_vec3_length(void)
{
  vec3_t v = vec3(1.0f, 1.0f, 1.0f);

  // len_sq = 1 * 1 + 1 * 1 + 1 * 1 = 3
  // len = sqrt(3) = 1.73205080757

  test_t test;
  jo_test_init(&test, "test_vec3_length");

  float32_t result = vec3_length(v);

  jo_test_time_stop(&test);

  assert(result == 1.7320508075f);

  jo_test_print_ok(&test);
}

void test_vec3_length_negative(void)
{
  vec3_t v = vec3(-5.0f, -2.0f, -3.0f);

  // len_sq = -5 * (-5) + (-2) * (-2) + (-3) * (-3) = 38
  // len = sqrt(38) = 6.16441400297

  test_t test;
  jo_test_init(&test, "test_vec3_length_negative");

  float32_t result = vec3_length(v);

  jo_test_time_stop(&test);

  assert(result == 6.16441400297f);

  jo_test_print_ok(&test);
}

void test_vec3_length_mix()
{
  vec3_t v = vec3(7.5f, -3.0f, 13.0f);

  // len_sq = 7.5 * 7.5 + (-3) * (-3) + 13 * 13 = 234.25 
  // len = sqrt(234.25) = 15.305227865 

  test_t test;
  jo_test_init(&test, "test_vec3_length_mix");

  float32_t result = vec3_length(v);

  jo_test_time_stop(&test);

  assert(result == 15.305227865f);

  jo_test_print_ok(&test);
}

void test_vec3_normalize(void)
{
  vec3_t v = vec3(2.0f, 2.0f, 2.0f);

  // len_sq = 2 * 2 + 2 * 2 + 2 * 2 = 12
  // len = sqrt(12) = 3.46410161514
  // x = 2 / 3.4641016151 = 0.57735026919
  // y = 2 / 3.4641016151 = 0.57735026919
  // z = 2 / 3.4641016151 = 0.57735026919

  test_t test;
  jo_test_init(&test, "test_vec3_normalize");

  vec3_t result = vec3_normalize(v);

  jo_test_time_stop(&test);
  
  float32_t expectedValue = 0.57735026919f;
 
  assert(fabs(result.x - expectedValue) < FLOAT32_EPSILON);
  assert(fabs(result.y - expectedValue) < FLOAT32_EPSILON);
  assert(fabs(result.z - expectedValue) < FLOAT32_EPSILON);

  jo_test_print_ok(&test);
}

void test_vec3_normalize_negative(void)
{
  vec3_t v = vec3(-5.0f, -5.0f, -5.0f);

  // len_sq = -5 * (-5) + (-5) * (-5) + (-5) * (-5) =  75
  // len = sqrt(75) = 8.66025403784
  // len = 1 / 8.66025403784 = 0.11547005383
  // x = -5 / 8.66025403784 = -0.57735026919
  // y = -5 / 8.66025403784 = -0.57735026919
  // z = -5 / 8.66025403784 = -0.57735026919
 
  test_t test;
  jo_test_init(&test, "test_vec3_normalize_negative");

  vec3_t result = vec3_normalize(v);

  jo_test_time_stop(&test);

  float32_t expectedValue = -0.57735026919f;

  assert(fabs(result.x - expectedValue) < FLOAT32_EPSILON);
  assert(fabs(result.y - expectedValue) < FLOAT32_EPSILON);
  assert(fabs(result.z - expectedValue) < FLOAT32_EPSILON);

  jo_test_print_ok(&test);
}

void test_vec3_normalize_mix(void)
{
  vec3_t v = vec3(7.5f, -2.5f, 45.0f);

  // len_sq = 7.5 * 7.5 + (-2.5) * (-2.5) + 45 * 45 = 2087.5 
  // len = sqrt(2087.5) = 45.6891672062
  // x = 7.5 / 45.6891672062 = 0.16415269655
  // y = -2.5 / 45.6891672062 = -0.05471756551  
  // z = 45 / 45.6891672062 = 0.98491617929

  test_t test;
  jo_test_init(&test, "test_vec3_normalize_mix");

  vec3_t result = vec3_normalize(v);

  jo_test_time_stop(&test);

  float32_t expected_x_value = 0.16415269655;
  float32_t expected_y_value = -0.05471756551;
  float32_t expected_z_value = 0.98491617929;

  assert(fabs(result.x - expected_x_value) < FLOAT32_EPSILON);
  assert(fabs(result.y - expected_y_value) < FLOAT32_EPSILON);
  assert(fabs(result.z - expected_z_value) < FLOAT32_EPSILON);

  jo_test_print_ok(&test);
}

void test_vec3_normalize_safe(void)
{
  vec3_t v = vec3_zero(); 

  test_t test;
  jo_test_init(&test, "test_vec3_normalize_safe");

  vec3_t result = vec3_normalize_safe(v);

  jo_test_time_stop(&test);
  
  assert(result.x == 0);
  assert(result.y == 0);
  assert(result.y == 0);

  jo_test_print_ok(&test);
}

void test_vec3_distance_squared(void)
{
  vec3_t a = vec3(1.0f, 1.0f, 1.0f);
  vec3_t b = vec3(2.0f, 2.0f, 2.0f);

  test_t test;
  jo_test_init(&test, "test_vec3_distance_squared");

  float32_t result = vec3_distance_squared(a, b);

  jo_test_time_stop(&test);

  printf("result %f\n", result);
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

  printf("\n");

  test_vec3_dot();
  test_vec3_dot_negative();
  test_vec3_dot_mix();

  printf("\n");

  test_vec3_cross();
  test_vec3_cross_negative();
  test_vec3_cross_mix();

  printf("\n");

  test_vec3_length_squared();
  test_vec3_length_squared_negative();
  test_vec3_length_squared_mix();

  printf("\n");

  test_vec3_length();
  test_vec3_length_negative();
  test_vec3_length_mix();

  printf("\n");

  test_vec3_normalize();
  test_vec3_normalize_negative();
  test_vec3_normalize_mix();

  printf("\n");

  test_vec3_normalize_safe();

  printf("\n");

  test_vec3_distance_squared();

  printf("\nAll tests passed!\n");
  return 0;
}
