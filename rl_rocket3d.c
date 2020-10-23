const char* rocket3d_desc = "rocket3d description here";

void rocket3d_preview(void) {
    DrawCylinder(cubePosition, 2.0f, 2.0f, 2.0f, 20, RED);
    DrawCylinderWires(cubePosition, 2.0f, 2.0f, 2.0f, 20, MAROON);
    return;
}

void rocket3d_gui(void) {
    GuiLabel((Rectangle){ 10, 10, 120, 20 }, "Simulation: Rocket3D");
    global_back_to_main_menu = GuiButton((Rectangle){ 10, 30, 120, 20 }, "Main Menu");
    if(global_back_to_main_menu) {
        current_gui = main_menu_gui;
    }
}