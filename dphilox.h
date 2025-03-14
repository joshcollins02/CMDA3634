#ifndef DPHILOX_H
#define DPHILOX_H

#include <stdint.h>

typedef struct {
    uint64_t counter;
    uint64_t key;
} philox_state;

void philox_init(philox_state *state, uint64_t seed);
uint64_t philox_next(philox_state *state);
double philox_next_double(philox_state *state);
double dphilox(uint64_t seed, uint64_t counter);

#endif
