#include <stdio.h>
#include "raylib.h"
#include "rlgl.h"
#include "rl_rocket2d.h"
#include "rocket2d.h"
#include "main.h"

#include "raygui/src/raygui.h"

bool global_back_to_main_menu = false;
const char* r2d_desc = "rocket2d description";
bool r2d_loaded = false;

struct r2d_state preview_state = {.x = {0.0f, 0.0f, 0.0f}, .y = {0.0f, 0.0f, 0.0f}, .theta = {0.0f, 0.0f, 0.0f}};
struct r2d_state* state = &preview_state;

const double f_increment = 0.1f;
const double a_increment = 0.001f;

double f = 9.82f;
double a = 0.0f;

char rotation[50];
char position[50];
char inputs[50];

void r2d_3d_render(void) {

    if(r2d_loaded) {
        r2d_step(t_frame);
        //sprintf(info, "rad: %.3f, deg: %.3f", rot_rad, rot);

        if(IsKeyDown(KEY_UP)) f += f_increment;
        if(IsKeyDown(KEY_DOWN)) f -= f_increment;
        if(IsKeyDown(KEY_RIGHT)) a -= a_increment;
        if(IsKeyDown(KEY_LEFT)) a += a_increment;

        r2d_set_inputs(f, a);

        sprintf(rotation, "rad: %.3f, deg: %.3f", state->theta[2], state->theta[2] * 180 / M_PI);
        sprintf(position, "x: %.3f, y: %.3f\n", state->x[2], state->y[2]);
        sprintf(inputs, "F: %.3f, alpha: %.3f\n", f, a);
    }

    rlPushMatrix();
        rlTranslatef(0.0f, state->y[2], state->x[2]);
        rlRotatef(state->theta[2] * 180.0 / M_PI, 1.0f, 0.0f, 0.0f);
        DrawCylinderWires((Vector3){0.0f}, 0.4f, 0.4f, 2.5f, 10, WHITE);
        rlRotatef(a * 180.0 / M_PI, 1.0f, 0.0f, 0.0f);
        DrawCylinderWires((Vector3){0.0f, -1.25f, 0.0f}, 0.1f, 0.1f, 1.25f, 10, RED);
    rlPopMatrix();
    DrawGrid(10, 1.0f);
    return;
}

void r2d_gui(void) {
    GuiLabel((Rectangle){gui_offset_x, gui_offset_y, 120, 20 }, "Simulation: Rocket2D");
    GuiLabel((Rectangle){gui_offset_x, gui_offset_y + 40, 120, 30 }, rotation);
    GuiLabel((Rectangle){gui_offset_x, gui_offset_y + 55, 120, 30 }, position);
    GuiLabel((Rectangle){gui_offset_x, gui_offset_y + 70, 120, 30 }, "g: -9.82m/s^2, L: 1.0");
    GuiLabel((Rectangle){gui_offset_x, gui_offset_y + 85, 120, 30 }, inputs);
    bool reload = GuiButton((Rectangle){gui_offset_x, gui_offset_y + 155, 120, 20}, "Reset");
    bool global_back_to_main_menu = GuiButton((Rectangle){gui_offset_x, gui_offset_y + 185, 120, 20 }, "Main Menu");
    
    if(global_back_to_main_menu) {
        main_main_menu();
        r2d_unload();
    } 
    if(reload) { 
        r2d_load();
    }
}

void r2d_load(void) {
    r2d_reset_state();
    state = r2d_get_struct();
    f = 9.82;
    a = 0.0f;
    r2d_loaded = true;
    return;
}

void r2d_unload(void) {
    state = &preview_state;
    return;
}