
#include <dphilox.h>

// Ensure we have 128-bit integers (this works on GCC/Clang)
#ifdef __SIZEOF_INT128__
typedef unsigned __int128 uint128_t;
#else
#error "128-bit integers are not supported on this compiler."
#endif

// Initialize the philox_state structure
void philox_init(philox_state *state, uint64_t seed) {
    state->counter = 0;  // Initial counter value (can be changed if needed)
    state->key = seed;   // Set the seed as the key
}

// dphilox: A counter-based PRNG using a simplified Philox-2x64 style transformation.
// Parameters:
//   seed   - the fixed seed (key) that selects the random sequence
//   counter- the counter (e.g. the n-th random number to generate)
//   rounds - the number of mixing rounds (more rounds mean better mixing)
// Returns:
//   a double in the interval [0, 1)
double dphilox(uint64_t seed, uint64_t counter) {
    // In a true counter-based generator, we derive the output solely
    // from the (fixed) seed and the counter. Here we set up two 64-bit words:
    // x is initialized to the counter, and y is initialized to 0.
    const int rounds = 10;
    uint64_t x = counter;
    uint64_t y = 0;
    // The key is derived from the seed and remains constant.
    uint64_t key = seed;

    // Constants used in Philox-2x64:
    // 'multiplier' is the fixed multiplier for mixing.
    // 'weyl' is a constant used to update the key each round.
    const uint64_t multiplier = 0xD2B74407B1CE6E93ULL; // Standard multiplier for Philox2x64.
    const uint64_t weyl       = 0x9E3779B97F4A7C15ULL; // Weyl constant (related to the golden ratio).

    // Apply the mixing rounds.
    for (int i = 0; i < rounds; i++) {
        // Multiply x by the multiplier to get a 128-bit product.
        uint128_t prod = (uint128_t)x * multiplier;
        // Extract the high and low 64-bit halves of the product.
        uint64_t hi = (uint64_t)(prod >> 64);
        uint64_t lo = (uint64_t)prod;
        // One round of the Philox transformation:
        //   new_x = hi XOR key XOR y
        //   new_y = lo
        uint64_t new_x = hi ^ key ^ y;
        uint64_t new_y = lo;

        x = new_x;
        y = new_y;

        // Update the key with the Weyl constant.
        key += weyl;
    }

    // Use x as the 64-bit random number.
    // Scale to a double in the interval [0, 1).
    double result = (double)x / (double)UINT64_MAX;
    return result;
}
