#include "pendulum.h"

static double state[3] = {0.1f, 0.1f, 0.0f};
static const double g = 9.82f;
static const double L = 1.0f;
static const double h = 0.001f;

#define f(y) ((g / L) * sin(y))
#define state_next() (f(state[1]) * h * h - state[0] + 2 * state[1])

double pend_step(double t) {
    int repeat = (int)round(t / h);
    for(int i = 0; i < repeat; i++) {
        state[2] = state_next();
        state[0] = state[1];
        state[1] = state[2];
    }
    return state[2];
}

void pend_reset_state(void) {
    state[0] = state[1] = 0.1f;
    state[2] = 0.0f;
    return;
}