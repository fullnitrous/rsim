#include "rocket2d.h"
#include <stdio.h>

#define i 1
#define j 1
#define k 1

struct r2d_state r2d_state = {.x = {0.0f, 0.0f, 0.0f}, .y = {0.0f, 0.0f, 0.0f}, .theta = {0.0f, 0.0f, 0.0f}};

#define x r2d_state.x
#define y r2d_state.y
#define theta r2d_state.theta

static const double g = -9.82f;
static const double l = 0.5f;
static const double h = 0.001f;
static const double m = 1.0f;
static const double I = (1.0f/12.0f)*m*l*l;

static double f = 9.82f;
static double a = 0.0f;

double fx = 0.0f;
double fy = 0.0f;
double tau = 0.0f;

struct r2d_state* r2d_get_struct(void) {
    return &r2d_state;
}

void r2d_set_inputs(double _f, double _a) {
    f = _f; a = _a;
    return;
}

void r2d_step(double t) {
    int repeat = (int)round(t / h);
    for(int z = 0; z < repeat; z++) {
        fx = f * sin(theta[j] - a);
        fy = f * cos(theta[j] - a);
        tau = l * f * sin(a);

        x[k + 1] = (fx / m) * h*h + 2.0f*x[k] - x[k - 1];
        x[k - 1] = x[k];
        x[k] = x[k + 1];

        y[i + 1] = ((fy+m*g)/m) * (h*h) + 2*y[i] - y[i - 1];
        y[i - 1] = y[i];
        y[i] = y[i + 1];

        theta[j + 1] = (tau/I) * (h*h) + 2*theta[j] - theta[j - 1];
        theta[j - 1] = theta[j];
        theta[j] = theta[j + 1];
    }
}

void r2d_reset_state(void) {
    for(int z = 0; z < 3; z++) {
        x[z] = y[z] = theta[z] = 0.0f;
    }
    f = 9.82f;
    a = 0.0f;

    return;
}

#undef x
#undef y
#undef theta
#undef i
#undef j
#undef k