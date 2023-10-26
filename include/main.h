#ifndef MAIN_H_
#define MAIN_H_

#include <stdbool.h>

typedef struct {
  bool signed_in;
} program_state_s;

program_state_s *program_state_init();

#endif // MAIN_H_
