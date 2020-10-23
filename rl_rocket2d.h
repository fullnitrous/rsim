#include <stdio.h>
#include "raylib.h"
#include "rlgl.h"
#include "rocket2d.h"

#include "raygui/src/raygui.h"

#ifndef RL_ROCKET2D_H
    #define RL_ROCKET2D_H

    #ifndef M_PI
        #define M_PI 3.14159265358979323846
    #endif

    const char* r2d_desc;
    bool r2d_loaded;

    void r2d_3d_render(void);
    void r2d_gui(void);
    void r2d_load(void);
    void r2d_unload(void);
#endif