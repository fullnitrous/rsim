#include <math.h>
#include <stdint.h>

#ifndef ROCKET2D_H
    #define ROCKET2D_H

    struct r2d_state {
        double x[3];
        double y[3];
        double theta[3];
    };

    struct r2d_state* r2d_get_struct(void);
    void r2d_step(double t);
    void r2d_reset_state(void);
    void r2d_set_inputs(double, double);
#endif