#include "test/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Todo(john): Move the measure out of test in a reusable logic for simple performance logging

void jo_test_init(test_t *test, const char *name)
{
  assert(test != NULL);
  assert(name != NULL);

  test->name = name;

  int result = clock_gettime(CLOCK_MONOTONIC, &test->start);
  assert(result == 0);

  test->end.tv_sec = 0;
  test->end.tv_nsec = 0;
}

void jo_test_time_start(test_t *test)
{
  assert(test != NULL);

  int result = clock_gettime(CLOCK_MONOTONIC, &test->start);
  assert(result == 0);
}

float64_t jo_test_time_stop(test_t *test)
{
  assert(test != NULL);

  int result = clock_gettime(CLOCK_MONOTONIC, &test->end);
  assert(result == 0);

  float64_t elapsed_sec = (float64_t)(test->end.tv_sec - test->start.tv_sec);
  float64_t elapsed_nsec = (float64_t)(test->end.tv_nsec - test->start.tv_nsec);
  
  float64_t time_spent = elapsed_sec + (elapsed_nsec / 1000000000.0); 

  assert(time_spent >= 0.0f);
  return time_spent;
}

void jo_test_print_ok(const test_t *test)
{
  assert(test != NULL);

  float64_t elapsed_sec = (float64_t)(test->end.tv_sec - test->start.tv_sec);
  float64_t elapsed_nsec = (float64_t)(test->end.tv_nsec - test->start.tv_nsec);

  int64_t total_ns = elapsed_sec * 1000000000LL + elapsed_nsec;

  float64_t value;
  const char *unit;

  if (total_ns < 1000) {
    value = (float64_t)total_ns;
    unit = "ns";
  } else if (total_ns < 1000000) {
    value = total_ns / 1e3;
    unit = "µs";
  } else if (total_ns / 1000000000LL) {
    value = total_ns / 1e6;
    unit = "ms";
  } else {
    value = total_ns / 1e9;
    unit = "s";
  }

  printf("\t[OK] %s %.3f %s\n", test->name, value, unit);
}
