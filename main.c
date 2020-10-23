#include <stdio.h>
#include "raylib.h"
#include "rlgl.h"
#include "rl_pendulum.h"
#include "rl_rocket2d.h"
#include "rl_rocket3d.h"
#include "main.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui/src/raygui.h"

//-Wl,--subsystem,windows in makefile shows or hides console lol omeglaulgligligligligili

int sim_selection = 0;
bool sim_selection_edit_mode = false;  
bool load_click = false;
bool drop_click = true;

char* current_desc;
void (*current_3d_render)(void);
void (*current_gui)(void);

float t_frame = 0.0f;

void main_main_menu(void) {
    current_gui = main_menu_gui;
}

void main_menu_gui(void) {
    gui_offset_x = gui_offset_y = 10;
    //int w = GetScreenWidth();
    int h = GetScreenHeight();
    load_click = GuiButton((Rectangle){gui_offset_x, 60 + gui_offset_y, 120, 20 }, "Load"); 
    GuiLabel((Rectangle){gui_offset_x, gui_offset_y, 120, 30 }, "Rocket Simulation Visualizer");
    GuiTextBoxMulti((Rectangle){10, 10 + h - 150, 280, 130}, current_desc, 256, false);
    if ((drop_click = GuiDropdownBox((Rectangle){ gui_offset_x, 30 + gui_offset_y, 120, 20 }, "Pendulum;Rocket2D" /*"Pendulum;Rocket2D;Rocket3D"*/, &sim_selection, sim_selection_edit_mode)))
        sim_selection_edit_mode = !sim_selection_edit_mode;
    if(drop_click) {
        printf("preview selection: %d\n", sim_selection);
        switch(sim_selection) {
            case 0:
                current_desc = (char*)pend_desc;
                current_3d_render = &pend_3d_render;
                break;
            case 1:
                current_desc = (char*)r2d_desc;
                current_3d_render = &r2d_3d_render;
                break;
            /*
            case 2:
                current_desc = rocket3d_desc;
                current_preview = &rocket3d_preview;
                break;
            */
            default:
                break;
        }
    }
    else if(load_click) {
        printf("load selection: %d\n", sim_selection);
        switch(sim_selection) {
            case 0:
                current_gui = pend_gui;
                pend_load();
                break;
            case 1:
                current_gui = r2d_gui;
                r2d_load();
                break;
            /*
            case 2:
                current_gui = rocket3d_gui;
                break;
            */
            default:
                break;
        }
    }
    return;
}

int main() 
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    current_desc = (char*)pend_desc;
    current_3d_render = pend_3d_render;
    current_gui = main_menu_gui;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Rocket Simulation Visualizer, v0.0.1, fullnitrous.com");
    
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 4.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;
    
    SetCameraMode(camera, CAMERA_FREE);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        DrawFPS(GetScreenWidth() - 85, 10);
        UpdateCamera(&camera);
        t_frame = GetFrameTime();
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                current_3d_render();
            EndMode3D();
            current_gui();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}