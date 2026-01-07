#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "modeller/types.h"
#include "test/utils.h"

#include <time.h>

typedef struct {
  const char *name;
  struct timespec start;
  struct timespec end;
} test_t;

void jo_test_init(test_t *test, const char *name);

void jo_test_time_start(test_t *test);
float64_t jo_test_time_stop(test_t *test);

void jo_test_print_ok(const test_t *test);

#endif
