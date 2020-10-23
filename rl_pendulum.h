#include <stdio.h>
#include "raylib.h"
#include "rlgl.h"
#include "pendulum.h"

#include "raygui/src/raygui.h"

#ifndef RL_PENDULUM_H
    #define RL_PENDULUM_H

    #ifndef M_PI
        #define M_PI 3.14159265358979323846
    #endif

    const char* pend_desc;
    bool pend_loaded;

    void pend_3d_render(void);
    void pend_gui(void);
    void pend_load(void);
    void pend_unload(void);
#endif