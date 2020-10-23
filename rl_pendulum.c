#include <stdio.h>
#include "raylib.h"
#include "rlgl.h"
#include "rl_pendulum.h"
#include "pendulum.h"
#include "main.h"

#include "raygui/src/raygui.h"

const char* pend_desc = "The physics of a rocket can simplified down to balancing a pencil on your index finger. The normal force your finger excerts on the pencil can be considered as the engine thrust. The pencil itself being the rocket body. The kinematics of that system is called an inverted pendulum in physics. This demonstration shows the kinematics of an inverted pendulum.";
bool pend_loaded = false;

float rot = 20.0f;
float rot_rad = 0.0f;
bool stopat90deg = false;
char info[50];

void pend_3d_render(void) {
    
    if(pend_loaded) {
        if(stopat90deg && rot >= 90.0f) goto next;
        rot_rad = pend_step(t_frame);
        rot = rot_rad * 180.0 / M_PI;
        sprintf(info, "rad: %.3f, deg: %.3f", rot_rad, rot);
    }
    
    next:
    DrawGrid(10, 1.0f);

    rlPushMatrix();
        rlRotatef(rot, 1.0f, 0.0f, 0.0f);
        DrawCylinderWires((Vector3){0.0f}, 0.10f, 0.10f, 2.5f, 10, WHITE);
        DrawSphereWires((Vector3){0.0f, 2.5f, 0.0f}, 0.15f, 5, 5, RED);
    rlPopMatrix();
    rlPushMatrix();
        rlRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        DrawCylinderWires((Vector3){0.0f, -0.5f, 0.0f}, 0.10f, 0.10f, 1.0f, 10, WHITE);
    rlPopMatrix();
    return;
}

void pend_gui(void) {
    GuiLabel((Rectangle){gui_offset_x, gui_offset_y, 120, 30 }, "Simulation: Pendulum");

    GuiLabel((Rectangle){gui_offset_x, gui_offset_y + 40, 120, 30 }, info);
    GuiLabel((Rectangle){gui_offset_x, gui_offset_y + 55, 120, 30 }, "g: -9.82m/s^2, L: 1.0");

    stopat90deg = GuiCheckBox((Rectangle){gui_offset_x, gui_offset_y + 105, 10, 10}, "stop @ >= 90 deg", stopat90deg);   

    bool reload = GuiButton((Rectangle){gui_offset_x, gui_offset_y + 155, 120, 20}, "Reset");
    bool global_back_to_main_menu = GuiButton((Rectangle){gui_offset_x, gui_offset_y + 185, 120, 20 }, "Main Menu");
    if(global_back_to_main_menu) {
        pend_unload();
        main_main_menu();
    }
    if(reload) { 
        pend_load();
    }
}

void pend_load() {
    pend_reset_state();
    pend_loaded = true;
    rot = 0.0f;
    return;
}

void pend_unload() {
    rot = 20.0f;
    pend_loaded = false;
    return;
}